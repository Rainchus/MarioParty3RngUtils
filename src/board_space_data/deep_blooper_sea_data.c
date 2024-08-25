#include "mp3.h"
#include "util.h"

s16 DeepBlooperSeaSpaces_00[] = {
 0x0011,
 0x0012,
 0x0013,
 0x0014,
 0x0015,
 0x0017,
 0x0018,
 0x0019,
 0x001A,
 0x001B,
 0x001C,
 0x001D,
 0x001E,
 0x001F,
 0x0020,
 0x0000,
 0x000B,
 0x0016,
 0x0021,
 0x002C,
 0x0068,
};

s16 DeepBlooperSeaSpaces_01[] = {
 0x0022,
 0x0023,
 0x0024,
 0x0025,
};

s16 DeepBlooperSeaSpaces_02[] = {
 0x0037,
 0x0042,
 0x004D,
 0x0073,
 0x0058,
 0x0001,
 0x0002,
 0x0003,
 0x0004,
 0x0005,
 0x0006,
 0x0007,
 0x0008,
 0x0009,
 0x000A,
};

s16 DeepBlooperSeaSpaces_03[] = {
 0x0026,
 0x0085,
 0x006A,
 0x0086,
 0x0027,
 0x0028,
 0x0029,
};

s16 DeepBlooperSeaSpaces_04[] = {
 0x000C,
 0x000D,
 0x000E,
 0x000F,
 0x0010,
 0x0084,
};

s16 DeepBlooperSeaSpaces_05[] = {
 0x007D,
};

s16 DeepBlooperSeaSpaces_06[] = {
 0x002A,
 0x002B,
 0x002D,
 0x002E,
 0x002F,
 0x0030,
 0x0031,
 0x0032,
 0x0033,
 0x0034,
 0x0035,
 0x0089,
};

s16 DeepBlooperSeaSpaces_07[] = {
 0x0036,
 0x0038,
 0x0039,
 0x003A,
 0x003B,
 0x003C,
 0x003D,
 0x003E,
 0x003F,
 0x0040,
 0x0041,
 0x0043,
 0x0044,
 0x0045,
 0x0046,
 0x0079,
 0x0047,
 0x0048,
 0x0049,
 0x004A,
 0x004B,
 0x004C,
 0x004E,
};

s16 DeepBlooperSeaSpaces_08[] = {
 0x005B,
 0x0069,
 0x005C,
 0x005D,
};

s16 DeepBlooperSeaSpaces_09[] = {
 0x0059,
 0x0087,
 0x006B,
 0x0088,
 0x005A,
};

s16 DeepBlooperSeaSpaces_0A[] = {
 0x004F,
 0x0050,
 0x0051,
 0x0052,
 0x0053,
 0x0054,
 0x0055,
 0x0056,
 0x0057,
};

s16 DeepBlooperSeaSpaces_0B[] = {
 0x0067,
};

s16 DeepBlooperSeaSpaces_0C[] = {
 0x0082,
};

s16 DeepBlooperSeaSpaces_0D[] = {
 0x0083,
};

SpaceChain DeepBlooperSeaChains[] = {
    {ARRAY_COUNT(DeepBlooperSeaSpaces_00), DeepBlooperSeaSpaces_00},
    {ARRAY_COUNT(DeepBlooperSeaSpaces_01), DeepBlooperSeaSpaces_01},
    {ARRAY_COUNT(DeepBlooperSeaSpaces_02), DeepBlooperSeaSpaces_02},
    {ARRAY_COUNT(DeepBlooperSeaSpaces_03), DeepBlooperSeaSpaces_03},
    {ARRAY_COUNT(DeepBlooperSeaSpaces_04), DeepBlooperSeaSpaces_04},
    {ARRAY_COUNT(DeepBlooperSeaSpaces_05), DeepBlooperSeaSpaces_05},
    {ARRAY_COUNT(DeepBlooperSeaSpaces_06), DeepBlooperSeaSpaces_06},
    {ARRAY_COUNT(DeepBlooperSeaSpaces_07), DeepBlooperSeaSpaces_07},
    {ARRAY_COUNT(DeepBlooperSeaSpaces_08), DeepBlooperSeaSpaces_08},
    {ARRAY_COUNT(DeepBlooperSeaSpaces_09), DeepBlooperSeaSpaces_09},
    {ARRAY_COUNT(DeepBlooperSeaSpaces_0A), DeepBlooperSeaSpaces_0A},
    {ARRAY_COUNT(DeepBlooperSeaSpaces_0B), DeepBlooperSeaSpaces_0B},
    {ARRAY_COUNT(DeepBlooperSeaSpaces_0C), DeepBlooperSeaSpaces_0C},
    {ARRAY_COUNT(DeepBlooperSeaSpaces_0D), DeepBlooperSeaSpaces_0D},
};

