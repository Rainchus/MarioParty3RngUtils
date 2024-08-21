#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"

void PlayerFaceForward(void);
u32 MeasureRngCalls(u32 seedStart, u32 seedEnd);
u8 rand8(void);
void InitialLoadInCalls(void);
s32 GetSpaceIndexFromChainAndSpace(s32 curChainIndex, s32 curSpaceIndex);
s32 HandleLogicFromItemSpace(s32);

s32 rng_advancements_between_spaces[] = {6, 11, 16};

u16 chilly_waters_total_board_spaces = 0x94; //(D_80105210)
u16 deep_blooper_sea_board_spaces = 0x8A; //(D_80105210)
u16 spiny_desert_board_spaces = 0x8F; //(D_80105210)
u16 woody_woods_board_spaces = 0x90; //(D_80105210)
u16 creepy_cavern_total_board_spaces = 0x98; //(D_80105210)

extern SpaceData chilly_waters_spaces[148];
extern SpaceChain ChillyWatersChains[];

char* speedsText[] = {
    "FAST",
    "NORMAL",
    "SLOW",
};

s32 HandleSpaceType(u8 spaceType) {
    //TODO: fill in logic for rng advancements
    switch (spaceType) {
    case SPACE_INVISIBLE:
    case SPACE_SHOP:
    case SPACE_STAR:
        return FALSE;
    case SPACE_BANK:
        //TODO: add advancements here
        return TRUE;
    default:
        return TRUE;
    }

}

void CPUWalkSpaces(s32 diceRoll, s32 walkSpeed, s32 messageSpeed) {
    Player* player = GetPlayerStruct(-1); //get current player struct
    s32 spaceID;
    s32 spaceCur, spaceNext;

    while (diceRoll > 0) {
        //move player to next space
        spaceCur = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index);
        player->cur_chain_index = player->next_chain_index;
        player->cur_space_index = player->next_space_index;

        for (int i = 0; i < rng_advancements_between_spaces[walkSpeed]; i++) {
            ADV_SEED(cur_rng_seed);
        }
        
        //check if next space would be out of array bounds
        //printf("Next space index would be %02X\n", player->cur_space_index + 1);

        //+2 because we need +1 for next space then another +1 to convert index -> non index
        if (player->cur_space_index + 2 >= ChillyWatersChains[player->cur_chain_index].amountOfSpaces) {
            //if it is, get function pointer for next space to appropriately set the next space correctly
            spaceID = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index + 1);
            SpaceData* space = &chilly_waters_spaces[spaceID];
            if (space->eventFunction == 0) {
                printf(ANSI_RED "Error: End of chain reached at next space %02lX with no known link to next chain\n" ANSI_RESET, spaceID);
                return;
            }
            //function pointer does exist, run function
            //TODO: this needs to include rng advancements at some point
            space->eventFunction(space->functionData);
        } else {
            //otherwise, just increment next space id
            player->next_space_index++;
        }

        spaceNext = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index);
        printf(ANSI_CYAN "Info: From chain %02X space %02X (0x%02lX) -> chain %02X space %02X (0x%02lX)\n" ANSI_RESET, player->cur_chain_index, player->cur_space_index, spaceCur, player->next_chain_index, player->next_space_index, spaceNext);

        spaceID = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index);
        SpaceData* space = &chilly_waters_spaces[spaceID];

        s32 shouldDecrementRoll = HandleSpaceType(space->space_type);
        if (shouldDecrementRoll == TRUE) {
            diceRoll--;
        }
        // //if invisible space, space count shouldn't decrement
        // if (space->space_type != SPACE_INVISIBLE && space->space_type != SPACE_SHOP && space->space_type != SPACE_STAR) {
        //     diceRoll--;
        // }
    }

    if (diceRoll == 0) {
        spaceID = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index);
        printf(ANSI_GREEN "Result: Cur Chain: 0x%02X, Cur Space: 0x%02X, Cur ABS Space: 0x%02lX\n" ANSI_RESET, player->cur_chain_index, player->cur_space_index, spaceID);
        PlayerFaceForward();
    }

    HandleLogicFromItemSpace(messageSpeed);
}

//starts from roll dice
void DoPlayerTurn(s32 boardIndex, s32 walkSpeed, s32 messageSpeed, s32 wantedRoll) {
    Blocks blockData;
    u8 diceRoll;

    blockData.coinBlockSpaceIndex = -1;
    blockData.itemBlockSpaceIndex = -1;
    blockData.starBlockSpaceIndex = -1;
    PlaceHiddenBlocksMain(&blockData, chilly_waters_total_board_spaces, CHILLY_WATERS); //place hidden blocks

    //calls until cpu makes decision on whether or not to use an item
    InitialLoadInCalls();

    //TODO: item check here, make sure this is correctly handled
    ADV_SEED(cur_rng_seed);

    //rest of calls until dice block is hit
    for (int j = 0; j < 12; j++) {
        ADV_SEED(cur_rng_seed);
    }

    //get rolled number
    diceRoll = RollDice();

    //if dice roll isn't correct number, exit
    if (diceRoll != wantedRoll) {
        return;
    }

    for (int walkSpeeds = 0; walkSpeeds < 3; walkSpeeds++) {
        for (int messageSpeeds = 0; messageSpeeds < 3; messageSpeeds++) {
            //CPUWalkSpaces();
        }
    }

    //
}

int main(int argc, char* argv[]) {
    u32 roll = 10;
    gPlayers[0].cur_chain_index = 0;
    gPlayers[0].cur_space_index = 0;

    gPlayers[0].next_chain_index = 1;
    gPlayers[0].next_space_index = 6;
    CPUWalkSpaces(roll, 0, 0); //fast walk, fast message speeds
    // u32 calls = 0;
    // calls = MeasureRngCalls(0xF7203643, 0xA2DF5357);
    // printf("Calls: %d", calls);
    // for (int i = 0; i < ARRAY_COUNT(chilly_waters_spaces); i++) {
    //     printf("Space 0x%02X: %d\n", i, chilly_waters_spaces[i].space_type);
    // }
    return EXIT_SUCCESS;
}