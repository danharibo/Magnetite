#include "BaseBlock.h"
#include "MagnetiteCore.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "WorldChunk.h"
#include "World.h"
#include <string>

BaseBlock::BaseBlock()
: mDataFlags( 0 )
{
}

BaseBlock::~BaseBlock(void)
{
}

void BaseBlock::_setPosition( unsigned short x, unsigned  short y, unsigned short z)
{
	//mDataFlags = ( x | (z<<4) | (y<<8) );
}

void BaseBlock::connectedChange( short face )
{

}

/*short BaseBlock::getX() {
	return (mDataFlags & BMASK_XPOS);
}

short BaseBlock::getY() {
	return ((mDataFlags & BMASK_YPOS)>>8);
}

short BaseBlock::getZ() {
	return ((mDataFlags & BMASK_ZPOS)>>4);
}*/

void BaseBlock::updateVisFlags(unsigned int flags)
{
	mDataFlags = (mDataFlags & ~BMASK_VISFLAGS) | (mDataFlags & ~(FACE_ALL<<0));
	mDataFlags = mDataFlags | (flags<<0);
}

unsigned short BaseBlock::getVisFlags()
{
	return ((mDataFlags & BMASK_VISFLAGS)>>0);
}

void BaseBlock::getTextureCoords( short face, short &x, short &y )
{
	x = 0;
	y = 0;
}

/*void BaseBlock::setPosition( long x, long y, long z )
{
	if( ctx.chunk )
		ctx.chunk->_blockMoved( this, x, y, z );
	_setPosition(x,y,z);
}

void BaseBlock::setPosition( const Vector3& vec)
{
	setPosition( vec.x, vec.y, vec.z );
}*/

void BaseBlock::appendToStream( std::ofstream& stream )
{
	stream.write( (char *) &mDataFlags, sizeof( mDataFlags ) );	
}

void BaseBlock::readFromStream( std::ifstream& stream )
{
	stream.read( (char *) &mDataFlags, sizeof( mDataFlags ) );	
}

