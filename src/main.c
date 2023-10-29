#include <stdio.h>
#include "mp1.h"

s16 coinBlockSpaceIndex = -1; //D_800CE1C4
s16 starBlockSpaceIndex = -1; //D_800D124E
s16 itemBlockSpaceIndex = -1; //D_800CC4E4
u32 cur_rng_seed = 0x0000D9ED; //initial starting seed

u16 total_board_spaces = 0x94; //chilly waters has 0x94 spaces (D_80105210)
s16 D_801054F8 = 0x08; //in chilly waters, this is 0x08 at first (does this change?)
s16 D_801054B6 = 0; //no idea, is zero on chilly waters start

s16 D_800D03FC = 0; //total coin blocks placed
s16 D_800CE208 = 0; //total star blocks placed
s16 D_800CDD68 = 0; //total item blocks placed

//i think this is only 8 in size, made it 16 for safety
//on chilly waters this array is blank, but on desert map it's not?
s16 D_801052B8[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

//probably only 4 entries but 10 for safety
u8 D_800CD0B6[] = {0xC8, 0xBD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

u8 HuGetRandomByte(void);
s16 func_800EB5DC_FF1FC(s32 arg0, u8 arg1);

s32 func_80035F98_36B98(s32 input) {
    s32 byteValue;
    s32 adjustedIndex;
    s32 byteIndex;
    s32 bitIndex;
    s32 mask;

    if (input < 0) {
        byteValue = D_800CD0B6[(input + 7) >> 3];
    } else {
        byteValue = D_800CD0B6[input >> 3];
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

// s32 func_80035F98_36B98(s32 arg0) {
//     s32 var_v0;
//     s32 var_v1;

    
//     if (arg0 < 0) {
//         var_v0 = arg0 + 7;
//     } else {
//         var_v0 = arg0;
//     }

//     if (arg0 < 0) {
//         var_v1 = arg0 + 7;
//     } else {
//         var_v1 = arg0;
//     }

//     printf("var_v0: %02X\nvar_v1: %02X\n\n", var_v0, var_v1);
    
//     return D_800CD0B6[var_v0] & (1 << (arg0 - var_v1));
// }

s16 func_800EBCD4_FF8F4(u8 arg0) {
    return func_800EB5DC_FF1FC(2, arg0);
}

u8 HuGetRandomByte(void) {
    cur_rng_seed = cur_rng_seed * 0x41C64E6D + 0x3039;
    return (cur_rng_seed + 1) >> 16;
}

s32 func_800EEF80_102BA0(f32 arg0) {
    // HuGetRandomByte returns an unsigned byte
    u8 randomByte1 = HuGetRandomByte();
    u8 randomByte2 = HuGetRandomByte();
    s32 shiftedByte1 = (randomByte1 << 8);

    // Normalize the 16-bit number to the range [0, 1), then multiply by arg0
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;
    
    return scaledRandom;
}

SpaceData* func_800EB160_FED80(s16 arg0) {
    return &spaces[arg0];
}

u8 D_80101468_115088[] = { //data for chilly waters
    0x01, 0x02, 0x04, 0x01, 0x10, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
};

s16 D_801054B8[] = { //data for chilly waters
    0x0036, 0x002F, 0x005E, 0x0012, 0x0051, 0x0060, 0x004D, 0x0029,
};

s16 func_800EB5DC_FF1FC(s32 arg0, u8 arg1) {
    s32 var_s1;
    u8 var_s1_2;
    SpaceData* temp_a1;
    s32 i, j;
    s32 tempVar;
    var_s1 = 0;

    //find valid spaces block could go
    for (i = 0; i < total_board_spaces; i++) {
        if ((D_80101468_115088[(func_800EB160_FED80(i)->space_type & 0xF)] & (u16)arg0)){
            var_s1++;
        }
    }

    var_s1_2 = var_s1 - D_801054F8;
    if ((arg1) < 5U) {
        var_s1_2 = var_s1_2 - D_801054B6;
    }

    var_s1_2 = func_800EEF80_102BA0((var_s1_2));

    tempVar = (arg1 & 0xFF) < 5;

    for (i = 0;; i = -(i < total_board_spaces) & i) {
        temp_a1 = func_800EB160_FED80(i);
        for (j = 0; j < D_801054F8; j++) {
            if (D_801054B8[j] == i) {
                break;
            }
        }

        if (j != D_801054F8) {
            i++;
            continue;
        } else {
            if (tempVar != 0) {
                for (j = 0; j < D_801054B6; j++) {
                    if (D_801052B8[j] == i) {
                        break;
                    }
                }
            
                if (j != D_801054B6) {
                    i++;
                    continue;
                }            
            }
        }
        if ( !(D_80101468_115088[(temp_a1->space_type & 0xF)] & (u16)arg0)){
            i++;
            continue;
        } else if ((var_s1_2 & 0xFF) == 0) {
            break;
        }
        var_s1_2--;
        i++;
    }

    return i;
}

void func_800FC594_1101B4(void) {
    if (func_80035F98_36B98(0xF) != 0) {
        while (coinBlockSpaceIndex == -1 || coinBlockSpaceIndex == starBlockSpaceIndex || coinBlockSpaceIndex == itemBlockSpaceIndex) {
            coinBlockSpaceIndex = func_800EBCD4_FF8F4(D_800D03FC);
            D_800D03FC += 1;
            //uneeded since we only care about initial placement
            // for (i = 0; i < 10; i++) {
            //     if (coinBlockSpaceIndex == prevCoinBlockSpaceIndexes[i]) {
            //         break;
            //     }
            // }
            // if (i != 0xA) {
            //     coinBlockSpaceIndex = -1;
            // }
        }
        while (starBlockSpaceIndex == -1 || coinBlockSpaceIndex == starBlockSpaceIndex || itemBlockSpaceIndex == starBlockSpaceIndex) {
            starBlockSpaceIndex = func_800EBCD4_FF8F4(D_800CE208);
            D_800CE208 += 1;
            //uneeded since we only care about initial placement
            // for (i = 0; i < 10; i++) {
            //     if (starBlockSpaceIndex == prevStarBlockSpaceIndexes[i]) {
            //         break;
            //     }
            // }
            // if (i != 0xA) {
            //     starBlockSpaceIndex = -1;
            // }
        }
        
        while (itemBlockSpaceIndex == -1 || coinBlockSpaceIndex == itemBlockSpaceIndex || starBlockSpaceIndex == itemBlockSpaceIndex) {
            itemBlockSpaceIndex = func_800EBCD4_FF8F4(D_800CDD68);
            D_800CDD68 += 1;
            //uneeded since we only care about initial placement
            // for (i = 0; i < 10; i++) {
            //     if (itemBlockSpaceIndex == prevItemBlockSpaceIndexes[i]) {
            //         break;
            //     }
            // }
            // if (i != 0xA) {
            //     itemBlockSpaceIndex = -1;
            // }
        }
    }
}


int main(void) {
    printf("Starting Seed: 0x%08lX\n", cur_rng_seed);
    func_800FC594_1101B4(); //place hidden blocks
    printf("Coin Block Space ID: 0x%02X\n", coinBlockSpaceIndex);
    printf("Star Block Space ID: 0x%02X\n", starBlockSpaceIndex);
    printf("Item Block Space ID: 0x%02X\n", itemBlockSpaceIndex);
    return 0;
}