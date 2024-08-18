#include <stdio.h>
#include <stdlib.h>
#include "mp3.h"

#define CHILLY_WATERS 0


//these spawn indicies are arbitrary based on the order i got when getting this data
/* https://cdn.discordapp.com/attachments/450961364362592262/1273882797727285258/Screenshot_1.png?ex=66c03b4e&is=66bee9ce&hm=3ea26677a384fbf0a355a173d45db0f4f8b676f1ae27c9231193bcf619828130& */

u8 ChillyWatersStarSpawn0[] = {0x88, 0xBF, 0x00, 0x00};
u8 ChillyWatersStarSpawn1[] = {0x48, 0xBF, 0x00, 0x00};
u8 ChillyWatersStarSpawn2[] = {0xC8, 0xBE, 0x00, 0x00};
u8 ChillyWatersStarSpawn3[] = {0xC8, 0xBD, 0x00, 0x00};
u8 ChillyWatersStarSpawn4[] = {0xC8, 0xBB, 0x00, 0x00};
u8 ChillyWatersStarSpawn5[] = {0xC8, 0xB7, 0x00, 0x00};
u8 ChillyWatersStarSpawn6[] = {0xC8, 0xAF, 0x00, 0x00};
u8 ChillyWatersStarSpawn7[] = {0xC8, 0x9F, 0x00, 0x00};

u8* ChillyWatersStarSpawnFlags[] = {
    ChillyWatersStarSpawn0,
    ChillyWatersStarSpawn1,
    ChillyWatersStarSpawn2,
    ChillyWatersStarSpawn3,
    ChillyWatersStarSpawn4,
    ChillyWatersStarSpawn5,
    ChillyWatersStarSpawn6,
    ChillyWatersStarSpawn7
};


u8 DeepBlooperSeaStarSpawn0[] = {0x89, 0xBF, 0x00, 0x00};
u8 DeepBlooperSeaStarSpawn1[] = {0x49, 0xBF, 0x00, 0x00};
u8 DeepBlooperSeaStarSpawn2[] = {0xC9, 0xBE, 0x00, 0x00};
u8 DeepBlooperSeaStarSpawn3[] = {0xC9, 0xAF, 0x00, 0x00};
u8 DeepBlooperSeaStarSpawn4[] = {0xC9, 0xBD, 0x00, 0x00};
u8 DeepBlooperSeaStarSpawn5[] = {0xC9, 0x9F, 0x00, 0x00};
u8 DeepBlooperSeaStarSpawn6[] = {0xC9, 0xBB, 0x00, 0x00};
u8 DeepBlooperSeaStarSpawn7[] = {0xC9, 0xB7, 0x00, 0x00};

u8* DeepBlooperSeaStarSpawnFlags[] = {
    DeepBlooperSeaStarSpawn0,
    DeepBlooperSeaStarSpawn1,
    DeepBlooperSeaStarSpawn2,
    DeepBlooperSeaStarSpawn3,
    DeepBlooperSeaStarSpawn4,
    DeepBlooperSeaStarSpawn5,
    DeepBlooperSeaStarSpawn6,
    DeepBlooperSeaStarSpawn7
};


u8 WoodyWoodsStarSpawn0[] = {0xC9, 0xBB, 0x00, 0x00};
u8 WoodyWoodsStarSpawn1[] = {0xC9, 0xB7, 0x00, 0x00};
u8 WoodyWoodsStarSpawn2[] = {0xC9, 0xBD, 0x00, 0x00};
u8 WoodyWoodsStarSpawn3[] = {0xC9, 0x9F, 0x00, 0x00};
u8 WoodyWoodsStarSpawn4[] = {0x89, 0xBF, 0x00, 0x00};
u8 WoodyWoodsStarSpawn5[] = {0x49, 0xBF, 0x00, 0x00};
u8 WoodyWoodsStarSpawn6[] = {0xC9, 0xBE, 0x00, 0x00};
u8 WoodyWoodsStarSpawn7[] = {0xC9, 0xAF, 0x00, 0x00};

