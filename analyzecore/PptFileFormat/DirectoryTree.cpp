#include "stdafx.h"
#include "GlobalDefines.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "AbstractHeader.h"
#include "Header.h"
#include "AbstractFat.h"
#include "Fat.h"
#include "AbstractDirectoryEntry.h"
#include "DirectoryEntry.h"
#include "DirectoryTree.h"
#include <math.h>

DirectoryTree::DirectoryTree()
{
}


DirectoryTree::DirectoryTree(shared_ptr<Fat> spFat, shared_ptr<Header> spHeader, shared_ptr<InputHandler> spFileHandler)
{
	_spFat = spFat;
	_spHeader = spHeader;
	_spFileHandler = spFileHandler;

	Init(_spHeader->_directoryStartSector);
}

DirectoryTree::~DirectoryTree()
{
}

void DirectoryTree::Init(unsigned long startSector)
{
	if (_spHeader->_noSectorsInDirectoryChain4KB > 0)
	{
		_sectorsUsedByDirectory = _spFat->GetSectorChain(startSector, _spHeader->_noSectorsInDirectoryChain4KB, _T("Directory"));
	}
	else
	{
		_sectorsUsedByDirectory = _spFat->GetSectorChain(startSector, 
			(unsigned __int64)ceil((double)_spFileHandler->GetIOStreamSize() / _spHeader->_sectorSize), 
			_T("Dictory"), 
			true);
	}

	GetAllDirectoryEntriesRecursive(0, _T(""));
}

/// <summary>
/// Determines the directory _entries in a compound file recursively
/// </summary>
/// <param name="sid">start sid</param>
void DirectoryTree::GetAllDirectoryEntriesRecursive(unsigned long sid, wstring path)
{
	shared_ptr<DirectoryEntry> spEntry = ReadDirectoryEntry(sid, path);
	if (spEntry == nullptr)
		return;

	unsigned long left = spEntry->_leftSiblingSid;
	unsigned long right = spEntry->_rightSiblingSid;
	unsigned long child = spEntry->_childSiblingSid;

	for (auto ele : _directoryEntries)
	{
		if (ele->_sid == spEntry->_sid)
			return;
	}

	_directoryEntries.push_back(spEntry);

	// Left sibling
	if (left != Common::SectorId::NOSTREAM)
	{
		GetAllDirectoryEntriesRecursive(left, path);
	}

	// Right sibling
	if (right != Common::SectorId::NOSTREAM)
	{
		GetAllDirectoryEntriesRecursive(right, path);
	}

	// Child
	if (child != Common::SectorId::NOSTREAM)
	{
		GetAllDirectoryEntriesRecursive(child, path + ((sid == 0) ? _T("") : spEntry->GetName()) + _T("\\"));
	}
}

/// <summary>
/// Returns a directory entry for a given sid
/// </summary>
std::shared_ptr<DirectoryEntry> DirectoryTree::ReadDirectoryEntry(unsigned long sid, wstring path)
{
	SeekToDirectoryEntry(sid);
	shared_ptr<DirectoryEntry> spResult = make_shared<DirectoryEntry>(_spHeader, _spFileHandler, sid, path);

	return spResult;
}

void DirectoryTree::SeekToDirectoryEntry(unsigned long sid)
{
	int sectorInDirectoryChain = (int)(sid * Common::Measures::DirectoryEntrySize) / _spHeader->_sectorSize;
	if (sectorInDirectoryChain < 0)
	{
		return;
	}

	_spFileHandler->SeekToPositionInSector(_sectorsUsedByDirectory[sectorInDirectoryChain], 
		(sid * Common::Measures::DirectoryEntrySize) % _spHeader->_sectorSize);
}

unsigned long DirectoryTree::GetMiniStreamStart()
{
	shared_ptr<DirectoryEntry> spRoot = GetDirectoryEntry(0);
	if (spRoot == nullptr)
		return 0;

	return spRoot->_startSector;
}

unsigned __int64 DirectoryTree::GetSizeOfMiniStream()
{
	shared_ptr<DirectoryEntry> spRoot = GetDirectoryEntry(0);
	if (spRoot == nullptr)
		return 0;

	return spRoot->_sizeOfStream;
}

std::shared_ptr<DirectoryEntry> DirectoryTree::GetDirectoryEntry(unsigned long sid)
{
	for (auto ele : _directoryEntries)
	{
		if (ele->_sid == sid)
			return ele;
	}

	return nullptr;
}

std::shared_ptr<DirectoryEntry> DirectoryTree::GetDirectoryEntry(wstring path)
{
	if (path.length() < 1)
		return nullptr;

	for (auto ele : _directoryEntries)
	{
		if (path[0] == '\\')
		{
			if (ele->GetPath() == path)
				return ele;
		}
		else
		{
			if (ele->GetName() == path)
				return ele;
		}
		
	}

	return nullptr;
}

/// <summary>
/// Returns all stream entry paths contained in a compound file
/// </summary>
std::vector<std::wstring> DirectoryTree::GetPathsOfAllStreamEntries()
{
	vector<wstring> result;
	for (auto ele : _directoryEntries)
	{
		if (ele->_type == Common::DirectoryEntryType::STGTY_STREAM)
		{
			result.push_back(ele->GetPath());
		}
	}

	return result;
}
