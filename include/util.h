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
extern SpaceChain ChillyWatersChains[17];
extern SpaceChain DeepBlooperSeaChains[14];
extern s16 CW_Space_34[];
extern s16 DBS_Space_25[];
extern DoubleJunction CW_Space_6C;
extern DoubleJunction DBS_Space_68;
extern BoardChainsData BoardChains[];
extern s32 rng_advancements_between_spaces[3];

s32 SetNextSpace(void* funcData);
s32 JunctionDecision(void* junctionData);
void SetPlayerNextChainAndSpaceFromAbsSpace(s32 absSpace, s32 mode);

#endif