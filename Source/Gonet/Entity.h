#pragma once
#include "message/Packet.h"
#include <unordered_map>
class EntityMgr
{
public:
	EntityMgr();
	~EntityMgr() {};
	bool _W_C_ENTITY(::google::protobuf::Message* _packet);//实体更新
public:
	static EntityMgr* Instance() {
		static EntityMgr s_Instace;
		return &s_Instace;
	}
};

#define ENTITYMGR EntityMgr::Instance()
