#include "Entity.h"
#include "message/Packet.h"
#include "message/game.pb.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/AI/NavigationSystemBase.h"
#include "GonetCharacter.h"
#include "GonetState.h"
#include "WinTcp/Account.h"
#include "base/types.h"

using namespace message;
EntityMgr::EntityMgr()
{
	REGISTER_PACKET(new W_C_ENTITY(), std::bind(&EntityMgr::_W_C_ENTITY, this, std::placeholders::_1));
}

#pragma optimize("",off) 
bool EntityMgr::_W_C_ENTITY(::google::protobuf::Message* _packet) {
	auto packet = (W_C_ENTITY*)(_packet);
	if (!packet) {
		return false;
	}

	auto pGonetState = Cast<AGonetState>(GWorld->GetGameState());
	auto& EntityMap = pGonetState->EntityMap;
	for (auto i = 0; i < packet->entityinfo_size(); i++) {
		auto entityInfo = packet->entityinfo(i);
		auto Id = entityInfo.id();
		AGameObjectCharacter* pEntity = NULL;
		auto itr = EntityMap.find(Id);
		if (Id == WinTcp::ACCOUNT->m_AccountId) {
			ACharacter* pCharacter = UGameplayStatics::GetPlayerCharacter(GWorld, 0);
			pEntity = Cast<AGameObjectCharacter>(pCharacter);
		}else if (itr != EntityMap.end()) {
			pEntity = itr->second;

		}else if(entityInfo.has_data() && !entityInfo.data().removeflag()) {//创建实体
			FVector pos = FVector(0, 0, 250);
			if (entityInfo.has_move()) {
				pos = FVector(-entityInfo.move().pos().x(), -entityInfo.move().pos().y(), entityInfo.move().pos().z());
			}
			pEntity = Cast<AGameObjectCharacter>(pGonetState->SpawnPlayer(pos, FRotator(0)));
			pEntity->DataId = entityInfo.data().dataid();
		}

		if (pEntity == NULL) {
			UE_LOG(LogClass, Log, TEXT("ENTITY CREATE ERROR"));
			continue;
		}

		pEntity->Id = Id;
		if (entityInfo.has_data() && entityInfo.data().removeflag()) {
			pEntity->Destroy();
			EntityMap.erase(Id);
			continue;
		}
		pEntity->Init();
		if (entityInfo.has_move()) {
			FVector pos = FVector(-entityInfo.move().pos().x(), -entityInfo.move().pos().y(), entityInfo.move().pos().z());
			if (Id == WinTcp::ACCOUNT->m_AccountId) {
				UE_LOG(LogClass, Log, TEXT("server move [%f] [%f] [%f]"), pos.X, pos.Y, pos.Z);
				FVector pos1 = pEntity->GetActorLocation();
                pos.Z = pos1.Z;
				pos1 -= pos;
				if (FMath::Abs(pos1.X) > 120 || FMath::Abs(pos1.Y) > 120) {
					pEntity->SetActorLocation(pos);
				}
			}else {
				auto pAi = Cast<AAIController>(pEntity->GetController());
				if (pAi) {
					pAi->MoveToLocation(pos);
				}
			}
		}

		//属性变化
		if (entityInfo.has_stats()) {
			FStats3 oldStats = pEntity->Stats;
			pEntity->Stats.HP = entityInfo.stats().hp();
			pEntity->Stats.MP = entityInfo.stats().mp();
			pEntity->Stats.MaxHP = entityInfo.stats().maxhp();
			pEntity->Stats.MaxMP = entityInfo.stats().maxmp();
			pEntity->Stats.PhyDamage = entityInfo.stats().phydamage();
			pEntity->Stats.PhyDefence = entityInfo.stats().phydefence();
			pEntity->Stats.SplDamage = entityInfo.stats().spldamage();
			pEntity->Stats.SplDefence = entityInfo.stats().spldefence();
			pEntity->Stats.Heal = entityInfo.stats().heal();
			pEntity->Stats.CriticalTimes = entityInfo.stats().criticaltimes();
			pEntity->Stats.Critical_gPc = entityInfo.stats().critical();
			pEntity->Stats.AntiCriticalTimes = entityInfo.stats().anticriticaltimes();
			pEntity->Stats.AntiCritical_gPc = entityInfo.stats().anticritical();
			pEntity->Stats.Dodge_gPc = entityInfo.stats().dodge();
			pEntity->Stats.Hit_gPc = entityInfo.stats().hit();
			FStats3 newStats = pEntity->Stats;
			newStats -= oldStats;
			if (newStats.HP != 0) {
				pEntity->ShowDamageAmount(newStats.HP);
			}
		}

		EntityMap[Id] = pEntity;
	}


	return true;
}
#pragma optimize("", on)

//void AShooterBot::FaceRotation(FRotator NewRotation, float DeltaTime)
//{
//	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);
//
//	Super::FaceRotation(CurrentRotation, DeltaTime);
//}
