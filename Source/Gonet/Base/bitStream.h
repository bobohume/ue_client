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
    U8*  GetBuffer() { return dataPtr; }
    U8*  GetBytePtr();
    U32  GetReadByteSize();
    S32  GetCurPos() const;
	U32  GetPosition() const;
	U32  GetStreamSize();
	bool SetPosition(const U32 in_newPosition);
    void Clear();
   
    
    virtual void WriteBits(S32 bitCount, const void *bitPtr);
    virtual void ReadBits(S32 bitCount, void *bitPtr);
	void WriteInt(S32 val, S32 bitCount);
	S32  ReadInt(S32 bitCount);
	void WriteInt64(S64 val, S32 bitCount);
	S64  ReadInt64(S32 bitCount);
	F32  ReadFloat();
	void WriteFloat(F32 f);
	F64  ReadFloat64();
	void WriteFloat64(F64 f);
    virtual bool WriteFlag(bool val); 
	virtual bool ReadFlag();
	void ReadString(char *stringBuf, int maxSize = 255);
	void WriteString(const char *stringBuf, S32 maxLen = 255);
	std::string ReadString(int maxSize = 255);
	void WriteString(std::string str, S32 maxLen = 255);
    
    bool isFull() { return bitNum > bitsLimite; }
    bool isValid() { return !error; }
    
	inline bool writeFlag(void *val)
	{
		return WriteFlag(val != 0);
	}
};
}
#endif //_BITSTREAM_H_