u8* WoodyWoodsStarSpawnFlags[] = {
    WoodyWoodsStarSpawn0,
    WoodyWoodsStarSpawn1,
    WoodyWoodsStarSpawn2,
    WoodyWoodsStarSpawn3,
    WoodyWoodsStarSpawn4,
    WoodyWoodsStarSpawn5,
    WoodyWoodsStarSpawn6,
    WoodyWoodsStarSpawn7
};


u8 CreepyCavernStarSpawn0[] = {0xC9, 0xBD, 0x00, 0x00};
u8 CreepyCavernStarSpawn1[] = {0xC9, 0xBB, 0x00, 0x00};
u8 CreepyCavernStarSpawn2[] = {0xC9, 0xBE, 0x00, 0x00};
u8 CreepyCavernStarSpawn3[] = {0xC9, 0x9F, 0x00, 0x00};
u8 CreepyCavernStarSpawn4[] = {0xC9, 0xB7, 0x00, 0x00};
u8 CreepyCavernStarSpawn5[] = {0x89, 0xBF, 0x00, 0x00};
u8 CreepyCavernStarSpawn6[] = {0x49, 0xBF, 0x00, 0x00};
u8 CreepyCavernStarSpawn7[] = {0xC9, 0xAF, 0x00, 0x00};

u8* CreepyCavernStarSpawnFlags[] = {
    CreepyCavernStarSpawn0,
    CreepyCavernStarSpawn1,
    CreepyCavernStarSpawn2,
    CreepyCavernStarSpawn3,
    CreepyCavernStarSpawn4,
    CreepyCavernStarSpawn5,
    CreepyCavernStarSpawn6,
    CreepyCavernStarSpawn7
};

//spawn 0
    //0x88, 0xBF

//spawn 1
    //0x48, 0xBF

//spawn 2
    //0xC8, 0xBE

//spawn 3
    //0xC8, 0xBD

//spawn 4
    //0xC8, 0xBB

//spawn 5
    //0xC8, 0xB7

//spawn 6
    //0xC8, 0xAF

//spawn 7
    //0xC8, 0x9F

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

u32 D_800D41C0 = 0; //cur spaces remaining to walk
s16 D_80102BC2 = 0; //TODO: tracks current player index a second time?
s16 D_80100D50_114970[] = {6, 7, 8, 9, 10, 11, 12, 13}; //unknown, extract from chilly waters
s32 func_800E4978_F8598(s32 playerIndex, s32 item);
s16 RunDecisionTree(DecisionTreeNonLeafNode* currentNode, s32 nodeTotal);

extern u32 cur_rng_seed;

void SetStarSpawnDataChillyWaters(s32 index) {
    for (s32 i = 0; i < 4; i++) {
        gGameStatus.D_800CD0B6[i] = ChillyWatersStarSpawnFlags[index][i];
    }
}

void SetStarSpawnDataDeepBlooperSea(s32 index) {
    for (s32 i = 0; i < 4; i++) {
        gGameStatus.D_800CD0B6[i] = DeepBlooperSeaStarSpawnFlags[index][i];
    }
}

void SetStarSpawnDataWoodyWoods(s32 index) {
    for (s32 i = 0; i < 4; i++) {
        gGameStatus.D_800CD0B6[i] = WoodyWoodsStarSpawnFlags[index][i];
    }
}

void SetStarSpawnDataCreepyCavern(s32 index) {
    for (s32 i = 0; i < 4; i++) {
        gGameStatus.D_800CD0B6[i] = CreepyCavernStarSpawnFlags[index][i];
    }
}

int aiMain(DecisionTreeNonLeafNode* node, s32 nodeCount, u32 seed) {
    // cur_rng_seed = seed;
    // cur_rng_seed = 0x0000D9ED; //starting seed
    // u32 cur_rng_seed_copy = seed;
    // s32 aiJunctionResult;

    return RunDecisionTree(node, nodeCount);
}