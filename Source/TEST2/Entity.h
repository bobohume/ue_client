#pragma once
#include "message/Packet.h"
class Entity
{
public:
	Entity();
	~Entity() {};
	bool _W_C_ENTITY(::google::protobuf::Message* _packet);
public:
	static Entity* Instance() {
		static Entity s_Instace;
		return &s_Instace;
	}
};

#define ENTITY Entity::Instance()
