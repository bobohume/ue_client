#pragma once  

#include "Base/types.h"
#include <unordered_map>

template<class U, class T>
class DataRes
{
public:
	DataRes() {
	}

	virtual ~DataRes() {
	}
	
	virtual void Close() {
		Clear();
	}

	virtual void Clear() {
		m_DataMap.clear();
	}

	virtual void AddData(U key, T data) {
		m_DataMap[key] = data;
	}

	virtual T GetData(U key) {
		auto itr = m_DataMap.find(key);
		if (itr != m_DataMap.end()) {
			return itr->second;
		}
		return NULL;
	}

	virtual std::unordered_map<U, T> GetMap() {
		return m_DataMap;
	}

	virtual bool Read() = 0;
private:
	std::unordered_map<U, T> m_DataMap;
};