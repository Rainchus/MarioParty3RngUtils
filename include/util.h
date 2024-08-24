#ifndef _UTIL_H
#define _UTIL_H

#include "mp3.h"

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
extern SpaceChain ChillyWatersChains[17];
extern SpaceChain DeepBlooperSeaChains[14];
extern SpaceChain SpinyDesertChains[14];
extern SpaceChain WoodyWoodsChains[15];
extern SpaceChain CreepyCavernChains[18];
extern DecisionTreeNonLeafNode WoodyWoodsJunction0Nodes[4];
extern s16 CW_Space_34[];
extern s16 DBS_Space_25[];
extern DoubleJunction CW_Space_6C;
extern DoubleJunction DBS_Space_68;
extern DoubleJunction WW_Space_67;
extern DoubleJunction CC_Space_83;
extern BoardChainsData BoardChains[];
extern s32 rng_advancements_between_spaces[3];

s32 SetNextSpace(void* funcData);
s32 JunctionDecision(void* junctionData);
void SetPlayerNextChainAndSpaceFromAbsSpace(s32 absSpace, s32 mode);

#endif