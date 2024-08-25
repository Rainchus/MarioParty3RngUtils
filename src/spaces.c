#include "mp3.h"
#include "util.h"
#include <stdio.h>

//frame counts for cpu swapping directions at a junction
#define FRAME_COUNT_NO_DIRECTION_SWAP 42
#define FRAME_COUNT_SWAP_DIRECTION 51

#define NO_DIRECTION_SWAP 0
#define DIRECTION_SWAP 1

extern DecisionTreeNonLeafNode ChillyWatersJunction0Nodes[3];

void advanceRNGBackwards(void);

BoardChainsData BoardChains[] = {
    {ChillyWatersChains, ARRAY_COUNT(ChillyWatersChains)},
    {DeepBlooperSeaChains, ARRAY_COUNT(DeepBlooperSeaChains)},
    {SpinyDesertChains, ARRAY_COUNT(SpinyDesertChains)},
    {WoodyWoodsChains, ARRAY_COUNT(WoodyWoodsChains)},
    {CreepyCavernChains, ARRAY_COUNT(CreepyCavernChains)},
    {WaluigisIslandChains, ARRAY_COUNT(WaluigisIslandChains)}
};

u32 GetChainAndSpaceFromAbsSpace(s32 space) {
    SpaceChain* curBoardChains = BoardChains[gGameStatus.boardIndex].boardChainData;
    u16 chainCount = BoardChains[gGameStatus.boardIndex].amountOfChains;

    for (u16 i = 0; i < chainCount; i++) {
        SpaceChain* curChain = &curBoardChains[i];
        for (u16 j = 0; j < curChain->amountOfSpaces; j++) {
            if (space == curChain->spaceChainArray[j]) {
                //return space;
                return (i << 16) | j;
            }
        }
    }
    return -1;
}

//we only ever care about the first player, so hardcode to player index 0
s32 SetNextSpace(void* funcData) {
    s16* spaces = funcData;

    SetPlayerNextChainAndSpaceFromAbsSpace(spaces[0], SET_NEXT, 0);
    return NORMAL_RETURN;
}

s32 JunctionDecision(void* junctionData) {
    s32 aiDecision = 1;

    //wait 5 frames after making it to junction before cpu decides where to go
    for (int i = 0; i < 5; i++) {
        ADV_SEED(cur_rng_seed);
    }

    switch (gGameStatus.boardIndex) {
    case CHILLY_WATERS:
        DoubleJunction* cw_node = junctionData;
        s16* cw_spaces = cw_node->spaceABS;

        aiDecision = aiMain(cw_node->junctionNodeData, ARRAY_COUNT(ChillyWatersJunction0Nodes));
        if (aiDecision == DIRECTION_SWAP) {
            return BAD_JUNCTION_RESULT;
        }

        //doesn't swap junction arrow decision, 42 frames
        for (int i = 0; i < FRAME_COUNT_NO_DIRECTION_SWAP; i++) {
            ADV_SEED(cur_rng_seed);
        }

        SetPlayerNextChainAndSpaceFromAbsSpace(cw_spaces[0], SET_NEXT, 0);
        break;
    case DEEP_BLOOPER_SEA:
        DoubleJunction* dbs_node = junctionData;
        s16* dbs_spaces = dbs_node->spaceABS;

        //pass arbitrary number as the max node count because it's unknown how many nodes deep this can go
        aiDecision = aiMain(dbs_node->junctionNodeData, 5);
        if (aiDecision == NO_DIRECTION_SWAP) {
            return BAD_JUNCTION_RESULT;
        }

        //swap junction arrow decision, 51 frames
        for (int i = 0; i < FRAME_COUNT_SWAP_DIRECTION; i++) {
            ADV_SEED(cur_rng_seed);
        }

        SetPlayerNextChainAndSpaceFromAbsSpace(dbs_spaces[1], SET_NEXT, 0);
        break;
    case SPINY_DESERT:
        break;
    case WOODY_WOODS:
        DoubleJunction* ww_node = junctionData;
        s16* ww_spaces = ww_node->spaceABS;

        aiDecision = aiMain(ww_node->junctionNodeData, 2);
        if (aiDecision == NO_DIRECTION_SWAP) {
            return BAD_JUNCTION_RESULT;
        }

        //swap junction arrow decision, 51 frames
        for (int i = 0; i < FRAME_COUNT_SWAP_DIRECTION; i++) {
            ADV_SEED(cur_rng_seed);
        }

        SetPlayerNextChainAndSpaceFromAbsSpace(ww_spaces[1], SET_NEXT, 0);
        break;
    case CREEPY_CAVERN:
        DoubleJunction* cc_node = junctionData;
        s16* cc_spaces = cc_node->spaceABS;

        //pass arbitrary number as the max node count because it's unknown how many nodes deep this can go
        aiDecision = aiMain(cc_node->junctionNodeData, 12);
        if (aiDecision == DIRECTION_SWAP) {
            return BAD_JUNCTION_RESULT;
        }

        //doesn't swap junction arrow decision, 42 frames
        for (int i = 0; i < FRAME_COUNT_NO_DIRECTION_SWAP; i++) {
            ADV_SEED(cur_rng_seed);
        }

        SetPlayerNextChainAndSpaceFromAbsSpace(cc_spaces[0], SET_NEXT, 0);
        break;
    case WALUIGIS_ISLAND:
        break;
    }
    
    return NORMAL_RETURN;
}

SpaceData* spacesForBoards[] = {
    chilly_waters_spaces,
    deep_blooper_sea_spaces,
    spiny_desert_spaces,
    woody_woods_spaces,
    creepy_cavern_spaces,
    waluigis_island_spaces
};