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


s32 DoCpuLogicChillyWaters(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, u32 numOfJumps);
s32 DoCpuLogicDeepBlooperSea(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 jumpsBeforeJunction, s32 jumpsAfterJunction);
s32 DoCpuLogicSpinyDesert(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 jumpsBeforeJunction, s32 jumpsAfterJunction);
s32 DoCpuLogicWoodyWoods1(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, u32 numOfJumps);

char* speedsText[] = {
    "FAST",
    "NORMAL",
    "SLOW",
};

void CPUGetWatchGeneric(s32 rollValue, u32 numOfJumps) {
    u32 prevSeed = cur_rng_seed;
    //204 calls from A press on cannon to cpu roll. not used, just a note
    for (u32 i = 0; i < 3000; i++) {
        if (i < 900) {
            ADV_SEED(cur_rng_seed);
            prevSeed = cur_rng_seed;
            continue;
        }
        //printf("CurSeed: %08lX\n", cur_rng_seed);
        cur_rng_seed = prevSeed;
        u32 seedTemp = cur_rng_seed;
        s32 roll = rollDice();
        
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
                    printf("Calls: "ANSI_COLOR_GREEN"%ld"ANSI_COLOR_WHITE", Target: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i, i * 2,seedTemp, roll, speedsText[j], speedsText[k]);
                }
                cur_rng_seed = prevSeed;
            }
        }
    }
}

void CPUGetWatchChillyWaters(s32 rollValue, u32 numOfJumps) {
    u32 prevSeed = cur_rng_seed;
    //204 calls from A press on cannon to cpu roll. not used, just a note
    for (u32 i = 0; i < 3000; i++) {
        //printf("CurSeed: %08lX\n", cur_rng_seed);
        cur_rng_seed = prevSeed;
        u32 seedTemp = cur_rng_seed;
        s32 roll = rollDice();
        
        prevSeed = cur_rng_seed;

        if (rollValue != 0) {
            if (roll != rollValue) {
                continue;
            }
        }

        //iterate over walk speeds and message speeds
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (DoCpuLogicChillyWaters(roll - 1, j, k, numOfJumps) == 1) {
                    printf("Calls: "ANSI_COLOR_GREEN"%ld"ANSI_COLOR_WHITE", Target: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i, i * 2,seedTemp, roll, speedsText[j], speedsText[k]);
                }
                cur_rng_seed = prevSeed;
            }
        }
    }
}

void CPUGetWatchDeepBlooperSea(s32 rollValue, s32 jumpsBeforeJunction, s32 jumpsAfterJunction) {
    u32 prevSeed = cur_rng_seed;
    //204 calls from A press on cannon to cpu roll. not used, just a note
    for (u32 i = 0; i < 3000; i++) {
        if (i < 900) {
            ADV_SEED(cur_rng_seed);
            prevSeed = cur_rng_seed;
            continue;
        }
        //printf("CurSeed: %08lX\n", cur_rng_seed);
        cur_rng_seed = prevSeed;
        u32 seedTemp = cur_rng_seed;
        s32 roll = rollDice();
        
        prevSeed = cur_rng_seed;

        if (rollValue != 0) {
            if (roll != rollValue) {
                continue;
            }
        }

        //iterate over walk speeds and message speeds
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (DoCpuLogicDeepBlooperSea(roll - 1, j, k, jumpsBeforeJunction, jumpsAfterJunction) == 1) {
                    printf("Calls: "ANSI_COLOR_GREEN"%ld"ANSI_COLOR_WHITE", Target: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i, i * 2,seedTemp, roll, speedsText[j], speedsText[k]);
                }
                cur_rng_seed = prevSeed;
            }
        }
    }
}

void CPUGetWatchSpinyDesert(s32 rollValue, s32 jumpsBeforeJunction, s32 jumpsAfterJunction) {
    u32 prevSeed = cur_rng_seed;
    //204 calls from A press on cannon to cpu roll. not used, just a note
    for (u32 i = 0; i < 3000; i++) {
        if (i < 900) {
            ADV_SEED(cur_rng_seed);
            prevSeed = cur_rng_seed;
            continue;
        }
        //printf("CurSeed: %08lX\n", cur_rng_seed);
        cur_rng_seed = prevSeed;
        u32 seedTemp = cur_rng_seed;
        s32 roll = rollDice();
        
        prevSeed = cur_rng_seed;

        if (rollValue != 0) {
            if (roll != rollValue) {
                continue;
            }
        }

        //iterate over walk speeds and message speeds
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (DoCpuLogicSpinyDesert(roll - 1, j, k, jumpsBeforeJunction, jumpsAfterJunction) == 1) {
                    printf("Calls: "ANSI_COLOR_GREEN"%ld"ANSI_COLOR_WHITE", Target: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i, i * 2,seedTemp, roll, speedsText[j], speedsText[k]);
                }
                cur_rng_seed = prevSeed;
            }
        }
    }    
}

