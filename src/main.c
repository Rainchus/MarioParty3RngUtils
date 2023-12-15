#include <stdio.h>
#include <string.h>
#include "../include/mp1.h"

//80109290 function that advances rng on cannon A press
//164 frames from cannon A press to dice roll

//menuing as fast as I could, 924 calls when 1st player (cpu) rolls
/*
Eon Timer notes:
Set to Gen 3
For evedrive, hover over Start Game and set calibration to 5096

For cpu to roll 1: target frame: ? Quite Slow (calls = 3147, or 4871)
Very slow, probably dont bother
Calibration: 5096
Pre-Timer: 2500
TargetFrame: ?

For cpu to roll 2: target frame: 1850 (calls = 1084)
Calibration: 5096
Pre-Timer: 2500
TargetFrame: 1850

For cpu to roll 3: target frame: ? (calls = 3222)
Very slow, probably dont bother
Calibration: 5096
Pre-Timer: 2500
TargetFrame: ?

For cpu to roll 4: target frame: 2392 (calls = 2154) 
Calibration: 5096
Pre-Timer: 2500
TargetFrame: 2392

For cpu to roll 5: target frame: 2691 (2681 atm?) (calls = 1499)
Calibration: 5096
Pre-Timer: 2500
TargetFrame: 2691 (2681 atm?)

For cpu to roll 6: target frame: 1884 (calls = 1092) (31.491 seconds, 944.73 frames)
Calibration: 5096
Pre-Timer: 2500
TargetFrame: 1884

For cpu to roll 7: target frame: ? (calls = 6588)
Very slow, probably dont bother (although going into battle royale tutorial and backing out twice helps a lot)
Calibration: 5096
Pre-Timer: 2500
TargetFrame: ?

For cpu to roll 8: target frame: 1763 (calls = 1041)
Calibration: 5096
Pre-Timer: 2500
TargetFrame: 1763

For cpu to roll 9: target frame: 1866 (calls = 1892)
!!!!NOTE: wait on star spawn on opening scene
Calibration: 5096
Pre-Timer: 2500
TargetFrame: 1866

*/

//HUGE NOTE: Pausing and unpausing can be done frame perfectly because of a lag spike that occurs
//With this, we can advance rng 5 times whenever we want easily

//idea: have cpu get wacky watch

typedef struct Blocks {
    s16 coinBlockSpaceIndex;
    s16 starBlockSpaceIndex;
    s16 itemBlockSpaceIndex;
} Blocks;

//valid seeds for things, used for testing various things
s32 seeds[]= {
0xFFF8F922,
};

//77 advancements from pressing A on millenium star screen to deciding first block location


// s16 coinBlockSpaceIndex = -1; //D_800CE1C4
// s16 starBlockSpaceIndex = -1; //D_800D124E
// s16 itemBlockSpaceIndex = -1; //D_800CC4E4
u32 cur_rng_seed = 0x0000D9ED; //initial starting seed D_80097650

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

u8 RNGPercentChance(s8 arg0) { //func_800EB9D4 in duel mode
    return arg0 > ((HuGetRandomByte() * 0x63) >> 8);
}

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

s16 func_800EBCD4_FF8F4(u8 arg0) {
    return func_800EB5DC_FF1FC(2, arg0);
}

u8 HuGetRandomByte(void) {
    ADV_SEED(cur_rng_seed);
    return (cur_rng_seed + 1) >> 16;
}

