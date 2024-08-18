#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/mp3.h"

#define FAST_TEXT 0
#define NORMAL_TEXT 1
#define SLOW_TEXT 2

#define FAST_WALK 0
#define NORMAL_WALK 1
#define SLOW_WALK 2

#define RARE_ITEM_WATCH 3
#define TOAD_QUESTION 0

#define GREEDY_OPTION 0
#define MIDDLE_OPTION 1
#define BOTTOM_OPTION 2

#define ROLL_DICE_BLOCK_TIME 23

#define ANSI_COLOR_BLACK   "\033[30m"
#define ANSI_COLOR_RED     "\033[31m"
#define ANSI_COLOR_GREEN   "\033[32m"
#define ANSI_COLOR_YELLOW  "\033[33m"
#define ANSI_COLOR_BLUE    "\033[34m"
#define ANSI_COLOR_MAGENTA "\033[35m"
#define ANSI_COLOR_CYAN    "\033[36m"
#define ANSI_COLOR_WHITE   "\033[37m"

#define NO_DIRECTION_CHANGE 0

extern s16 D_800D03FC; //total coin blocks placed
extern s16 D_800CE208; //total star blocks placed
extern s16 D_800CDD68; //total item blocks placed
extern u16 chilly_waters_total_board_spaces;
extern u16 deep_blooper_sea_board_spaces;
extern u16 spiny_desert_board_spaces;
extern u16 woody_woods_board_spaces;
extern u16 creepy_cavern_total_board_spaces;

s32 DoCpuLogicGeneric(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 numOfJumps);
s32 DoCpuLogicChillyWaters(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 jumpsBeforeJunction, s32 jumpsAfterJunction);
s32 DoCpuLogicDeepBlooperSea(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 jumpsBeforeJunction, s32 jumpsAfterJunction);
s32 DoCpuLogicSpinyDesert(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 jumpsBeforeJunction, s32 jumpsAfterJunction, s32 itemSlot1);
s32 DoCpuLogicWoodyWoods1(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 jumpsBeforeJunction, s32 jumpsAfterJunction);
s32 DoCpuLogicCreepyCavern(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 jumpsBeforeJunction, s32 jumpsAfterJunction);
int aiMain(DecisionTreeNonLeafNode* node, s32 nodeCount, u32 seed);

//decision tree nodes for chilly waters first junction
DecisionTreeNonLeafNode ChillyWatersJunction0Nodes[] = {
    {
        .type = 0x02,
        .node_data1.data = 0x00000001,
        .node_data2.data = 0x1C96A846,
        .isPointer = 0,
    },
    {
        .type = 0x02,
        .node_data1.data = 0x00000042,
        .node_data2.data = 0x0C96A846,
        .isPointer = 0,
    },
    {
        .type = 0,
        .node_data1.data = 0x00,
        .node_data2.data = 0x064C9932,
        .isPointer = 0,
    }
};

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
        .isPointer = 1,
    },
    //is this needed?
    // {
    //     .type = 0,
    //     .node_data1.data = 0x00,
    //     .node_data2.data = 0x064C9932
    // }
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

//0x8011D338
DecisionTreeNonLeafNode CreepyCavernJunction4Nodes[] = {
    {
        .type = 0x03,
        .node_data1.data = 0x00000001,
        .node_data2.data = 0x1C96A33C,
        .isPointer = 0,
    },
    {
        .type = 0x00,
        .node_data1.data = 0x00000000,
        .node_data2.data = 0x0C96A33C,
        .isPointer = 0,
    },
};

//0x8011D374
DecisionTreeNonLeafNode CreepyCavernJunction3Nodes[] = {
    {
        .type = 0x03,
        .node_data1.data = 0x00000001,
        .node_data2.data = 0x1C96A33C,
        .isPointer = 0,
    },
    {
        .type = 0x00,
        .node_data1.data = 0x00000000,
        .node_data2.data = 0x0C96A33C,
        .isPointer = 0,
    },
};

//0x8011D350
DecisionTreeNonLeafNode CreepyCavernJunction2Nodes[] = {
    {
        .type = 0x04,
        .node_data1.data = 0x00300000,
        .node_data2.data = 0x1BF6A33C,
        .isPointer = 0,
    },
    {
        .type = 0x03,
        .node_data1.data = 0x00000004,
        .node_data2.data = 0x1C96A33C,
        .isPointer = 0,
    },
    {
        .type = 0x00,
        .node_data1.data = 0x00000000,
        .node_data2.data = 0x0C96A33C,
        .isPointer = 0,
    },
};

//0x8011D2F0
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
    //hopefully this is enough node data...
};

