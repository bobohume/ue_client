#include "Player.h"
#include "message/Packet.h"
#include "message/game.pb.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TEST2Character.h"

using namespace message;
Player::Player()
{
	REGISTER_PACKET(new W_C_LoginMap(), std::bind(&Player::_W_C_LoginMap, this, std::placeholders::_1));
}

bool Player::_W_C_LoginMap(::google::protobuf::Message* _packet) {
	auto packet = (W_C_LoginMap*)(_packet);
	if (!packet) {
		return false;
	}


	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, 0);
	ATEST2Character* PlayerController1 = Cast<ATEST2Character>(PlayerController->GetCharacter());
	PlayerController1->Id = packet->id();
	packet->id();
	packet->pos();
	packet->rotation();

	return true;
}