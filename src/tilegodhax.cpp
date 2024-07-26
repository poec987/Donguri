#include "game/level/level.h"
#include "game/level/levelinfo.h"
#include "game/tilemgr.h"

void copyTilesInLocation(Level::Area::Location *loc, f32 x, f32 y, u8 layer, bool destroy) {
	u8 rows = (loc->w >> 4) + 1;
	u8 cols = (loc->h >> 4) + 1;
	
	for (int row = 0; row < rows; row++) {
		for (int column = 0; column < cols; column++) {
			u16 *dst = TileMgr::instance->getTilePtr(x + row * 16, -y + column * 16, layer, 0);
			if (destroy) {
				*dst = 0xFFFF;
			}
			else {
				u16 *src = TileMgr::instance->getTilePtr(loc->x + row * 16, loc->y + column * 16, 0, 0);
				*dst = *src;
			}
		}
	}
}

extern "C" void copyTilesFromLocation(u8 locationId, u8 layer, bool spawns, f32 x, f32 y) {
	u8 areaNum = LevelInfo::instance->area;
	Level::Area *area = Level::instance->getArea(areaNum);
	Level::Area::Location *loc = area->getLocation(0, locationId);
	
	if (loc) {
		copyTilesInLocation(loc, x, y, layer, !spawns);
	} else {
		DEBUG("Tsuru tile god location not found.");
	}
}

ASM_START

.include "macros.S"

.text

.global tileGodHacks
tileGodHacks:
	lwz r16, 0x14(r26)
	srwi. r15, r16, 28		// Use NewerU tile god?
	beq tileGodHacks_retail // If not, use the retail code
	extrwi r3, r16, 4, 8	// Location ID
	extrwi r4, r16, 4, 4	// Layer
	mr r5, r27
	lfs f1, 0x6C(r26)		// X
	lfs f2, 0x70(r26)		// Y
	bl copyTilesFromLocation
	b 0xF2E5DB0

.global tileGodHacks_retail
tileGodHacks_retail:
	li r16, 1
	blr

ASM_END