//decision tree nodes for woody woods first junction
//TODO: is this actually enough nodes?
//starts at 8011D3D4
DecisionTreeNonLeafNode CreepyCavernJunction0Nodes[] = {
    // //temp test
    // {
    //     .type = 0x02,
    //     .node_data1.data = 0x000000F0,
    //     .node_data2.data = 0x1BF6A33C
    // },
    // {
    //     .type = 0x02,
    //     .node_data1.data = 0x00000003,
    //     .node_data2.data = 0x0BF6A33C
    // },
    //end of temp test

    
    {
        .type = 0x08,
        .node_data1.data = 0x00000001,
        .node_data2.node_data = CreepyCavernJunction1Nodes, //0x8011D2F0
        .isPointer = 1,
    },

    {
        .type = 0x02,
        .node_data1.data = 0x00000001,
        .node_data2.node_data = CreepyCavernJunction2Nodes, //0x8011D350
        .isPointer = 1,
    },

    {
        .type = 0x02,
        .node_data1.data = 0x00000002,
        .node_data2.node_data = CreepyCavernJunction3Nodes, //0x8011D374
        .isPointer = 1,
    },

    // {
    //     .type = 0x00,
    //     .node_data1.data = 0x00000000,
    //     .node_data2.data = 0x0B54233C
    // },
    // {
    //     .type = 0x02,
    //     .node_data1.data = 0x00,
    //     .node_data2.data = 0x1B54233C
    // },
    // {
    //     .type = 0x00,
    //     .node_data1.data = 0x00,
    //     .node_data2.data = 0x064C9932
    // }
};

char* speedsText[] = {
    "FAST",
    "NORMAL",
    "SLOW",
};

//does not consider hidden block placement. Usually fine, but can rarely generate wrong seeds if 
//- a hidden block is placed on another hidden block and has to be randomly placed again
void CPUGetWatchGeneric(s32 rollValue, u32 numOfJumps) {
    u32 prevSeed = cur_rng_seed;

    for (u32 i = 0; i < 3000; i++) {
        if (i < 900) {
            ADV_SEED(cur_rng_seed);
            prevSeed = cur_rng_seed;
            continue;
        }
        //printf("CurSeed: %08lX\n", cur_rng_seed);
        cur_rng_seed = prevSeed;
        u32 seedTemp = cur_rng_seed;
        s32 roll = RollDice();
        
        prevSeed = cur_rng_seed;

        if (rollValue != 0) {
            if (roll != rollValue) {
                continue;
            }
        }

        //iterate over walk speeds and message speeds
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (DoCpuLogicGeneric(roll - 1, j, k, numOfJumps) == 1) {
                    printf("Calls: "ANSI_COLOR_GREEN"%ld"ANSI_COLOR_WHITE", Target: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08X, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i, i * 2,seedTemp, roll, speedsText[j], speedsText[k]);
                }
                cur_rng_seed = prevSeed;
            }
        }
    }
}

void CPUGetWatchChillyWaters(s32 rollValue, s32 jumpsBeforeJunction, s32 jumpsAfterJunction, s32 itemSlot1) {
    Blocks blockData;

    u32 prevSeed = cur_rng_seed;
    u32 seedBeforeInGameLogic;

    for (u32 i = 0; i < 3000; i++) {
        //printf("CurSeed: %08X\n", cur_rng_seed);
        cur_rng_seed = prevSeed;
        u32 seedTemp = cur_rng_seed;
        blockData.coinBlockSpaceIndex = -1;
        blockData.itemBlockSpaceIndex = -1;
        blockData.starBlockSpaceIndex = -1;
        func_800FC594_1101B4(&blockData, chilly_waters_total_board_spaces, CHILLY_WATERS); //place hidden blocks

        //sim time to load into game
        for (int j = 0; j < 70; j++) {
            ADV_SEED(cur_rng_seed);
        }

        u32 seedBeforeRoll = cur_rng_seed;
        //printf("Seed before roll: %08X\n", seedBeforeRoll);
        s32 roll = RollDice();
        

        if (rollValue != 0) {
            if (roll != rollValue) {
                cur_rng_seed = prevSeed;
                ADV_SEED(cur_rng_seed);
                prevSeed = cur_rng_seed;
                continue;
            }
        }

        seedBeforeInGameLogic = cur_rng_seed;

        //iterate over walk speeds and message speeds
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (DoCpuLogicChillyWaters(roll - 1, j, k, jumpsBeforeJunction, jumpsAfterJunction) == 1) {
                    //// printf("Seed before roll: %08lX\n", seedBeforeRoll);
                    //printf("Calls: "ANSI_COLOR_GREEN"%ld"ANSI_COLOR_WHITE", Target: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i, i * 2,seedTemp, roll, speedsText[j], speedsText[k]);
                    printf("Calls: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i, prevSeed, roll, speedsText[j], speedsText[k]);
                }
                cur_rng_seed = seedBeforeInGameLogic;
            }
        }
        cur_rng_seed = prevSeed;
        ADV_SEED(cur_rng_seed);
        prevSeed = cur_rng_seed;
    }
}

