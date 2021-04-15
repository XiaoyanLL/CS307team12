#include "Tile.h"
#include "glad/glad.h"
namespace Core
{
// Sets the spriteID (eventually mCurrentDepth too)
	Tile::Tile ():
		mSpriteID ( -1 ),
		mIsInvisible(false)
	{
// Nothing needs to be done here
// Sprite ID gets set to -1 by default, just meaning the sprite hasn't been set
	}

	// Copy the given coordinates to the coordinates of the tile
	void Tile::setCoords ( int *coords )
	{
		// P1
		mCoords[0] = coords[0];
		mCoords[1] = coords[1];
		// P1 texture coords
		mCoords[2] = 0;
		mCoords[3] = 1;

		// P2
		mCoords[4] = coords[2];
		mCoords[5] = coords[3];
		// P2 texture coords
		mCoords[6] = 0;
		mCoords[7] = 0;

		// P3
		mCoords[8] = coords[4];
		mCoords[9] = coords[5];
		// P3 texture coords
		mCoords[10] = 1;
		mCoords[11] = 1;

		// P4
		mCoords[12] = coords[6];
		mCoords[13] = coords[7];
		// P4 texture coords
		mCoords[14] = 1;
		mCoords[15] = 0;
	}

	int *Tile::getCoords ()
	{
		return mCoords;
	}

	bool Tile::isInvisibleTile() {
		return mIsInvisible;
	}

	void Tile::setInvisibleTile(bool value) {
		mIsInvisible = value;
	}
}