#include "DataFile.h"
#include <stdio.h>

CDataFile::CDataFile()
{
	ReadDataInit();
}
//
CDataFile::~CDataFile()
{
	ReadDataClose();
}
//
void  CDataFile::ReadDataInit()
{
	ColumNum = 0;
	RecordNum = 0;
	readstep = 0;
	m_pData = NULL;
	fstream = NULL;
}
//
void CDataFile::ReadDataClose()
{
	if (m_pData) {
		free(m_pData);
		m_pData = NULL;
	}
	fstream = NULL;
}

bool  CDataFile::ReadDataFile(const char* name)
{
	m_DataTypes.clear();
	m_CurrentColumnIndex = 0;

	//先定位数据
	FILE* fp = fopen(name, "rb");

	if (!fp)
		return false;

	fseek(fp, 0, SEEK_END);
	long lsize = ftell(fp);
	rewind(fp);
	m_pData = (char *)malloc(lsize * sizeof(char) + 1);
	memset(m_pData, 0, lsize * sizeof(char) + 1);
	size_t result = fread(m_pData, 1, lsize, fp);
	fclose(fp);

	fstream = new BitStream(m_pData, lsize);
	while(1){
		auto tchr = fstream->ReadInt(8);
		if (tchr == '@') //找到数据文件的开头
		{
			fstream->ReadInt(8);//这个是换行字符
			break;
		}
	}

	//得到记录总数
	RecordNum = fstream->ReadInt(32);
	//得到列的总数
	ColumNum = fstream->ReadInt(32);

	//sheet name
	fstream->ReadString();

	readstep = RecordNum * ColumNum;
	for (S32 nColumnIndex = 0; nColumnIndex < ColumNum; nColumnIndex++)
	{
		//col name
		fstream->ReadString();
		int nDataType = fstream->ReadInt(8);
		m_DataTypes.push_back(nDataType);
	}

	return true;
}

/****************************
	格式:
	头文件:
	1、总记录数(int)
	2、总字段数(int)
	字段格式:
	1、字段长度(int)
	2、字读数据类型(int->2,string->1,enum->3,float->4)
	3、字段内容(int,string)
*************************/
bool  CDataFile::GetData(RData& pData)
{
	if ((readstep == 0) || (!fstream))
		return false;

	switch (m_DataTypes[m_CurrentColumnIndex])
	{
	case DType_String:
		pData.m_String = fstream->ReadString();
		break;
	case DType_S8:
		pData.m_S8 = S8(fstream->ReadInt(8));
		break;
	case DType_S16:
		pData.m_S16 = S16(fstream->ReadInt(16));
		break;
	case DType_S32:
		pData.m_S32 = fstream->ReadInt(32);
		break;
	case DType_Enum:
		pData.m_Enum = fstream->ReadInt(16);
		break;
	case DType_F32:
		pData.m_F32 = fstream->ReadFloat();
		break;
	case DType_F64:
		pData.m_F64 = fstream->ReadFloat64();
		break;
	case DType_S64:
		pData.m_S64 = fstream->ReadInt64(64);
		break;
	}

	pData.m_Type = m_DataTypes[m_CurrentColumnIndex];
	m_CurrentColumnIndex = (m_CurrentColumnIndex + 1) % ColumNum;
	readstep--;
	return true;
}

/****************************
	RData funciton
****************************/
std::string RData::String(std::string dataname, std::string datacol){
	ASSERT(m_Type == DType_String, fmt.Sprintf("read [%s] col[%s] error", dataname, datacol));
	return m_String;
}

S32 RData::Enum(std::string dataname, std::string datacol) {
	ASSERT(m_Type == DType_Enum,  fmt.Sprintf("read [%s] col[%s] error", dataname, datacol));
	return m_Enum;
}

S8 RData::Int8(std::string dataname, std::string datacol) {
	ASSERT(m_Type == DType_S8, fmt.Sprintf("read [%s] col[%s] error", dataname, datacol));
	return m_S8;
}

S16 RData::Int16(std::string dataname, std::string datacol) {
	ASSERT(m_Type == DType_S16, fmt.Sprintf("read [%s] col[%s] error", dataname, datacol));
	return m_S16;
}

S32 RData::Int(std::string dataname, std::string datacol) {
	ASSERT(m_Type == DType_S32,  fmt.Sprintf("read [%s] col[%s] error", dataname, datacol));
	return m_S32;
}

F32 RData::Float32(std::string dataname, std::string datacol) {
	ASSERT(m_Type == DType_F32, fmt.Sprintf("read [%s] col[%s] error", dataname, datacol));
	return m_F32;
}

F64 RData::Float64(std::string dataname, std::string datacol) {
	ASSERT(m_Type == DType_F64, fmt.Sprintf("read [%s] col[%s] error", dataname, datacol));
	return m_F64;
}

S64 RData::Int64(std::string dataname, std::string datacol) {
	ASSERT(m_Type == DType_S64, fmt.Sprintf("read [%s] col[%s] error", dataname, datacol));
	return m_S64;
}

/*
	FString str = FPaths::GameDir() + "Content/data/AI.dat";
	CDataFile file;
	file.ReadDataFile(TCHAR_TO_UTF8(*str));
	RData r;
	file.GetData(r);
	file.GetData(r);
	file.GetData(r);
	file.GetData(r);
	FString str1(UTF8_TO_TCHAR(r.String("Aidata", "Name").c_str()));
	file.GetData(r);
	file.GetData(r);
*/