#pragma once  

#include <Base/types.h>
#include <unordered_map>

template<class U, class T>
class DataRes
{
public:
	DataRes() {
	}

	~DataRes() {
	}
	
	void Close() {
		Clear();
	}

	void Clear() {
		m_DataMap.clear();
	}

	void AddData(U key, T data) {
		m_DataMap[key] = data;
	}

	T GetData(U key) {
		auto itr = m_DataMap.find(key);
		if (itr != m_DataMap.end()) {
			return itr->second;
		}
		return NULL;
	}

	std::unordered_map<U, T> GetMap() {
		return m_DataMap;
	}

	virtual bool Read() {
		return true;
	}
private:
	std::unordered_map<U, T> m_DataMap;
};