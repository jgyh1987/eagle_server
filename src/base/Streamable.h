#ifndef _STEAMABLE_H_
#define _STEAMABLE_H_

namespace eagle
{

class WriteStream;
class ReadStream;

class Streamable
{
public:
    virtual ~Streamable();
    virtual int Serialize(WriteStream* writeStream) const = 0;
    virtual int Unserialize(ReadStream* readStream) = 0;
};

};

#endif
