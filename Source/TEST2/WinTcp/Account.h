#ifndef _ACCOUNT_PROCESS_H
#define _ACCOUNT_PROCESS_H
#include <stdint.h>
#include "message/Packet.h"
#define BUILD_NO "1,5,1,1"

enum
{
	NONE_ERROR,
	VERSION_ERROR,		//版本不正确
	ACCOUNT_NOEXIST,	//账号不存在
};

namespace WinTcp
{
class Account
{
	Account();
	~Account() {};
public:
	static Account* Instance();
	bool LoginGame();
	bool LoginAccount();

	bool _W_C_SelectPlayerResponse(::google::protobuf::Message* _packet);
	bool _W_C_CreatePlayerResponse(::google::protobuf::Message* _packet);
	bool _A_C_LoginRequest(::google::protobuf::Message* _packet);
	bool _A_C_RegisterResponse(::google::protobuf::Message* _packet);

	int64_t m_AccountId;
	int64_t m_PlayerId;
};

#define ACCOUNT Account::Instance()
}
#endif
