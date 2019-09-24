// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ExportData.h"
#include "ExportDataPrivatePCH.h"
#include "SlateBasics.h"
#include "SlateExtras.h"

#include "ExportDataStyle.h"
#include "ExportDataCommands.h"

#include "LevelEditor.h"
#include "dtMeshTile3.h"

#if WITH_RECAST

#include "NavMesh/RecastNavMesh.h"
#include "NavMesh/RecastNavMeshGenerator.h"
#include "NavMesh/PImplRecastNavMesh.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "NavigationSystem.h"
#include "Detour/DetourNavMesh.h"
#include "Recast/Recast.h"
#include "EngineUtils.h"
#endif

static const int NAVMESHSET_MAGIC = 'M' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'MSET';
static const int NAVMESHSET_VERSION = 1;
static char* EXPORT_PATH = "E:/git/myserver/bin/nav/";
static const FName ExportDataTabName("ExportData");

static unsigned int s_tileBits = 0;
static unsigned int s_polyBits = 0;

#define LOCTEXT_NAMESPACE "FExportDataModule"

void FExportDataModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FExportDataStyle::Initialize();
	FExportDataStyle::ReloadTextures();

	FExportDataCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FExportDataCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FExportDataModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FExportDataModule::AddMenuExtension));
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		//TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		//ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FExportDataModule::AddToolbarExtension));
		//LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FExportDataModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FExportDataStyle::Shutdown();

	FExportDataCommands::Unregister();
}

class ARecastNavMeshTrick : public ARecastNavMesh { public: const FPImplRecastNavMesh* GetRecastNavMeshImplTrick() const { return GetRecastNavMeshImpl(); } };

void FExportDataModule::PluginButtonClicked()
{
	FWorldContext &EditorContext = GEditor->GetEditorWorldContext();
	UWorld * InWorld = EditorContext.World();
	UNavigationSystemV1* navigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(InWorld);
	TArray<FNavDataConfig> supportedAgents = navigationSystem->GetSupportedAgents();
	for (int32 agents = 0; agents < supportedAgents.Num(); agents++)
	{
		FNavDataConfig dataConfig = supportedAgents[agents];
		ANavigationData* NavData = navigationSystem->GetNavDataForProps(dataConfig);
		if (NavData && !NavData->IsPendingKill())
		{
			ARecastNavMeshTrick * RecastNavData = Cast<ARecastNavMeshTrick>(NavData);
			const FPImplRecastNavMesh* tempRN = RecastNavData->GetRecastNavMeshImplTrick();
			const dtNavMesh* NavMesh = tempRN->GetRecastMesh();
			char text[128];
			snprintf(text, 128, "%s%s.nav", EXPORT_PATH, TCHAR_TO_UTF8(*InWorld->GetName()));//获取地图名字
			if (NavMesh != NULL)
			{
				UE_LOG(LogNavigation, Error, TEXT("Succeed to get navigation data!!!"));
				SaveData(text, NavMesh);
			}
			else
			{
				UE_LOG(LogNavigation, Error, TEXT("Failed to export navigation data due to navigation data"));
			}
		}
	}
}

void FExportDataModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FExportDataCommands::Get().PluginAction);
}

void FExportDataModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FExportDataCommands::Get().PluginAction);
}

dtTileRef3 encodePolyId(unsigned int salt, unsigned int it, unsigned int ip, const dtNavMesh* mesh)
{
	return (dtTileRef3)((salt << (s_polyBits + s_tileBits)) | ((dtTileRef3)it << s_polyBits) | (dtTileRef3)ip);
}

dtTileRef3 getTileRef(const dtMeshTile* tile, const dtNavMesh* mesh)
{
	if (!tile) return 0;
	const unsigned int it = (unsigned int)(tile - mesh->getTile(0));
	return (dtTileRef3)encodePolyId(tile->salt, it, 0, mesh);
}

