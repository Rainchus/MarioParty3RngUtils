#include "mp3.h"
#include "util.h"

SpaceData creepy_cavern_spaces[] = {
/* 0x000 */ {0x01, 0x01, 0x0000, 0x00000000,  { 210.6470f, 0.0000f, 211.8305f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x001 */ {0x01, 0x01, 0x0000, 0x01000203,  { 50.0000f, 0.0000f, 50.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x002 */ {0x01, 0x04, 0x0000, 0x04040403,  { 50.0000f, 0.0000f, 20.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x003 */ {0x01, 0x03, 0x0000, 0x00000505,  { 43.8823f, 0.0000f, -95.4920f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x004 */ {0x01, 0x05, 0x0000, 0x0B0A0000,  { 39.0294f, 0.0000f, -120.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x005 */ {0x01, 0x04, 0x0000, 0x04040404,  { 34.2057f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x006 */ {0x01, 0x01, 0x0000, 0x0D00000D,  { 40.0000f, 0.0000f, -180.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x007 */ {0x01, 0x01, 0x0000, 0x0F0F0F00,  { 57.0885f, 0.0000f, -205.1940f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x008 */ {0x01, 0x06, 0x0000, 0x11111312,  { 75.0000f, 0.0000f, -227.2540f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x009 */ {0x01, 0x02, 0x0000, 0x11131400,  { 100.0000f, 0.0000f, -232.5180f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00A */ {0x01, 0x0F, 0x0000, 0x00000000,  { 127.4120f, 0.0000f, -232.0600f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00B */ {0x01, 0x01, 0x0000, 0x10000F11,  { 186.7645f, 0.0000f, 220.0000f}, { 0.1150f, 0.1000f, 0.1150f }, 0x00000000, 0x0000 },
/* 0x00C */ {0x01, 0x01, 0x0000, 0x12131111,  { 155.0000f, 0.0000f, -228.6270f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00D */ {0x01, 0x01, 0x0000, 0x00000000,  { 177.4120f, 0.0000f, -214.9655f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00E */ {0x01, 0x01, 0x0000, 0x100F0000,  { 198.7060f, 0.0000f, -196.3390f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x00F */ {0x01, 0x01, 0x0000, 0x13121212,  { 210.0000f, 0.0000f, -173.3645f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x010 */ {0x01, 0x04, 0x0000, 0x00000000,  { 215.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x011 */ {0x01, 0x01, 0x0000, 0x0F0F0F00,  { 177.5300f, 0.0000f, -120.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x012 */ {0x01, 0x02, 0x0000, 0x11111512,  { 183.8530f, 0.0000f, -93.2380f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x013 */ {0x01, 0x01, 0x0000, 0x11131400,  { 180.0000f, 0.0000f, -66.8305f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x014 */ {0x01, 0x06, 0x0000, 0x00000000,  { 167.7355f, 0.0000f, -42.7117f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x015 */ {0x01, 0x01, 0x0000, 0x1D00191C,  { 160.0000f, 0.0000f, -10.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x016 */ {0x01, 0x02, 0x0000, 0x1D221C1C,  { 160.0000f, 0.0000f, 221.8305f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x017 */ {0x01, 0x01, 0x0000, 0x1D1D1D1D,  { 176.7650f, 0.0000f, 13.6603f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x018 */ {0x01, 0x01, 0x0000, 0x261C0000,  { 204.8240f, 0.0000f, 53.8910f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x019 */ {0x01, 0x01, 0x0000, 0x001D1D1D,  { 210.0000f, 0.0000f, 85.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01A */ {0x01, 0x04, 0x0000, 0x0000001D,  { 210.0000f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01B */ {0x01, 0x01, 0x0000, 0x2E2E0000,  { 197.5880f, 0.0000f, 146.3385f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01C */ {0x01, 0x0C, 0x0000, 0x00343038,  { 213.0590f, 0.0000f, 174.5080f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01D */ {0x01, 0x01, 0x0000, 0x35390000,  { 160.0000f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01E */ {0x01, 0x04, 0x0000, 0x00000000,  { 120.0000f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x01F */ {0x01, 0x01, 0x0000, 0x00000000,  { 92.2645f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x020 */ {0x01, 0x01, 0x0000, 0x343D2E00,  { 65.7940f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x021 */ {0x01, 0x07, 0x0000, 0x002E0000,  { 130.0000f, 0.0000f, 221.3730f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x022 */ {0x01, 0x01, 0x0000, 0x3F3E0000,  { 80.0000f, 0.0000f, 0.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x023 */ {0x01, 0x02, 0x0000, 0x43040404,  { 105.0000f, 0.0000f, -7.7117f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x024 */ {0x01, 0x09, 0x0000, 0x41000041,  { 130.0000f, 0.0000f, -10.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x025 */ {0x01, 0x04, 0x0000, 0x00000000,  { 190.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x026 */ {0x01, 0x0C, 0x0000, 0x191C1E1D,  { 145.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x027 */ {0x01, 0x09, 0x0000, 0x201C1C1D,  { 105.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x028 */ {0x01, 0x01, 0x0000, 0x00000000,  { 81.4560f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x029 */ {0x01, 0x06, 0x0000, 0x00000000,  { 57.2645f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02A */ {0x01, 0x06, 0x0000, 0x00000000,  { 30.0000f, 0.0000f, 163.4310f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02B */ {0x01, 0x01, 0x0000, 0x00000000,  { -50.0000f, 0.0000f, 200.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02C */ {0x01, 0x01, 0x0000, 0x00000000,  { 100.1760f, 0.0000f, 217.7460f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02D */ {0x01, 0x06, 0x0000, 0x00000000,  { -76.4410f, 0.0000f, 206.5665f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02E */ {0x01, 0x01, 0x0000, 0x00000000,  { -102.9120f, 0.0000f, 208.8555f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x02F */ {0x01, 0x02, 0x0000, 0x00000000,  { -130.0000f, 0.0000f, 208.3975f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x030 */ {0x01, 0x09, 0x0000, 0x00000000,  { -156.7645f, 0.0000f, 207.9400f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x031 */ {0x01, 0x01, 0x0000, 0x00000000,  { -180.0000f, 0.0000f, 201.8305f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x032 */ {0x01, 0x01, 0x0000, 0x00000000,  { -207.9120f, 0.0000f, 191.3735f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x033 */ {0x01, 0x01, 0x0000, 0x0000F000,  { -222.5880f, 0.0000f, 161.8305f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x034 */ {0x01, 0x01, 0x0000, 0x00000000,  { -227.7645f, 0.0000f, 134.5080f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x035 */ {0x01, 0x04, 0x0000, 0x00F00000,  { -219.5295f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x036 */ {0x01, 0x01, 0x0000, 0x00F00000,  { -207.4120f, 0.0000f, 67.1855f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x037 */ {0x01, 0x01, 0x0000, 0xF0000000,  { 75.0000f, 0.0000f, 195.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x038 */ {0x01, 0x01, 0x0000, 0x000000FF,  { -216.1180f, 0.0000f, 40.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x039 */ {0x01, 0x06, 0x0000, 0x00000000,  { -220.0000f, 0.0000f, 13.6613f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03A */ {0x01, 0x01, 0x0000, 0xFFFFFF00,  { -210.0000f, 0.0000f, -10.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03B */ {0x01, 0x06, 0x0000, 0x00000000,  { -190.0000f, 0.0000f, -30.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03C */ {0x01, 0x02, 0x0000, 0x80000000,  { -210.0000f, 0.0000f, -48.1690f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03D */ {0x01, 0x01, 0x0000, 0x0000F000,  { -230.0000f, 0.0000f, -84.5420f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03E */ {0x01, 0x01, 0x0000, 0x00000000,  { -243.8530f, 0.0000f, -103.5930f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x03F */ {0x01, 0x01, 0x0000, 0x008F0000,  { -234.8525f, 0.0000f, -125.8815f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x040 */ {0x01, 0x04, 0x0000, 0x00F00000,  { -225.8235f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x041 */ {0x01, 0x04, 0x0000, 0x80000000,  { -200.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x042 */ {0x01, 0x01, 0x0000, 0x00008FFF,  { 60.0000f, 0.0000f, 170.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x043 */ {0x01, 0x01, 0x0000, 0x00008FFF,  { -179.2950f, 0.0000f, -177.1855f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x044 */ {0x01, 0x06, 0x0000, 0x0F0F8008,  { -180.0000f, 0.0000f, -204.0505f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x045 */ {0x01, 0x07, 0x0000, 0x0F0F0000,  { -160.0000f, 0.0000f, -226.7965f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x046 */ {0x01, 0x01, 0x0000, 0x08FF0000,  { -135.1470f, 0.0000f, -240.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x047 */ {0x01, 0x09, 0x0000, 0x0000FFFF,  { -110.0000f, 0.0000f, -246.7965f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x048 */ {0x01, 0x01, 0x0000, 0x00000000,  { -80.0000f, 0.0000f, -247.7115f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x049 */ {0x01, 0x01, 0x0000, 0x00000000,  { -50.0000f, 0.0000f, -208.8560f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04A */ {0x01, 0x01, 0x0000, 0x00000000,  { -50.0000f, 0.0000f, -177.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04B */ {0x01, 0x06, 0x0000, 0x00000000,  { -50.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04C */ {0x01, 0x04, 0x0000, 0x0000FFFF,  { -50.0000f, 0.0000f, -120.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04D */ {0x01, 0x04, 0x0000, 0x00000000,  { 40.0000f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04E */ {0x01, 0x0F, 0x0000, 0x00000000,  { -50.0000f, 0.0000f, 20.0009f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x04F */ {0x01, 0x03, 0x0000, 0xFF800000,  { -50.0000f, 0.0000f, 50.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x050 */ {0x01, 0x09, 0x0000, 0xF0000000,  { -50.0000f, 0.0000f, 80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x051 */ {0x01, 0x04, 0x0000, 0x0000FFF8,  { -50.0000f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x052 */ {0x01, 0x01, 0x0000, 0x00000000,  { -50.0000f, 0.0000f, 140.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x053 */ {0x01, 0x01, 0x0000, 0xF000F000,  { -50.0000f, 0.0000f, 170.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x054 */ {0x01, 0x01, 0x0000, 0xF8000000,  { -148.3825f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x055 */ {0x01, 0x0C, 0x0000, 0x00000000,  { -125.0000f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x056 */ {0x01, 0x01, 0x0000, 0x0000FFFF,  { -100.0000f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x057 */ {0x01, 0x04, 0x0000, 0x00000000,  { -75.0000f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x058 */ {0x01, 0x06, 0x0000, 0xF0000000,  { 40.0000f, 0.0000f, 80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x059 */ {0x01, 0x01, 0x0000, 0xFF800000,  { -74.8530f, 0.0000f, -87.0250f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05A */ {0x01, 0x01, 0x0000, 0xF0000000,  { -98.0590f, 0.0000f, -77.2540f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05B */ {0x01, 0x0C, 0x0000, 0x0000FFFF,  { -120.6470f, 0.0000f, -67.2540f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05C */ {0x01, 0x01, 0x0000, 0x00000000,  { -143.8530f, 0.0000f, -59.0845f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05D */ {0x01, 0x01, 0x0000, 0x0F000000,  { -167.0885f, 0.0000f, -45.9151f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05E */ {0x01, 0x01, 0x0000, 0xFFF00000,  { -125.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x05F */ {0x01, 0x01, 0x0000, 0x80000000,  { -100.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x060 */ {0x01, 0x04, 0x0000, 0x0000F0F8,  { -75.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x061 */ {0x01, 0x05, 0x0000, 0x00000000,  { -19.8238f, 0.0000f, -233.2020f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x062 */ {0x01, 0x03, 0x0000, 0xF0000000,  { -5.1763f, 0.0000f, -43.1356f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x063 */ {0x01, 0x03, 0x0000, 0x000F8000,  { -85.3525f, 0.0000f, 46.9680f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x064 */ {0x01, 0x03, 0x0000, 0x00F00000,  { 188.7060f, 0.0000f, 195.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x065 */ {0x01, 0x03, 0x0000, 0x0000F0F8,  { 90.0000f, 0.0000f, 85.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x066 */ {0x01, 0x03, 0x0000, 0x00000000,  { 80.0000f, 0.0000f, -171.7150f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x067 */ {0x01, 0x03, 0x0000, 0xF000F000,  { 160.0000f, 0.0000f, -80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x068 */ {0x01, 0x03, 0x0000, 0xFF800000,  { -80.0000f, 0.0000f, -273.1695f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x069 */ {0x01, 0x03, 0x0000, 0x00000000,  { -150.0000f, 0.0000f, -85.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06A */ {0x01, 0x03, 0x0000, 0x0000F000,  { -100.8815f, 0.0000f, 85.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06B */ {0x01, 0x03, 0x0000, 0x00000000,  { -175.0000f, 0.0000f, 175.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06C */ {0x01, 0x00, 0x0000, 0xF0F80000,  { 240.0000f, 0.0000f, 230.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06D */ {0x01, 0x03, 0x0000, 0xFF800000,  { 130.0000f, 0.0000f, 188.6270f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06E */ {0x01, 0x03, 0x0000, 0x80000000,  { 160.0000f, 0.0000f, 80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x06F */ {0x01, 0x03, 0x0000, 0x000000F0,  { 170.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x070 */ {0x01, 0x0D, 0x0000, 0x00000000,  { 125.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x071 */ {0x01, 0x03, 0x0000, 0xF000F000,  { 125.0000f, 0.0000f, -180.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x072 */ {0x01, 0x03, 0x0000, 0x00F00000,  { 145.0000f, 0.0000f, -180.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x073 */ {0x01, 0x03, 0x0000, 0x00000000,  { 10.0000f, 0.0000f, 170.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x074 */ {0x01, 0x03, 0x0000, 0xF000F00F,  { -20.0000f, 0.0000f, 190.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x075 */ {0x01, 0x03, 0x0000, 0x00000000,  { -5.0000f, 0.0000f, 183.5460f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x076 */ {0x01, 0x0D, 0x0000, 0x08F8F000,  { -216.1180f, 0.0000f, -69.0845f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x077 */ {0x01, 0x03, 0x0000, 0x00F00000,  { -190.9415f, 0.0000f, -85.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x078 */ {0x01, 0x03, 0x0000, 0x00000000,  { 160.0000f, 0.0000f, 190.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x079 */ {0x01, 0x03, 0x0000, 0x000000F8,  { -163.2350f, 0.0000f, -258.6270f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07A */ {0x01, 0x03, 0x0000, 0x00FF0FF0,  { -135.3410f, 0.0000f, -269.4500f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07B */ {0x01, 0x03, 0x0000, 0x00000000,  { -60.3525f, 0.0000f, -250.4575f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07C */ {0x01, 0x03, 0x0000, 0x00000000,  { -50.0000f, 0.0000f, -100.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07D */ {0x01, 0x03, 0x0000, 0x00000000,  { -197.5885f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07E */ {0x01, 0x0D, 0x0000, 0x0000F000,  { -172.0880f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x07F */ {0x01, 0x03, 0x0000, 0x00000000,  { -170.1470f, 0.0000f, 80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x080 */ {0x01, 0x03, 0x0000, 0x08F00000,  { -147.0880f, 0.0000f, 80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x081 */ {0x01, 0x03, 0x0000, 0x08F00000,  { -50.0000f, 0.0000f, -7.3215f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x082 */ {0x01, 0x03, 0x0000, 0x000000F0,  { -180.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x083 */ {0x01, 0x03, 0x0000, 0x00000000,  { 55.1765f, 0.0000f, 152.8145f}, { 0.1000f, 0.1000f, 0.1000f }, JunctionDecision, &CC_Space_83 },
/* 0x084 */ {0x01, 0x0D, 0x0000, 0x00000000,  { -150.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x085 */ {0x01, 0x03, 0x0000, 0xF00F0000,  { -150.0000f, 0.0000f, -180.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x086 */ {0x01, 0x03, 0x0000, 0x00000000,  { -125.0000f, 0.0000f, -180.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x087 */ {0x01, 0x03, 0x0000, 0x00000000,  { -5.9058f, 0.0000f, -225.8230f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x088 */ {0x01, 0x03, 0x0000, 0x00000FFF,  { 20.0000f, 0.0000f, -200.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x089 */ {0x01, 0x03, 0x0000, 0x00000000,  { 12.4587f, 0.0000f, -206.0540f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x08A */ {0x01, 0x03, 0x0000, 0xF00F0000,  { -50.0000f, 0.0000f, -67.0495f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x08B */ {0x01, 0x03, 0x0000, 0x00000000,  { -50.0000f, 0.0000f, -34.0985f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x08C */ {0x01, 0x03, 0x0000, 0xF0000000,  { 44.4674f, 0.0000f, -67.0495f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x08D */ {0x01, 0x03, 0x0000, 0x0000FFF0,  { 45.7615f, 0.0000f, -38.6750f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x08E */ {0x01, 0x03, 0x0000, 0x00000000,  { 50.0000f, 0.0000f, -4.5080f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x08F */ {0x01, 0x03, 0x0000, 0x0F00F000,  { -340.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x090 */ {0x01, 0x03, 0x0000, 0x00000000,  { 340.0000f, 0.0000f, -147.7120f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x091 */ {0x01, 0x03, 0x0000, 0xF0000000,  { -340.0000f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x092 */ {0x01, 0x03, 0x0000, 0x0000F000,  { 340.0000f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x093 */ {0x01, 0x0D, 0x0000, 0x00000000,  { 190.4705f, 0.0000f, 32.2889f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x094 */ {0x01, 0x03, 0x0000, 0x00F00000,  { 220.0000f, 0.0000f, 16.7955f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x095 */ {0x01, 0x03, 0x0000, 0x00000000,  { 190.0000f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x096 */ {0x01, 0x0D, 0x0000, 0xF0000000,  { 140.0000f, 0.0000f, 112.2880f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
/* 0x097 */ {0x01, 0x03, 0x0000, 0x0000F000,  { 140.0000f, 0.0000f, 80.0000f}, { 0.1000f, 0.1000f, 0.1000f }, 0x00000000, 0x0000 },
};

s16 CreepyCavernSpaces_00[] = {
 0x006C,
};

s16 CreepyCavernSpaces_01[] = {
 0x001B,
 0x001C,
 0x0000,
 0x000B,
 0x0016,
 0x0021,
 0x002C,
 0x0037,
 0x0042,
 0x0083,
};

s16 CreepyCavernSpaces_02[] = {
 0x001D,
 0x0096,
 0x001E,
 0x001F,
 0x0020,
};

s16 CreepyCavernSpaces_03[] = {
 0x004D,
 0x0058,
 0x0001,
 0x0002,
 0x008E,
};

s16 CreepyCavernSpaces_04[] = {
 0x0022,
 0x0023,
 0x0024,
 0x0015,
 0x0017,
 0x0093,
 0x0018,
 0x0019,
 0x001A,
 0x0095,
};

s16 CreepyCavernSpaces_05[] = {
 0x0026,
 0x0070,
 0x0027,
 0x0028,
 0x0029,
};

s16 CreepyCavernSpaces_06[] = {
 0x0011,
 0x0012,
 0x0013,
 0x0014,
};

s16 CreepyCavernSpaces_07[] = {
 0x002A,
 0x0073,
 0x0075,
 0x0074,
};

s16 CreepyCavernSpaces_08[] = {
 0x007E,
 0x0054,
 0x0055,
 0x0056,
 0x0057,
};

s16 CreepyCavernSpaces_09[] = {
 0x0036,
 0x0038,
 0x0039,
 0x003A,
 0x003B,
 0x003C,
 0x0076,
 0x003D,
 0x003E,
 0x003F,
 0x0040,
 0x0041,
 0x0082,
};

s16 CreepyCavernSpaces_0A[] = {
 0x0084,
 0x005E,
 0x005F,
 0x0060,
};

s16 CreepyCavernSpaces_0B[] = {
 0x0043,
 0x0044,
 0x0045,
 0x0046,
 0x0047,
 0x0048,
 0x007B,
};

s16 CreepyCavernSpaces_0C[] = {
 0x0059,
 0x005A,
 0x005B,
 0x005C,
 0x005D,
};

s16 CreepyCavernSpaces_0D[] = {
 0x0061,
 0x0087,
 0x0089,
 0x0088,
};

s16 CreepyCavernSpaces_0E[] = {
 0x008D,
 0x008C,
 0x0003,
 0x0004,
 0x0005,
 0x0006,
 0x0007,
 0x0008,
 0x0009,
 0x000A,
 0x000C,
 0x000D,
 0x000E,
 0x000F,
 0x0010,
 0x0025,
 0x006F,
};

s16 CreepyCavernSpaces_0F[] = {
 0x0049,
 0x004A,
 0x004B,
 0x004C,
 0x007C,
 0x008A,
 0x008B,
};

s16 CreepyCavernSpaces_10[] = {
 0x0081,
 0x004E,
 0x004F,
 0x0050,
 0x0051,
 0x0052,
 0x0053,
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
 0x007D,
};

s16 CreepyCavernSpaces_11[] = {
};

SpaceChain CreepyCavernChains[] = {
    {ARRAY_COUNT(CreepyCavernSpaces_00), CreepyCavernSpaces_00},
    {ARRAY_COUNT(CreepyCavernSpaces_01), CreepyCavernSpaces_01},
    {ARRAY_COUNT(CreepyCavernSpaces_02), CreepyCavernSpaces_02},
    {ARRAY_COUNT(CreepyCavernSpaces_03), CreepyCavernSpaces_03},
    {ARRAY_COUNT(CreepyCavernSpaces_04), CreepyCavernSpaces_04},
    {ARRAY_COUNT(CreepyCavernSpaces_05), CreepyCavernSpaces_05},
    {ARRAY_COUNT(CreepyCavernSpaces_06), CreepyCavernSpaces_06},
    {ARRAY_COUNT(CreepyCavernSpaces_07), CreepyCavernSpaces_07},
    {ARRAY_COUNT(CreepyCavernSpaces_08), CreepyCavernSpaces_08},
    {ARRAY_COUNT(CreepyCavernSpaces_09), CreepyCavernSpaces_09},
    {ARRAY_COUNT(CreepyCavernSpaces_0A), CreepyCavernSpaces_0A},
    {ARRAY_COUNT(CreepyCavernSpaces_0B), CreepyCavernSpaces_0B},
    {ARRAY_COUNT(CreepyCavernSpaces_0C), CreepyCavernSpaces_0C},
    {ARRAY_COUNT(CreepyCavernSpaces_0D), CreepyCavernSpaces_0D},
    {ARRAY_COUNT(CreepyCavernSpaces_0E), CreepyCavernSpaces_0E},
    {ARRAY_COUNT(CreepyCavernSpaces_0F), CreepyCavernSpaces_0F},
    {ARRAY_COUNT(CreepyCavernSpaces_10), CreepyCavernSpaces_10},
    {ARRAY_COUNT(CreepyCavernSpaces_11), CreepyCavernSpaces_11},
};

s32 func_80108798(void) {
    s32 var_a1;
    s32 itemID;
    s32 i;

    for (var_a1 = 1, i = 0; i < 3; i++) {
        itemID = gPlayers[gGameStatus.curPlayerIndex].items[i];
        switch (gGameStatus.D_800CD096_s16[2][0]) {
        case 0:
            itemID ^= 1;
            var_a1 &= -(itemID != 0);
            break;
        case 1:
            var_a1 &= -(itemID != 0);
            break;
        case 2:
            itemID ^= 2;
            var_a1 &= -(itemID != 0);
            break;
        default:
            break;
        }
    }
    return var_a1;
}

//TODO: fix the node data

DecisionTreeNonLeafNode CreepyCavernJunction5Nodes[] = {
    {
        .type = 0x03,
        .node_data1.data = 0x00000001,
        .node_data2.data = 0x0B54233C,
        .isPointer = 0,
    },
    {
        .type = 0x00,
        .node_data1.data = 0x00000000,
        .node_data2.data = 0x1C96A33C,
        .isPointer = 0,
    },
};

DecisionTreeNonLeafNode CreepyCavernJunction4Nodes[] = {
    {
        .type = 0x03,
        .node_data1.data = 0x00000008,
        .node_data2.data = 0x1B54233C,
        .isPointer = 0,
    },
    {
        .type = 0x00,
        .node_data1.data = 0x00000000,
        .node_data2.data = 0x0C96A33C,
        .isPointer = 0,
    },
};

DecisionTreeNonLeafNode CreepyCavernJunction3Nodes[] = {
    {
        .type = 0x03,
        .node_data1.data = 0x00000001,
        .node_data2.data = 0x1C96A33C,
        .isPointer = 1,
    },
    {
        .type = 0x00,
        .node_data1.data = 0x00000000,
        .node_data2.data = 0x0C96A33C,
        .isPointer = 1,
    },
};

DecisionTreeNonLeafNode CreepyCavernJunction1Nodes[] = {
    {
        .type = 0x02,
        .node_data1.data = 0x000000F0,
        .node_data2.data = 0x1BF6A33C,
        .isPointer = 0,
    },
    {
        .type = 0x02,
        .node_data1.data = 0x00000003,
        .node_data2.data = 0x0BF6A33C,
        .isPointer = 0,
    },
    {
        .type = 0x04,
        .node_data1.data = 0x00000001,
        .node_data2.node_data = CreepyCavernJunction4Nodes, //8011D2C0
        .isPointer = 0,
    },
    {
        .type = 0x06,
        .node_data1.func = func_80108798,
        .node_data2.data = 0x0BF6A33C,
        .isPointer = 0,
    },
    {
        .type = 0x04,
        .node_data1.data = 0x00300000,
        .node_data2.data = 0x0BF6A33C, //8011D2D8
        .isPointer = 0,
    },
    {
        .type = 0x00,
        .node_data1.data = 0x00000000,
        .node_data2.data = 0x1C96A33C,
        .isPointer = 0,
    },
};

DecisionTreeNonLeafNode CreepyCavernJunction2Nodes[] = {
    {
        .type = 0x04,
        .node_data1.data = 0x00300000,
        .node_data2.node_data = CreepyCavernJunction1Nodes, //8011D2F0
        .isPointer = 0,
    },
    {
        .type = 0x03,
        .node_data1.data = 0x00000001,
        .node_data2.data = 0x1C96A33C,
        .isPointer = 0,
    },
    // {
    //     .type = 0x08,
    //     .node_data1.data = 0x00000001,
    //     .node_data2.data = 0x1B54233C,
    //     .isPointer = 0,
    // },
};

DecisionTreeNonLeafNode CreepyCavernJunction0Nodes[] = {
    {
        .type = 0x08,
        .node_data1.data = 0x00000001,
        .node_data2.node_data = CreepyCavernJunction1Nodes, //8011D2F0
        .isPointer = 0,
    },
    {
        .type = 0x02,
        .node_data1.data = 0x00000001,
        .node_data2.node_data = CreepyCavernJunction2Nodes, //8011D350
        .isPointer = 0,
    },
    {
        .type = 0x02,
        .node_data1.data = 0x00000002,
        .node_data2.node_data = CreepyCavernJunction3Nodes, //8011D374
        .isPointer = 0,
    },
    {
        .type = 0x02,
        .node_data1.data = 0x0000000C,
        .node_data2.node_data = CreepyCavernJunction3Nodes, //8011D38C
        .isPointer = 0,
    },
};

DoubleJunction CC_Space_83 = {
    .spaceABS = {
    0x4D, //space id 0x002A (up at junction)
    0x2A, //space id 0x002A (left at junction)
    },
    .junctionNodeData = CreepyCavernJunction0Nodes
};