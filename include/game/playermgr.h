#pragma once

#include <sead.h>
#include <game/actor/stage/player.h>

class PlayerMgr {
    SEAD_SINGLETON_DISPOSER(PlayerMgr)

public:
    u32 _10;
    u32 _14;
    u32 _18;
    u32 _1C;
    Player* mPlayers[4];
    Player** mPtrToPlayers;
    u32 _34;
    u32 _38;
    u32 _3C;
    u16 _40;
    u16 mPlayerFlags;
    u32 _44;
    u32 _48;
    u32 _4C;
    u32 _50;
};