void FExportDataModule::SaveData(const char* path, const dtNavMesh* mesh)
{
	if (!mesh) return;

	// Store header.
	NavMeshSetHeader header;
	//header.magic = NAVMESHSET_MAGIC;
	header.version = NAVMESHSET_VERSION;
	header.numTiles = 0;
	int maxPolys = 0;
	for (int i = 0; i < mesh->getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = mesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;
		header.numTiles++;
		if (tile->header->polyCount > maxPolys) {
			maxPolys = tile->header->polyCount;
		}
	}
	
	//判断是否有数据，没有数据，直接返回
	if (header.numTiles == 0)
		return;

	FILE* fp = fopen(path, "wb");
	if (!fp)
		return;

	memcpy(&header.params, mesh->getParams(), sizeof(dtNavMeshParams));
	header.params.maxPolys = maxPolys;
	s_tileBits = dtIlog2(dtNextPow2((unsigned int)header.params.maxTiles));
	s_polyBits = dtIlog2(dtNextPow2((unsigned int)header.params.maxPolys));
	fwrite(&header, sizeof(NavMeshSetHeader), 1, fp);

	// Store tiles.
	for (int i = 0; i < mesh->getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = mesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;

		const int headerSize = dtAlign4(sizeof(dtMeshHeader3));
		const int vertsSize = dtAlign4(sizeof(float) * 3 * tile->header->vertCount);
		const int polysSize = dtAlign4(sizeof(dtPoly)*tile->header->polyCount);
		const int linksSize = dtAlign4(sizeof(dtLink3)*tile->header->maxLinkCount);
		const int detailMeshesSize = dtAlign4(sizeof(dtPolyDetail)*tile->header->detailMeshCount);
		const int detailVertsSize = dtAlign4(sizeof(float) * 3 * tile->header->detailVertCount);
		const int detailTrisSize = dtAlign4(sizeof(unsigned char) * 4 * tile->header->detailTriCount);
		const int bvTreeSize = dtAlign4(sizeof(dtBVNode)*tile->header->bvNodeCount);
		const int offMeshConsSize = dtAlign4(sizeof(dtOffMeshConnection)*tile->header->offMeshConCount);

		const int dataSize = headerSize + vertsSize + polysSize + linksSize +
			detailMeshesSize + detailVertsSize + detailTrisSize +
			bvTreeSize + offMeshConsSize;

		unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char)*dataSize);
		if (!data)
		{
			//dtFree(offMeshConClass);
			return;
		}
		memset(data, 0, dataSize);

		unsigned char* d = data;

		dtMeshHeader3* header = dtGetThenAdvanceBufferPointer<dtMeshHeader3>(d, headerSize);
		float* navVerts = dtGetThenAdvanceBufferPointer<float>(d, vertsSize);
		dtPoly* navPolys = dtGetThenAdvanceBufferPointer<dtPoly>(d, polysSize);
		//dtLink* navPolys = dtGetThenAdvanceBufferPointer<dtLink3>(d, polysSize);
		d += linksSize; // Ignore links; just leave enough space for them. They'll be created on load.
		dtPolyDetail* navDMeshes = dtGetThenAdvanceBufferPointer<dtPolyDetail>(d, detailMeshesSize);
		float* navDVerts = dtGetThenAdvanceBufferPointer<float>(d, detailVertsSize);
		unsigned char* navDTris = dtGetThenAdvanceBufferPointer<unsigned char>(d, detailTrisSize);
		dtBVNode* navBvtree = dtGetThenAdvanceBufferPointer<dtBVNode>(d, bvTreeSize);
		dtOffMeshConnection* offMeshCons = dtGetThenAdvanceBufferPointer<dtOffMeshConnection>(d, offMeshConsSize);

		// Store header
		header->magic = tile->header->magic;
		header->version = tile->header->version;
		header->x = tile->header->x;
		header->y = tile->header->y;
		header->layer = tile->header->layer;
		header->userId = tile->header->userId;
		header->polyCount = tile->header->polyCount;
		header->vertCount = tile->header->vertCount;
		header->maxLinkCount = tile->header->maxLinkCount;
		for (auto i = 0; i < 3; i++) {
			header->bmin[i] = tile->header->bmin[i];
			header->bmax[i] = tile->header->bmax[i];
		}
		header->detailMeshCount = tile->header->detailMeshCount;
		header->detailVertCount = tile->header->detailVertCount;
		header->detailTriCount = tile->header->detailTriCount;
		header->bvQuantFactor = tile->header->bvQuantFactor;
		header->offMeshBase = tile->header->offMeshBase;
		header->walkableHeight = tile->header->walkableHeight;
		header->walkableRadius = tile->header->walkableRadius;
		header->walkableClimb = tile->header->walkableClimb;
		header->offMeshConCount = tile->header->offMeshConCount;
		header->bvNodeCount = tile->header->bvNodeCount;

		memcpy(navVerts, tile->verts, vertsSize);
		memcpy(navPolys, tile->polys, polysSize);
		memcpy(navDMeshes, tile->detailMeshes, detailMeshesSize);
		memcpy(navDVerts, tile->detailVerts, detailVertsSize);
		memcpy(navDTris, tile->detailTris, detailTrisSize);
		memcpy(navBvtree, tile->bvTree, bvTreeSize);
		memcpy(offMeshCons, tile->offMeshCons, offMeshConsSize);

		NavMeshTileHeader tileHeader;
		tileHeader.tileRef = getTileRef(tile, mesh);
		tileHeader.dataSize = dataSize;	
		fwrite(&tileHeader, sizeof(tileHeader), 1, fp);
		fwrite(data, dataSize, 1, fp);
		free(data);
	}

	fclose(fp);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExportDataModule, ExportData)