void CPUGetWatchDeepBlooperSea(s32 rollValue, s32 jumpsBeforeJunction, s32 jumpsAfterJunction, s32 itemSlot1) {
    Blocks blockData;

    u32 prevSeed = cur_rng_seed;
    u32 seedBeforeInGameLogic;
    u32 seedBeforeItemUse;
    s32 setSeedBeforeItemUse = 0;

    for (u32 i = 0; i < 3000; i++) {
        //printf("CurSeed: %08lX\n", cur_rng_seed);
        cur_rng_seed = prevSeed;
        u32 seedTemp = cur_rng_seed;
        blockData.coinBlockSpaceIndex = -1;
        blockData.itemBlockSpaceIndex = -1;
        blockData.starBlockSpaceIndex = -1;
        func_800FC594_1101B4(&blockData, deep_blooper_sea_board_spaces, DEEP_BLOOPER_SEA); //place hidden blocks

        //sim time to load into game
        for (int j = 0; j < 58; j++) {
            ADV_SEED(cur_rng_seed);
        }
        setSeedBeforeItemUse = 0;
        //check if cpu has mushroom and run logic accordingly
        if (itemSlot1 == MUSHROOM) {
            setSeedBeforeItemUse = 1;
            seedBeforeItemUse = cur_rng_seed;
            if (RNGPercentChance(80) == 1) {
                cur_rng_seed = prevSeed;
                ADV_SEED(cur_rng_seed);
                prevSeed = cur_rng_seed;
                continue;
            }
        }

        for (int j = 0; j < 12; j++) {
            ADV_SEED(cur_rng_seed);
        }

        // u32 seedBeforeRoll = cur_rng_seed;
        s32 roll = RollDice();
        
        if (rollValue != 0) {
            if (roll != rollValue) {
                cur_rng_seed = prevSeed;
                ADV_SEED(cur_rng_seed);
                prevSeed = cur_rng_seed;
                continue;
            }
        }

        seedBeforeInGameLogic = cur_rng_seed;

        //iterate over walk speeds and message speeds
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (DoCpuLogicDeepBlooperSea(roll - 1, j, k, jumpsBeforeJunction, jumpsAfterJunction) == 1) {
                    //// printf("Seed before roll: %08lX\n", seedBeforeRoll);
                    // printf("Calls: "ANSI_COLOR_GREEN"%ld"ANSI_COLOR_WHITE", Target: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i, i * 2,seedTemp, roll, speedsText[j], speedsText[k]);
                    // printf("Seed before roll: %08lX\n", seedBeforeRoll);
                    if (setSeedBeforeItemUse == 1) {
                        // printf("Seed before Rng Check %08lX\n", seedBeforeItemUse);
                    }
                    printf("Calls: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i,seedTemp, roll, speedsText[j], speedsText[k]);
                }
                cur_rng_seed = seedBeforeInGameLogic;
            }
        }
        cur_rng_seed = prevSeed;
        ADV_SEED(cur_rng_seed);
        prevSeed = cur_rng_seed;
    }
}

void CPUGetWatchSpinyDesert(s32 rollValue, s32 jumpsBeforeJunction, s32 jumpsAfterJunction, s32 itemSlot1) {
    Blocks blockData;

    u32 prevSeed = cur_rng_seed;
    u32 seedBeforeInGameLogic;
    u32 seedBeforeItemUse;
    s32 setSeedBeforeItemUse = 0;

    for (u32 i = 0; i < 5000; i++) {
        //printf("CurSeed: %08lX\n", cur_rng_seed);
        cur_rng_seed = prevSeed;
        blockData.coinBlockSpaceIndex = -1;
        blockData.itemBlockSpaceIndex = -1;
        blockData.starBlockSpaceIndex = -1;
        func_800FC594_1101B4(&blockData, spiny_desert_board_spaces, SPINY_DESERT); //place hidden blocks

        //sim time to load into game
        for (int j = 0; j < 58; j++) {
            ADV_SEED(cur_rng_seed);
        }
        setSeedBeforeItemUse = 0;
        //check if cpu has mushroom and run logic accordingly
        if (itemSlot1 == MUSHROOM) {
            setSeedBeforeItemUse = 1;
            seedBeforeItemUse = cur_rng_seed;
            if (RNGPercentChance(80) == 1) {
                cur_rng_seed = prevSeed;
                ADV_SEED(cur_rng_seed);
                prevSeed = cur_rng_seed;
                continue;
            }
        }

        for (int j = 0; j < 12; j++) {
            ADV_SEED(cur_rng_seed);
        }

        // u32 seedBeforeRoll = cur_rng_seed;
        s32 roll = RollDice();
        
        if (rollValue != 0) {
            if (roll != rollValue) {
                cur_rng_seed = prevSeed;
                ADV_SEED(cur_rng_seed);
                prevSeed = cur_rng_seed;
                continue;
            }
        }

        seedBeforeInGameLogic = cur_rng_seed;

        //iterate over walk speeds and message speeds
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (DoCpuLogicSpinyDesert(roll - 1, j, k, jumpsBeforeJunction, jumpsAfterJunction, itemSlot1) == 1) {
                    //// printf("Seed before roll: %08lX\n", seedBeforeRoll);
                    // printf("Calls: "ANSI_COLOR_GREEN"%ld"ANSI_COLOR_WHITE", Target: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i, i * 2,seedTemp, roll, speedsText[j], speedsText[k]);
                    // printf("Seed before roll: %08lX\n", seedBeforeRoll);
                    if (setSeedBeforeItemUse == 1) {
                        //printf("Seed before Rng Check %08lX\n", seedBeforeItemUse);
                    }
                    printf("Calls: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i, prevSeed, roll, speedsText[j], speedsText[k]);
                }
                cur_rng_seed = seedBeforeInGameLogic;
            }
        }
        cur_rng_seed = prevSeed;
        ADV_SEED(cur_rng_seed);
        prevSeed = cur_rng_seed;
    }
}

