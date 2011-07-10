/**
 * Libaries
 */
#define NOMINMAX
#include <GL/GLee.h>
#include <GL/freeglut.h>
#undef None
#include <SFML/Window.hpp>
#include <SFML/Window/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <limits>
#include <iostream>
#include <stdio.h>

#include "util.h"
#include "Vector.h"
#include "Matrix.h"

/**
 * Define vector type
 */
typedef std::vector<std::string> stringvector;

class BaseBlock;
struct WorldNode;
typedef BaseBlock* BlockPtr;
typedef BlockPtr* BlockArray;
typedef std::map<size_t,BaseBlock*> BlockList;
typedef std::pair<const size_t,BaseBlock*> BlockPosPair;
typedef unsigned char LightIndex;

typedef std::vector<WorldNode*> NodeList;

//typedef *BaseBlock[] BlockList;

class WorldChunk;
typedef std::vector<WorldChunk*> ChunkList;

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 128
#define CHUNK_SIZE (CHUNK_WIDTH*CHUNK_WIDTH*CHUNK_HEIGHT)
#define NODE_SIZE ((CHUNK_HEIGHT/CHUNK_WIDTH))

#define BLOCK_INDEX_2( x, y, z ) ( z * CHUNK_WIDTH * CHUNK_HEIGHT + y * CHUNK_WIDTH + x )
#define BLOCK_INDEX( block ) (block->getZ() * CHUNK_WIDTH * CHUNK_HEIGHT + block->getY() * CHUNK_WIDTH + block->getX())
