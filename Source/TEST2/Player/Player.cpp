#include "Player.h"
#include "message/Packet.h"
#include "message/game.pb.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
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


	ACharacter* pCharacter = UGameplayStatics::GetPlayerCharacter(GWorld, 0);
	ATEST2Character* pPlayerController = Cast<ATEST2Character>(pCharacter);
	pPlayerController->Id = packet->id();
	FTransform Transform;
	Transform.SetLocation(FVector(packet->pos().y(), packet->pos().x(), packet->pos().z()));
	pPlayerController->SetActorTransform(Transform);

	return true;
}