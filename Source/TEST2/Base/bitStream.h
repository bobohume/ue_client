#ifndef _BASE_BITSTREAM_H_
#define _BASE_BITSTREAM_H_

//Includes
#include "types.h"
#include <assert.h>

namespace Base
{
const int Bit8  = 8;
const int Bit16 = 16;
const int Bit32 = 32;
const int Bit64 = 64;
const int Bit128 = 128;
//-------------------------------------- Some caveats when using this class:
//                                        - Get/setPosition semantics are changed
//                                         to indicate bit position rather than
//                                         byte position.
//
class BitStream
{
protected:
    U8 *dataPtr;
    S32  bitNum;
    S32  flagNum;
    bool tailFlag;
    S32  bufSize;
    S32  bitsLimite;
    bool error;
    S32  maxReadBitNum;
    S32  maxWriteBitNum;
public:
	BitStream(void *bufPtr, S32 bufSize, S32 maxWriteSize = -1);
	virtual ~BitStream();

    bool bindPacketStream(U8 *buffer,U32 writeSize); 
    void setBuffer(void *bufPtr, S32 bufSize, S32 maxSize = -1);
    U8*  getBuffer() { return dataPtr; }
    U8*  getBytePtr();
    U32 getReadByteSize();
    S32  getCurPos() const;
	U32  getPosition() const;
	U32  getStreamSize();
	bool setPosition(const U32 in_newPosition);
    void clear();
   
    
    virtual void writeBits(S32 bitCount, const void *bitPtr);
    virtual void readBits(S32 bitCount, void *bitPtr);
	void writeInt(S32 val, S32 bitCount);
	S32  readInt(S32 bitCount);
	void writeInt64(S64 val, S32 bitCount);
	S64  readInt64(S32 bitCount);
	F32  readFloat(S32 bitCount);
	void writeFloat(F32 f, S32 bitCount);
	F64  readFloat64(S32 bitCount);
	void writeFloat64(F64 f, S32 bitCount);
    virtual bool writeFlag(bool val); 
	virtual bool readFlag();
	void readString(char *stringBuf, int maxSize = 255);
	void writeString(const char *stringBuf, S32 maxLen = 255);
	std::string readString(int maxSize = 255);
	void writeString(std::string str, S32 maxLen = 255);
    
    bool isFull() { return bitNum > bitsLimite; }
    bool isValid() { return !error; }
    
	inline bool writeFlag(void *val)
	{
		return writeFlag(val != 0);
	}
};

//------------------------------------------------------------------------------
//-------------------------------------- INLINES
//
inline S32 BitStream::getCurPos() const
{
    return bitNum;
}

inline bool BitStream::readFlag()
{
    if((flagNum - ((flagNum>>3)<<3) ==0) && !tailFlag)
    {
        flagNum = bitNum;
        
        if(bitNum + 8 < maxReadBitNum)
            bitNum+=8; //Ray; ????8??????��flag
        else
            tailFlag = true;
    }
    
    if(flagNum + 1 > maxReadBitNum)
    {
        error = true;
        LIB_ASSERT(false, "Out of range read");
        return false;
    }
    
    S32 mask = 1 << (flagNum & 0x7);
    bool ret = (*(dataPtr + (flagNum >> 3)) & mask) != 0;
    flagNum++;
    return ret;
}
}
#endif //_BITSTREAM_H_