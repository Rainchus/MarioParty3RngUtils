#ifndef _MP1_H
#define _MP1_H

#include "ansi_colors.h"

#define ARRAY_COUNT(arr) (sizeof(arr) / sizeof(arr[0]))

typedef unsigned long u32;
typedef long s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct SpaceData {
/* 0x00 */ s8 unk_00;
/* 0x01 */ u8 space_type; // enum board_space_type
/* 0x02 */ s16 unk_02;
/* 0x04 */ s32 unk_04;
/* 0x08 */ Vec3f coords;
/* 0x14 */ Vec3f rot;
/* 0x20 */ void* event_list;
} SpaceData;

typedef struct Blocks {
    s16 coinBlockSpaceIndex;
    s16 starBlockSpaceIndex;
    s16 itemBlockSpaceIndex;
} Blocks;

extern SpaceData spaces[];
extern u32 cur_rng_seed;

#define ADV_SEED(seed) seed = (seed * 0x41C64E6D + 0x3039)

u8 rollDice(void);
u8 RNGPercentChance(s8 arg0);
s32 func_800EEF80_102BA0(f32 arg0);
s32 MeasureRngCalls(u32 seedStart, u32 seedEnd);
SpaceData* func_800EB160_FED80(s16 arg0);
void func_800FC594_1101B4(Blocks* blocks);
s16 func_800EBCD4_FF8F4(u8 arg0);
s32 func_80035F98_36B98(s32 input);
void hidden_block_gen_main(void);
s32 DoCpuLogicGeneric(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, u32 numOfJumps);
void CPUGetWatchGeneric(s32 rollValue, u32 numOfJumps);

#endif