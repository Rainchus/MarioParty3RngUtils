#include "mp3.h"
#include "util.h"
#include <stdio.h>

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

u32 cur_rng_seed = 0x0000D9ED; //initial starting seed D_80097650
//
s32 framesForInitialTextBoxes[] = {648, 728, 868};

//advancements that happen during cpu selection on each message speed
s32 CpuSelectionArray0[] = {116, 196, 336};
s32 CpuSelectionArray1[] = {184, 264, 404};

//advancements that happen before rare item is decided
s32 CpuSelectionArray2[] = {108, 188, 328};

//advancements that happen while a cpu is at a bank at all 3 message speeds
s32 CpuBankRngAdvancements[] = {159, 199, 269};

GameStatus gGameStatus = {
    .unk0 = 1,
    .boardIndex = CHILLY_WATERS,
    .TotalTurns = 20,
    .CurrentTurn = 1,
    .curGameLength = 0, //20 turns
    .curStarSpawnIndex = 0, //TODO, verify this
    //does the game randomize these on board load and then randomly pick from one?
    .starSpawnIndicies = {1, 3, 2, 0, 4, 6, 5, 7}, //TODO, verify this
    .unkE = 0,
    .curPlayerIndex = 0,
    .unkData.unkArray_s16 = {0},
    .D_800CD096_s16 = {{0}},
    .D_800CD0B6 = {0x00, 0x00, 0x00, 0x00}, //is this longer?
};

u8 StarSpaceFlagArray[][2] = {
    {0x89, 0xBF}, //star space index 0
    {0x49, 0xBF}, //star space index 1
    {0xC9, 0xBE}, //star space index 2
    {0xC9, 0xBD}, //star space index 3
    {0xC9, 0xBB}, //star space index 4
    {0xC9, 0xB7}, //star space index 5
    {0xC9, 0xAF}, //star space index 6
    {0xC9, 0x9F}, //star space index 7
};



void SetStarSpawnData(s32 starSpawnIndex, s32 boardIndex) {
    //only first 2 bytes matter
    gGameStatus.D_800CD0B6[0] = StarSpaceFlagArray[starSpawnIndex][0];
    gGameStatus.D_800CD0B6[1] = StarSpaceFlagArray[starSpawnIndex][1];

    printf("[0]: %02X, [1]: %02X, [2]: %02X, [3]: %02X\n", gGameStatus.D_800CD0B6[0], gGameStatus.D_800CD0B6[1], gGameStatus.D_800CD0B6[2], gGameStatus.D_800CD0B6[3]);
}

s16 GetCurrentPlayerIndex(void) {
    return gGameStatus.curPlayerIndex;
}

Player* GetPlayerStruct(s32 index) {
    if (index < 0) {
        index = GetCurrentPlayerIndex();
    }
    return &gPlayers[index];
}

u8 rand8(void) {
    cur_rng_seed = cur_rng_seed * 0x41C64E6D + 0x3039;
    return (cur_rng_seed + 1) >> 16;
}

//func_800ECE9C
s16 RNGPercentChance(s8 percentChance) {
    u32 result;
    u32 randVal;

    randVal = rand8();
    //printf("randVal is %08X\n", randVal);
    result = (percentChance > ((randVal * 99) >> 8));

    return result;
}

s32 func_800EEF80_102BA0(f32 arg0) { //800EFE20 in duel mode
    // rand8 returns an unsigned byte
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);

    // Normalize the 16-bit number to the range [0, 1), then multiply by arg0
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;
    
    return scaledRandom;
}

u8 RollDice(void) { //func_800DBC2C in board play, func_800DB148 in duel mode
    u8 randByte = rand8();
    return ((randByte % 10) + 1);
}

//8 rng advancements to face fowards
void PlayerFaceForward(void) {
    for (int i = 0; i < 8; i++) {
        ADV_SEED(cur_rng_seed);
    }    
}

u32 MeasureRngCalls(u32 seedStart, u32 seedEnd) {
    u32 calls = 0;
    cur_rng_seed = seedStart;
    while (cur_rng_seed != seedEnd) {
        if (calls > 10000000) {
            printf("Is more than 10 million calls away...\n");
            return -1;
        }
        rand8();
        calls++;
    }
    return calls;
}

