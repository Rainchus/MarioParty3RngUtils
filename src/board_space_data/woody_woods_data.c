#include "mp3.h"
#include "util.h"

s16 WoodyWoodsSpaces_00[] = {
 0x0066,
};

s16 WoodyWoodsSpaces_01[] = {
 0x0027,
 0x0028,
 0x008D,
 0x0029,
 0x002A,
 0x002C,
 0x002D,
 0x008C,
 0x002E,
 0x002F,
 0x005D,
 0x0030,
 0x0031,
 0x0032,
 0x0033,
 0x0007,
 0x0006,
 0x0005,
 0x0002,
 0x0003,
 0x0004,
 0x0000,
 0x000A,
 0x0015,
 0x0020,
 0x0067,
};

s16 WoodyWoodsSpaces_02[] = {
 0x002B,
 0x005B,
 0x0071,
 0x005A,
 0x0055,
 0x0054,
 0x004F,
 0x0074,
};

s16 WoodyWoodsSpaces_03[] = {
 0x0036,
 0x0041,
 0x004C,
 0x0057,
 0x0001,
};

s16 WoodyWoodsSpaces_04[] = {
 0x0050,
 0x0051,
 0x0052,
 0x0053,
 0x0072,
};

s16 WoodyWoodsSpaces_05[] = {
 0x005C,
 0x0070,
 0x006F,
 0x0088,
};

s16 WoodyWoodsSpaces_06[] = {
 0x000F,
 0x000C,
 0x008B,
};

s16 WoodyWoodsSpaces_07[] = {
 0x000B,
 0x0009,
 0x0008,
};

s16 WoodyWoodsSpaces_08[] = {
 0x000D,
 0x000E,
 0x0010,
 0x0011,
};

s16 WoodyWoodsSpaces_09[] = {
 0x004E,
 0x004D,
 0x004B,
 0x004A,
 0x0049,
 0x003F,
 0x006C,
};

s16 WoodyWoodsSpaces_0A[] = {
 0x0040,
 0x0042,
 0x0043,
 0x0044,
 0x0045,
 0x0046,
 0x0047,
 0x0048,
 0x0073,
 0x0059,
 0x0058,
 0x0056,
};

s16 WoodyWoodsSpaces_0B[] = {
 0x003E,
 0x003D,
 0x003C,
 0x003B,
 0x008F,
};

s16 WoodyWoodsSpaces_0C[] = {
 0x001A,
 0x0019,
 0x0018,
 0x0017,
 0x0016,
 0x0014,
 0x0013,
 0x0012,
 0x0068,
 0x0034,
 0x0035,
 0x0037,
 0x0038,
};

s16 WoodyWoodsSpaces_0D[] = {
 0x001B,
 0x001C,
 0x001D,
 0x001E,
 0x001F,
 0x0021,
 0x0022,
 0x0023,
 0x0024,
 0x0025,
 0x0026,
 0x008E,
};

s16 WoodyWoodsSpaces_0E[] = {
 0x0039,
 0x003A,
 0x0069,
 0x006A,
 0x006B,
};

