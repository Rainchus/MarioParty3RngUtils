#include <stdio.h>
#include <string.h>
#include "../include/mp3.h"

// typedef struct playerMain {
// /* 0x00 */ u8  unk_00;
// /* 0x01 */ u8  cpu_difficulty;
// /* 0x02 */ u8  controller_port_index;
// /* 0x03 */ u8  characterID;
// /* 0x04 */ u8  flags1; //value & 1 == Player is CPU
// /* 0x05 */ char unk_05;
// /* 0x06 */ s16 extraMinigameCoins; //extra coins collected in minigames
// /* 0x08 */ s16 minigameCoins; //coins for winning current minigame
// /* 0x0A */ s16 coins; //referenced as u16 and s16 (usually if u16 it's casted to s16)
// /* 0x0C */ char unk_0C[2];
// /* 0x0E */ s8  stars;
// /* 0x0F */ u8  chainIndexCur;
// /* 0x10 */ u8  spaceIndexCur;
// /* 0x11 */ u8  chainIndexNext;
// /* 0x12 */ u8  spaceIndexNext;
// /* 0x13 */ u8  unk_13; //(Chain Index?)
// /* 0x14 */ u8  unk_14; //(Space Index?)
// /* 0x15 */ u8  chainIndexPrevious;
// /* 0x16 */ u8  spaceIndexPrevious;
// /* 0x17 */ u8  flags2;
// /* 0x18 */ u8  items[3];
// /* 0x1B */ u8  bowser_suit_flags;
// /* 0x1C */ u8  turn_status; //space type landed on (blue, red, etc.)
// /* 0x1D */ s8 	playerIndex;
// /* 0x1E */ char unk_1E[2]; //likely padding
// /* 0x20 */ void* unk_20;
// /* 0x24	*/ void* player_obj; //ptr to struct 0x48 in size (things like model position, rotation, etc.)
// /* 0x28 */ s16 minigameCoinsTotal; //for minigame star
// /* 0x2A */ s16 coinsPeak; //most coins held at once for coin star
// /* 0x2C */ s8 happeningSpacesLandedOn;
// /* 0x2D */ s8 redSpacesLandedOn;
// /* 0x2E */ s8 blueSpacesLandedOn;
// /* 0x2F */ s8 chanceSpacesLandedOn;
// /* 0x30 */ s8 bowserSpacesLandedOn;
// /* 0x31 */ s8 battleSpacesLandedOn;
// /* 0x32 */ s8 itemSpacesLandedOn;
// /* 0x33 */ s8 bankSpacesLandedOn;
// /* 0x34 */ s8 gameGuySpacesLandedOn;
// /* 0x35 */ char unk_35[3]; //likely padding
// } Player; //sizeof 0x38

s32 func_800EB184(u16, u16); //GetSpaceIndex
s32 func_80108918_351788(s16*);

typedef struct unkStruct {
    s8 unk0;
    s8 curPlayerIndex;
    char unk2[0x32];
    s16 unk33;
} unkStruct;

extern unkStruct D_800CD066;

// D_8011C368_3651D8
s32 D_8011C368_3651D8[] = {
    0x00000001,
    0x00020003,
    0x00040006,
    0x00050007
};

// D_8011C378_3651E8
s32 D_8011C378_3651E8[] = {
    0x00000001,
    0x00020003,
    0x00040006,
    0x00050007
};

// D_8011C388_3651F8
s32 D_8011C388_3651F8[] = {
    0x00010002,
    0x00030004,
    0x00060005,
    0x00070000
};

// D_8011C398_365208
s32 D_8011C398_365208[] = {
    0x00040006,
    0x00010005,
    0x00070003,
    0x00000002
};

s32 D_8011C3A8_365218[] = {
    0x00060001,
    0x00050007,
    0x00030004,
    0x00000002
};

// D_8011C3B8_365228
s32 D_8011C3B8_365228[] = {
    0x00060007,
    0x00010005,
    0x00030000,
    0x00040002
};

// D_8011C3C8_365238
s32 D_8011C3C8_365238[] = {
    0x00010006,
    0x00050007,
    0x00030004,
    0x00000002
};

s16 D_8011C358_3651C8[] = {
    6, 7, 8, 9, 10, 11, 12, 13
};

s16 D_800CD096 = 3; //mirage Star Space

void SetSpinyDesertMirageStar(void) {
    D_800CD096 = func_800EEF80_102BA0(6.0f);
}

s32 func_80108918_351788(s16* arg0) {
    s32 i;
    s32 ret;
    for (i = 0, ret = 0; i < 8; i++, arg0++) {
        if (*arg0 == D_800CD096) {
            ret = 1;
            break;
        }
        if (func_80035F98_36B98(D_8011C358_3651C8[*arg0]) == 0) {
            break;
        }
    }
    return ret;
}

//arg0 is ai decision data that goes unused here
// s32 func_801089AC_35181C(s16* arg0) {
//     Player* player = GetPlayerStruct(-1);
//     s16 junctionSpaceIndex = func_800EB184(player->cur_chain_index, player->cur_space_index);

//     switch (junctionSpaceIndex) {
//     case 0x79: 
//         arg0 = D_8011C368_3651D8;
//         break;
//     case 0x84:
//         arg0 = D_8011C378_3651E8;
//         break;
//     case 0x89:
//         arg0 = D_8011C388_3651F8;
//         break;
//     case 0x8A:
//         arg0 = D_8011C398_365208;
//         break;
//     case 0x8B:
//         arg0 = D_8011C3A8_365218;
//         break;
//     case 0x6F:
//         arg0 = D_8011C3B8_365228;
//         break;
//     default:
//         arg0 = D_8011C3C8_365238;
//         break;
//     }
//     if (func_80108918_351788(arg0) != 0) {
//         D_800CD066.unk33 = D_800CD066.unk33 | (1 << D_800CD066.curPlayerIndex);
//     } else {
//         D_800CD066.unk33 = D_800CD066.unk33 & ~(1 << D_800CD066.curPlayerIndex);
//     }
//     return 0;
// }
