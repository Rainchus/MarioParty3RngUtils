#include "mp3.h"
#include <stdio.h>

s16 func_800EB5DC_FF1FC(s32 arg0, u8 arg1, s32 numOfBoardSpaces, s32 boardIndex);

s16 D_800D03FC = 0; //total coin blocks placed
s16 D_800CE208 = 0; //total star blocks placed
s16 D_800CDD68 = 0; //total item blocks placed

s16 D_801054F8 = 0x08; //in chilly waters, this is 0x08 at first (does this change?)
s16 D_801054B6 = 0; //no idea, is zero on chilly waters start

// s16 CurBoardStarSpaces[] = {
//     -1, -1, -1, -1, -1, -1, -1, -1,
// };

s16 ChillyWatersStarSpaces[] = { //data for chilly waters
    0x0036, 0x002F, 0x005E, 0x0012, 0x0051, 0x0060, 0x004D, 0x0029,
};

s16 DeepBlooperSeaStarSpaces[] = {
    0x001E, 0x0028, 0x0015, 0x0007, 0x0041, 0x005C, 0x004C, 0x0056
};

s16* StarSpaceArray[] = {
    ChillyWatersStarSpaces,
    DeepBlooperSeaStarSpaces,
};

//i think this is only 8 in size, made it 16 for safety
//on chilly waters this array is blank, but on desert map it's not?
s16 D_801052B8[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

s32 func_80035F98_36B98(s32 input) {
    s32 byteValue;
    s32 adjustedIndex;
    s32 byteIndex;
    s32 bitIndex;
    s32 mask;

    if (input < 0) {
        byteValue = gGameStatus.D_800CD0B6[(input + 7) >> 3];
    } else {
        byteValue = gGameStatus.D_800CD0B6[input >> 3];
    }

    if (input >= 0) {
        adjustedIndex = input;
    } else {
        adjustedIndex = input + 7;
    }

    // Calculate the byte index (divide by 8)
    byteIndex = adjustedIndex >> 3;

    // Calculate the bit index
    bitIndex = input - (byteIndex << 3);

    mask = (1 << bitIndex);

    return byteValue & mask;
}


u8 D_80101468_115088[] = { //data for chilly waters (all boards?)
    0x01, 0x02, 0x04, 0x01, 0x10, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
};

s16 func_800EBCD4_FF8F4(u8 arg0, s32 numOfBoardSpaces, s32 boardIndex) {
    return func_800EB5DC_FF1FC(2, arg0, numOfBoardSpaces, boardIndex);
}

//func_800EB160_FED80
SpaceData* GetSpaceData(s16 arg0, s32 boardIndex) {
    SpaceData* boardSpaces = spacesForBoards[boardIndex];
    return &boardSpaces[arg0];
}

void SetStarSpace(s32 starSpaceIndex, s32 boardIndex) {
    s16 starSpaceID = StarSpaceArray[boardIndex][starSpaceIndex];
    GetSpaceData(starSpaceID, boardIndex)->space_type = SPACE_STAR;
}

void ResetStarSpaces(s32 boardIndex) {
    for (int i = 0; i < 8; i++) {
        s16 starSpaceID = StarSpaceArray[boardIndex][i];
        GetSpaceData(starSpaceID, boardIndex)->space_type = SPACE_BLUE;
    }
}

s16 func_800EB5DC_FF1FC(s32 arg0, u8 arg1, s32 numOfBoardSpaces, s32 boardIndex) {
    u8 var_s1;
    SpaceData* temp_a1;
    s32 i, j;
    var_s1 = 0;

    for (i = 0; i < numOfBoardSpaces; i++) {
        temp_a1 = GetSpaceData(i, boardIndex);
        if (D_80101468_115088[temp_a1->space_type & 0xF] & arg0){
            var_s1++;
        }
    }

    var_s1 -= D_801054F8;
    if (arg1 < 5) {
        var_s1 -= D_801054B6;
    }

    var_s1 = func_800EEF80_102BA0(var_s1);

    for (i = 0;; i = (++i < numOfBoardSpaces) ? i : 0) {
        temp_a1 = GetSpaceData(i, boardIndex);
        for (j = 0; j < D_801054F8; j++) {
            if (StarSpaceArray[boardIndex][j] == i) {
                break;
            }
        }
        if (j == D_801054F8) {
            if (arg1 < 5) {
                for (j = 0; j < D_801054B6; j++) {
                    if (D_801052B8[j] == i) {
                        break;
                    }
                }
                if (j == D_801054B6) {
                    if (D_80101468_115088[temp_a1->space_type & 0xF] & arg0) {
                        if (var_s1 == 0) {
                            break;
                        }
                        var_s1--;
                    }
                }           
            } else {
                if (D_80101468_115088[temp_a1->space_type & 0xF] & arg0) {
                    if (var_s1 == 0) {
                        break;
                    }
                    var_s1--;
                }
            }
        }
    }

    return i;
}

//func_800FC594_1101B4
void PlaceHiddenBlocksMain(Blocks* blocks, s32 numOfSpaces, s32 boardIndex) {
    D_800D03FC = 0;
    D_800CE208 = 0;
    D_800CDD68 = 0;
    if (func_80035F98_36B98(0xF) != 0) {
        while (blocks->coinBlockSpaceIndex == -1 || blocks->coinBlockSpaceIndex == blocks->starBlockSpaceIndex || blocks->coinBlockSpaceIndex == blocks->itemBlockSpaceIndex) {
            blocks->coinBlockSpaceIndex = func_800EBCD4_FF8F4(D_800D03FC, numOfSpaces, boardIndex);
            D_800D03FC += 1;
        }
        while (blocks->starBlockSpaceIndex == -1 || blocks->coinBlockSpaceIndex == blocks->starBlockSpaceIndex || blocks->itemBlockSpaceIndex == blocks->starBlockSpaceIndex) {
            blocks->starBlockSpaceIndex = func_800EBCD4_FF8F4(D_800CE208, numOfSpaces, boardIndex);
            D_800CE208 += 1;
        }
        while (blocks->itemBlockSpaceIndex == -1 || blocks->coinBlockSpaceIndex == blocks->itemBlockSpaceIndex || blocks->starBlockSpaceIndex == blocks->itemBlockSpaceIndex) {
            blocks->itemBlockSpaceIndex = func_800EBCD4_FF8F4(D_800CDD68, numOfSpaces, boardIndex);
            D_800CDD68 += 1;
        }
    }
}