SpaceChain WoodyWoodsChains[] = {
    {ARRAY_COUNT(WoodyWoodsSpaces_00), WoodyWoodsSpaces_00},
    {ARRAY_COUNT(WoodyWoodsSpaces_01), WoodyWoodsSpaces_01},
    {ARRAY_COUNT(WoodyWoodsSpaces_02), WoodyWoodsSpaces_02},
    {ARRAY_COUNT(WoodyWoodsSpaces_03), WoodyWoodsSpaces_03},
    {ARRAY_COUNT(WoodyWoodsSpaces_04), WoodyWoodsSpaces_04},
    {ARRAY_COUNT(WoodyWoodsSpaces_05), WoodyWoodsSpaces_05},
    {ARRAY_COUNT(WoodyWoodsSpaces_06), WoodyWoodsSpaces_06},
    {ARRAY_COUNT(WoodyWoodsSpaces_07), WoodyWoodsSpaces_07},
    {ARRAY_COUNT(WoodyWoodsSpaces_08), WoodyWoodsSpaces_08},
    {ARRAY_COUNT(WoodyWoodsSpaces_09), WoodyWoodsSpaces_09},
    {ARRAY_COUNT(WoodyWoodsSpaces_0A), WoodyWoodsSpaces_0A},
    {ARRAY_COUNT(WoodyWoodsSpaces_0B), WoodyWoodsSpaces_0B},
    {ARRAY_COUNT(WoodyWoodsSpaces_0C), WoodyWoodsSpaces_0C},
    {ARRAY_COUNT(WoodyWoodsSpaces_0D), WoodyWoodsSpaces_0D},
    {ARRAY_COUNT(WoodyWoodsSpaces_0E), WoodyWoodsSpaces_0E},
};