SpaceData deep_blooper_sea_spaces[] = {
/* 0x000 */ {0x01, 0x01, 0x0000, 0x00000000,  { 195.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x001 */ {0x01, 0x01, 0x0000, 0x01000203,  { -145.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x002 */ {0x01, 0x0C, 0x0000, 0x04040403,  { -170.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x003 */ {0x01, 0x06, 0x0000, 0x00000505,  { -195.0000f, 0.0000f, 185.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x004 */ {0x01, 0x01, 0x0000, 0x0B0A0000,  { -230.0000f, 0.0000f, 185.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x005 */ {0x01, 0x01, 0x0000, 0x04040404,  { -230.0000f, 0.0000f, 150.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x006 */ {0x01, 0x02, 0x0000, 0x0D00000D,  { -230.0000f, 0.0000f, 120.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x007 */ {0x01, 0x01, 0x0000, 0x0F0F0F00,  { -230.0000f, 0.0000f, 80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x008 */ {0x01, 0x09, 0x0000, 0x11111312,  { -230.0000f, 0.0000f, 50.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x009 */ {0x01, 0x01, 0x0000, 0x11131400,  { -230.0000f, 0.0000f, 20.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00A */ {0x01, 0x01, 0x0000, 0x00000000,  { -230.0000f, 0.0000f, -10.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00B */ {0x01, 0x01, 0x0000, 0x10000F11,  { 170.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00C */ {0x01, 0x01, 0x0000, 0x12131111,  { -185.0000f, 0.0000f, -25.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00D */ {0x01, 0x06, 0x0000, 0x00000000,  { -160.0000f, 0.0000f, -10.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00E */ {0x01, 0x02, 0x0000, 0x100F0000,  { -135.0000f, 0.0000f, -5.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00F */ {0x01, 0x04, 0x0000, 0x13121212,  { -110.0000f, 0.0000f, -15.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x010 */ {0x01, 0x01, 0x0000, 0x00000000,  { -85.0000f, 0.0000f, -15.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x011 */ {0x01, 0x04, 0x0000, 0x0F0F0F00,  { -35.0000f, 0.0000f, -10.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x012 */ {0x01, 0x04, 0x0000, 0x11111512,  { -10.0000f, 0.0000f, 5.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x013 */ {0x01, 0x01, 0x0000, 0x11131400,  { 15.0000f, 0.0000f, 20.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x014 */ {0x01, 0x01, 0x0000, 0x00000000,  { 40.0000f, 0.0000f, 30.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x015 */ {0x01, 0x01, 0x0000, 0x1D00191C,  { 65.0000f, 0.0000f, 50.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x016 */ {0x01, 0x01, 0x0000, 0x1D221C1C,  { 140.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x017 */ {0x01, 0x06, 0x0000, 0x1D1D1D1D,  { 90.0000f, 0.0000f, 55.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x018 */ {0x01, 0x06, 0x0000, 0x261C0000,  { 115.0000f, 0.0000f, 35.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x019 */ {0x01, 0x04, 0x0000, 0x001D1D1D,  { 140.0000f, 0.0000f, 30.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01A */ {0x01, 0x01, 0x0000, 0x0000001D,  { 170.0000f, 0.0000f, 35.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01B */ {0x01, 0x04, 0x0000, 0x2E2E0000,  { 195.0000f, 0.0000f, 45.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01C */ {0x01, 0x01, 0x0000, 0x00343038,  { 220.0000f, 0.0000f, 55.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01D */ {0x01, 0x06, 0x0000, 0x35390000,  { 220.0000f, 0.0000f, 85.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01E */ {0x01, 0x01, 0x0000, 0x00000000,  { 220.0000f, 0.0000f, 120.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01F */ {0x01, 0x05, 0x0000, 0x00000000,  { 220.0000f, 0.0000f, 150.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x020 */ {0x01, 0x0F, 0x0000, 0x343D2E00,  { 220.0000f, 0.0000f, 180.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x021 */ {0x01, 0x07, 0x0000, 0x002E0000,  { 110.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x022 */ {0x01, 0x01, 0x0000, 0x3F3E0000,  { 50.0000f, 0.0000f, 170.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x023 */ {0x01, 0x09, 0x0000, 0x43040404,  { 65.0000f, 0.0000f, 135.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x024 */ {0x01, 0x01, 0x0000, 0x41000041,  { 75.0000f, 0.0000f, 110.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x025 */ {0x01, 0x0C, 0x0000, 0x00000000,  { 85.0000f, 0.0000f, 85.0000f}, { 0.1000f, 0.1000f, 0.1000f }, SetNextSpace, DBS_Space_25 },
/* 0x026 */ {0x01, 0x06, 0x0000, 0x191C1E1D,  { -65.0000f, 0.0000f, 30.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x027 */ {0x01, 0x05, 0x0000, 0x201C1C1D,  { -130.0000f, 0.0000f, 120.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x028 */ {0x01, 0x01, 0x0000, 0x00000000,  { -150.0000f, 0.0000f, 140.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x029 */ {0x01, 0x0C, 0x0000, 0x00000000,  { -175.0000f, 0.0000f, 160.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02A */ {0x01, 0x01, 0x0000, 0x00000000,  { -190.0000f, 0.0000f, -80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02B */ {0x01, 0x06, 0x0000, 0x00000000,  { -160.0000f, 0.0000f, -90.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02C */ {0x01, 0x01, 0x0000, 0x00000000,  { 80.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02D */ {0x01, 0x01, 0x0000, 0x00000000,  { -135.0000f, 0.0000f, -90.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02E */ {0x01, 0x01, 0x0000, 0x00000000,  { -110.0000f, 0.0000f, -80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02F */ {0x01, 0x04, 0x0000, 0x00000000,  { -80.0000f, 0.0000f, -80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x030 */ {0x01, 0x0C, 0x0000, 0x00000000,  { -50.0000f, 0.0000f, -85.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x031 */ {0x01, 0x01, 0x0000, 0x00000000,  { -30.0000f, 0.0000f, -70.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x032 */ {0x01, 0x01, 0x0000, 0x00000000,  { -5.0000f, 0.0000f, -55.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x033 */ {0x01, 0x04, 0x0000, 0x0000F000,  { 25.0000f, 0.0000f, -50.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x034 */ {0x01, 0x04, 0x0000, 0x00000000,  { 50.0000f, 0.0000f, -35.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x035 */ {0x01, 0x09, 0x0000, 0x00F00000,  { 60.0000f, 0.0000f, -65.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x036 */ {0x01, 0x01, 0x0000, 0x00F00000,  { 105.0000f, 0.0000f, -100.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x037 */ {0x01, 0x06, 0x0000, 0xF0000000,  { 10.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x038 */ {0x01, 0x01, 0x0000, 0x000000FF,  { 130.0000f, 0.0000f, -95.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x039 */ {0x01, 0x06, 0x0000, 0x00000000,  { 150.0000f, 0.0000f, -70.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03A */ {0x01, 0x01, 0x0000, 0xFFFFFF00,  { 160.0000f, 0.0000f, -45.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03B */ {0x01, 0x04, 0x0000, 0x00000000,  { 180.0000f, 0.0000f, -30.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03C */ {0x01, 0x01, 0x0000, 0x80000000,  { 200.0000f, 0.0000f, -20.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03D */ {0x01, 0x04, 0x0000, 0x0000F000,  { 230.0000f, 0.0000f, -10.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03E */ {0x01, 0x01, 0x0000, 0x00000000,  { 230.0000f, 0.0000f, -45.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03F */ {0x01, 0x09, 0x0000, 0x008F0000,  { 225.0000f, 0.0000f, -80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x040 */ {0x01, 0x01, 0x0000, 0x00F00000,  { 225.0000f, 0.0000f, -110.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x041 */ {0x01, 0x01, 0x0000, 0x80000000,  { 220.0000f, 0.0000f, -140.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x042 */ {0x01, 0x01, 0x0000, 0x00008FFF,  { -15.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x043 */ {0x01, 0x06, 0x0000, 0x00008FFF,  { 215.0000f, 0.0000f, -175.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x044 */ {0x01, 0x01, 0x0000, 0x0F0F8008,  { 200.0000f, 0.0000f, -210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x045 */ {0x01, 0x01, 0x0000, 0x0F0F0000,  { 180.0000f, 0.0000f, -230.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x046 */ {0x01, 0x02, 0x0000, 0x08FF0000,  { 150.0000f, 0.0000f, -240.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x047 */ {0x01, 0x0C, 0x0000, 0x0000FFFF,  { 90.0000f, 0.0000f, -240.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x048 */ {0x01, 0x01, 0x0000, 0x00000000,  { 60.0000f, 0.0000f, -240.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x049 */ {0x01, 0x06, 0x0000, 0x00000000,  { 30.0000f, 0.0000f, -240.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04A */ {0x01, 0x06, 0x0000, 0x00000000,  { 0.0000f, 0.0000f, -240.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04B */ {0x01, 0x07, 0x0000, 0x00000000,  { -30.0000f, 0.0000f, -240.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04C */ {0x01, 0x01, 0x0000, 0x0000FFFF,  { -60.0000f, 0.0000f, -240.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04D */ {0x01, 0x02, 0x0000, 0x00000000,  { -50.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04E */ {0x01, 0x03, 0x0000, 0x00000000,  { -90.0000f, 0.0000f, -240.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04F */ {0x01, 0x01, 0x0000, 0xFF800000,  { -120.0000f, 0.0000f, -240.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x050 */ {0x01, 0x04, 0x0000, 0xF0000000,  { -150.0000f, 0.0000f, -240.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x051 */ {0x01, 0x04, 0x0000, 0x0000FFF8,  { -170.0000f, 0.0000f, -220.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x052 */ {0x01, 0x04, 0x0000, 0x00000000,  { -190.0000f, 0.0000f, -200.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x053 */ {0x01, 0x04, 0x0000, 0xF000F000,  { -210.0000f, 0.0000f, -180.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x054 */ {0x01, 0x04, 0x0000, 0xF8000000,  { -230.0000f, 0.0000f, -160.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x055 */ {0x01, 0x04, 0x0000, 0x00000000,  { -250.0000f, 0.0000f, -140.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x056 */ {0x01, 0x01, 0x0000, 0x0000FFFF,  { -245.0000f, 0.0000f, -105.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x057 */ {0x01, 0x09, 0x0000, 0x00000000,  { -230.0000f, 0.0000f, -80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x058 */ {0x01, 0x01, 0x0000, 0xF0000000,  { -110.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x059 */ {0x01, 0x0F, 0x0000, 0xFF800000,  { -85.0000f, 0.0000f, -210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05A */ {0x01, 0x05, 0x0000, 0xF0000000,  { -55.0000f, 0.0000f, -115.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05B */ {0x01, 0x01, 0x0000, 0x0000FFFF,  { 70.0000f, 0.0000f, -140.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05C */ {0x01, 0x01, 0x0000, 0x00000000,  { 45.0000f, 0.0000f, -190.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05D */ {0x01, 0x01, 0x0000, 0x0F000000,  { 35.0000f, 0.0000f, -215.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05E */ {0x01, 0x03, 0x0000, 0xFFF00000,  { 240.0000f, 0.0000f, 115.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05F */ {0x01, 0x03, 0x0000, 0x80000000,  { -160.0000f, 0.0000f, 120.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x060 */ {0x01, 0x03, 0x0000, 0x0000F0F8,  { 70.0000f, 0.0000f, 25.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x061 */ {0x01, 0x03, 0x0000, 0x00000000,  { -205.0000f, 0.0000f, 75.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x062 */ {0x01, 0x03, 0x0000, 0xF0000000,  { 240.0000f, 0.0000f, -145.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x063 */ {0x01, 0x03, 0x0000, 0x000F8000,  { 20.0000f, 0.0000f, -190.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x064 */ {0x01, 0x03, 0x0000, 0x00F00000,  { -60.0000f, 0.0000f, -265.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x065 */ {0x01, 0x03, 0x0000, 0x0000F0F8,  { -220.0000f, 0.0000f, -115.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x066 */ {0x01, 0x03, 0x0000, 0x00000000,  { 120.0000f, 0.0000f, -270.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x067 */ {0x01, 0x00, 0x0000, 0xF000F000,  { 235.0000f, 0.0000f, 215.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x068 */ {0x01, 0x03, 0x0000, 0xFF800000,  { 55.0000f, 0.0000f, 205.0000f}, { 0.1000f, 0.1000f, 0.1000f }, JunctionDecision, &DBS_Space_68 },
/* 0x069 */ {0x01, 0x0D, 0x0000, 0x00000000,  { 57.5000f, 0.0000f, -165.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06A */ {0x01, 0x03, 0x0000, 0x0000F000,  { -87.5000f, 0.0000f, 75.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06B */ {0x01, 0x03, 0x0000, 0x00000000,  { -70.0000f, 0.0000f, -160.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06C */ {0x01, 0x03, 0x0000, 0xF0F80000,  { -80.0000f, 0.0000f, 175.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06D */ {0x01, 0x03, 0x0000, 0xFF800000,  { 92.5000f, 0.0000f, -172.5000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06E */ {0x01, 0x03, 0x0000, 0x80000000,  { 110.0000f, 0.0000f, 180.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06F */ {0x01, 0x03, 0x0000, 0x000000F0,  { 137.5000f, 0.0000f, 185.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x070 */ {0x01, 0x03, 0x0000, 0x00000000,  { -30.0000f, 0.0000f, -270.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x071 */ {0x01, 0x03, 0x0000, 0xF000F000,  { -2.5000f, 0.0000f, -265.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x072 */ {0x01, 0x03, 0x0000, 0x00F00000,  { 110.0000f, 0.0000f, -35.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x073 */ {0x01, 0x0D, 0x0000, 0x00000000,  { -80.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x074 */ {0x01, 0x03, 0x0000, 0xF000F00F,  { 260.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x075 */ {0x01, 0x03, 0x0000, 0x00000000,  { -280.0000f, 0.0000f, 145.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x076 */ {0x01, 0x03, 0x0000, 0x08F8F000,  { 220.0000f, 0.0000f, -220.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x077 */ {0x01, 0x03, 0x0000, 0x00F00000,  { -250.0000f, 0.0000f, -45.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x078 */ {0x01, 0x03, 0x0000, 0x00000000,  { -310.0000f, 0.0000f, -365.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x079 */ {0x01, 0x03, 0x0000, 0x000000F8,  { 120.0000f, 0.0000f, -245.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07A */ {0x01, 0x03, 0x0000, 0x00FF0FF0,  { -255.0000f, 0.0000f, -300.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07B */ {0x01, 0x03, 0x0000, 0x00000000,  { -300.0000f, 0.0000f, -30.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07C */ {0x01, 0x03, 0x0000, 0x00000000,  { -295.0000f, 0.0000f, -110.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07D */ {0x01, 0x03, 0x0000, 0x00000000,  { -215.0000f, 0.0000f, -45.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07E */ {0x01, 0x03, 0x0000, 0x0000F000,  { -285.0000f, 0.0000f, -110.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07F */ {0x01, 0x03, 0x0000, 0x00000000,  { -275.0000f, 0.0000f, -110.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x080 */ {0x01, 0x03, 0x0000, 0x08F00000,  { -265.0000f, 0.0000f, -110.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x081 */ {0x01, 0x03, 0x0000, 0x08F00000,  { -235.0000f, 150.0000f, -180.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x082 */ {0x01, 0x03, 0x0000, 0x000000F0,  { -205.0000f, 0.0000f, -60.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x083 */ {0x01, 0x03, 0x0000, 0x00000000,  { -205.0000f, 0.0000f, -35.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x084 */ {0x01, 0x03, 0x0000, 0x00000000,  { -65.0000f, 0.0000f, -15.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x085 */ {0x01, 0x03, 0x0000, 0xF00F0000,  { -80.0000f, 0.0000f, 50.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x086 */ {0x01, 0x03, 0x0000, 0x00000000,  { -110.0000f, 0.0000f, 95.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x087 */ {0x01, 0x03, 0x0000, 0x00000000,  { -80.0000f, 0.0000f, -190.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x088 */ {0x01, 0x03, 0x0000, 0x00000FFF,  { -65.0000f, 0.0000f, -145.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x089 */ {0x01, 0x03, 0x0000, 0x00000000,  { 70.0000f, 0.0000f, -90.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
};

//should be 0B54233C

DecisionTreeNonLeafNode DeepBlooperSeaRandomNode[] = {
    {
        .type = 0x03,
        .node_data1.data = 0x00000140,
        .node_data2.data = 0x1B54233C,
        .isPointer = 0,
        },
    {
        .type = 0,
        .node_data1.data = 0,
        .node_data2.data = 0x0B54233C,
        .isPointer = 0,
    }
};

//decision tree nodes for deep blooper sea first junction
//8011C904
DecisionTreeNonLeafNode DeepBlooperSeaJunction0Nodes[] = {
    {
        .type = 0x02,
        .node_data1.data = 0x00000001,
        .node_data2.data = 0x1B54233C,
        .isPointer = 0,
    },
    {
        .type = 0x02,
        .node_data1.data = 0x00000090,
        .node_data2.node_data = DeepBlooperSeaRandomNode,
        .isPointer = 0, //?
    },
    //is this needed?
    {
        .type = 0,
        .node_data1.data = 0x00,
        .node_data2.data = 0x0B54233C,
        .isPointer = 0,
    }
};

s16 DBS_Space_25[] = {
    0x17
};

DoubleJunction DBS_Space_68 = {
    .spaceABS = {
    0x37, //space id 0x0037 (left at junction)
    0x22, //space id 0x0022 (right at junction)
    },
    .junctionNodeData = DeepBlooperSeaJunction0Nodes
};