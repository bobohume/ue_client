// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

template<typename TypeToRetrieveAs>
TypeToRetrieveAs* dtGetThenAdvanceBufferPointer(const unsigned char*& buffer, const size_t distanceToAdvance)
{
    TypeToRetrieveAs* returnPointer = reinterpret_cast<TypeToRetrieveAs*>(buffer);
    buffer += distanceToAdvance;
    return returnPointer;
}

template<typename TypeToRetrieveAs>
TypeToRetrieveAs* dtGetThenAdvanceBufferPointer(unsigned char*& buffer, const size_t distanceToAdvance)
{
    TypeToRetrieveAs* returnPointer = reinterpret_cast<TypeToRetrieveAs*>(buffer);
    buffer += distanceToAdvance;
    return returnPointer;
}

typedef unsigned int dtTileRef3;

struct NavMeshSetHeader
{
    //int magic;
    int version;
    int numTiles;
    dtNavMeshParams params;
};

struct NavMeshTileHeader
{
    dtTileRef3 tileRef;
    int dataSize;
};

/// Defines a link between polygons.
/// @note This structure is rarely if ever used by the end user.
/// @see dtMeshTile
struct dtLink3
{
	dtTileRef3 ref;					///< Neighbour reference. (The neighbor that is linked to.)
	unsigned int next;				///< Index of the next link.
	unsigned char edge;				///< Index of the polygon edge that owns this link.
	unsigned char side;				///< If a boundary link, defines on which side the link is.
	unsigned char bmin;				///< If a boundary link, defines the minimum sub-edge area.
	unsigned char bmax;				///< If a boundary link, defines the maximum sub-edge area.
};

/// Provides high level information related to a dtMeshTile object.
/// @ingroup detour
struct dtMeshHeader3
{
    int magic;                ///< Tile magic number. (Used to identify the data format.)
    int version;            ///< Tile data format version number.
    int x;                    ///< The x-position of the tile within the dtNavMesh tile grid. (x, y, layer)
    int y;                    ///< The y-position of the tile within the dtNavMesh tile grid. (x, y, layer)
    int layer;                ///< The layer of the tile within the dtNavMesh tile grid. (x, y, layer)
    unsigned int userId;    ///< The user defined id of the tile.
    int polyCount;            ///< The number of polygons in the tile.
    int vertCount;            ///< The number of vertices in the tile.
    int maxLinkCount;        ///< The number of allocated links.
    int detailMeshCount;    ///< The number of sub-meshes in the detail mesh.
    
    /// The number of unique vertices in the detail mesh. (In addition to the polygon vertices.)
    int detailVertCount;
    
    int detailTriCount;            ///< The number of triangles in the detail mesh.
    int bvNodeCount;            ///< The number of bounding volume nodes. (Zero if bounding volumes are disabled.)
    int offMeshConCount;        ///< The number of off-mesh connections.
    int offMeshBase;            ///< The index of the first polygon which is an off-mesh connection.
    float walkableHeight;        ///< The height of the agents using the tile.
    float walkableRadius;        ///< The radius of the agents using the tile.
    float walkableClimb;        ///< The maximum climb height of the agents using the tile.
    float bmin[3];                ///< The minimum bounds of the tile's AABB. [(x, y, z)]
    float bmax[3];                ///< The maximum bounds of the tile's AABB. [(x, y, z)]
    
    /// The bounding volume quantization factor.
    float bvQuantFactor;
};

/// Defines a navigation mesh tile.
/// @ingroup detour
struct dtMeshTile3
{
    unsigned int salt;                    ///< Counter describing modifications to the tile.
    
    unsigned int linksFreeList;            ///< Index to the next free link.
    dtMeshHeader3* header;                ///< The tile header.
    dtPoly* polys;                        ///< The tile polygons. [Size: dtMeshHeader::polyCount]
    float* verts;                        ///< The tile vertices. [Size: dtMeshHeader::vertCount]
    dtLink* links;                        ///< The tile links. [Size: dtMeshHeader::maxLinkCount]
    dtPolyDetail* detailMeshes;            ///< The tile's detail sub-meshes. [Size: dtMeshHeader::detailMeshCount]
    
    /// The detail mesh's unique vertices. [(x, y, z) * dtMeshHeader::detailVertCount]
    float* detailVerts;
    
    /// The detail mesh's triangles. [(vertA, vertB, vertC, triFlags) * dtMeshHeader::detailTriCount].
    /// See dtDetailTriEdgeFlags and dtGetDetailTriEdgeFlags.
    unsigned char* detailTris;
    
    /// The tile bounding volume nodes. [Size: dtMeshHeader::bvNodeCount]
    /// (Will be null if bounding volumes are disabled.)
    dtBVNode* bvTree;
    
    dtOffMeshConnection* offMeshCons;        ///< The tile off-mesh connections. [Size: dtMeshHeader::offMeshConCount]
    
    unsigned char* data;                    ///< The tile data. (Not directly accessed under normal situations.)
    int dataSize;                            ///< Size of the tile data.
    int flags;                                ///< Tile flags. (See: #dtTileFlags)
    dtMeshTile3* next;                        ///< The next free tile, or the next tile in the spatial grid.
};