SpaceData woody_woods_spaces[] = {
/* 0x000 */ {0x01, 0x01, 0x0000, 0x00000000,  { 210.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x001 */ {0x01, 0x02, 0x0000, 0x01000203,  { 210.0000f, 0.0000f, 130.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x002 */ {0x01, 0x09, 0x0000, 0x04040403,  { 235.0000f, 0.0000f, 120.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x003 */ {0x01, 0x01, 0x0000, 0x00000505,  { 235.0000f, 0.0000f, 150.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x004 */ {0x01, 0x06, 0x0000, 0x0B0A0000,  { 235.0000f, 0.0000f, 180.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x005 */ {0x01, 0x0C, 0x0000, 0x04040404,  { 235.0000f, 0.0000f, 90.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x006 */ {0x01, 0x07, 0x0000, 0x0D00000D,  { 235.0000f, 0.0000f, 60.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x007 */ {0x01, 0x01, 0x0000, 0x0F0F0F00,  { 235.0000f, 0.0000f, 30.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x008 */ {0x01, 0x05, 0x0000, 0x11111312,  { 210.0000f, 0.0000f, -0.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x009 */ {0x01, 0x01, 0x0000, 0x11131400,  { 185.0000f, 0.0000f, -5.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00A */ {0x01, 0x02, 0x0000, 0x00000000,  { 185.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00B */ {0x01, 0x01, 0x0000, 0x10000F11,  { 160.0000f, 0.0000f, -5.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00C */ {0x01, 0x04, 0x0000, 0x12131111,  { 130.0000f, 0.0000f, 25.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00D */ {0x01, 0x01, 0x0000, 0x00000000,  { 90.0000f, 0.0000f, -10.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00E */ {0x01, 0x01, 0x0000, 0x100F0000,  { 65.0000f, 0.0000f, -15.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00F */ {0x01, 0x01, 0x0000, 0x13121212,  { 125.0000f, 0.0000f, 50.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x010 */ {0x01, 0x0F, 0x0000, 0x00000000,  { 55.0000f, 0.0000f, -40.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x011 */ {0x01, 0x06, 0x0000, 0x0F0F0F00,  { 45.0000f, 0.0000f, -65.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x012 */ {0x01, 0x02, 0x0000, 0x11111512,  { 40.0000f, 0.0000f, -90.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x013 */ {0x01, 0x06, 0x0000, 0x11131400,  { 15.0000f, 0.0000f, -85.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x014 */ {0x01, 0x01, 0x0000, 0x00000000,  { -10.0000f, 0.0000f, -80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x015 */ {0x01, 0x01, 0x0000, 0x1D00191C,  { 160.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x016 */ {0x01, 0x01, 0x0000, 0x1D221C1C,  { -40.0000f, 0.0000f, -75.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x017 */ {0x01, 0x0C, 0x0000, 0x1D1D1D1D,  { -70.0000f, 0.0000f, -75.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x018 */ {0x01, 0x01, 0x0000, 0x261C0000,  { -100.0000f, 0.0000f, -70.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x019 */ {0x01, 0x01, 0x0000, 0x001D1D1D,  { -130.0000f, 0.0000f, -70.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01A */ {0x01, 0x01, 0x0000, 0x0000001D,  { -155.0000f, 0.0000f, -70.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01B */ {0x01, 0x01, 0x0000, 0x2E2E0000,  { -215.0000f, 0.0000f, -95.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01C */ {0x01, 0x01, 0x0000, 0x00343038,  { -230.0000f, 0.0000f, -120.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01D */ {0x01, 0x01, 0x0000, 0x35390000,  { -240.0000f, 0.0000f, -145.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01E */ {0x01, 0x06, 0x0000, 0x00000000,  { -230.0000f, 0.0000f, -170.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01F */ {0x01, 0x04, 0x0000, 0x00000000,  { -205.0000f, 0.0000f, -185.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x020 */ {0x01, 0x01, 0x0000, 0x343D2E00,  { 135.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x021 */ {0x01, 0x04, 0x0000, 0x002E0000,  { -180.0000f, 0.0000f, -180.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x022 */ {0x01, 0x04, 0x0000, 0x3F3E0000,  { -155.0000f, 0.0000f, -190.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x023 */ {0x01, 0x02, 0x0000, 0x43040404,  { -130.0000f, 0.0000f, -210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x024 */ {0x01, 0x09, 0x0000, 0x41000041,  { -105.0000f, 0.0000f, -220.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x025 */ {0x01, 0x01, 0x0000, 0x00000000,  { -80.0000f, 0.0000f, -230.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x026 */ {0x01, 0x01, 0x0000, 0x191C1E1D,  { -50.0000f, 0.0000f, -235.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x027 */ {0x01, 0x01, 0x0000, 0x201C1C1D,  { 10.0000f, 0.0000f, -235.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x028 */ {0x01, 0x0F, 0x0000, 0x00000000,  { 35.0000f, 0.0000f, -235.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x029 */ {0x01, 0x01, 0x0000, 0x00000000,  { 95.0000f, 0.0000f, -235.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02A */ {0x01, 0x01, 0x0000, 0x00000000,  { 120.0000f, 0.0000f, -235.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02B */ {0x01, 0x01, 0x0000, 0x00000000,  { 70.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02C */ {0x01, 0x06, 0x0000, 0x00000000,  { 145.0000f, 0.0000f, -225.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02D */ {0x01, 0x09, 0x0000, 0x00000000,  { 170.0000f, 0.0000f, -210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02E */ {0x01, 0x01, 0x0000, 0x00000000,  { 215.0000f, 0.0000f, -160.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02F */ {0x01, 0x01, 0x0000, 0x00000000,  { 225.0000f, 0.0000f, -130.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x030 */ {0x01, 0x01, 0x0000, 0x00000000,  { 235.0000f, 0.0000f, -80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x031 */ {0x01, 0x01, 0x0000, 0x00000000,  { 235.0000f, 0.0000f, -55.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x032 */ {0x01, 0x01, 0x0000, 0x00000000,  { 235.0000f, 0.0000f, -30.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x033 */ {0x01, 0x06, 0x0000, 0x0000F000,  { 235.0000f, 0.0000f, 0.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x034 */ {0x01, 0x01, 0x0000, 0x00000000,  { 95.0000f, 0.0000f, -125.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x035 */ {0x01, 0x01, 0x0000, 0x00F00000,  { 105.0000f, 0.0000f, -150.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x036 */ {0x01, 0x01, 0x0000, 0x00F00000,  { 110.0000f, 0.0000f, 180.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x037 */ {0x01, 0x0C, 0x0000, 0xF0000000,  { 120.0000f, 0.0000f, -175.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x038 */ {0x01, 0x01, 0x0000, 0x000000FF,  { 135.0000f, 0.0000f, -200.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x039 */ {0x01, 0x06, 0x0000, 0x00000000,  { -30.0000f, 0.0000f, -200.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03A */ {0x01, 0x05, 0x0000, 0xFFFFFF00,  { -45.0000f, 0.0000f, -175.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03B */ {0x01, 0x04, 0x0000, 0x00000000,  { -205.0000f, 0.0000f, -50.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03C */ {0x01, 0x06, 0x0000, 0x80000000,  { -220.0000f, 0.0000f, -25.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03D */ {0x01, 0x07, 0x0000, 0x0000F000,  { -225.0000f, 0.0000f, -0.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03E */ {0x01, 0x01, 0x0000, 0x00000000,  { -220.0000f, 0.0000f, 25.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03F */ {0x01, 0x04, 0x0000, 0x008F0000,  { -190.0000f, 0.0000f, 85.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x040 */ {0x01, 0x0C, 0x0000, 0x00F00000,  { -245.0000f, 0.0000f, 85.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x041 */ {0x01, 0x06, 0x0000, 0x80000000,  { 135.0000f, 0.0000f, 165.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x042 */ {0x01, 0x06, 0x0000, 0x00008FFF,  { -245.0000f, 0.0000f, 110.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x043 */ {0x01, 0x01, 0x0000, 0x00008FFF,  { -245.0000f, 0.0000f, 135.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x044 */ {0x01, 0x06, 0x0000, 0x0F0F8008,  { -240.0000f, 0.0000f, 160.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x045 */ {0x01, 0x09, 0x0000, 0x0F0F0000,  { -230.0000f, 0.0000f, 185.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x046 */ {0x01, 0x01, 0x0000, 0x08FF0000,  { -210.0000f, 0.0000f, 200.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x047 */ {0x01, 0x01, 0x0000, 0x0000FFFF,  { -185.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x048 */ {0x01, 0x02, 0x0000, 0x00000000,  { -160.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x049 */ {0x01, 0x04, 0x0000, 0x00000000,  { -165.0000f, 0.0000f, 90.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04A */ {0x01, 0x04, 0x0000, 0x00000000,  { -140.0000f, 0.0000f, 90.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04B */ {0x01, 0x01, 0x0000, 0x00000000,  { -110.0000f, 0.0000f, 95.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04C */ {0x01, 0x01, 0x0000, 0x0000FFFF,  { 160.0000f, 0.0000f, 150.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04D */ {0x01, 0x02, 0x0000, 0x00000000,  { -85.0000f, 0.0000f, 100.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04E */ {0x01, 0x01, 0x0000, 0x00000000,  { -60.0000f, 0.0000f, 105.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04F */ {0x01, 0x04, 0x0000, 0xFF800000,  { -35.0000f, 0.0000f, 145.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x050 */ {0x01, 0x01, 0x0000, 0xF0000000,  { -5.0000f, 0.0000f, 105.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x051 */ {0x01, 0x06, 0x0000, 0x0000FFF8,  { 20.0000f, 0.0000f, 90.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x052 */ {0x01, 0x01, 0x0000, 0x00000000,  { 45.0000f, 0.0000f, 75.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x053 */ {0x01, 0x01, 0x0000, 0xF000F000,  { 70.0000f, 0.0000f, 60.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x054 */ {0x01, 0x01, 0x0000, 0xF8000000,  { -35.0000f, 0.0000f, 170.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x055 */ {0x01, 0x01, 0x0000, 0x00000000,  { -35.0000f, 0.0000f, 195.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x056 */ {0x01, 0x06, 0x0000, 0x0000FFFF,  { -60.0000f, 0.0000f, 205.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x057 */ {0x01, 0x01, 0x0000, 0x00000000,  { 185.0000f, 0.0000f, 140.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x058 */ {0x01, 0x01, 0x0000, 0xF0000000,  { -85.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x059 */ {0x01, 0x01, 0x0000, 0xFF800000,  { -110.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05A */ {0x01, 0x01, 0x0000, 0xF0000000,  { -10.0000f, 0.0000f, 205.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05B */ {0x01, 0x01, 0x0000, 0x0000FFFF,  { 45.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05C */ {0x01, 0x09, 0x0000, 0x00000000,  { 115.0000f, 0.0000f, 80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05D */ {0x01, 0x02, 0x0000, 0x0F000000,  { 230.0000f, 0.0000f, -105.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05E */ {0x01, 0x03, 0x0000, 0xFFF00000,  { 260.0000f, 0.0000f, 150.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05F */ {0x01, 0x03, 0x0000, 0x80000000,  { 260.0000f, 0.0000f, -80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x060 */ {0x01, 0x03, 0x0000, 0x0000F0F8,  { 80.0000f, 0.0000f, -165.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x061 */ {0x01, 0x03, 0x0000, 0x00000000,  { -80.0000f, 0.0000f, -255.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x062 */ {0x01, 0x03, 0x0000, 0xF0000000,  { -40.0000f, 0.0000f, -100.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x063 */ {0x01, 0x03, 0x0000, 0x000F8000,  { -110.0000f, 0.0000f, 70.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x064 */ {0x01, 0x03, 0x0000, 0x00F00000,  { -195.0000f, 0.0000f, 175.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x065 */ {0x01, 0x03, 0x0000, 0x0000F0F8,  { 185.0000f, 0.0000f, -30.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x066 */ {0x01, 0x00, 0x0000, 0x00000000,  { 240.0000f, 0.0000f, 230.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x067 */ {0x01, 0x08, 0x0000, 0xF000F000,  { 110.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, JunctionDecision, &WW_Space_67 },
/* 0x068 */ {0x01, 0x03, 0x0000, 0xFF800000,  { 75.0000f, 0.0000f, -110.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x069 */ {0x01, 0x03, 0x0000, 0x00000000,  { -65.0000f, 0.0000f, -150.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06A */ {0x01, 0x03, 0x0000, 0x0000F000,  { -85.0000f, 0.0000f, -120.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06B */ {0x01, 0x03, 0x0000, 0x00000000,  { -95.0000f, 0.0000f, -100.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06C */ {0x01, 0x08, 0x0000, 0xF0F80000,  { -210.0000f, 0.0000f, 70.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06D */ {0x01, 0x03, 0x0000, 0xFF800000,  { 267.5000f, 0.0000f, 60.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06E */ {0x01, 0x03, 0x0000, 0x80000000,  { 277.5000f, 0.0000f, 90.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06F */ {0x01, 0x03, 0x0000, 0x000000F0,  { 142.5000f, 0.0000f, 125.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x070 */ {0x01, 0x03, 0x0000, 0x00000000,  { 125.0000f, 0.0000f, 95.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x071 */ {0x01, 0x0D, 0x0000, 0xF000F000,  { 17.5000f, 0.0000f, 207.5000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x072 */ {0x01, 0x08, 0x0000, 0x00F00000,  { 90.0000f, 0.0000f, 50.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x073 */ {0x01, 0x03, 0x0000, 0x00000000,  { -135.0000f, 0.0000f, 210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x074 */ {0x01, 0x08, 0x0000, 0xF000F00F,  { -35.0000f, 0.0000f, 120.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x075 */ {0x01, 0x03, 0x0000, 0x00000000,  { 17.5000f, 0.0000f, 180.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x076 */ {0x01, 0x03, 0x0000, 0x08F8F000,  { 220.0000f, 0.0000f, -210.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x077 */ {0x01, 0x03, 0x0000, 0x00F00000,  { -255.0000f, 0.0000f, -0.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x078 */ {0x01, 0x03, 0x0000, 0x00000000,  { -267.5000f, 0.0000f, 30.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x079 */ {0x01, 0x03, 0x0000, 0x000000F8,  { 125.0000f, 0.0000f, -35.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07A */ {0x01, 0x03, 0x0000, 0x00FF0FF0,  { -35.0000f, 0.0000f, 80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07B */ {0x01, 0x03, 0x0000, 0x00000000,  { -180.0000f, 0.0000f, -105.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07C */ {0x01, 0x03, 0x0000, 0x00000000,  { -157.5000f, 0.0000f, 35.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07D */ {0x01, 0x03, 0x0000, 0x00000000,  { 65.0000f, 0.0000f, -265.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07E */ {0x01, 0x03, 0x0000, 0x0000F000,  { -200.0000f, 0.0000f, -245.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07F */ {0x01, 0x03, 0x0000, 0x00000000,  { -135.0000f, 0.0000f, 185.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x080 */ {0x01, 0x03, 0x0000, 0x08F00000,  { 60.0000f, 0.0000f, -125.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x081 */ {0x01, 0x03, 0x0000, 0x08F00000,  { -15.0000f, 0.0000f, 80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x082 */ {0x01, 0x03, 0x0000, 0x000000F0,  { -160.0000f, 0.0000f, -105.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x083 */ {0x01, 0x03, 0x0000, 0x00000000,  { 145.0000f, 0.0000f, -35.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x084 */ {0x01, 0x03, 0x0000, 0x00000000,  { -127.5000f, 75.0000f, 50.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x085 */ {0x01, 0x03, 0x0000, 0xF00F0000,  { -177.5000f, 75.0000f, 50.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x086 */ {0x01, 0x03, 0x0000, 0x00000000,  { -225.0000f, 75.0000f, -230.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x087 */ {0x01, 0x03, 0x0000, 0x00000000,  { -165.0000f, 75.0000f, -230.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x088 */ {0x01, 0x03, 0x0000, 0x00000FFF,  { 150.0000f, 0.0000f, 135.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x089 */ {0x01, 0x03, 0x0000, 0x00000000,  { -157.5000f, 0.0000f, 62.5000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x08A */ {0x01, 0x03, 0x0000, 0xF00F0000,  { -200.0000f, 0.0000f, -217.5000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x08B */ {0x01, 0x08, 0x0000, 0x00000000,  { 125.0000f, 0.0000f, -0.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x08C */ {0x01, 0x0D, 0x0000, 0xF0000000,  { 195.0000f, 0.0000f, -190.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x08D */ {0x01, 0x03, 0x0000, 0x0000FFF0,  { 65.0000f, 0.0000f, -235.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x08E */ {0x01, 0x08, 0x0000, 0x00000000,  { -25.0000f, 0.0000f, -240.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x08F */ {0x01, 0x08, 0x0000, 0x0F00F000,  { -190.0000f, 0.0000f, -75.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
};

//decision tree nodes for woody woods first junction
//TODO: is this actually enough nodes?
DecisionTreeNonLeafNode WoodyWoodsJunction0Nodes[] = {
    {
        .type = 0x02,
        .node_data1.data = 0x00000080,
        .node_data2.data = 0x1B54233C,
        .isPointer = 0,
    },

    {
        .type = 0x00,
        .node_data1.data = 0x00000000,
        .node_data2.data = 0x0B54233C,
        .isPointer = 0,
    },
    {
        .type = 0x02,
        .node_data1.data = 0x00,
        .node_data2.data = 0x1B54233C,
        .isPointer = 0,
    },
    {
        .type = 0x00,
        .node_data1.data = 0x00,
        .node_data2.data = 0x064C9932,
        .isPointer = 0,
    }
};

DoubleJunction WW_Space_67 = {
    .spaceABS = {
    0x2B, //space id 0x002B (left at junction)
    0x36, //space id 0x0036 (right at junction)
    },
    .junctionNodeData = WoodyWoodsJunction0Nodes
};