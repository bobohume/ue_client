#pragma once
#include "message/Packet.h"
class Player
{
public:
	Player();
	~Player() {};
	bool _W_C_LoginMap(::google::protobuf::Message* _packet);//��¼��ͼ
public:
	static Player* Instance() {
		static Player s_Instace;
		return &s_Instace;
	}
};

#define PLAYER Player::Instance()
