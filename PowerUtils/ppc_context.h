#pragma once
#include <cstdint>
#include <cstdlib>
#include <cmath>

#ifdef __clang__
#include <x86intrin.h>
#define __restrict __restrict__
#define _byteswap_ushort __builtin_bswap16
#define _byteswap_ulong __builtin_bswap32
#define _byteswap_uint64 __builtin_bswap64
#define isnan __builtin_isnan
#define PPC_FUNC __attribute__((weak,noinline))
#else
#include <intrin.h>
#define PPC_FUNC __declspec(noinline)
#endif

#define PPC_LOAD_U8(x) *(uint8_t*)(base + (x))
#define PPC_LOAD_U16(x) _byteswap_ushort(*(uint16_t*)(base + (x)))
#define PPC_LOAD_U32(x) _byteswap_ulong(*(uint32_t*)(base + (x)))
#define PPC_LOAD_U64(x) _byteswap_uint64(*(uint64_t*)(base + (x)))

#define PPC_STORE_U8(x, y) *(uint8_t*)(base + (x)) = (y)
#define PPC_STORE_U16(x, y) *(uint16_t*)(base + (x)) = _byteswap_ushort(y)
#define PPC_STORE_U32(x, y) *(uint32_t*)(base + (x)) = _byteswap_ulong(y)
#define PPC_STORE_U64(x, y) *(uint64_t*)(base + (x)) = _byteswap_uint64(y)

typedef void PPCFunc(struct PPCContext& __restrict ctx, uint8_t* base);

struct PPCRegister
{
    union
    {
        int8_t s8;
        uint8_t u8;
        int16_t s16;
        uint16_t u16;
        int32_t s32;
        uint32_t u32;
        int64_t s64;
        uint64_t u64;
        float f32;
        double f64;
    };
};

struct PPCXERRegister
{
    uint8_t so;
    uint8_t ov;
    uint8_t ca;
};

struct PPCCRRegister
{
    uint8_t lt;
    uint8_t gt;
    uint8_t eq;
    union
    {
        uint8_t so;
        uint8_t un;
    };

    template<typename T>
    void compare(T left, T right, const PPCXERRegister& xer)
    {
        lt = left < right;
        gt = left > right;
        eq = left == right;
        so = xer.so;
    }

    void compare(double left, double right)
    {
        lt = left < right;
        gt = left > right;
        eq = left == right;
        un = isnan(left) || isnan(right);
    }
};

struct alignas(0x10) PPCVRegister
{
    union
    {
        int8_t s8[16];
        uint8_t u8[16];
        int16_t s16[8];
        uint16_t u16[8];
        int32_t s32[4];
        uint32_t u32[4];
        int64_t s64[2];
        uint64_t u64[2];
        float f32[4];
        double f64[2];
    };
};

struct PPCContext
{
    PPCFunc** fn;
    uint64_t lr;
    uint64_t ctr;
    PPCXERRegister xer;
    PPCRegister reserved;

    union
    {
        struct
        {
            PPCCRRegister cr0;
            PPCCRRegister cr1;
            PPCCRRegister cr2;
            PPCCRRegister cr3;
            PPCCRRegister cr4;
            PPCCRRegister cr5;
            PPCCRRegister cr6;
            PPCCRRegister cr7;
        };
        PPCCRRegister cr[8];
    };

    union
    {
        struct
        {
            PPCRegister r0;
            PPCRegister r1;
            PPCRegister r2;
            PPCRegister r3;
            PPCRegister r4;
            PPCRegister r5;
            PPCRegister r6;
            PPCRegister r7;
            PPCRegister r8;
            PPCRegister r9;
            PPCRegister r10;
            PPCRegister r11;
            PPCRegister r12;
            PPCRegister r13;
            PPCRegister r14;
            PPCRegister r15;
            PPCRegister r16;
            PPCRegister r17;
            PPCRegister r18;
            PPCRegister r19;
            PPCRegister r20;
            PPCRegister r21;
            PPCRegister r22;
            PPCRegister r23;
            PPCRegister r24;
            PPCRegister r25;
            PPCRegister r26;
            PPCRegister r27;
            PPCRegister r28;
            PPCRegister r29;
            PPCRegister r30;
            PPCRegister r31;
        };
        PPCRegister r[32];
    };

