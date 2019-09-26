#include "Entity.h"
#include "message/Packet.h"
#include "message/game.pb.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "TEST2Character.h"
#include "CGonetState.h"
#include "WinTcp/Account.h"
#include "base/types.h"

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
		ATEST2Character* pEntity = NULL;
		auto itr = EntityMap.find(Id);
		if (Id == WinTcp::ACCOUNT->m_AccountId) {
			ACharacter* pCharacter = UGameplayStatics::GetPlayerCharacter(GWorld, 0);
			pEntity = Cast<ATEST2Character>(pCharacter);
		}else if (itr == EntityMap.end()) {//创建实体
			FVector pos = FVector(0, 0, 250);
			if (entityInfo.has_move()) {
				pos = FVector(entityInfo.move().pos().x(), entityInfo.move().pos().y(), entityInfo.move().pos().z());
			}
			pEntity = Cast<ATEST2Character>(pGonetState->SpawnPlayer(FVector(0, 0, 250), FRotator(0)));
		}else {
			pEntity = itr->second;
		}

		if (pEntity == NULL) {
			UE_LOG(LogClass, Log, TEXT("ENTITY CREATE ERROR"));
			continue;
		}

		if (entityInfo.has_data()) {
			pEntity->Id = Id;
			if (entityInfo.data().removeflag()) {
				pEntity->Destroy();
				EntityMap.erase(Id);
			}
		}

		if (entityInfo.has_move()) {
			FTransform Dest;
			Dest.SetLocation(FVector(entityInfo.move().pos().x(), entityInfo.move().pos().y(), entityInfo.move().pos().z()));
			FTransform Source = pEntity->GetTransform();
			FTransform Transform;
			Transform.LerpTranslationScale3D(Source, Dest, ScalarRegister(0.1f));
			auto pAI = Cast<AAIController>(pEntity->AIControllerClass);
			if (pAI != NULL) {
				pAI->MoveToLocation(FVector(entityInfo.move().pos().x(), entityInfo.move().pos().y(), entityInfo.move().pos().z()));
			}
			//pEntity->SetActorTransform(Transform);
			//pEntity->SetActorLocation(FVector(entityInfo.move().pos().x(), entityInfo.move().pos().y(), entityInfo.move().pos().z()));
		}

		EntityMap[Id] = pEntity;
	}


	return true;
}

//void AShooterBot::FaceRotation(FRotator NewRotation, float DeltaTime)
//{
//	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);
//
//	Super::FaceRotation(CurrentRotation, DeltaTime);
//}