void BaseBlock::buildCubeData( BlockContext& ctx, size_t& ind, size_t& eInd, GLvertex* data, GLedge* edges)
{
	if( ctx.chunk == NULL ) {
		Util::log("Can't generate geometry without a chunk?", Util::Error);
		return;
	}
	float x = ctx.worldX, y = ctx.worldY, z = ctx.worldZ;
	long wx = (ctx.chunk->getX()*CHUNK_WIDTH) + x, wy = (ctx.chunk->getY()*CHUNK_HEIGHT) + y, wz = (ctx.chunk->getZ()*CHUNK_WIDTH) + z;
	short texX = 0, texY = 0;

	short visFlags = getVisFlags();

	/* Face -Z */
	if((visFlags & FACE_BACK) == FACE_BACK ) {
		this->getTextureCoords( FACE_BACK, texX, texY );
		GLuvrect rect = MagnetiteCore::Singleton->getTextureManager()->getBlockUVs( texX, texY );
		
		float color = World::getLightColor( ctx.world->getLightLevel( wx, wy, wz+1 ) );
		data[ind + 0] = Renderer::vertex( x + 1.0f, y + 1.0f,	z + 1.0f, // Coordinates
								rect.x, rect.y,
								color );
		data[ind + 1] = Renderer::vertex( x - 0.0f, y + 1.0f, z + 1.0f, // Coordinates
								rect.x + rect.w, rect.y,
								color );
		data[ind + 2] = Renderer::vertex( x - 0.0f, y - 0.0f, z + 1.0f, // Coordinates
								rect.x + rect.w, rect.y + rect.h,
								color );
		data[ind + 3] = Renderer::vertex( x + 1.0f, y - 0.0f, z + 1.0f, // Coordinates
								rect.x, rect.y + rect.h,
								color );
		edges[eInd + 0] = ind + 2; edges[eInd + 1] = ind + 1; edges[eInd + 2] = ind + 0;
		edges[eInd + 3] = ind + 2; edges[eInd + 4] = ind + 0; edges[eInd + 5] = ind + 3;
		eInd += 6;
 		ind += 4;
	}
	/* Face +Z */
	if((visFlags & FACE_FORWARD) == FACE_FORWARD ) {
		this->getTextureCoords( FACE_FORWARD, texX, texY );
		GLuvrect rect = MagnetiteCore::Singleton->getTextureManager()->getBlockUVs( texX, texY );

		float color = World::getLightColor( ctx.world->getLightLevel( wx, wy, wz-1 ) );
		data[ind + 0] = Renderer::vertex( x + 1.0f, y + 1.0f, z - 0.0f, // Coordinates
								rect.x, rect.y,
								color );
		data[ind + 1] = Renderer::vertex( x - 0.0f, y + 1.0f, z - 0.0f, // Coordinates
								rect.x + rect.w, rect.y,
								color );
		data[ind + 2] = Renderer::vertex( x - 0.0f, y - 0.0f, z - 0.0f, // Coordinates
								rect.x + rect.w, rect.y + rect.h,
								color );
		data[ind + 3] = Renderer::vertex( x + 1.0f, y - 0.0f, z - 0.0f, // Coordinates
								rect.x, rect.y + rect.h,
								color );
		edges[eInd + 5] = ind + 2; edges[eInd + 4] = ind + 1; edges[eInd + 3] = ind + 0;
		edges[eInd + 2] = ind + 2; edges[eInd + 1] = ind + 0; edges[eInd + 0] = ind + 3;
		eInd += 6;
		ind += 4;
	}
	/* Face +X */
	if((visFlags & FACE_RIGHT) == FACE_RIGHT) {
		this->getTextureCoords( FACE_RIGHT, texX, texY );
		GLuvrect rect = MagnetiteCore::Singleton->getTextureManager()->getBlockUVs( texX, texY );

		float color = World::getLightColor( ctx.world->getLightLevel( wx+1, wy, wz ) );
		data[ind + 0] = Renderer::vertex( x + 1.0f, y + 1.0f, z + 1.0f, // Coordinates
								rect.x + rect.w, rect.y,
								color );
		data[ind + 1] = Renderer::vertex( x + 1.0f, y - 0.0f, z + 1.0f, // Coordinates
								rect.x + rect.w, rect.y + rect.h,
								color );
		data[ind + 2] = Renderer::vertex( x + 1.0f, y - 0.0f, z - 0.0f, // Coordinates
								rect.x, rect.y + rect.h,
								color );
		data[ind + 3] = Renderer::vertex( x + 1.0f, y + 1.0f, z - 0.0f, // Coordinates
								rect.x, rect.y,
								color );
		edges[eInd + 0] = ind + 2; edges[eInd + 1] = ind + 1; edges[eInd + 2] = ind + 0;
		edges[eInd + 3] = ind + 2; edges[eInd + 4] = ind + 0; edges[eInd + 5] = ind + 3;
		eInd += 6;
		ind += 4;
	}
	/* Face -Y */
	if((visFlags & FACE_BOTTOM) == FACE_BOTTOM) {
		this->getTextureCoords( FACE_BOTTOM, texX, texY );
		GLuvrect rect = MagnetiteCore::Singleton->getTextureManager()->getBlockUVs( texX, texY );

		float color = World::getLightColor( ctx.world->getLightLevel( wx, wy-1, wz ) );
		data[ind + 0] = Renderer::vertex( x - 0.0f, y - 0.0f, z + 1.0f, // Coordinates
								rect.x, rect.y,
								color );
		data[ind + 1] = Renderer::vertex( x - 0.0f, y - 0.0f, z - 0.0f, // Coordinates
								rect.x + rect.w, rect.y,
								color );
		data[ind + 2] = Renderer::vertex( x + 1.0f, y - 0.0f, z - 0.0f, // Coordinates
								rect.x + rect.w, rect.y + rect.h,
								color );
		data[ind + 3] = Renderer::vertex( x + 1.0f, y - 0.0f, z + 1.0f, // Coordinates
								rect.x, rect.y + rect.h,
								color );
		edges[eInd + 0] = ind + 2; edges[eInd + 1] = ind + 1; edges[eInd + 2] = ind + 0;
		edges[eInd + 3] = ind + 2; edges[eInd + 4] = ind + 0; edges[eInd + 5] = ind + 3;
		eInd += 6;
		ind += 4;
	}
	/* Face +Y */
	if((visFlags & FACE_TOP) == FACE_TOP) {
		this->getTextureCoords( FACE_TOP, texX, texY );
		GLuvrect rect = MagnetiteCore::Singleton->getTextureManager()->getBlockUVs( texX, texY );

		float color = World::getLightColor( ctx.world->getLightLevel( wx, wy+1, wz ) );
		data[ind + 0] = Renderer::vertex( x - 0.0f, y + 1.0f, z + 1.0f, // Coordinates
								rect.x, rect.y,
								color );
		data[ind + 1] = Renderer::vertex( x + 1.0f, y + 1.0f, z + 1.0f, // Coordinates
								rect.x + rect.w, rect.y,
								color );
		data[ind + 2] = Renderer::vertex( x + 1.0f, y + 1.0f, z - 0.0f, // Coordinates
								rect.x + rect.w, rect.y + rect.h,
								color );
		data[ind + 3] = Renderer::vertex( x - 0.0f, y + 1.0f, z - 0.0f, // Coordinates
								rect.x, rect.y + rect.h,
								color );
		edges[eInd + 0] = ind + 2; edges[eInd + 1] = ind + 1; edges[eInd + 2] = ind + 0;
		edges[eInd + 3] = ind + 2; edges[eInd + 4] = ind + 0; edges[eInd + 5] = ind + 3;
		eInd += 6;
		ind += 4;
	}
	/* Face -X */
	if((visFlags & FACE_LEFT) == FACE_LEFT) {
		this->getTextureCoords( FACE_LEFT, texX, texY );
		GLuvrect rect = MagnetiteCore::Singleton->getTextureManager()->getBlockUVs( texX, texY );

		float color = World::getLightColor( ctx.world->getLightLevel( wx-1, wy, wz ) );
		data[ind + 0] = Renderer::vertex( x - 0.0f, y + 1.0f, z - 0.0f, // Coordinates
								rect.x + rect.w, rect.y,
								color );
		data[ind + 1] = Renderer::vertex( x - 0.0f, y - 0.0f, z - 0.0f, // Coordinates
								rect.x + rect.w, rect.y + rect.h,
								color );
		data[ind + 2] = Renderer::vertex( x - 0.0f, y - 0.0f, z + 1.0f, // Coordinates
								rect.x, rect.y + rect.h,
								color );
		data[ind + 3] = Renderer::vertex( x - 0.0f, y + 1.0f, z + 1.0f, // Coordinates
								rect.x, rect.y,
								color );
		edges[eInd + 0] = ind + 2; edges[eInd + 1] = ind + 1; edges[eInd + 2] = ind + 0;
		edges[eInd + 3] = ind + 2; edges[eInd + 4] = ind + 0; edges[eInd + 5] = ind + 3;
		eInd += 6;
		ind += 4;
	}
}