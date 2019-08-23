#pragma once
class MemoryStream 
	: public BaseStream
{
public:
	MemoryStream();
	MemoryStream(unsigned char* byteArray, size_t size);
	~MemoryStream();

	virtual int Read(unsigned char* p, int offset, size_t size) override;

	virtual int Read(char* p, int offset, size_t size) override;

	// get/set
	__int64 GetPosition() override{ return _spStream->getIndex(); }
	void SetPosition(__int64 position) override{ _spStream->setIndex(position); }

	__int64 GetLength() override{ return _spStream->getLength(); }

private:
	shared_ptr<simple::mem_istream<std::true_type>> _spStream = nullptr;
};