void CPUGetWatchWoodyWoods(s32 rollValue, u32 numOfJumps) {
    u32 prevSeed = cur_rng_seed;

    // //extra advancements for cannon shot
    // for (int i = 0; i < 33 * 2; i++) {
    //     ADV_SEED(cur_rng_seed);
    // }
    // //do advancements after pressing A on text box
    // for (int i = 0; i < 92; i++) {
    //     ADV_SEED(cur_rng_seed);
    // }
    //204 calls from A press on cannon to cpu roll. not used, just a note
    for (u32 i = 0; i < 3000; i++) {
        if (i < 900) {
            ADV_SEED(cur_rng_seed);
            prevSeed = cur_rng_seed;
            continue;
        }
        //printf("CurSeed: %08lX\n", cur_rng_seed);
        cur_rng_seed = prevSeed;
        u32 seedTemp = cur_rng_seed;
        s32 roll = rollDice();
        
        prevSeed = cur_rng_seed;

        if (rollValue != 0) {
            if (roll != rollValue) {
                continue;
            }
        }

        //iterate over walk speeds and message speeds
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (DoCpuLogicWoodyWoods1(roll - 1, j, k, numOfJumps) == 1) {
                    printf("Calls: "ANSI_COLOR_GREEN"%ld"ANSI_COLOR_WHITE", Target: "ANSI_COLOR_YELLOW"%ld"ANSI_COLOR_WHITE", Seed: %08lX, Roll: "ANSI_COLOR_MAGENTA"%ld"ANSI_COLOR_WHITE" \t| Walk: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE" \t| Message: "ANSI_COLOR_RED"%s"ANSI_COLOR_WHITE"\n", i, i * 2,seedTemp, roll, speedsText[j], speedsText[k]);
                }
                cur_rng_seed = prevSeed;
            }
        }
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

    if (outcomeWanted == NO_DIRECTION_CHANGE) { //CPU went the way the arrow as already facing
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
s32 DoCpuLogicGeneric(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, u32 numOfJumps) {
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

s32 DoCpuLogicChillyWaters(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, u32 numOfJumps) {
    s32 ret = 0;
    int rngAdvancements = 0;
    if (numOfJumps != 0) {
        DoJumpAdvancements(walkSpeed, numOfJumps);
    }
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
            //2 spaces after bank but before junction
            if (rollIndex > 3) {
                rngAdvancements = (callAmountBetweenSpace[walkSpeed] * 2);
            } else {
                rngAdvancements  = ROLL_DICE_BLOCK_TIME + (callAmountBetweenSpace[walkSpeed] * (rollIndex - 1));
            }

            DoUpToJunctionAdvancements(rngAdvancements);

            //cpu decides direction
            if (RNGPercentChance(50) == 0) { //CPU went up
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
            //2 spaces after bank but before junction
            if (rollIndex > 5) {
                rngAdvancements = (callAmountBetweenSpace[walkSpeed] * 2);
            } else {
                rngAdvancements  = ROLL_DICE_BLOCK_TIME + (callAmountBetweenSpace[walkSpeed] * (rollIndex - 3));
            }

            s32 junctionOutcome = DoJunction(rngAdvancements, 70, 0, jumpsBeforeJunction, walkSpeed);
            if (junctionOutcome == 0) {
                return 0;
            }

            // DoUpToJunctionAdvancements(rngAdvancements);

            // //cpu decides direction
            // //printf("Seed before junction: %08lX\n", cur_rng_seed);
            // if (RNGPercentChance(70) == 1) { //CPU went left
            //     return 0;
            // }
            // //cpu decision time (cpu chose the way the arrow was already facing)
            // //TODO: figure out time if cpu needs to swap directions

            // //42 if same direction, 51 if not
            // for (int i = 0; i < 51; i++) {
            //     ADV_SEED(cur_rng_seed);
            // }

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
            ret = HandleLogicFromItemSpace(messageSpeed);
            break;
    }
    return ret;
}

s32 DoCpuLogicSpinyDesert(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, s32 jumpsBeforeJunction, s32 jumpsAfterJunction) {
    int rngAdvancements;
    switch (rollIndex) {
        case 9:
        case 8:
        case 7:
        
            rngAdvancements  = ROLL_DICE_BLOCK_TIME + (callAmountBetweenSpace[walkSpeed] * (rollIndex - 6));
            s32 junctionOutcome = DoJunction(rngAdvancements, 60, NO_DIRECTION_CHANGE, jumpsBeforeJunction, walkSpeed);
            if (junctionOutcome == 0) {
                return 0;
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

            //NOTE! For reasons unknown, advance 2 extra times??
            // for (int i = 0; i < 2; i++) {
            //     ADV_SEED(cur_rng_seed);
            // }
        

            //player turn to space
            for (int i = 0; i < 8; i++) {
                ADV_SEED(cur_rng_seed);
            }
            return HandleLogicFromItemSpace(messageSpeed);  
    }
    return 0;
}

s32 DoCpuLogicWoodyWoods1(s32 rollIndex, s32 walkSpeed, s32 messageSpeed, u32 numOfJumps) {
    int rngAdvancements;
    if (numOfJumps != 0) {
        switch (walkSpeed) {
        case 0:
            for (int i = 0; i < 2; i++) {
                ADV_SEED(cur_rng_seed);
            }
            break;
        case 1:
            for (int i = 0; i < 5; i++) {
                ADV_SEED(cur_rng_seed);
            }
            break;
        case 2:
            for (int i = 0; i < 15; i++) {
                ADV_SEED(cur_rng_seed);
            }
            break;
        }
    }

    switch (rollIndex) {
        case 9:
        case 8:
        case 7:
        
            rngAdvancements  = ROLL_DICE_BLOCK_TIME + (callAmountBetweenSpace[walkSpeed] * (rollIndex - 6));
            //printf("number of advancements: %d\n", rngAdvancements);
            DoUpToJunctionAdvancements(rngAdvancements);

            //cpu decides direction
            //printf("Seed before junction: %08lX\n", cur_rng_seed);

            //easy difficulty decision
            if (RNGPercentChance(60) == 1) { //changes from base direction
                return 0;
            }

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