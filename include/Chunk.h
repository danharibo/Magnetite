#ifndef _CHUNK_H_
#define _CHUNK_H_
#include "prerequisites.h"
#include <mutex>

// for standard size types
#include <cstdint>

/**
 * @struct ChunkIndex
 * contains the 3 components of a chunk's index in the world
 */
struct ChunkIndex
{
	long x;
	long y;
	long z;
};

typedef std::map<size_t, BlockPtr> BlockList;

struct GLgeometry;

class Chunk
{
protected:
	/**
	 * Array of blocks
	 */
	BlockArray	mBlocks;
	
	/**
	 * List of blocks that are visible
	 */
	BlockList	mVisibleBlocks;

	/**
	 * Index of the chunk in the world
	 */
	ChunkIndex	mWorldIndex;
	
	/**
	 * Array of light values
	 */
	LightIndex* mLightValues;
	
	/**
	 * Number of visible faces.
	 */
	size_t	mVisibleFaces;
	
	/**
	 * The chunk's geometry
	 */
	GLgeometry*	mGeometry;

	/**
	 * Allocates the array of a given size
	 */
	void _allocateArray( size_t size );

	/**
	 * Chunk flags
	 */
	uint16_t mChunkFlags;

	/**
	 * Blocks to be deleted
	 */
	BlockList mDeletedBlocks;
	
	/**
	 * Physics Objects
	 */
	btCollisionShape*		mPhysicsShape;
	btDefaultMotionState*	mPhysicsState;
	btTriangleMesh*		mPhysicsMesh;
	btRigidBody*		mPhysicsBody;
	
	/**
	 * Block counter
	 */
	size_t mNumBlocks;
	
	/**
	 * Threading lock
	 *  ensures that only one thread is doing something with this chunk.
	 */
	std::mutex mMutex;

public:
	/**
	 * Flags Enum
	 */
	enum {
		DataUpdated = 1, // Data has been updated, Visibility check needed
		MeshInvalid = 2 // Data has changed, mesh should be updated.
	};

public:
	Chunk( ChunkIndex index );
	~Chunk();

	/**
	 * Returns the chunk's X index.
	 */
	long getX();
	
	/**
	 * Returns the chunks Y index
	 */
	long getY();

	/**
	 * Returns the chunks z index
	 */
	long getZ();
	
	/**
	 * returns the light level at the block
	 */
	size_t getLightLevel( short x, short y, short z );

	/**
	 * Inserts the block at the given position
	 */
	void setBlockAt( BlockPtr block, short x, short y, short z );

	/**
	 * Inserts the block at the given index
	 */
	void setBlockAt( BlockPtr block, short index );

	/**
	 * Removes a block at the given position 
	 */
	void removeBlockAt( short x, short y, short z );

	/**
	 * Removes the block at the given index
	 */
	void removeBlockAt( short index );

	/**
	 * Returns the block at the given position
	 */
	BlockPtr getBlockAt( short x, short y, short z );

	/**
	 * Returns the block at the given index
	 */
	BlockPtr getBlockAt( size_t index );

	/**
	 * Returns all of the blocks
	 */
	BlockPtr* getBlocks();

    /**
     * Returns the number of visisble faces this chunk has
     */
    size_t getVisibleFaceCount();

	/**
	 * Retuns true if there's a block next to the given position
	 */
	bool hasNeighbours( long int x, long int y, long int z );
	
	/** 
	 * Sets the light value at the given pointer
	 */
	void setLightLevel( LightIndex value, short x, short y, short z );
	
	/**
	 * Returns a pointer to this chunk's geometry
	 */
	GLgeometry* getGeometry();
	
	/**
	 * Requests that the chunk re-generate
	 */
	void requestGenerate();
	
	/**
	 * Generates the chunk's actual geometry
	 */
	void generate();
	
	/**
	 * Generates the geometry for this chunk's mesh.
	 */
	void generateGeometry();
	
	/**
	 * Generates the light data for this chunk
	 */
	void generateLighting();
	
	/**
	 * Generates the chunk's physical geometry
	 */
	void generatePhysics();
	
	/**
	 * Updates the visibility flags of each block
	 */
	void updateVisibility();

	/**
	 * Updates the chunk
	 */
	void update( float dt );

	/**
	 * Raises a given flag on this chunk
	 */
	void _raiseChunkFlag( uint16_t flag );

	/**
	 * Returns true if the given flag is raised
	 */
	bool _hasChunkFlag( uint16_t flag );
	
	/**
	 * Removes a chunk flag
	 */
	void _lowerChunkFlag( uint16_t flag );
	
	/**
	 * Returns the number of non-empty blocks in the chunk
	 */
    const size_t getBlockCount();
	
	/**
	 * Returns the mutex for this chunk
	 */
	std::mutex& getMutex();
};


#endif