s32 func_800EEF80_102BA0(f32 arg0) { //800EFE20 in duel mode
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

s32 itemIDAmounts[148]; //ARRAY_COUNT(spaces)

u8 rollDice(void) { //func_800DB148 in duel mode
    return (((HuGetRandomByte() & 0xFF) % 10) + 1);
}

s32 startSeed = 0;


s32 framesFromRollToItemDecision[] = {
    0, 38, 49, 0, 71, 82
};

//used for hidden block generation. starts from 
u8 DoCPUTurn(s32 spaceID, s32 rollWanted) {
    //advance rng 70 times to simulate time between item block placement and cpu roll
    s32 rollAmount = framesFromRollToItemDecision[rollWanted];
    for (int j = 0; j < 70; j++) {
        HuGetRandomByte();
    }

    //now check if cpu roll
    s32 diceRoll = rollDice();
    if (diceRoll != rollWanted) {
        return -1;
    }

    for (int j = 0; j < rollAmount; j++) {
        HuGetRandomByte();
    }

    //59, 58, 57, 56, 55
    //printf("\nSeed before item check: %08X\n", cur_rng_seed);
    //should be 0x4DE86038

    u8 randByte = func_800EEF80_102BA0(100.0f);
    return randByte + 1;
}

u32 runStuff(FILE* file, Blocks* blockVariables, s32 i) {
    blockVariables->coinBlockSpaceIndex = -1;
    blockVariables->starBlockSpaceIndex = -1;
    blockVariables->itemBlockSpaceIndex = -1;
    // cur_rng_seed = i;
    u32 startingSeed = cur_rng_seed;
    func_800FC594_1101B4(blockVariables);

    //Check goes here
    u8 randByte;

    switch (blockVariables->itemBlockSpaceIndex) {
        case 0:
            randByte = DoCPUTurn(0, 1);
            break;
        case 0x0B:
            randByte = DoCPUTurn(0x0B, 2);
            break;
        case 0x21:
            randByte = DoCPUTurn(0x21, 4);
            break;
        case 0x2C:
            randByte = DoCPUTurn(0x2C, 5);
            break;
        default:
            return - 1;
    }

    if (randByte == -1) {
        return - 1;
    }

    if (randByte > 0x55 && randByte < 0x5B) {
        fprintf(file, "Index: %ld, Seed: %08lX\n", i, startingSeed);
    }
    //printf("%ld: %08lX\n", seedsFound, startingSeed);
    return startingSeed;
}

void findValidSeeds(void) {
    FILE *file = fopen("output.txt", "w");
    Blocks blockVariables;
    s32 seedsFound = 0;
    blockVariables.coinBlockSpaceIndex = -1;
    blockVariables.starBlockSpaceIndex = -1;
    blockVariables.itemBlockSpaceIndex = -1;
    func_800FC594_1101B4(&blockVariables);
    //77 advancements from pressing A to blocks being decided isn't calculated here
    for (u32 i = 0; i < 1000000; i++) {
        u32 prevSeed = cur_rng_seed;
        runStuff(file, &blockVariables, i);
        seedsFound++;
        cur_rng_seed = prevSeed;
        HuGetRandomByte();

        //determine item cpu will get

        //will land on item block and dice roll was 5. print starting seed
        // printf("%d: %08X\n", seedsFound, startingSeed);
        // seedsFound++;

    }
}

s32 MeasureRngCalls(u32 seedStart, u32 seedEnd) {
    s32 calls = 0;
    cur_rng_seed = seedStart;
    while (cur_rng_seed != seedEnd) {
        if (calls > 10000000) {
            printf("Is more than 10 million calls away...\n");
            return -1;
        }
        HuGetRandomByte();
        calls++;
    }
    return calls;
}

void splitRngManip2Parts(void) {
    FILE *file = fopen("output.txt", "w");
    for (u32 i = 0; i < 0xFFFFFFFF; i++) {
        u32 seedCopy = cur_rng_seed;
        u32 seedCopy2 = seedCopy;
        Blocks blockVariables;
        s32 chain = 0;
        blockVariables.coinBlockSpaceIndex = -1;
        blockVariables.starBlockSpaceIndex = -1;
        blockVariables.itemBlockSpaceIndex = -1;
        func_800FC594_1101B4(&blockVariables);
        if (blockVariables.itemBlockSpaceIndex == 0x2C) {
            seedCopy2 = seedCopy;
            while (blockVariables.itemBlockSpaceIndex == 0x2C) {
                chain++;
                cur_rng_seed = seedCopy2;
                HuGetRandomByte();
                seedCopy2 = cur_rng_seed;
                blockVariables.coinBlockSpaceIndex = -1;
                blockVariables.starBlockSpaceIndex = -1;
                blockVariables.itemBlockSpaceIndex = -1;
                func_800FC594_1101B4(&blockVariables);
            }
            if (chain >= 2) {
                printf("Chain of %ld found Seed: %08lX\n", chain, seedCopy);
            }
            if (chain >= 4) {
                fprintf(file, "Chain of %ld found Seed: %08lX\n", chain, seedCopy);
            }
            
        } else {
            chain = 0;
        }
    }
}

//3 is glitched? also doesn't account for cpu decision at junction
// s32 FramesToWalkToItemSpaceNormalWalkNormalMessage[] = {
//     0, 42, 53, 123, -1, -1, -1, -1, -1, -1, -1 
// };

typedef struct framesToRollDecision {
    s32 firstHalf; //up to junction decision
    s32 secondHalf; //after junction decision
    s32 cpuWeight;
    s32 decisionWanted;
} framesToRollDecision;

#define CPU_NONE -1
#define CPU_UP 0
#define CPU_LEFT 1

//normal fast walk speed, fast message speed
framesToRollDecision FramesToWalkToItemSpaceFastWalkFastMessage[] = {
/* 0x00 */ {0, 0, 0, CPU_NONE},
/* 0x01 */ {37, 0, 0, CPU_NONE},
/* 0x02 */ {37, 0, 0, CPU_NONE},
};

//normal walk speed, normal message speed
framesToRollDecision FramesToWalkToItemSpaceNormalWalkNormalMessage[] = {
/* 0x00 */ {0, 0, 0, CPU_NONE},
/* 0x01 */ {42, 0, 0, CPU_NONE},
/* 0x02 */ {53, 0, 0, CPU_NONE},
/* 0x03 */ {39, 83, 50, CPU_LEFT},
/* 0x04 */ {50, 83, 50, CPU_LEFT},
/* 0x05 */ {268, 83, 50, CPU_LEFT},
/* 0x06 */ {279, 83, 50, CPU_LEFT},
/* 0x07 */ {290, 83, 50, CPU_LEFT},
/* 0x08 */ {301, 83, 50, CPU_LEFT},
/* 0x09 */ {312, 83, 50, CPU_LEFT},
/* 0x0A */ {0, 0, 0, CPU_NONE},
};

#define NO_BANK_OR_JUNCTION 0
#define JUNCTION_ONLY 1
#define BANK_AND_JUNCTION 2

typedef struct CpuWalkStats {
    s32 advancementsFromBankToJunction;
    s32 advancementsJunctionToItemSpace; //or start roll to item space if no junction
    s32 advancementsItemSpaceToQuestion;
    s32 advancementsItemSpaceToCpuDecision;
    s32 advancementsCpuDecisionToWatchChosen;
} CpuWalkStats;

/*
FastFast:
43 - 37 = 6 advances per space
*/

CpuWalkStats FastFast[] = {
    //0
    {
    .advancementsFromBankToJunction = 0,
    .advancementsJunctionToItemSpace = 37,
    .advancementsItemSpaceToQuestion = 648,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 108
    },
    //1
    {
    .advancementsFromBankToJunction = 0,
    .advancementsJunctionToItemSpace = 43,
    .advancementsItemSpaceToQuestion = 648,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 108
    },
    //2
    {
    .advancementsFromBankToJunction = 34,
    .advancementsJunctionToItemSpace = 68,
    .advancementsItemSpaceToQuestion = 648,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 108
    },
    //3
    {
    .advancementsFromBankToJunction = 40,
    .advancementsJunctionToItemSpace = 68,
    .advancementsItemSpaceToQuestion = 648,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 108
    },
    //4
    {
    .advancementsFromBankToJunction = 213,
    .advancementsJunctionToItemSpace = 68,
    .advancementsItemSpaceToQuestion = 648,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 108
    },
    //5
    {
    .advancementsFromBankToJunction = 219,
    .advancementsJunctionToItemSpace = 68,
    .advancementsItemSpaceToQuestion = 648,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 108
    },
    //6
    {
    .advancementsFromBankToJunction = 225,
    .advancementsJunctionToItemSpace = 68,
    .advancementsItemSpaceToQuestion = 648,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 108
    },
    //7
    {
    .advancementsFromBankToJunction = 231,
    .advancementsJunctionToItemSpace = 68,
    .advancementsItemSpaceToQuestion = 648,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 108
    },
    //8
    {
    .advancementsFromBankToJunction = 237,
    .advancementsJunctionToItemSpace = 68,
    .advancementsItemSpaceToQuestion = 648,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 108
    },
};

/*
NormalNormal:
53 - 42 = 11 advances per space
*/

CpuWalkStats NormalNormal[] = {
    //0
    {
    .advancementsFromBankToJunction = 0,
    .advancementsJunctionToItemSpace = 42,
    .advancementsItemSpaceToQuestion = 728,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 188
    },

    //1
    {
    .advancementsFromBankToJunction = 0,
    .advancementsJunctionToItemSpace = 53,
    .advancementsItemSpaceToQuestion = 728,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 188
    },

    //2
    {
    .advancementsFromBankToJunction = 39,
    .advancementsJunctionToItemSpace = 83,
    .advancementsItemSpaceToQuestion = 728,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 188
    },
    //3
    {
    .advancementsFromBankToJunction = 50,
    .advancementsJunctionToItemSpace = 83,
    .advancementsItemSpaceToQuestion = 728,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 188
    },
    //4
    {
    .advancementsFromBankToJunction = 268,
    .advancementsJunctionToItemSpace = 83,
    .advancementsItemSpaceToQuestion = 728,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 188
    },
    //5
    {
    .advancementsFromBankToJunction = 279,
    .advancementsJunctionToItemSpace = 83,
    .advancementsItemSpaceToQuestion = 728,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 188
    },
    //6
    {
    .advancementsFromBankToJunction = 290,
    .advancementsJunctionToItemSpace = 83,
    .advancementsItemSpaceToQuestion = 728,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 188
    },
    //7
    {
    .advancementsFromBankToJunction = 301,
    .advancementsJunctionToItemSpace = 83,
    .advancementsItemSpaceToQuestion = 728,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 188
    },
    //8
    {
    .advancementsFromBankToJunction = 312,
    .advancementsJunctionToItemSpace = 83,
    .advancementsItemSpaceToQuestion = 728,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 188
    },
};

/*
SlowSlow
63 - 47 = 16 advances per space
*/

CpuWalkStats SlowSlow[] = {
    //0
    {
    .advancementsFromBankToJunction = 0,
    .advancementsJunctionToItemSpace = 47,
    .advancementsItemSpaceToQuestion = 868,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 328
    },
    //1
    {
    .advancementsFromBankToJunction = 0,
    .advancementsJunctionToItemSpace = 63,
    .advancementsItemSpaceToQuestion = 868,
    .advancementsItemSpaceToCpuDecision = 56,
    .advancementsCpuDecisionToWatchChosen = 328
    },
};

#define TOAD_QUESTION 0

#define GREEDY_OPTION 0
#define MIDDLE_OPTION 1
#define BOTTOM_OPTION 2

#define CPU_MESSAGE_FAST_OPTION_INDEX_1_FRAMES 116
#define CPU_MESSAGE_FAST_OPTION_INDEX_2_FRAMES 184
#define CPU_MESSAGE_FAST_CLOSE_RARE_ITEM_TEXT_FRAMES 108

#define CPU_MESSAGE_NORMAL_OPTION_INDEX_1_FRAMES 196
#define CPU_MESSAGE_NORMAL_OPTION_INDEX_2_FRAMES 264

#define CPU_MESSAGE_SLOW_OPTION_INDEX_1_FRAMES 336
#define CPU_MESSAGE_SLOW_OPTION_INDEX_2_FRAMES 404

s32 OptionMiddleIndexes[] = {
    CPU_MESSAGE_FAST_OPTION_INDEX_1_FRAMES, CPU_MESSAGE_NORMAL_OPTION_INDEX_1_FRAMES, CPU_MESSAGE_SLOW_OPTION_INDEX_1_FRAMES
};

s32 OptionBottomIndexes[] = {
    CPU_MESSAGE_FAST_OPTION_INDEX_2_FRAMES, CPU_MESSAGE_NORMAL_OPTION_INDEX_2_FRAMES, CPU_MESSAGE_SLOW_OPTION_INDEX_2_FRAMES
};

#define RARE_ITEM_WATCH 3


s32 callAmountBetweenSpace[] = {6, 11, 16};

s32 messageSpeedsArray0[] = {648, 728, 868};

//advancements that happen during cpu selection on each message speed
s32 CpuSelectionArray1[] = {116, 196, 336};

s32 CpuSelectionArray2[] = {184, 264, 404};

//advancements that happen before rare item is decided
s32 CpuSelectionArray3[] = {108, 188, 328};

//advancements during bank visit based on text speed
s32 CpuSelectionArray4[] = {167, 207, 277};


//handles all rng related things starting at decision of item space event
s32 HandleLogicFromItemSpace(s32 messageSpeed) {
    //printf("Seed before event: %08lX\n", cur_rng_seed);
    s32 itemSpaceOutcome = func_800EEF80_102BA0(5.0f);
    if (itemSpaceOutcome != TOAD_QUESTION) {
        return 0;
    }

    //advance rng up to text box based on text speed
    
    for (int i = 0; i < messageSpeedsArray0[messageSpeed]; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //get random question (advances rng twice)
    //printf("Seed before question asked: %08lX\n", cur_rng_seed);
    func_800EEF80_102BA0(5.0f);

    //advance rng through text box popping up
    for (int i = 0; i < 56; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //cpu choosen an option to the question
    //printf("Seed before chosen index: %08lX\n", cur_rng_seed);
    s32 cpuChosenIndex = func_800EEF80_102BA0(3);
    if (cpuChosenIndex == GREEDY_OPTION) {
        return 0;
    }

    s32 textBoxFrames;
    if (cpuChosenIndex == MIDDLE_OPTION) {
        textBoxFrames = CpuSelectionArray1[messageSpeed];
    } else if (cpuChosenIndex == BOTTOM_OPTION) {
        textBoxFrames = CpuSelectionArray2[messageSpeed];
    } else {
        //??? code shouldn't get here
        return 0;
    }

    //advance rng during cpu decision for option index
    for (int i = 0; i < textBoxFrames; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //what happens based on what cpu answers
    // seed4 = cur_rng_seed;
    //printf("Seed before question outcome: %08lX\n", cur_rng_seed);
    s32 questionOutcome = func_800EEF80_102BA0(10.0f);

    if (cpuChosenIndex == MIDDLE_OPTION) {
        if (questionOutcome >= 2) {
            return 0;
        }
    }

    if (cpuChosenIndex == BOTTOM_OPTION) {
        if (questionOutcome >= 3) {
            return 0;
        }
    }

    //cpu got rare item, advance rng for text box
    for (int i = 0; i < CpuSelectionArray3[messageSpeed]; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //printf("Seed before rand item chosen: %08lX\n", cur_rng_seed);
    s32 itemChosen = func_800EEF80_102BA0(4);
    if (itemChosen == RARE_ITEM_WATCH) {
        return 1;
    }
    return 0;
    
}

//FastFast base 37 + (callAmountBetweenSpace[speed] * rollIndex)
//NormalNormal base 42 + (callAmountBetweenSpace[speed] * rollIndex)
//SlowSlow base 47 + (callAmountBetweenSpace[speed] * rollIndex)

//FastFast 648
//NormalNormal 728
//SlowSlow 868
//140

//FastFast Bank takes 167 advances

s32 DoCpuLogicTurnv2(s32 rollIndex, s32 walkSpeed, s32 messageSpeed) {
    u32 advancements = 0;
    s32 ret = 0;
    int j = 0;
    int k = 0;
    switch(rollIndex) {
        case 8:
        case 7:
        case 6:
        case 5:
        case 4:
            //walk to bank
            //printf("Seed after roll: %08lX\n", cur_rng_seed);
            j = 28 + (callAmountBetweenSpace[walkSpeed] * (rollIndex - 3));

            for (int i = 0; i < j; i++) {
                ADV_SEED(cur_rng_seed);
            }   

            //time at bank
            for (int i = 0; i < CpuSelectionArray4[messageSpeed]; i++) { //fastest text time
                ADV_SEED(cur_rng_seed);
            }

        case 3:
        case 2:
            //advance rng up to function
            if (rollIndex > 3) {
                j = (callAmountBetweenSpace[walkSpeed] * 2);
            } else {
                j = 28 + (callAmountBetweenSpace[walkSpeed] * (rollIndex - 1));
            }
            
            //printf("j is : %d\n", j);
            for (int i = 0; i < j; i++) {
                ADV_SEED(cur_rng_seed);
            }    
            //cpu decides direction
            //printf("Seed Before Cpu Decision: %08lX\n", cur_rng_seed);
            if (RNGPercentChance(50) == 0) { //CPU went up
                return 0;
            }
            //cpu decision time
            for (int i = 0; i < 50; i++) {
                ADV_SEED(cur_rng_seed);
            }

        //after junction
        case 1:
        case 0:
            //advance rng up to item space event decision
            if (rollIndex > 1) {
                k = (callAmountBetweenSpace[walkSpeed] * 3);
            } else {
                //k = 37 + (walkSpeed * 5);
                k = 31 + callAmountBetweenSpace[walkSpeed] * (rollIndex + 1);
            }
            
            //printf("k is : %d\n", k);
            for (int i = 0; i < k; i++) {
                ADV_SEED(cur_rng_seed);
            }
            //printf("Seed Before Item Space Event: %08lX\n", cur_rng_seed);
            ret = HandleLogicFromItemSpace(messageSpeed);
            break;
    }
    return ret;
}

// s32 DoCpuLogicTurnv2(s32 rollIndex, s32 speed) {
//     u32 advancements = 0;
//     s32 ret = 0;
//     int j = 0;
//     int k = 0;
//     switch(rollIndex) {
//         case 8:
//         case 7:
//         case 6:
//         case 5:
//         case 4:
//             //stuff here
//             //TEMPORARY
//             return 0;
//         case 3:
//         case 2:
//             //advance rng up to function
//             j = 37 + callAmountBetweenSpace[speed] * rollIndex + 1;
//             printf("j is : %d\n", j);
//             for (int i = 0; i < j; i++) {
//                 ADV_SEED(cur_rng_seed);
//             }    
//             //cpu decides direction
//             if (RNGPercentChance(50) == 0) { //CPU went up
//                 return 0;
//             }
//         //after junction
//         case 1:
//         case 0:
//             //advance rng up to item space event decision
//             k = 37 + (speed * 5);
//             //printf("k is : %d\n", k);
//             for (int i = 0; i < k; i++) {
//                 ADV_SEED(cur_rng_seed);
//             }
//             ret = HandleLogicFromItemSpace(speed);
//             break;
//     }
//     return ret;
// }

// s32 DoCpuLogicTurnv2(s32 rollIndex, s32 speed) {
//     u32 advancements = 0;
//     s32 ret = 0;
//     switch(rollIndex) {
//         //after junction
//         case 0:
//         case 1:
//             //advance rng up to item space event decision
//             for (int i = 0; i < (37 + speed * 5); i++) {
//                 ADV_SEED(cur_rng_seed);
//             }
//             ret = HandleLogicFromItemSpace(speed);
//             break;
//         //before junction, after bank space
//         case 2:
//         case 3:
//             //advance rng up to function
//             for (int i = 0; i < (28 + callAmountBetweenSpace[speed]); i++) {
//                 ADV_SEED(cur_rng_seed);
//             }    
//             //cpu decides direction
//             if (RNGPercentChance(50) == 0) { //CPU went up
//                 return 0;
//             } 
//             //advance rng up to item space event decision
//             for (int i = 0; i < (37 + speed * 5); i++) {
//                 ADV_SEED(cur_rng_seed);
//             }
//             ret = HandleLogicFromItemSpace(speed);
//             break;
//             break;
//         //before junction, before bank space
//         case 4:
//         case 5:
//         case 6:
//         case 7:
//         case 8:
//             ret = 0;
//             break;
//     }
//     return ret;
// }












s32 DoCpuLogicTurn(s32 rollIndex, s32 speed) {
    //u32 seed1, seed2, seed3, seed4, seed5;
    CpuWalkStats* curCpuTiming = &FastFast[rollIndex];
    // CpuWalkStats* curCpuTiming = &NormalNormal[rollIndex];
    //CpuWalkStats* curCpuTiming = &SlowSlow[rollIndex];

    for (int i = 0; i < curCpuTiming->advancementsFromBankToJunction; i++) {
        ADV_SEED(cur_rng_seed);
    } 

    if (curCpuTiming->advancementsFromBankToJunction != 0) {
        if (RNGPercentChance(50) == 0) { //CPU went up
            return 0;
        }
    }

    //advance rng until item space event decision
    for (int i = 0; i < curCpuTiming->advancementsJunctionToItemSpace; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //determine item space event (toad question, baby bowser question, or minigame)
    // seed1 = cur_rng_seed;
    s32 itemSpaceOutcome = func_800EEF80_102BA0(5.0f);
    if (itemSpaceOutcome != TOAD_QUESTION) {
        return 0;
    }

    for (int i = 0; i < curCpuTiming->advancementsItemSpaceToQuestion; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //doesn't actually matter, just needed to advance rng
    //(add 2 to below loop iteration to optimize program and remove this line)
    // seed2 = cur_rng_seed;
    //s32 questionAsked = func_800EEF80_102BA0(5.0f);

    for (int i = 0; i < curCpuTiming->advancementsItemSpaceToCpuDecision + 2; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //cpu chooses answer to question
    // seed3 = cur_rng_seed;
    s32 cpuChosenIndex = func_800EEF80_102BA0(3);

    if (cpuChosenIndex == GREEDY_OPTION) {
        return 0;
    }

    s32 textBoxFrames;
    if (cpuChosenIndex == MIDDLE_OPTION) {
        textBoxFrames = OptionMiddleIndexes[speed];
    } else if (cpuChosenIndex == BOTTOM_OPTION) {
        textBoxFrames = OptionBottomIndexes[speed];
    } else {
        //??? code shouldn't get here
        return 0;
    }

    //advance rng during cpu decision for option index
    for (int i = 0; i < textBoxFrames; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //what happens based on what cpu answers
    // seed4 = cur_rng_seed;
    s32 questionOutcome = func_800EEF80_102BA0(10.0f);

    if (cpuChosenIndex == MIDDLE_OPTION) {
        if (questionOutcome >= 2) {
            return 0;
        }
    }

    if (cpuChosenIndex == BOTTOM_OPTION) {
        if (questionOutcome >= 3) {
            return 0;
        }
    }

    //cpu got rare item, advance rng for text box
    for (int i = 0; i < curCpuTiming->advancementsCpuDecisionToWatchChosen; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //decide random rare item
    // seed5 = cur_rng_seed;
    s32 itemChosen = func_800EEF80_102BA0(4);
    if (itemChosen == RARE_ITEM_WATCH) {
        return 1;
    }
    return 0;
}

// void DoCpuLogicJunctionOnly(void) {

// }

// void DoCpuLogicBankAndJunction(void) {

// }

#define FAST_TEXT 0
#define NORMAL_TEXT 1
#define SLOW_TEXT 2

#define FAST_WALK 0
#define NORMAL_WALK 1
#define SLOW_WALK 2

char* speedsText[] = {
    "FAST",
    "NORMAL",
    "SLOW",
};

void CPUGetWatchFromItemSpace2(s32 rollValue, s32 walkSpeedIndex, s32 messageSpeedIndex) {
    u32 prevSeed = cur_rng_seed;
    //204 calls from A press on cannon to cpu roll
    for (u32 i = 0; i < 10000; i++) {
        //printf("CurSeed: %08lX\n", cur_rng_seed);
        cur_rng_seed = prevSeed;
        u32 seedTemp = cur_rng_seed;

        // for (int i = 0; i < 205; i++) {
        //     ADV_SEED(cur_rng_seed);
        // }
        
        s32 roll = rollDice(); //before roll dice
        
        prevSeed = cur_rng_seed;

        if (rollValue != 0) {
            if (roll != rollValue) {
                continue;
            }
        }

        if (DoCpuLogicTurnv2(roll - 1, FAST_WALK, FAST_TEXT) == 1) {
            printf("Calls: %ld, Seed: %08lX, Roll: %ld \t| Walk: %s \t| Message: %s\n", i, seedTemp, roll, speedsText[FAST_WALK], speedsText[FAST_TEXT]);
        }
        cur_rng_seed = prevSeed;

        if (DoCpuLogicTurnv2(roll - 1, FAST_WALK, NORMAL_TEXT) == 1) {
            printf("Calls: %ld, Seed: %08lX, Roll: %ld \t| Walk: %s \t| Message: %s\n", i, seedTemp, roll, speedsText[FAST_WALK], speedsText[NORMAL_TEXT]);
        }
        cur_rng_seed = prevSeed;

        if (DoCpuLogicTurnv2(roll - 1, FAST_WALK, SLOW_TEXT) == 1) {
            printf("Calls: %ld, Seed: %08lX, Roll: %ld \t| Walk: %s \t| Message: %s\n", i, seedTemp, roll, speedsText[FAST_WALK], speedsText[SLOW_TEXT]);
        }
        cur_rng_seed = prevSeed;

        if (DoCpuLogicTurnv2(roll - 1, NORMAL_WALK, FAST_TEXT) == 1) {
            printf("Calls: %ld, Seed: %08lX, Roll: %ld \t| Walk: %s \t| Message: %s\n", i, seedTemp, roll, speedsText[NORMAL_WALK], speedsText[FAST_TEXT]);
        }
        cur_rng_seed = prevSeed;

        if (DoCpuLogicTurnv2(roll - 1, NORMAL_WALK, NORMAL_TEXT) == 1) {
            printf("Calls: %ld, Seed: %08lX, Roll: %ld \t| Walk: %s \t| Message: %s\n", i, seedTemp, roll, speedsText[NORMAL_WALK], speedsText[NORMAL_TEXT]);
        }
        cur_rng_seed = prevSeed;

        if (DoCpuLogicTurnv2(roll - 1, NORMAL_WALK, SLOW_TEXT) == 1) {
            printf("Calls: %ld, Seed: %08lX, Roll: %ld \t| Walk: %s \t| Message: %s\n", i, seedTemp, roll, speedsText[NORMAL_WALK], speedsText[SLOW_TEXT]);
        }
        cur_rng_seed = prevSeed;

        if (DoCpuLogicTurnv2(roll - 1, SLOW_WALK, FAST_TEXT) == 1) {
            printf("Calls: %ld, Seed: %08lX, Roll: %ld \t| Walk: %s \t| Message: %s\n", i, seedTemp, roll, speedsText[SLOW_WALK], speedsText[FAST_TEXT]);
        }
        cur_rng_seed = prevSeed;

        if (DoCpuLogicTurnv2(roll - 1, SLOW_WALK, NORMAL_TEXT) == 1) {
            printf("Calls: %ld, Seed: %08lX, Roll: %ld \t| Walk: %s \t| Message: %s\n", i, seedTemp, roll, speedsText[SLOW_WALK], speedsText[NORMAL_TEXT]);
        }
        cur_rng_seed = prevSeed;

        if (DoCpuLogicTurnv2(roll - 1, SLOW_WALK, SLOW_TEXT) == 1) {
            printf("Calls: %ld, Seed: %08lX, Roll: %ld \t| Walk: %s \t| Message: %s\n", i, seedTemp, roll, speedsText[SLOW_WALK], speedsText[SLOW_TEXT]);
        }
        cur_rng_seed = prevSeed;
    }
}
















void CPUGetWatchFromItemSpace(s32 rollValue) {
    u32 prevSeed = cur_rng_seed;
    //204 calls from A press on cannon to cpu roll
    for (u32 i = 0; i < 80000; i++) {
        //printf("CurSeed: %08lX\n", cur_rng_seed);
        cur_rng_seed = prevSeed;
        u32 seedTemp = cur_rng_seed;
        
        s32 roll = rollDice(); //before roll dice
        
        prevSeed = cur_rng_seed;
        if (roll != rollValue) {
            continue;
        }

        if (FramesToWalkToItemSpaceNormalWalkNormalMessage[roll].cpuWeight == -1) {
            for (s32 j = 0; j < FramesToWalkToItemSpaceNormalWalkNormalMessage[roll].firstHalf; j++) {
                ADV_SEED(cur_rng_seed);
            }
        } else {
            for (s32 j = 0; j < FramesToWalkToItemSpaceNormalWalkNormalMessage[roll].firstHalf; j++) {
                ADV_SEED(cur_rng_seed);
            }
            u8 cpuDecision = RNGPercentChance(FramesToWalkToItemSpaceNormalWalkNormalMessage[roll].cpuWeight);
            if (cpuDecision != FramesToWalkToItemSpaceNormalWalkNormalMessage[roll].decisionWanted) {
                continue;
            }
            for (s32 j = 0; j < FramesToWalkToItemSpaceNormalWalkNormalMessage[roll].secondHalf; j++) {
                ADV_SEED(cur_rng_seed);
            }
        }

        s32 itemSpaceOutcome = func_800EEF80_102BA0(5.0f);
        if (itemSpaceOutcome != 0) { //if isn't toad question, continue loop
            continue;
        }

        for (s32 j = 0; j < 728; j++) {
            ADV_SEED(cur_rng_seed);
        }

        //doesn't actually matter, just needed to advance rng
        //s32 questionAsked = func_800EEF80_102BA0(5.0f);
        HuGetRandomByte();
        HuGetRandomByte();

        for (s32 j = 0; j < 56; j++) {
            ADV_SEED(cur_rng_seed);
        }

        s32 cpuChosenIndex = func_800EEF80_102BA0(3);
        cpuChosenIndex++;
        if (cpuChosenIndex == 2) {
            for (s32 j = 0; j < 196; j++) {
                ADV_SEED(cur_rng_seed);
            }
            s32 percentChanceOfPick = func_800EEF80_102BA0(10.0f);
            if (percentChanceOfPick == 0 || percentChanceOfPick == 1) {
                for (s32 j = 0; j < 188; j++) {
                    ADV_SEED(cur_rng_seed);
                }
                s32 itemChosen = func_800EEF80_102BA0(4);
                if (itemChosen == 3) {
                    printf("Calls: %ld, Option 1: %08lX, Roll: %ld\n", i, seedTemp, roll);
                }
            }
        } else if (cpuChosenIndex == 3) {
            for (s32 j = 0; j < 264; j++) {
                ADV_SEED(cur_rng_seed);
            }
            s32 percentChanceOfPick = func_800EEF80_102BA0(10.0f);
            if (percentChanceOfPick == 0 || percentChanceOfPick == 1 || percentChanceOfPick == 2) {
                for (s32 j = 0; j < 188; j++) {
                    ADV_SEED(cur_rng_seed);
                }
                s32 itemChosen = func_800EEF80_102BA0(4);
                if (itemChosen == 3) {
                    printf("Calls: %ld, Option 2: %08lX, Roll: %ld\n", i, seedTemp, roll);
                }
            }
        } else {
            continue;
        }
    }
}

void SimDuelMode(void);
void SimDuelMode2(void);
void SimDuelMode3(void);


void PrintArgUsage(void) {
    printf(
        ANSI_GREEN"Run the program with a command and no additional args to see usage\n"ANSI_RESET
        "Commands List:\n"
        "--simduel\n"
        "--simduel2\n"
        "--simduel3\n"
        "--rngadv\n"
        "--rollchain\n"
        "--rollchain2(pointless?)\n"
        "--cpuitemspacewatch\n"
        "--hiddenblockgen\n"
    );
    //printf("Arg stuff\n");
}

void tempFunction(void) {
    for (s32 i = 0; i < 3000; i++) {
        u32 prevSeed = cur_rng_seed;
        u8 diceRollValue = rollDice();
        // if (diceRollValue != 8) {
        //     continue;
        // }
        printf("Calls: %ld, Seed: %08lX Rolls: %d\n", i, prevSeed, diceRollValue);
    }
}

int main(int argc, char *argv[]) {

    // CPUGetWatchFromItemSpace2(1, 0, 0); //fast fast
    // return 0;

    if (strncmp("--temp", argv[1], sizeof("--temp")) == 0) {
        tempFunction();
        return 0;
    }

    //printf(ANSI_GREEN"MP3 rng util\n"ANSI_RESET);
    if (argc == 1 || strncmp("--options", argv[1], sizeof("--options")) == 0) {
        PrintArgUsage();
        return 0;
    }

    if (strncmp("--simduel", argv[1], sizeof("--simduel")) == 0) {
        SimDuelMode();
        return 0;
    }

    if (strncmp("--simduel2", argv[1], sizeof("--simduel2")) == 0) {
        SimDuelMode2();
        return 0;
    }

    if (strncmp("--simduel3", argv[1], sizeof("--simduel3")) == 0) {
        SimDuelMode3();
        return 0;
    }

    u32 seed1;
    u32 seed2;

    if (strncmp("--rngadv", argv[1], sizeof("--rngadv")) == 0) {
        if (argc != 4) {
            printf("Usage: %s --rngadv <hexadecimal_seed1> <hexadecimal_seed2>\n", argv[0]);
            return 0;
        }
        char* hexValue1 = argv[2];
        char* hexValue2 = argv[3];

        if (hexValue1[0] == '0') {
            if (hexValue1[1] == 'x' || hexValue1[1] == 'X'){ 
                hexValue1 += 2; //iterate over prefix
            }
        }

        if (hexValue2[0] == '0') {
            if (hexValue2[1] == 'x' || hexValue2[1] == 'X'){ 
                hexValue2 += 2; //iterate over prefix
            }
        }

        if (sscanf(hexValue1, "%08lX", &seed1) != 1 || sscanf(hexValue2, "%08lX", &seed2) != 1) {
            printf("Usage: %s --rngadv <hexadecimal_seed1> <hexadecimal_seed2>\n", argv[0]);
            return 0;
        }

        //printf("Seed1: %08lX, Seed2: %08lX\n", seed1, seed2);
        s32 callTotal = MeasureRngCalls(seed1, seed2);
        printf("Calls: %ld", callTotal);
        return 0;
    }

    if (strncmp("--rollchain", argv[1], sizeof("--rollchain")) == 0) {
        u32 chain_bound;
        //printf("arg count: %d\n", argc);
        if (argc <= 2) {
            printf("Usage: %s --rollchain <rollValue> <chainAmount(optional, defaults to 2)>\n", argv[0]);
            return 0;
        }
        if (argc == 4) {
            sscanf(argv[3], "%08lX", &chain_bound);
        } else {
            printf("Chain length defaulting to 2\n");
            chain_bound = 2;
        }

        u32 wantedRoll;
        sscanf(argv[2], "%ld", &wantedRoll);
        u32 prevDiceRoll = 0;
        s32 chain = 0;
        u32 seedChainStart = 0;
        for (s32 i = 0; i < 20000; i++) {
            u32 prevSeed = cur_rng_seed;
            u8 diceRollValue = rollDice();
            if (prevDiceRoll == diceRollValue && diceRollValue == wantedRoll) {
                if (chain == 0) {
                    seedChainStart = prevSeed;
                }
                chain++;
            } else {
                if (chain >= chain_bound) {
                    printf("Chain for %ld, length %ld, Iterations %ld, Seed: %08lX\n", prevDiceRoll, chain, i - chain, seedChainStart);
                }
                chain = 0;
            }
            prevDiceRoll = diceRollValue;

            cur_rng_seed = prevSeed;
            ADV_SEED(cur_rng_seed);
        }
        return 0;
    }

    if (strncmp("--rollchain2", argv[1], sizeof("--rollchain2")) == 0) {
        u32 chain_bound;
        //printf("arg count: %d\n", argc);
        if (argc == 3) {
            sscanf(argv[2], "%08lX", &chain_bound);
        } else {
            chain_bound = 2;
        }

        u32 prevDiceRoll = 0;
        s32 chain = 0;
        u32 seedChainStart = 0;
        for (s32 i = 0; i < 20000; i++) {
            u32 prevSeed = cur_rng_seed;
            u8 diceRollValue = rollDice();
            if ((prevDiceRoll == 1 || prevDiceRoll == 2 || prevDiceRoll == 3) && (diceRollValue == 1 || diceRollValue == 2 || diceRollValue == 3)) {
                if (chain == 0) {
                    seedChainStart = prevSeed;
                }
                chain++;
            } else {
                if (chain >= chain_bound) {
                    printf("Chain for %ld, length %ld, Iterations %ld, Seed: %08lX\n", prevDiceRoll, chain, i - chain, seedChainStart);
                }
                chain = 0;
            }
            prevDiceRoll = diceRollValue;

            cur_rng_seed = prevSeed;
            ADV_SEED(cur_rng_seed);
        }
        return 0;
    }

    if (strncmp("--cpuitemspacewatch", argv[1], sizeof("--cpuitemspacewatch")) == 0) {
        u32 hexValue;
        if (argc == 2) {
            hexValue = 0;
            //printf("Usage: %s --cpuitemspacewatch <roll_value>\n", argv[0]);
            //return 0;
        } else {
            char* arg2Temp = argv[2];
            if (arg2Temp[0] == '0') {
                if (arg2Temp[1] == 'x' || arg2Temp[1] == 'X') {
                    arg2Temp += 2;
                }
            }
            sscanf(arg2Temp, "%08lX", &hexValue);
        }
        CPUGetWatchFromItemSpace2(hexValue, 0, 0); //fast fast
    }

    //pthread_t threads[NUM_THREADS];

    // u32 distance = 0xFFFFFFFF;
    // u32 seedFound = 0;
    // for (int i = 0; i < ARRAY_COUNT(seeds); i++) {
    //     s32 rngResult = MeasureRngCalls(0x0000D9ED, seeds[i]);
    //     if (rngResult < distance) {
    //         distance = rngResult;
    //         seedFound = seeds[i];
    //     }
    // }
    // printf("Seed: %08X Distance: %d\n", seedFound, distance);

    // for (u32 i = 0; i < 80000; i++) {
    //     u32 seed_backup = cur_rng_seed;

    // }

    //splitRngManip2Parts();

    //printf("%d", MeasureRngCalls(0x704834F0, 0xC328D379));

    //CPUGetWatchFromItemSpace(1);

    // findValidSeeds();

    // if (argc != 2) {
    //     printf("Usage: %s <hexadecimal_seed>\n", argv[0]);
    //     return 1;
    // }


    if (strncmp("--hiddenblockgen", argv[1], sizeof("--hiddenblockgen")) == 0) {
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
        return 0;
    }

    return 0;
}