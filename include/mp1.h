#ifndef _MP1_H
#define _MP1_H

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

extern SpaceData spaces[];
#endif