//this one is tricky. hidden blocks are placed when loading the stage, but we
// - wait until closing the text box of the sign turn to try and manip a wacky watch.
// - due to this, unfortunately we just pray we dont get extra advancements on block placement.
// perhaps a frame window of a second or so exist where we could avoid this issue
void CPUGetWatchWoodyWoods(s32 rollValue, s32 jumpsBeforeJunction, s32 jumpsAfterJunction, s32 itemSlot1) {
    Blocks blockData;

    u32 prevSeed = cur_rng_seed;
    u32 seedBeforeInGameLogic;
    u32 seedBeforeItemUse;
    s32 setSeedBeforeItemUse = 0;

    for (u32 i = 0; i < 3000; i++) {
        //printf("CurSeed: %08lX\n", cur_rng_seed);
        cur_rng_seed = prevSeed;
        u32 seedTemp = cur_rng_seed;
        blockData.coinBlockSpaceIndex = -1;
        blockData.itemBlockSpaceIndex = -1;
        blockData.starBlockSpaceIndex = -1;
        func_800FC594_1101B4(&blockData, woody_woods_board_spaces, WOODY_WOODS); //place hidden blocks

        //sim time to load into game
        for (int j = 0; j < 58; j++) {
            ADV_SEED(cur_rng_seed);
        }
        setSeedBeforeItemUse = 0;
        //check if cpu has mushroom and run logic accordingly
        if (itemSlot1 == MUSHROOM) {
            setSeedBeforeItemUse = 1;
            seedBeforeItemUse = cur_rng_seed;
            if (RNGPercentChance(80) == 1) {
                cur_rng_seed = prevSeed;
                ADV_SEED(cur_rng_seed);
                prevSeed = cur_rng_seed;
                continue;
            }
        }

        for (int j = 0; j < 12; j++) {
            ADV_SEED(cur_rng_seed);
        }

        u32 seedBeforeRoll = cur_rng_seed;
        s32 roll = RollDice();
        
        if (rollValue != 0) {
            if (roll != rollValue) {
                cur_rng_seed = prevSeed;
                ADV_SEED(cur_rng_seed);
                prevSeed = cur_rng_seed;
                continue;
            }
        }

        seedBeforeInGameLogic = cur_rng_seed;

        //iterate over walk speeds and message speeds
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (DoCpuLogicWoodyWoods1(roll - 1, j, k, jumpsBeforeJunction, jumpsAfterJunction) == 1) {
                    printf("Seed before roll: %08lX\n", seedBeforeRoll);
                    // printf("Calls: "ANSI_COLOR_GREEN"%ld"ANSI_COLOR_WHITE", Target: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i, i * 2,seedTemp, roll, speedsText[j], speedsText[k]);
                    // printf("Seed before roll: %08lX\n", seedBeforeRoll);
                    if (setSeedBeforeItemUse == 1) {
                        // printf("Seed before Rng Check %08lX\n", seedBeforeItemUse);
                    }
                    printf("Calls: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i,seedTemp, roll, speedsText[j], speedsText[k]);
                }
                cur_rng_seed = seedBeforeInGameLogic;
            }
        }
        cur_rng_seed = prevSeed;
        ADV_SEED(cur_rng_seed);
        prevSeed = cur_rng_seed;
    }
}

//this is broken, rip
void CPUGetWatchCreepyCavern(s32 rollValue, s32 jumpsBeforeJunction, s32 jumpsAfterJunction, s32 itemSlot1) {
    Blocks blockData;

    u32 prevSeed = cur_rng_seed;
    u32 seedBeforeInGameLogic;
    u32 seedBeforeItemUse;
    s32 setSeedBeforeItemUse = 0;

    for (u32 i = 0; i < 3000; i++) {
        //printf("CurSeed: %08lX\n", cur_rng_seed);
        cur_rng_seed = prevSeed;
        u32 seedTemp = cur_rng_seed;
        blockData.coinBlockSpaceIndex = -1;
        blockData.itemBlockSpaceIndex = -1;
        blockData.starBlockSpaceIndex = -1;
        func_800FC594_1101B4(&blockData, creepy_cavern_total_board_spaces, CREEPY_CAVERN); //place hidden blocks

        //sim time to load into game
        for (int j = 0; j < 58; j++) {
            ADV_SEED(cur_rng_seed);
        }
        setSeedBeforeItemUse = 0;
        //check if cpu has mushroom and run logic accordingly
        if (itemSlot1 == MUSHROOM) {
            setSeedBeforeItemUse = 1;
            seedBeforeItemUse = cur_rng_seed;
            if (RNGPercentChance(80) == 1) {
                cur_rng_seed = prevSeed;
                ADV_SEED(cur_rng_seed);
                prevSeed = cur_rng_seed;
                continue;
            }
        }

        for (int j = 0; j < 12; j++) {
            ADV_SEED(cur_rng_seed);
        }

        // u32 seedBeforeRoll = cur_rng_seed;
        s32 roll = RollDice();
        
        if (rollValue != 0) {
            if (roll != rollValue) {
                cur_rng_seed = prevSeed;
                ADV_SEED(cur_rng_seed);
                prevSeed = cur_rng_seed;
                continue;
            }
        }

        seedBeforeInGameLogic = cur_rng_seed;

        //iterate over walk speeds and message speeds
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (DoCpuLogicCreepyCavern(roll - 1, j, k, jumpsBeforeJunction, jumpsAfterJunction) == 1) {
                    //// printf("Seed before roll: %08lX\n", seedBeforeRoll);
                    // printf("Calls: "ANSI_COLOR_GREEN"%ld"ANSI_COLOR_WHITE", Target: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i, i * 2,seedTemp, roll, speedsText[j], speedsText[k]);
                    // printf("Seed before roll: %08lX\n", seedBeforeRoll);
                    if (setSeedBeforeItemUse == 1) {
                        // printf("Seed before Rng Check %08lX\n", seedBeforeItemUse);
                    }
                    printf("Calls: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i,seedTemp, roll, speedsText[j], speedsText[k]);
                }
                cur_rng_seed = seedBeforeInGameLogic;
            }
        }
        cur_rng_seed = prevSeed;
        ADV_SEED(cur_rng_seed);
        prevSeed = cur_rng_seed;
    }
}