    union
    {
        struct
        {
            PPCRegister f0;
            PPCRegister f1;
            PPCRegister f2;
            PPCRegister f3;
            PPCRegister f4;
            PPCRegister f5;
            PPCRegister f6;
            PPCRegister f7;
            PPCRegister f8;
            PPCRegister f9;
            PPCRegister f10;
            PPCRegister f11;
            PPCRegister f12;
            PPCRegister f13;
            PPCRegister f14;
            PPCRegister f15;
            PPCRegister f16;
            PPCRegister f17;
            PPCRegister f18;
            PPCRegister f19;
            PPCRegister f20;
            PPCRegister f21;
            PPCRegister f22;
            PPCRegister f23;
            PPCRegister f24;
            PPCRegister f25;
            PPCRegister f26;
            PPCRegister f27;
            PPCRegister f28;
            PPCRegister f29;
            PPCRegister f30;
            PPCRegister f31;
        };
        PPCRegister f[32];
    };

    union
    {
        struct
        {
            PPCVRegister v0;
            PPCVRegister v1;
            PPCVRegister v2;
            PPCVRegister v3;
            PPCVRegister v4;
            PPCVRegister v5;
            PPCVRegister v6;
            PPCVRegister v7;
            PPCVRegister v8;
            PPCVRegister v9;
            PPCVRegister v10;
            PPCVRegister v11;
            PPCVRegister v12;
            PPCVRegister v13;
            PPCVRegister v14;
            PPCVRegister v15;
            PPCVRegister v16;
            PPCVRegister v17;
            PPCVRegister v18;
            PPCVRegister v19;
            PPCVRegister v20;
            PPCVRegister v21;
            PPCVRegister v22;
            PPCVRegister v23;
            PPCVRegister v24;
            PPCVRegister v25;
            PPCVRegister v26;
            PPCVRegister v27;
            PPCVRegister v28;
            PPCVRegister v29;
            PPCVRegister v30;
            PPCVRegister v31;
            PPCVRegister v32;
            PPCVRegister v33;
            PPCVRegister v34;
            PPCVRegister v35;
            PPCVRegister v36;
            PPCVRegister v37;
            PPCVRegister v38;
            PPCVRegister v39;
            PPCVRegister v40;
            PPCVRegister v41;
            PPCVRegister v42;
            PPCVRegister v43;
            PPCVRegister v44;
            PPCVRegister v45;
            PPCVRegister v46;
            PPCVRegister v47;
            PPCVRegister v48;
            PPCVRegister v49;
            PPCVRegister v50;
            PPCVRegister v51;
            PPCVRegister v52;
            PPCVRegister v53;
            PPCVRegister v54;
            PPCVRegister v55;
            PPCVRegister v56;
            PPCVRegister v57;
            PPCVRegister v58;
            PPCVRegister v59;
            PPCVRegister v60;
            PPCVRegister v61;
            PPCVRegister v62;
            PPCVRegister v63;
            PPCVRegister v64;
            PPCVRegister v65;
            PPCVRegister v66;
            PPCVRegister v67;
            PPCVRegister v68;
            PPCVRegister v69;
            PPCVRegister v70;
            PPCVRegister v71;
            PPCVRegister v72;
            PPCVRegister v73;
            PPCVRegister v74;
            PPCVRegister v75;
            PPCVRegister v76;
            PPCVRegister v77;
            PPCVRegister v78;
            PPCVRegister v79;
            PPCVRegister v80;
            PPCVRegister v81;
            PPCVRegister v82;
            PPCVRegister v83;
            PPCVRegister v84;
            PPCVRegister v85;
            PPCVRegister v86;
            PPCVRegister v87;
            PPCVRegister v88;
            PPCVRegister v89;
            PPCVRegister v90;
            PPCVRegister v91;
            PPCVRegister v92;
            PPCVRegister v93;
            PPCVRegister v94;
            PPCVRegister v95;
            PPCVRegister v96;
            PPCVRegister v97;
            PPCVRegister v98;
            PPCVRegister v99;
            PPCVRegister v100;
            PPCVRegister v101;
            PPCVRegister v102;
            PPCVRegister v103;
            PPCVRegister v104;
            PPCVRegister v105;
            PPCVRegister v106;
            PPCVRegister v107;
            PPCVRegister v108;
            PPCVRegister v109;
            PPCVRegister v110;
            PPCVRegister v111;
            PPCVRegister v112;
            PPCVRegister v113;
            PPCVRegister v114;
            PPCVRegister v115;
            PPCVRegister v116;
            PPCVRegister v117;
            PPCVRegister v118;
            PPCVRegister v119;
            PPCVRegister v120;
            PPCVRegister v121;
            PPCVRegister v122;
            PPCVRegister v123;
            PPCVRegister v124;
            PPCVRegister v125;
            PPCVRegister v126;
            PPCVRegister v127;
        };
        PPCVRegister v[128];
    };
};
