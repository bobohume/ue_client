#pragma once
#include "message/Packet.h"
class Entity
{
public:
	Entity();
	~Entity() {};
	static bool _W_C_ENTITY3(::google::protobuf::Message* _packet);
	bool _W_C_ENTITY2(::google::protobuf::Message* _packet);
public:
	static Entity* Instance() {
		static Entity s_Instace;
		return &s_Instace;
	}
};

#define ENTITY Entity::Instance()
