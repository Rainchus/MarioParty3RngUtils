#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"

#define ERROR -1
#define ROLL_DICE_BLOCK_TIME 23

void DoBankAdvancements(s32 messageSpeed);
void PlayerFaceForward(void);
u32 MeasureRngCalls(u32 seedStart, u32 seedEnd);
u8 rand8(void);
s32 GetSpaceIndexFromChainAndSpace(s32 curChainIndex, s32 curSpaceIndex);
s32 HandleLogicFromItemSpace(s32);
u32 GetChainAndSpaceFromAbsSpace(s32 space);
void ResetStarSpaces(s32 boardIndex);
void SetStarSpace(s32 starSpaceIndex, s32 boardIndex);

s32 rng_advancements_between_spaces[] = {6, 11, 16};

u16 boardSpaceCounts[] = {
    0x94, //chilly_waters_total_board_spaces
    0x8A, //deep_blooper_sea_board_spaces
    0x8F, //spiny_desert_board_spaces
    0x90, //woody_woods_board_spaces
    0x98, //creepy_cavern_total_board_spaces
};

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

s32 HandleSpaceType(u8 spaceType, s32 messageSpeed) {
    //TODO: fill in logic for rng advancements
    switch (spaceType) {
    case SPACE_INVISIBLE:
    case SPACE_SHOP:
    case SPACE_STAR:
        return FALSE;
    case SPACE_BANK:
        //TODO: add advancements here
        DoBankAdvancements(messageSpeed);
        return TRUE;
    default:
        return TRUE;
    }
}

s32 CPUWalkSpaces(s32 diceRoll, s32 walkSpeed, s32 messageSpeed) {
    Player* player = GetPlayerStruct(-1); //get current player struct
    s32 spaceID;
    s32 spaceCur, spaceNext;
    s32 funcEventResult;

    s32 temp0, temp1;

    //time to roll dice and start moving
    for (int i = 0; i < ROLL_DICE_BLOCK_TIME; i++) {
        ADV_SEED(cur_rng_seed);
    }

    temp0 = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index);
    temp1 = GetSpaceIndexFromChainAndSpace(player->next_chain_index, player->next_space_index);
    //printf(ANSI_CYAN "Info: From chain %02X space %02X (0x%02lX) -> chain %02X space %02X (0x%02lX)\n" ANSI_RESET, player->cur_chain_index, player->cur_space_index, temp0, player->next_chain_index, player->next_space_index, temp1);
    while (diceRoll > 0) {
        //move player to next space
        spaceCur = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index);
        player->cur_chain_index = player->next_chain_index;
        player->cur_space_index = player->next_space_index;

        //advance rng seed by +1 each frame of walking to the space
        for (int i = 0; i < rng_advancements_between_spaces[walkSpeed]; i++) {
            ADV_SEED(cur_rng_seed);
        }
        
        //check if next space would be out of array bounds
        //printf("Next space index would be %02X\n", player->cur_space_index + 1);

        //+1 to convert index -> non index
        if (player->cur_space_index + 1 >= ChillyWatersChains[player->cur_chain_index].amountOfSpaces) {
            //if it is, get function pointer for space to appropriately set the next space correctly
            spaceID = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index);
            SpaceData* space = &spacesForBoards[gGameStatus.boardIndex][spaceID];

            if (space->eventFunction == 0) {
                printf(ANSI_RED "Error: End of chain reached at space %02lX with no known link to next chain\n" ANSI_RESET, spaceID);
                return ERROR;
            }
            //function pointer does exist, run function
            //TODO: be sure to fill in *all* rng advacements here
            funcEventResult = space->eventFunction(space->functionData);
            switch (funcEventResult) {
            case NORMAL_RETURN:
                break;
            case BAD_JUNCTION_RESULT:
                return 0; //cpu went wrong way, exit
            }
        } else {
            //otherwise, just increment next space id
            player->next_space_index++;
        }

        spaceNext = GetSpaceIndexFromChainAndSpace(player->next_chain_index, player->next_space_index);
        //printf(ANSI_CYAN "Info: From chain %02X space %02X (0x%02lX) -> chain %02X space %02X (0x%02lX)\n" ANSI_RESET, player->cur_chain_index, player->cur_space_index, spaceCur, player->next_chain_index, player->next_space_index, spaceNext);

        spaceID = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index);
        SpaceData* space = &spacesForBoards[gGameStatus.boardIndex][spaceID];

        s32 shouldDecrementRoll = HandleSpaceType(space->space_type, messageSpeed);
        if (shouldDecrementRoll == TRUE) {
            diceRoll--;
        }
        // //if invisible space, space count shouldn't decrement
        // if (space->space_type != SPACE_INVISIBLE && space->space_type != SPACE_SHOP && space->space_type != SPACE_STAR) {
        //     diceRoll--;
        // }
    }


    spaceID = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index);
    //printf(ANSI_GREEN "Result: Cur Chain: 0x%02X, Cur Space: 0x%02X, Cur ABS Space: 0x%02lX\n" ANSI_RESET, player->cur_chain_index, player->cur_space_index, spaceID);
    //face player foward in 8 frames
    for (int i = 0; i < 8; i++) {
        ADV_SEED(cur_rng_seed);
    }   
    return HandleLogicFromItemSpace(messageSpeed);
}

