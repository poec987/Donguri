#pragma once

#include <sead.h>

class EventMgr { // Size: 0x940
    SEAD_SINGLETON_DISPOSER(EventMgr)

public:
    void set(u32 id, u32 time, bool active, u32 unk1 = 0, u32 unk2 = 0, u32 unk3 = 0, u32 unk4 = 0);

    inline u64 mask(u8 id) { return 1ULL << id; }

    inline bool isActive(u8 id) { return (this->events & mask(id)) != 0; }
    inline bool isInactive(u8 id) { return (this->events & mask(id)) == 0; }

    u64 events;            // _10
    u8 _18[0x928];         // _18
};