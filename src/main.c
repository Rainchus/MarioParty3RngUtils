#include <stdio.h>
#include <string.h>
#include "../include/mp1.h"

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

u8 RNGPercentChance(s8 arg0) {
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
    cur_rng_seed = cur_rng_seed * 0x41C64E6D + 0x3039;
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

u8 rollDice(void) {
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
        fprintf(file, "Index: %d, Seed: %08lX\n", i, startingSeed);
    }
    //printf("%ld: %08lX\n", seedsFound, startingSeed);
    return startingSeed;
}

void findValidSeeds(void) {
    FILE *file = fopen("output.txt", "w");
    Blocks blockVariables;
    s32 chain = 0;
    u32 startingSeed = 0;
    s32 seedsFound = 0;
    s32 seedStartChain = 0;
    s32 seedBackup = 0;
    blockVariables.coinBlockSpaceIndex = -1;
    blockVariables.starBlockSpaceIndex = -1;
    blockVariables.itemBlockSpaceIndex = -1;
    func_800FC594_1101B4(&blockVariables);
    //77 advancements from pressing A to blocks being decided isn't calculated here
    for (u32 i = 0; i < 1000000; i++) {
        u32 prevSeed = cur_rng_seed;
        u32 var = runStuff(file, &blockVariables, i);
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
// s32 FramesToWalkToItemSpace[] = {
//     0, 42, 53, 123, -1, -1, -1, -1, -1, -1, -1 
// };

typedef struct framesToRollDecision {
    s32 firstHalf;
    s32 secondHalf;
    s32 cpuWeight;
    s32 decisionWanted;
} framesToRollDecision;

framesToRollDecision FramesToWalkToItemSpace[] = {
/* 0x00 */ {0, 0, 0, 0},
/* 0x01 */ {42, 0, 0, 0},
/* 0x02 */ {53, 0, 0, 0},
/* 0x03 */ {39, 83, 50, 1}, //want CPU to get left not up
/* 0x04 */ {50, 83, 50, 1},
/* 0x05 */ {268, 83, 50, 1},
/* 0x06 */ {279, 83, 50, 1},
/* 0x07 */ {290, 83, 50, 1},
/* 0x08 */ {301, 83, 50, 1},
/* 0x09 */ {312, 83, 50, 1},
/* 0x0A */ {0, 0, 0, 0},
};

void CPUGetWatchFromItemSpace(s32 rollValue) {
    u32 prevSeed = cur_rng_seed;
    u32 beforeCall1, beforeCall2, beforeCall3, beforeCall4, beforeCall5, beforeCall6;
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

        beforeCall1 = cur_rng_seed;
        //cpu walks 2 spaces, does 53 calls
        if (FramesToWalkToItemSpace[roll].cpuWeight == 0) {
            for (s32 j = 0; j < FramesToWalkToItemSpace[roll].firstHalf; j++) {
                cur_rng_seed = cur_rng_seed * 0x41C64E6D + 0x3039;
            }
        } else {
            for (s32 j = 0; j < FramesToWalkToItemSpace[roll].firstHalf; j++) {
                cur_rng_seed = cur_rng_seed * 0x41C64E6D + 0x3039;
            }
            u8 cpuDecision = RNGPercentChance(FramesToWalkToItemSpace[roll].cpuWeight);
            if (cpuDecision != FramesToWalkToItemSpace[roll].decisionWanted) {
                continue;
            }
            for (s32 j = 0; j < FramesToWalkToItemSpace[roll].secondHalf; j++) {
                cur_rng_seed = cur_rng_seed * 0x41C64E6D + 0x3039;
            }
        }

        //printf("Before Item Space Outcome: %08lX\n", cur_rng_seed);
        beforeCall2 = cur_rng_seed;
        s32 itemSpaceOutcome = func_800EEF80_102BA0(5.0f);
        if (itemSpaceOutcome != 0) { //
            continue;
        }

        beforeCall3 = cur_rng_seed;
        for (s32 j = 0; j < 728; j++) {
            cur_rng_seed = cur_rng_seed * 0x41C64E6D + 0x3039;
        }

        beforeCall4 = cur_rng_seed;
        s32 questionAsked = func_800EEF80_102BA0(5.0f);
        if (questionAsked != 2) {
            continue;
        }

        for (s32 j = 0; j < 56; j++) {
            cur_rng_seed = cur_rng_seed * 0x41C64E6D + 0x3039;
        }

        
        beforeCall5 = cur_rng_seed;
        s32 cpuChosenIndex = func_800EEF80_102BA0(3);
        cpuChosenIndex++;
        //printf("Seed: %08lX, Index: %d\n", beforeCall5, cpuChosenIndex);
        if (cpuChosenIndex == 2) {
            for (s32 j = 0; j < 196; j++) {
                cur_rng_seed = cur_rng_seed * 0x41C64E6D + 0x3039;
            }
            beforeCall6 = cur_rng_seed;
            s32 percentChanceOfPick = func_800EEF80_102BA0(10.0f);
            if (percentChanceOfPick == 0 || percentChanceOfPick == 1) {
                //some advancements here
                for (s32 j = 0; j < 188; j++) {
                    cur_rng_seed = cur_rng_seed * 0x41C64E6D + 0x3039;
                }
                s32 itemChosen = func_800EEF80_102BA0(4);
                if (itemChosen == 3) {
                    //printf("Option 1: %08lX\n", seedTemp);
                    //printf("Option 1: %08lX: %08lX, %08lX, %08lX, %08lX, %08lX, %08lX\n", seedTemp, beforeCall1, beforeCall2, beforeCall3, beforeCall4, beforeCall5, beforeCall6);
                    printf("Calls: %d, Option 1: %08lX, Roll: %d\n", i, seedTemp, roll);
                }
                
                //printf("Seed:%08X Calls: %d\n", printSeed, i + 1);
            }
        } else if (cpuChosenIndex == 3) {
            for (s32 j = 0; j < 264; j++) {
                cur_rng_seed = cur_rng_seed * 0x41C64E6D + 0x3039;
            }
            beforeCall6 = cur_rng_seed;
            s32 percentChanceOfPick = func_800EEF80_102BA0(10.0f);
            if (percentChanceOfPick == 0 || percentChanceOfPick == 1 || percentChanceOfPick == 2) {
                //some advancements here
                for (s32 j = 0; j < 188; j++) {
                    cur_rng_seed = cur_rng_seed * 0x41C64E6D + 0x3039;
                }
                s32 itemChosen = func_800EEF80_102BA0(4);
                if (itemChosen == 3) {
                    //printf("Option 2: %08lX: %08lX, %08lX, %08lX, %08lX, %08lX, %08lX\n", seedTemp, beforeCall1, beforeCall2, beforeCall3, beforeCall4, beforeCall5, beforeCall6);
                    printf("Calls: %d, Option 2: %08lX, Roll: %d\n", i, seedTemp, roll);
                }
                //printf("%08lX: %08lX, %08lX, %08lX, %08lX, %08lX, %08lX\n", seedTemp, beforeCall1, beforeCall2, beforeCall3, beforeCall4, beforeCall5, beforeCall6);
                //printf("Seed:%08X Calls: %d\n", printSeed, i + 1);
            }
        } else {
            continue;
        }

    }
}

//4610

int main(int argc, char *argv[]) {
    //pthread_t threads[NUM_THREADS];

    // s32 gen = 0;
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

    //printf("%d", MeasureRngCalls(0x36891793, 0x6229FEDB));

    //CPUGetWatchFromItemSpace(1);

    // findValidSeeds();

    // if (argc != 2) {
    //     printf("Usage: %s <hexadecimal_seed>\n", argv[0]);
    //     return 1;
    // }

    // if (sscanf(argv[1], "0x%08lX", &cur_rng_seed) != 1) {
    //     if (strncmp("--gen", argv[1], sizeof("--gen")) == 0) {
    //         gen = 1;
    //     } else {
    //         printf("Invalid hexadecimal input. Please provide a 32-bit hexadecimal number.\n");
    //         return 1;
    //     }
    // }

    // if (gen == 1) {
    //     s32 prevItemLocation;
    //     Blocks blockVariables;
    //     s32 chain = 0;
    //     blockVariables.coinBlockSpaceIndex = -1;
    //     blockVariables.starBlockSpaceIndex = -1;
    //     blockVariables.itemBlockSpaceIndex = -1;
    //     cur_rng_seed = 0;
    //     func_800FC594_1101B4(&blockVariables);
    //     itemIDAmounts[blockVariables.itemBlockSpaceIndex]++;
    //     prevItemLocation = blockVariables.itemBlockSpaceIndex;
    //     for (u32 i = 1; i < 0x100000; i++) {
    //         blockVariables.coinBlockSpaceIndex = -1;
    //         blockVariables.starBlockSpaceIndex = -1;
    //         blockVariables.itemBlockSpaceIndex = -1;
    //         cur_rng_seed = i;
    //         func_800FC594_1101B4(&blockVariables);
    //         itemIDAmounts[blockVariables.itemBlockSpaceIndex]++;
    //         if (prevItemLocation == blockVariables.itemBlockSpaceIndex) {
    //             if (blockVariables.itemBlockSpaceIndex == 0x2C) {
    //                 chain++;
    //             } else {
    //                 chain = 0;
    //             }
    //             //
    //         }
    //         if (i % 1000000 == 0) {
    //             printf("Iterations: %ld\n", i);
    //         }
    //     }
    //     for (int i = 0; i < ARRAY_COUNT(itemIDAmounts); i++) {
    //         printf("Space %d: %ld\n", i, itemIDAmounts[i]);
    //     }
    // } else {
    //     Blocks blockVariables;
    //     blockVariables.coinBlockSpaceIndex = -1;
    //     blockVariables.starBlockSpaceIndex = -1;
    //     blockVariables.itemBlockSpaceIndex = -1;
    //     printf("Using Seed: 0x%08lX\n", cur_rng_seed);
    //     func_800FC594_1101B4(&blockVariables); //place hidden blocks
    //     printf("Coin Block Space ID: 0x%02X\n", blockVariables.coinBlockSpaceIndex);
    //     printf("Star Block Space ID: 0x%02X\n", blockVariables.starBlockSpaceIndex);
    //     printf("Item Block Space ID: 0x%02X\n", blockVariables.itemBlockSpaceIndex);
    // }

    return 0;
}