//starts from placement of hidden blocks
void DoPlayerTurn(s32 wantedRoll, s32 iteration, s32 absSpaceStart, s32 absSpaceNext, s32 absSpaceEnd, s32 boardIndex) {
    Blocks blockData;
    u8 diceRoll;
    u32 startingSeed = cur_rng_seed;
    u32 prevSeed;
    u16 spaceCount = boardSpaceCounts[boardIndex];
    u32 seedTemp;
    u32 seedTemp2 = cur_rng_seed;

    blockData.coinBlockSpaceIndex = -1;
    blockData.itemBlockSpaceIndex = -1;
    blockData.starBlockSpaceIndex = -1;
    u32 BeforeHiddenBlocksSeed = cur_rng_seed;
    PlaceHiddenBlocksMain(&blockData, spaceCount, boardIndex); //place hidden blocks
    u32 AfterHiddenBlocksSeed = cur_rng_seed;


    //calls until cpu makes decision on whether or not to use an item
    for (int j = 0; j < 58; j++) {
        ADV_SEED(cur_rng_seed);
    }

    // //TODO: item check here, make sure this is correctly handled
    // ADV_SEED(cur_rng_seed);

    //rest of calls until dice block is hit
    for (int j = 0; j < 12; j++) {
        ADV_SEED(cur_rng_seed);
    }

    seedTemp = cur_rng_seed;

    //get rolled number
    diceRoll = RollDice();

    prevSeed = cur_rng_seed;

    //if dice roll isn't correct number, exit
    if (diceRoll != wantedRoll) {
        return;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            u32 AbsSpace = GetChainAndSpaceFromAbsSpace(absSpaceStart);
            gPlayers[0].cur_chain_index = AbsSpace >> 16;
            gPlayers[0].cur_space_index = AbsSpace & 0xFFFF;

            u32 AbsSpaceNext = GetChainAndSpaceFromAbsSpace(absSpaceNext);
            gPlayers[0].next_chain_index = AbsSpaceNext >> 16;
            gPlayers[0].next_space_index = AbsSpaceNext & 0xFFFF;

            s32 cpuTurnResult = CPUWalkSpaces(diceRoll, i, j); //try all walk and message speed combinations
            if (cpuTurnResult == ERROR) {
                return;
            } else if (cpuTurnResult == 1) {
                // printf("Calls: %d, startingSeed: %08X\n", iteration, startingSeed);
                //printf("Seed before roll: %08lX\n", seedTemp);
                // printf("Seed before blocks: %08lX\n", BeforeHiddenBlocksSeed);
                // printf("Seed after blocks: %08lX\n", AfterHiddenBlocksSeed);
                //printf("Coin: %02X, Star: %02X, Item: %02X\n", blockData.coinBlockSpaceIndex, blockData.starBlockSpaceIndex, blockData.itemBlockSpaceIndex);
                printf("Calls: "ANSI_YELLOW"%ld"ANSI_WHITE", Seed: %08X, Roll: "ANSI_MAGENTA"%d"ANSI_WHITE" \t| Walk: "ANSI_RED"%s"ANSI_WHITE" \t| Message: "ANSI_RED"%s"ANSI_WHITE"\n", iteration, startingSeed, diceRoll, speedsText[i], speedsText[j]);
            }
            cur_rng_seed = prevSeed;
        }
    }
}

void ReadParametersFromFile(const char* filename, u32* startSpace, u32* nextSpace, u32* endSpace, u32* board, u32* roll, u32* starSpaceIndex) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    char valueStr[256];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "StartSpace: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", startSpace);
            } else {
                *startSpace = (u32)atoi(valueStr);
            }
        } else if (sscanf(line, "NextSpace: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", nextSpace);
            } else {
                *nextSpace = (u32)atoi(valueStr);
            }
        } else if (sscanf(line, "EndSpace: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", endSpace);
            } else {
                *endSpace = (u32)atoi(valueStr);
            }
        } else if (sscanf(line, "Board: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", board);
            } else {
                *board = (u32)atoi(valueStr);
            }
        } else if (sscanf(line, "Roll: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", roll);
            } else {
                *roll = (u32)atoi(valueStr);
            }
        } else if (sscanf(line, "Star: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", starSpaceIndex);
            } else {
                *starSpaceIndex = (u32)atoi(valueStr);
            }
        }
    }

    fclose(file);
}

//70 calls from after block spawn to beginning of dice roll rng
// void SetStarSpawnDataChillyWaters(s32 index);
void SetStarSpawnData(s32 starSpawnIndex, s32 boardIndex);
// extern u8** StarSpawnFlags[];

int main(int argc, char* argv[]) {
    u32 prevSeed = cur_rng_seed;
    u32 startSpace = -1, nextSpace = -1, endSpace = -1, board = -1, roll = -1, starSpaceIndex = -1;
    Player* player = GetPlayerStruct(-1);
    ReadParametersFromFile("input.txt", &startSpace, &nextSpace, &endSpace, &board, &roll, &starSpaceIndex);

    printf(
        "StartSpace: 0x%02X\n"
        "NextSpace: 0x%02X\n"
        "EndSpace: 0x%02X\n"
        "Board: %d\n"
        "Roll: %d\n"
        "Star: %d\n",
        startSpace, nextSpace, endSpace, board, roll, starSpaceIndex
        );

    gGameStatus.boardIndex = board;
    if (starSpaceIndex >= 8) {
        printf(ANSI_RED "Error: Invalid star space index of %d passed. max is 7\n" ANSI_RESET, starSpaceIndex);
        return EXIT_FAILURE;
    }

    SetStarSpawnData(starSpaceIndex, CHILLY_WATERS);

    //simulate first 3000 seeds
    for (s32 i = 0; i < 3000; i++) {
        ResetStarSpaces(gGameStatus.boardIndex);
        SetStarSpace(starSpaceIndex, gGameStatus.boardIndex);
        DoPlayerTurn(roll, i, startSpace, nextSpace, endSpace, gGameStatus.boardIndex);
        ADV_SEED(prevSeed);
        cur_rng_seed = prevSeed;
    }
    // printf("Chain: %02X, Space: %02X", AbsSpace >> 16, AbsSpace & 0xFFFF);

    return EXIT_SUCCESS;
}