void CPUGetWatchWaluigisIsland(s32 rollValue, s32 jumpsBeforeJunction, s32 jumpsAfterJunction, s32 itemSlot1) {
    Blocks blockData;

    u32 prevSeed = cur_rng_seed;
    u32 seedBeforeInGameLogic;
    u32 seedBeforeItemUse;
    s32 setSeedBeforeItemUse = 0;

    for (u32 i = 0; i < 3000; i++) {
        //printf("CurSeed: %08lX\n", cur_rng_seed);
        cur_rng_seed = prevSeed;
        u32 seedTemp = cur_rng_seed;
        blockData.coinBlockSpaceIndex = -1;
        blockData.itemBlockSpaceIndex = -1;
        blockData.starBlockSpaceIndex = -1;
        func_800FC594_1101B4(&blockData, chilly_waters_total_board_spaces, CREEPY_CAVERN); //place hidden blocks

        //sim time to load into game
        for (int j = 0; j < 58; j++) {
            ADV_SEED(cur_rng_seed);
        }
        setSeedBeforeItemUse = 0;
        //check if cpu has mushroom and run logic accordingly
        if (itemSlot1 == MUSHROOM) {
            setSeedBeforeItemUse = 1;
            seedBeforeItemUse = cur_rng_seed;
            if (RNGPercentChance(80) == 1) {
                cur_rng_seed = prevSeed;
                ADV_SEED(cur_rng_seed);
                prevSeed = cur_rng_seed;
                continue;
            }
        }

        for (int j = 0; j < 12; j++) {
            ADV_SEED(cur_rng_seed);
        }

        // u32 seedBeforeRoll = cur_rng_seed;
        s32 roll = RollDice();
        
        if (rollValue != 0) {
            if (roll != rollValue) {
                cur_rng_seed = prevSeed;
                ADV_SEED(cur_rng_seed);
                prevSeed = cur_rng_seed;
                continue;
            }
        }

        seedBeforeInGameLogic = cur_rng_seed;

        //iterate over walk speeds and message speeds
        // for (int j = 0; j < 3; j++) {
        //     for (int k = 0; k < 3; k++) {
        //         if (DoCpuLogicWaluigisIsland(roll - 1, j, k, jumpsBeforeJunction, jumpsAfterJunction) == 1) {
        //             //// printf("Seed before roll: %08lX\n", seedBeforeRoll);
        //             // printf("Calls: "ANSI_COLOR_GREEN"%ld"ANSI_COLOR_WHITE", Target: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i, i * 2,seedTemp, roll, speedsText[j], speedsText[k]);
        //             // printf("Seed before roll: %08lX\n", seedBeforeRoll);
        //             if (setSeedBeforeItemUse == 1) {
        //                 // printf("Seed before Rng Check %08lX\n", seedBeforeItemUse);
        //             }
        //             printf("Calls: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i,seedTemp, roll, speedsText[j], speedsText[k]);
        //         }
        //         cur_rng_seed = seedBeforeInGameLogic;
        //     }
        // }
        cur_rng_seed = prevSeed;
        ADV_SEED(cur_rng_seed);
        prevSeed = cur_rng_seed;
    }
}

s32 callAmountBetweenSpace[] = {6, 11, 16};

s32 messageSpeedsArray0[] = {648, 728, 868};

//advancements that happen during cpu selection on each message speed
s32 CpuSelectionArray1[] = {116, 196, 336};

s32 CpuSelectionArray2[] = {184, 264, 404};

//advancements that happen before rare item is decided
s32 CpuSelectionArray3[] = {108, 188, 328};

//advancements during bank visit based on text speed
s32 CpuSelectionArray4[] = {167, 207, 277};

s32 CpuSelectionArray4Backup[] = {159, 199, 269};

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

