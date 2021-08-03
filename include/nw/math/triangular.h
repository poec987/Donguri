#pragma once

#include "nw/math/constant.h"

namespace nw { namespace math { namespace internal {

// Based on sead
struct SinCosSample {
    f32 mSinVal;
    f32 mSinDelta;
    f32 mCosVal;
    f32 mCosDelta;
};

extern const SinCosSample gSinCosTbl[0x100+1];

}

inline void SinCosIdx(f32* sinVal, f32* cosVal, u32 angle) {
    u32 idx = (angle >> 24) & 0xFF;
    f32 del = static_cast<f32>(angle & 0xFFFFFF) / 0x1000000;
    const internal::SinCosSample& sample = internal::gSinCosTbl[idx];

    // if (sinVal != NULL)
        *sinVal = sample.mSinVal + sample.mSinDelta * del;
    // if (cosVal != NULL)
        *cosVal = sample.mCosVal + sample.mCosDelta * del;
}

inline f32 SinIdx(u32 angle) {
    // Does not match if using SinCosIdx
    // f32 sinVal; SinCosIdx(&sinVal, NULL, angle); 
    // return sinVal;

    u32 idx = (angle >> 24) & 0xFF;
    f32 del = static_cast<f32>(angle & 0xFFFFFF) / 0x1000000;
    const internal::SinCosSample& sample = internal::gSinCosTbl[idx];

    return sample.mSinVal + sample.mSinDelta * del;
}

inline f32 CosIdx(u32 angle) {
    // Does not match if using SinCosIdx
    // f32 cosVal; SinCosIdx(NULL, &cosVal, angle);
    // return cosVal;

    u32 idx = (angle >> 24) & 0xFF;
    f32 del = static_cast<f32>(angle & 0xFFFFFF) / 0x1000000;
    const internal::SinCosSample& sample = internal::gSinCosTbl[idx];

    return sample.mCosVal + sample.mCosDelta * del;
}

inline f32 Idx2Rad(f32 angle) {
    return angle * (F_PI / I_HALF_ROUND_IDX);
}

inline u32 Rad2Idx(f32 rad) {
    return static_cast<s64>(rad * (I_HALF_ROUND_IDX / F_PI));
}

inline void SinCosRad(f32* sinVal, f32* cosVal, f32 rad) {
    SinCosIdx(sinVal, cosVal, Rad2Idx(rad));
}

inline f32 SinRad(f32 rad) {
    // Does not match if using SinCosRad
    // f32 sinVal; SinCosRad(&sinVal, NULL, rad);
    // return sinVal;

    return SinIdx(Rad2Idx(rad));
}

inline f32 CosRad(f32 rad) {
    // Does not match if using SinCosRad
    // f32 cosVal; SinCosRad(NULL< &cosVal, rad)
    // return cosVal;

    return CosIdx(Rad2Idx(rad));
}

} }