s32 GetSpaceIndexFromChainAndSpace(s32 curChainIndex, s32 curSpaceIndex) {
    SpaceChain* curBoardChains = BoardChains[gGameStatus.boardIndex].boardChainData;
    s16* curSpaceChain = curBoardChains[curChainIndex].spaceChainArray;
    return curSpaceChain[curSpaceIndex];
}

void SetPlayerNextChainAndSpaceFromAbsSpace(s32 absSpace, s32 mode) {
    u32 AbsSpace = GetChainAndSpaceFromAbsSpace(absSpace);

    switch (mode) {
    case SET_CURRENT:
        gPlayers[0].cur_chain_index = AbsSpace >> 16;
        gPlayers[0].cur_space_index = AbsSpace & 0xFFFF;
        break;
    case SET_NEXT:
        gPlayers[0].next_chain_index = AbsSpace >> 16;
        gPlayers[0].next_space_index = AbsSpace & 0xFFFF;
        break;
    }
}

//handles all rng related things starting at decision of item space event
s32 HandleLogicFromItemSpace(s32 messageSpeed, s16* data) {
    u32 rngBeforeItemSpaceResult = cur_rng_seed;
    
    s32 itemSpaceOutcome = func_800EEF80_102BA0(5.0f);
    if (itemSpaceOutcome != TOAD_QUESTION) {
        return 0;
    }

    //advance rng up to text box based on text speed
    for (int i = 0; i < framesForInitialTextBoxes[messageSpeed]; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //get random question (advances rng twice)
    func_800EEF80_102BA0(5.0f);

    //advance rng through text box popping up
    for (int i = 0; i < 56; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //cpu choosen an option to the question
    s32 cpuChosenIndex = func_800EEF80_102BA0(3);

    s32 textBoxFrames;
    if (cpuChosenIndex == MIDDLE_OPTION) {
        textBoxFrames = CpuSelectionArray0[messageSpeed];
    } else if (cpuChosenIndex == BOTTOM_OPTION) {
        textBoxFrames = CpuSelectionArray1[messageSpeed];
    } else {
        //GREEDY_OPTION
        return 0;
    }

    //advance rng during cpu decision for option index
    for (int i = 0; i < textBoxFrames; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //what happens based on what cpu answers
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
    for (int i = 0; i < CpuSelectionArray2[messageSpeed]; i++) {
        ADV_SEED(cur_rng_seed);
    }

    s32 itemChosen = func_800EEF80_102BA0(4);
    if (itemChosen == RARE_ITEM_WATCH) {
        // for (int j = 0; j < 12; j++) {
        //     printf("Space: %04X\n", data[j]);
        // }
        //printf("Seed Before item space is %08X\n", rngBeforeItemSpaceResult);
        return 1;
    }
    return 0;
    
}

void DoBankAdvancements(s32 messageSpeed) {
    //player face bank when passing it
    for (int i = 0; i < 8; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //time at bank
    for (int i = 0; i < CpuBankRngAdvancements[messageSpeed]; i++) {
        ADV_SEED(cur_rng_seed);
    }
}

int SetStarBitIndex(u32 index) {
    switch (index) {
    case 0x89BF:
        return 0;
    case 0x49BF:
        return 1;
    case 0xC9BE:
        return 2;
    case 0xC9BD:
        return 3;
    case 0xC9BB:
        return 4;
    case 0xC9B7:
        return 5;
    case 0xC9AF:
        return 6;
    case 0xC99F:
        return 7;
    default:
        return -1;
    }
}

int GetStarBitIndex(u32 value) {
    switch (value) {
    case 0x89BF:
        return 0;
    case 0x49BF:
        return 1;
    case 0xC9BE:
        return 2;
    case 0xC9BD:
        return 3;
    case 0xC9BB:
        return 4;
    case 0xC9B7:
        return 5;
    case 0xC9AF:
        return 6;
    case 0xC99F:
        return 7;
    default:
        return -1;
    }
}