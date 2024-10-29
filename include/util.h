#ifndef _UTIL_H
#define _UTIL_H

#include "mp3.h"

#define ROLL_DICE_BLOCK_TIME 23
#define FACE_SPACE_TIME 8

typedef struct DoubleJunction {
    s16 spaceABS[2];
    DecisionTreeNonLeafNode* junctionNodeData;
} DoubleJunction;

typedef struct BoardChainsData {
    SpaceChain* boardChainData;
    int amountOfChains;
} BoardChainsData;

extern SpaceData chilly_waters_spaces[148];
extern SpaceData deep_blooper_sea_spaces[138];
extern SpaceData spiny_desert_spaces[143];
extern SpaceData woody_woods_spaces[144];
extern SpaceData creepy_cavern_spaces[152];
extern SpaceData waluigis_island_spaces[154];
extern SpaceChain ChillyWatersChains[17];
extern SpaceChain DeepBlooperSeaChains[14];
extern SpaceChain SpinyDesertChains[14];
extern SpaceChain WoodyWoodsChains[15];
extern SpaceChain CreepyCavernChains[18];
extern SpaceChain WaluigisIslandChains[22];
extern DecisionTreeNonLeafNode WoodyWoodsJunction0Nodes[4];
extern s16 CW_Space_34[];
extern s16 DBS_Space_25[];
extern s16 WI_Space_2C[];
extern s16 WW_Space_01[];
extern s16 SD_Space_45[];
extern DoubleJunction CW_Space_6C;
extern DoubleJunction DBS_Space_68;
extern DoubleJunction WW_Space_67;
extern DoubleJunction CC_Space_83;
extern DoubleJunction SD_Space_79;
extern BoardChainsData BoardChains[];
extern s32 rng_advancements_between_spaces[3];

s32 SetNextSpace(void* funcData);
s32 DoubleJunctionDecision(void* junctionData);
void SetPlayerNextChainAndSpaceFromAbsSpace(s32 absSpace, s32 mode, s32 playerIndex);
s32 func_800F9A68_10D688(s32 arg0);
void AdvanceRng(s32);

#endif