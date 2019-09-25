#include "Entity.h"
#include "message/Packet.h"
#include "message/game.pb.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TEST2Character.h"
#include "CGonetState.h"

using namespace message;
EntityMgr::EntityMgr()
{
	REGISTER_PACKET(new W_C_ENTITY(), std::bind(&EntityMgr::_W_C_ENTITY, this, std::placeholders::_1));
}

bool EntityMgr::_W_C_ENTITY(::google::protobuf::Message* _packet) {
	auto packet = (W_C_ENTITY*)(_packet);
	if (!packet) {
		return false;
	}

	auto pGonetState = Cast<ACGonetState>(GWorld->GetGameState());
	auto& EntityMap = pGonetState->EntityMap;
	for (auto i = 0; i < packet->entityinfo_size(); i++) {
		auto entityInfo = packet->entityinfo(i);
		auto Id = entityInfo.id();
		ATEST2Character* pEntity = EntityMap[Id];
		//创建实体
		if (pEntity == NULL) {
			pEntity = Cast<ATEST2Character>(pGonetState->SpawnPlayer(FVector(0, 0, 250), FRotator(0)));
		}

		if (entityInfo.has_data()) {
			pEntity->Id = Id;
			if (entityInfo.data().removeflag()) {
				pEntity->Destroy();
				EntityMap.erase(Id);
			}
		}

		if (entityInfo.has_move()) {
			pEntity->SetActorLocation(FVector(entityInfo.move().pos().x(), entityInfo.move().pos().y(), entityInfo.move().pos().z()));
		}

		EntityMap[Id] = pEntity;
	}


	return true;
}