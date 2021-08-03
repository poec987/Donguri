#pragma once

#include "nw/eft/enum.h"
#include "dynlibs/gx2/types.h"

namespace nw { namespace eft {

class Heap;

class Shader { // Size: 0x278
public:
    enum VertexFormat {
        VertexFormatU32 = GX2_ATTRIB_FORMAT_32_UINT,
        VertexFormatVEC3 = GX2_ATTRIB_FORMAT_32_32_32_FLOAT,
        VertexFormatVEC4 = GX2_ATTRIB_FORMAT_32_32_32_32_FLOAT
    };

public:
    Shader();

    void Finalize(Heap* heap);
    void BindShader();
    bool CreateShader(Heap* heap, const void* binary, u32 binarySize);
    s32 GetFragmentSamplerLocation(const char* name);
    s32 GetAttributeLocation(const char* name);
    u32 GetAttribute(const char* name, u32 buffer, VertexFormat attribFormat, u32 offset, bool instanceID);
    void SetupShader(Heap* heap);

    GX2VertexShader* mVertexShader;
    GX2PixelShader* mPixelShader;
    GX2GeometryShader* mGeometryShader;
    GX2FetchShader mFetchShader;
    void* mFetchShaderBufPtr;
    u32 mNumAttribute;
    GX2AttribStream mAttributes[16];
    u32 mAttributeBuffer[16];
    bool mInitialized;
};

static_assert(sizeof(Shader) == 0x278, "Shader size mismatch");

class TextureSampler { // Size: 0xC
public:
    TextureSampler();
    ~TextureSampler();

    bool Setup(TextureFilterMode filterMode, TextureWrapMode wrapmodeX, TextureWrapMode wrapModeY);
    bool SetupLOD(f32 maxLOD, f32 biasLOD);

    GX2Sampler mSampler;
};

static_assert(sizeof(TextureSampler) == 0xC, "TextureSampler size mismatch");

class UniformBlock { // Size: 0x10
public:
    enum ShaderStage {
        ShaderStageVertex   = 0,
        ShaderStageFragment = 1,
        ShaderStageGeometry = 2,
        ShaderStageMax      = 3
    };

public:
    UniformBlock() {
        this->mInitialized = false;
        this->mBlockNotExist = false;
        this->mBufferSize = 0;
        this->mLocation = 0;
        this->mShaderStage = ShaderStageMax;
    }

    bool InitializeVertexUniformBlock(Shader* shader, const char* name, u32);
    bool InitializePixelUniformBlock(Shader* shader, const char* name, u32);
    void BindUniformBlock(const void* buffer);

    bool mInitialized;
    bool mBlockNotExist;
    u32 mBufferSize;
    u32 mLocation;
    ShaderStage mShaderStage;
};

static_assert(sizeof(UniformBlock) == 0x10, "UniformBlock size mismatch");

class VertexBuffer { // Size: 0x10
public:
    VertexBuffer();

    void* AllocateVertexBuffer(Heap* heap, u32 bufSize, u32 size);
    void Finalize(Heap* heap);
    void Invalidate();
    void BindBuffer(u32 index, u32 size, u32 stride);

    static void BindExtBuffer(u32 index, u32 size, u32, u32 stride, void* buffer);

    u32 mUnused;
    u32 mSize;
    u32 mBufferSize;
    void* mBuffer;
};

static_assert(sizeof(VertexBuffer) == 0x10, "VertexBuffer size mismatch");

} }

typedef int BOOL;

BOOL _DEMOGFDReadVertexShader(nw::eft::Heap* heap, GX2VertexShader** shader, u32 index, const void* binary);
BOOL _DEMOGFDReadPixelShader(nw::eft::Heap* heap, GX2PixelShader** shader, u32 index, const void* binary);
BOOL _DEMOGFDReadGeometryShader(nw::eft::Heap* heap, GX2GeometryShader** shader, u32 index, const void* binary);