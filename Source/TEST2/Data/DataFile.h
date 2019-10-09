#pragma once  

#include <iostream>
#include <vector>
#include <Base/bitStream.h>

using namespace Base;
enum enDataType
{
	DType_none,
	DType_String,
	DType_Enum,
	DType_S8,
	DType_S16,
	DType_S32,
	DType_F32,
	DType_F64,
	DType_S64,
};

struct RData {
	int m_Type;
	std::string m_String;
	int m_Enum;
	S8 m_S8;
	S16	m_S16;
	S32 m_S32;
	F32 m_F32;
	F64 m_F64;
	S64 m_S64;

	std::string String(std::string dataname, std::string datacol);
	S32 Enum(std::string dataname, std::string datacol);
	S8	Int8(std::string dataname, std::string datacol);
	S16	Int16(std::string dataname, std::string datacol);
	S32	Int(std::string dataname, std::string datacol);
	F32	Float32(std::string dataname, std::string datacol);
	F64	Float64(std::string dataname, std::string datacol);
	S64 Int64(std::string dataname, std::string datacol);
};

class CDataFile
{
public:
	int  RecordNum;  //记录数量
	int  ColumNum;   //列数量

	CDataFile();
	~CDataFile();
	//
	bool ReadDataFile(const char* name);    //读取data文件
	bool GetData        (RData&);              //得到具体的内容
	//
	void ReadDataInit();
	void ReadDataClose();
private:
	BitStream* fstream;
	int       readstep;   //控制读的总的数量
	std::vector<int> m_DataTypes;
	int	m_CurrentColumnIndex;
	char* m_pData;
};