void DoJumpAdvancements(s32 walkSpeed, u32 numOfJumps) {
    switch (walkSpeed) {
    case 0:
        for (int i = 0; i < 2 * numOfJumps; i++) {
            ADV_SEED(cur_rng_seed);
        }
        break;
    case 1:
        for (int i = 0; i < 5 * numOfJumps; i++) {
            ADV_SEED(cur_rng_seed);
        }
        break;
    case 2:
        for (int i = 0; i < 15 * numOfJumps; i++) {
            ADV_SEED(cur_rng_seed);
        }
        break;
    }
}

s32 DoJunction(s32 advancements, s32 odds, s32 outcomeWanted, s32 jumpsBeforeJunction, s32 walkSpeed) {
    //advance game up to junction decision
    for (int i = 0; i < advancements; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //wait 5 frames after making it to junction before cpu decides where to go
    for (int i = 0; i < 5; i++) {
        ADV_SEED(cur_rng_seed);
    }

    if (jumpsBeforeJunction != 0) {
        DoJumpAdvancements(walkSpeed, jumpsBeforeJunction);
    }

    if ((RNGPercentChance(odds) != outcomeWanted)) {
        return 0;
    }

    if (outcomeWanted == 1) { //CPU went the way the arrow as already facing
        for (int i = 0; i < 42; i++) {
            ADV_SEED(cur_rng_seed);
        }        
    } else {
        for (int i = 0; i < 51; i++) {
            ADV_SEED(cur_rng_seed);
        }     
    }

    return 1;
}

void DoBankAdvancements(s32 messageSpeed) {
    //player face bank when passing it
    for (int i = 0; i < 8; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //time at bank
    for (int i = 0; i < CpuSelectionArray4Backup[messageSpeed]; i++) {
        ADV_SEED(cur_rng_seed);
    }
}

void DoUpToJunctionAdvancements(s32 j) {
    //advance game up to junction decision
    for (int i = 0; i < j; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //wait 5 frames after making it to junction before cpu decides where to go
    for (int i = 0; i < 5; i++) {
        ADV_SEED(cur_rng_seed);
    }
}

//works when the cpu only needs to go across spaces to get to item space
s32 DoCpuLogicGeneric(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 numOfJumps) {
    if (numOfJumps != 0) {
        DoJumpAdvancements(walkSpeed, numOfJumps);
    }
    //get cpu to item space. NOTE: requires only spaces between start and target space
    int advancements = ROLL_DICE_BLOCK_TIME + callAmountBetweenSpace[walkSpeed] * (rollIndex + 1);

    for (int i = 0; i < advancements; i++) {
        ADV_SEED(cur_rng_seed);
    }
    //player turn to space
    for (int i = 0; i < 8; i++) {
        ADV_SEED(cur_rng_seed);
    }
    return HandleLogicFromItemSpace(messageSpeed);
}

s32 DoCpuLogicChillyWaters(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 jumpsBeforeJunction, s32 jumpsAfterJunction) {
    s32 ret = 0;
    int rngAdvancements = 0;
    switch(rollIndex) {
        case 8:
        case 7:
        case 6:
        case 5:
        case 4:    
            rngAdvancements = ROLL_DICE_BLOCK_TIME + (callAmountBetweenSpace[walkSpeed] * (rollIndex - 3));
            
            // walk to bank
            for (int i = 0; i < rngAdvancements; i++) {
                ADV_SEED(cur_rng_seed);
            }

            DoBankAdvancements(messageSpeed);
        case 3:
        case 2:
            if (jumpsBeforeJunction != 0) {
                DoJumpAdvancements(walkSpeed, jumpsBeforeJunction);
            }
            //2 spaces after bank but before junction
            if (rollIndex > 3) {
                rngAdvancements = (callAmountBetweenSpace[walkSpeed] * 2);
            } else {
                rngAdvancements  = ROLL_DICE_BLOCK_TIME + (callAmountBetweenSpace[walkSpeed] * (rollIndex - 1));
            }

            DoUpToJunctionAdvancements(rngAdvancements);

            if (aiMain(ChillyWatersJunction0Nodes, ARRAY_COUNT(ChillyWatersJunction0Nodes), cur_rng_seed) == 1) {
                return 0;
            }
            
            //cpu decision time (cpu chose the way the arrow was already facing)
            //TODO: figure out time if cpu needs to swap directions
            for (int i = 0; i < 42; i++) {
                ADV_SEED(cur_rng_seed);
            }

        // //after junction
        case 1:
        case 0:
            if (jumpsAfterJunction != 0) {
                DoJumpAdvancements(walkSpeed, jumpsAfterJunction);
            }
            //advance rng up to item space event decision
            if (rollIndex > 1) {
                rngAdvancements = (callAmountBetweenSpace[walkSpeed] * 3);
            } else {
                rngAdvancements = ROLL_DICE_BLOCK_TIME + callAmountBetweenSpace[walkSpeed] * (rollIndex + 1);
            }
            
            for (int i = 0; i < rngAdvancements; i++) {
                ADV_SEED(cur_rng_seed);
            }
            
            //player face screen after stopping
            for (int i = 0; i < 8; i++) {
                ADV_SEED(cur_rng_seed);
            }

            ret = HandleLogicFromItemSpace(messageSpeed);
            break;
    }
    return ret;
}

s32 DoCpuLogicDeepBlooperSea(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 jumpsBeforeJunction, s32 jumpsAfterJunction) {
    s32 ret = 0;
    int rngAdvancements = 0;
    u32 seedBeforeJunction = 0;
    u32 seedBeforeItemSpaceEventDecision = 0;

    switch(rollIndex) {
        case 9:
        case 8:
        case 7:
        case 6:        
            rngAdvancements = ROLL_DICE_BLOCK_TIME + (callAmountBetweenSpace[walkSpeed] * (rollIndex - 5));
            
            // walk to bank
            for (int i = 0; i < rngAdvancements; i++) {
                ADV_SEED(cur_rng_seed);
            }

            DoBankAdvancements(messageSpeed);
        case 5:
        case 4:
            if (jumpsBeforeJunction != 0) {
                DoJumpAdvancements(walkSpeed, jumpsBeforeJunction);
            }
            //2 spaces after bank but before junction
            if (rollIndex > 5) {
                rngAdvancements = (callAmountBetweenSpace[walkSpeed] * 2);
            } else {
                rngAdvancements  = ROLL_DICE_BLOCK_TIME + (callAmountBetweenSpace[walkSpeed] * (rollIndex - 3));
            }

            DoUpToJunctionAdvancements(rngAdvancements);

            // cpu decides direction
            // printf("Seed before junction: %08lX\n", cur_rng_seed);
            // seedBeforeJunction = cur_rng_seed;
            if (aiMain(DeepBlooperSeaJunction0Nodes, ARRAY_COUNT(DeepBlooperSeaJunction0Nodes), cur_rng_seed) == 0) {
                return 0;
            }

            //cpu decision time (cpu chose the way the arrow was already facing)
            //42 if same direction, 51 if not
            for (int i = 0; i < 51; i++) {
                ADV_SEED(cur_rng_seed);
            }

        //after junction
        case 3:
        case 2:
        case 1:
        case 0:
            if (jumpsAfterJunction != 0) {
                DoJumpAdvancements(walkSpeed, jumpsAfterJunction);
            }
            //advance rng up to item space event decision
            if (rollIndex > 3) {
                rngAdvancements = (callAmountBetweenSpace[walkSpeed] * 5);
            } else {
                rngAdvancements = ROLL_DICE_BLOCK_TIME + callAmountBetweenSpace[walkSpeed] * (rollIndex + 1);
            }
            
            for (int i = 0; i < rngAdvancements; i++) {
                ADV_SEED(cur_rng_seed);
            }
            
            //player face screen after stopping
            for (int i = 0; i < 8; i++) {
                ADV_SEED(cur_rng_seed);
            }
            //printf("Seed before Item Space Event: %08lX\n", cur_rng_seed);
            seedBeforeItemSpaceEventDecision = cur_rng_seed;
            //printf("Seed before junction: %08lX, Seed Before Item Space: %08lX\n", seedBeforeJunction, seedBeforeItemSpaceEventDecision);
            ret = HandleLogicFromItemSpace(messageSpeed);
            break;
    }
    return ret;
}

s32 DoCpuLogicSpinyDesert(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 jumpsBeforeJunction, s32 jumpsAfterJunction, s32 itemSlot1) {
    int rngAdvancements;
    u32 seedBeforeJunction = 0;
    switch (rollIndex) {
        case 9:
        case 8:
        case 7:
            if (jumpsBeforeJunction != 0) {
                DoJumpAdvancements(walkSpeed, jumpsBeforeJunction);
            }
        
            rngAdvancements  = ROLL_DICE_BLOCK_TIME + (callAmountBetweenSpace[walkSpeed] * (rollIndex - 6));
            //printf("number of advancements: %d\n", rngAdvancements);
            DoUpToJunctionAdvancements(rngAdvancements);

            //cpu decides direction
            //printf("Seed before junction: %08lX\n", cur_rng_seed);
            seedBeforeJunction = cur_rng_seed;

            if (itemSlot1 == SKELETON_KEY) {
                // if (RNGPercentChance(60) == 0) {
                //     return 0;
                // }
                //unknown what this should actually be. pick high number that should handle all cases?
                if (RNGPercentChance(60) == 1) {
                    return 0;
                }           
            } else {
                if (RNGPercentChance(60) == 1) {
                    return 0;
                }
            }

            //cpu decision time (cpu chose the way the arrow was already facing)
            //Note: Arrow always starts facing left?

            //42 if cpu goes same direction arrow starts (left); 51 advancements if arrow needs to change
            for (int i = 0; i < 42; i++) {
                ADV_SEED(cur_rng_seed);
            }
        case 6:
        case 5:
        case 4:
        case 3:
        case 2:
        case 1:
        case 0:
            if (jumpsAfterJunction != 0) {
                DoJumpAdvancements(walkSpeed, jumpsAfterJunction);
            }
            //advance rng up to item space event decision
            if (rollIndex > 6) {
                rngAdvancements = (callAmountBetweenSpace[walkSpeed] * 8);
            } else {
                rngAdvancements = ROLL_DICE_BLOCK_TIME + callAmountBetweenSpace[walkSpeed] * (rollIndex + 1);
            }

            for (int i = 0; i < rngAdvancements; i++) {
                ADV_SEED(cur_rng_seed);
            }     

            //player turn to space
            for (int i = 0; i < 8; i++) {
                ADV_SEED(cur_rng_seed);
            }
            // printf("seedBeforeJunction %08lX\n", seedBeforeJunction);
            return HandleLogicFromItemSpace(messageSpeed);  
    }
    return 0;
}

s32 DoCpuLogicWoodyWoods1(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 jumpsBeforeJunction, s32 jumpsAfterJunction) {
    int rngAdvancements;

    switch (rollIndex) {
        case 9:
        case 8:
        case 7:
            if (jumpsBeforeJunction != 0) {
                DoJumpAdvancements(walkSpeed, jumpsBeforeJunction);
            }
            rngAdvancements  = ROLL_DICE_BLOCK_TIME + (callAmountBetweenSpace[walkSpeed] * (rollIndex - 6));
            //printf("number of advancements: %d\n", rngAdvancements);
            DoUpToJunctionAdvancements(rngAdvancements);

            //cpu decides direction
            //printf("Seed before junction: %08lX\n", cur_rng_seed);

            if (aiMain(WoodyWoodsJunction0Nodes, ARRAY_COUNT(WoodyWoodsJunction0Nodes), cur_rng_seed) == 0) {
                return 0;
            }

            // //easy difficulty decision
            // if (RNGPercentChance(60) == 1) { //changes from base direction
            //     return 0;
            // }

            //for normal
            // if (RNGPercentChance(70) == 1) { //changes from base direction
            //     return 0;
            // }
            //cpu decision time (cpu chose the way the arrow was already facing)
            //TODO: figure out time if cpu needs to swap directions
            //Note: Arrow always starts facing left?

            //42 if same direction, 51 if not
            for (int i = 0; i < 51; i++) {
                ADV_SEED(cur_rng_seed);
            }
        case 6:
        case 5:
        case 4:
        case 3:
        case 2:
        case 1:
        case 0:
            if (jumpsAfterJunction != 0) {
                DoJumpAdvancements(walkSpeed, jumpsAfterJunction);
            }
            //advance rng up to item space event decision
            if (rollIndex > 6) {
                rngAdvancements = (callAmountBetweenSpace[walkSpeed] * 8);
            } else {
                rngAdvancements = ROLL_DICE_BLOCK_TIME + callAmountBetweenSpace[walkSpeed] * (rollIndex + 1);
            }

            for (int i = 0; i < rngAdvancements; i++) {
                ADV_SEED(cur_rng_seed);
            }

            //player turn to space
            for (int i = 0; i < 8; i++) {
                ADV_SEED(cur_rng_seed);
            }
            return HandleLogicFromItemSpace(messageSpeed);  
    }
    return 0;
}


s32 DoCpuLogicCreepyCavern(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 jumpsBeforeJunction, s32 jumpsAfterJunction) {
    int rngAdvancements;

    switch (rollIndex) {
        case 6:
        case 5:
        case 4:

            rngAdvancements = ROLL_DICE_BLOCK_TIME + (callAmountBetweenSpace[walkSpeed] * (rollIndex - 3));
            
            // walk to bank
            for (int i = 0; i < rngAdvancements; i++) {
                ADV_SEED(cur_rng_seed);
            }

            DoBankAdvancements(messageSpeed);
        case 3:
        case 2:
        case 1:
        case 0:
            if (jumpsBeforeJunction != 0) {
                DoJumpAdvancements(walkSpeed, jumpsBeforeJunction);
            }

            if (rollIndex > 3) {
                rngAdvancements = (callAmountBetweenSpace[walkSpeed] * 4);
            } else {
                rngAdvancements = ROLL_DICE_BLOCK_TIME + callAmountBetweenSpace[walkSpeed] * (rollIndex + 1);
            }
            //printf("number of advancements: %d\n", rngAdvancements);
            DoUpToJunctionAdvancements(rngAdvancements);

            //cpu decides direction
            //printf("Seed before junction: %08lX\n", cur_rng_seed);

            // //easy difficulty decision
            // if (RNGPercentChance(60) == 1) { //cpu didnt change direction, exit
            //     return 0;
            // }

            //this node is kind of weird and breaks the normal ARRAY_COUNT macro from working
            //have to hardcode the node count to an arbitrary number
            if (aiMain(CreepyCavernJunction0Nodes, 10, cur_rng_seed) == 1) {
                return 0;
            }

            //change direction of the junction
            for (int i = 0; i < 51; i++) {
                ADV_SEED(cur_rng_seed);
            }

            for (int i = 0; i < callAmountBetweenSpace[walkSpeed]; i++) {
                ADV_SEED(cur_rng_seed);
            }

            //player turn to space
            for (int i = 0; i < 8; i++) {
                ADV_SEED(cur_rng_seed);
            }

            //printf("Seed before item space event: %08lX\n", cur_rng_seed);
            return HandleLogicFromItemSpace(messageSpeed);
    }
    return 0;
}