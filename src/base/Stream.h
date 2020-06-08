#ifndef _STREAM_H_
#define _STREAM_H_

#include "Sys.h"

namespace eagle
{

class ReadStream
{
protected:
    const char* ptr;
    const char* cur;
    size_t len;

public:
    ReadStream(const char* p, size_t l) : ptr(p), cur(p), len(l) {}

    virtual ~ReadStream(){}

    virtual size_t GetSize() const = 0;

    virtual bool IsEmpty() const = 0;    

    virtual bool Read(char* str, size_t strlen, /* out */ size_t & len) = 0;

    virtual bool Read(/* out */ int64_t & i) = 0;

    virtual bool Read(/* out */ int32_t & i) = 0;

    virtual bool Read(/* out */ int16_t & i) = 0;

    virtual bool Read(/* out */ char & c) = 0;

    bool Read(/* out */ double& f);

    virtual bool ReadNoCopy(const char*& str, size_t& len) = 0;

    virtual bool ReadContent(char* buf, size_t buflen) = 0;

    virtual bool ReadContentNoCopy(const char*& str, size_t len) = 0;

    virtual size_t ReadAll(char * szBuffer, size_t iLen) const = 0;

    virtual bool IsEnd() const = 0;

    virtual const char* GetData() const = 0;

    virtual const char* GetCurrent() const = 0;

    virtual void Reset() = 0;

    virtual void Assign(const char* p, size_t size) = 0;
};

class WriteStream
{
protected:
    char* ptr;
    char* cur;
    size_t len;

public:
    WriteStream(char* p, size_t l) : ptr(p), cur(p), len(l) {}

    virtual ~WriteStream(){}

    virtual bool Write(const char* str, size_t len) = 0;

    virtual bool Write(int64_t i) = 0;

    virtual bool Write(int32_t i) = 0;

    virtual bool Write(int16_t i) = 0;

    virtual bool Write(char  c) = 0;

    bool Write(const double& f);

    virtual bool WriteContent(const char* buf, size_t buflen) = 0;

    virtual void Clear() = 0;

    virtual void Flush() = 0;

    virtual const char* GetData() const = 0;

    virtual size_t GetSize() const = 0;

    virtual char* GetCurrent() const = 0;

    virtual bool IsValid() const = 0;

    virtual void Reset() = 0;

    virtual void Assign(char* p, size_t size) = 0;
};


enum
{
    BINARY_PACKLEN_LEN        = 4,
    BINARY_PACKAGE_MAXLEN    = 0xffffffff,
};

enum HEADER_FLAG
{
    LENGTH_INCLUDE_SELF,
    LENGTH_EXCLUDE_SELF
};

class BinaryReadStream : public ReadStream
{
private:
    size_t lenFieldLen;
    HEADER_FLAG headerFlag;

public:
    BinaryReadStream(const char* ptr, size_t len, size_t lenFieldLen=BINARY_PACKLEN_LEN, HEADER_FLAG headerFlag=LENGTH_INCLUDE_SELF);

    virtual size_t GetSize() const;

    virtual bool IsEmpty() const;

    virtual bool Read(char* str, size_t strlen, /* out */ size_t& len);

    virtual bool Read(/* out */ int64_t & i);

    virtual bool Read(/* out */ int32_t & i);

    virtual bool Read(/* out */ int16_t & i);

    virtual bool Read(/* out */ char  & c);

    virtual const char* GetData() const;

    virtual size_t ReadAll(char * szBuffer, size_t iLen) const;

    virtual bool IsEnd() const;

    virtual bool IsValid() const;

    virtual const char* GetCurrent() const;

    virtual bool ReadNoCopy(const char*& str, size_t& len);

    virtual bool ReadContent(char* buf, size_t buflen);

    virtual bool ReadContentNoCopy(const char*& buf, size_t buflen);

    virtual void Reset();

    virtual void Assign(const char* p, size_t size);

public:

    bool ReadLength(size_t & len);

    bool ReadLengthWithoutOffset(size_t & outlen);    

public:
    static BinaryReadStream ExtractStream(const char* ptr, size_t len, size_t lenFieldLen=BINARY_PACKLEN_LEN, HEADER_FLAG headerFlag=LENGTH_INCLUDE_SELF);
};

class BinaryWriteStream : public WriteStream
{
private:
    size_t lenFieldLen;
    HEADER_FLAG headerFlag;

    BinaryWriteStream(const BinaryWriteStream&);
    BinaryWriteStream& operator=(const BinaryWriteStream&);

public:
    BinaryWriteStream(char* ptr, size_t len, size_t lenFieldLen=BINARY_PACKLEN_LEN, HEADER_FLAG headerFlag=LENGTH_INCLUDE_SELF);

    virtual bool Write(const char* str, size_t len);

    virtual bool Write(int64_t i);

    virtual bool Write(int32_t i);

    virtual bool Write(int16_t i);

    virtual bool Write(char  c);

    virtual bool WriteContent(const char* str, size_t len);

    virtual size_t GetSize() const;

    virtual bool IsValid() const;

    virtual void Flush();

    virtual void Clear();

    virtual const char* GetData() const;

    virtual char* GetCurrent() const;

    virtual void Reset();

    virtual void Assign(char* p, size_t size);

public:
    bool WriteLength(size_t len);
};

};

#endif // _STREAM_H_
