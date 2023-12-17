#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/mp3.h"

s32 itemIDAmounts[148]; //ARRAY_COUNT(spaces)

//i think this is only 8 in size, made it 16 for safety
//on chilly waters this array is blank, but on desert map it's not?
s16 D_801052B8[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

u16 total_board_spaces = 0x94; //chilly waters has 0x94 spaces (D_80105210)
s16 D_801054F8 = 0x08; //in chilly waters, this is 0x08 at first (does this change?)
s16 D_801054B6 = 0; //no idea, is zero on chilly waters start

s16 D_800D03FC = 0; //total coin blocks placed
s16 D_800CE208 = 0; //total star blocks placed
s16 D_800CDD68 = 0; //total item blocks placed

u8 D_80101468_115088[] = { //data for chilly waters
    0x01, 0x02, 0x04, 0x01, 0x10, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
};

s16 D_801054B8[] = { //data for chilly waters
    0x0036, 0x002F, 0x005E, 0x0012, 0x0051, 0x0060, 0x004D, 0x0029,
};

void hidden_block_gen_main(void) {
    s32 prevItemLocation;
    Blocks blockVariables;
    s32 chain = 0;
    blockVariables.coinBlockSpaceIndex = -1;
    blockVariables.starBlockSpaceIndex = -1;
    blockVariables.itemBlockSpaceIndex = -1;
    cur_rng_seed = 0;
    func_800FC594_1101B4(&blockVariables);
    itemIDAmounts[blockVariables.itemBlockSpaceIndex]++;
    prevItemLocation = blockVariables.itemBlockSpaceIndex;
    for (u32 i = 1; i < 0x100000; i++) {
        blockVariables.coinBlockSpaceIndex = -1;
        blockVariables.starBlockSpaceIndex = -1;
        blockVariables.itemBlockSpaceIndex = -1;
        cur_rng_seed = i;
        func_800FC594_1101B4(&blockVariables);
        itemIDAmounts[blockVariables.itemBlockSpaceIndex]++;
        if (prevItemLocation == blockVariables.itemBlockSpaceIndex) {
            if (blockVariables.itemBlockSpaceIndex == 0x2C) {
                chain++;
            } else {
                chain = 0;
            }
            //
        }
        if (i % 1000000 == 0) {
            printf("Iterations: %ld\n", i);
        }
    }
    for (int i = 0; i < ARRAY_COUNT(itemIDAmounts); i++) {
        printf("Space %d: %ld\n", i, itemIDAmounts[i]);
    }
}

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

void func_800FC594_1101B4(Blocks* blocks) {
    if (func_80035F98_36B98(0xF) != 0) {
        while (blocks->coinBlockSpaceIndex == -1 || blocks->coinBlockSpaceIndex == blocks->starBlockSpaceIndex || blocks->coinBlockSpaceIndex == blocks->itemBlockSpaceIndex) {
            blocks->coinBlockSpaceIndex = func_800EBCD4_FF8F4(D_800D03FC);
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
        while (blocks->starBlockSpaceIndex == -1 || blocks->coinBlockSpaceIndex == blocks->starBlockSpaceIndex || blocks->itemBlockSpaceIndex == blocks->starBlockSpaceIndex) {
            blocks->starBlockSpaceIndex = func_800EBCD4_FF8F4(D_800CE208);
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
        
        while (blocks->itemBlockSpaceIndex == -1 || blocks->coinBlockSpaceIndex == blocks->itemBlockSpaceIndex || blocks->starBlockSpaceIndex == blocks->itemBlockSpaceIndex) {
            blocks->itemBlockSpaceIndex = func_800EBCD4_FF8F4(D_800CDD68);
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