#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"
#include "util.h"

#define ERROR -1
#define ROLL_DICE_BLOCK_TIME 23

s16 absSpacesWalked[20] = {0};

void DoBankAdvancements(s32 messageSpeed);
void PlayerFaceForward(void);
u32 MeasureRngCalls(u32 seedStart, u32 seedEnd);
u8 rand8(void);
s32 GetSpaceIndexFromChainAndSpace(s32 curChainIndex, s32 curSpaceIndex);
s32 HandleLogicFromItemSpace(s32, s16*);
u32 GetChainAndSpaceFromAbsSpace(s32 space);
void ResetStarSpaces(s32 boardIndex);
void SetStarSpace(s32 starSpaceIndex, s32 boardIndex);
void SetStarSpawnData(s32 starSpawnIndex, s32 boardIndex);

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
    s32 funcEventResult;
    s16* spacesWalked = absSpacesWalked;

    for (int i = 0; i < 7; i++) {
        absSpacesWalked[i] = 0;
    }

    //time to roll dice and start moving
    for (int i = 0; i < ROLL_DICE_BLOCK_TIME; i++) {
        ADV_SEED(cur_rng_seed);
    }

    while (diceRoll > 0) {
        //move player to next space
        player->cur_chain_index = player->next_chain_index;
        player->cur_space_index = player->next_space_index;
        
        //advance rng seed by +1 each frame of walking to the space
        for (int i = 0; i < rng_advancements_between_spaces[walkSpeed]; i++) {
            ADV_SEED(cur_rng_seed);
        }
        
        //check if next space would be out of array bounds
        //+1 to convert index -> non index
        SpaceChain* curBoardChains = BoardChains[gGameStatus.boardIndex].boardChainData;
        if (player->cur_space_index + 1 >= curBoardChains[player->cur_chain_index].amountOfSpaces) {
            //if it is, get function pointer for space to appropriately set the next space
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

        spaceID = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index);
        SpaceData* space = &spacesForBoards[gGameStatus.boardIndex][spaceID];
        *spacesWalked++ = spaceID;

        

        s32 shouldDecrementRoll = HandleSpaceType(space->space_type, messageSpeed);
        if (shouldDecrementRoll == TRUE) {
            diceRoll--;
        }

        //printf("Dice: %d, Space: %04X\n", diceRoll, spaceID);
    }

    //face player foward in 8 frames
    for (int i = 0; i < 8; i++) {
        ADV_SEED(cur_rng_seed);
    }
    spacesWalked = absSpacesWalked;
    return HandleLogicFromItemSpace(messageSpeed, spacesWalked);
}

//starts from placement of hidden blocks
void DoPlayerTurn(s32 wantedRoll, s32 iteration, s32 absSpaceStart, s32 absSpaceNext, s32 absSpaceEnd, s32 boardIndex) {
    Blocks blockData;
    u8 diceRoll;
    u32 startingSeed = cur_rng_seed;
    u32 prevSeed;
    u16 spaceCount = boardSpaceCounts[boardIndex];

    blockData.coinBlockSpaceIndex = -1;
    blockData.itemBlockSpaceIndex = -1;
    blockData.starBlockSpaceIndex = -1;
    PlaceHiddenBlocksMain(&blockData, spaceCount, boardIndex); //place hidden blocks

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

    //get rolled number
    diceRoll = RollDice();

    //if dice roll isn't correct number, exit
    if (diceRoll != wantedRoll) {
        return;
    }

    //save seed before simulation is ran
    prevSeed = cur_rng_seed;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            //set player cur chain and space
            SetPlayerNextChainAndSpaceFromAbsSpace(absSpaceStart, SET_CURRENT);

            //set player next chain and space
            SetPlayerNextChainAndSpaceFromAbsSpace(absSpaceNext, SET_NEXT);

            //move cpu across the board
            s32 cpuTurnResult = CPUWalkSpaces(diceRoll, i, j); //try all walk and message speed combinations
            if (cpuTurnResult == ERROR) {
                return;
            } else if (cpuTurnResult == 1) {
                //is wanted result, print info
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

int main(int argc, char* argv[]) {
    u32 prevSeed = cur_rng_seed;
    u32 startSpace = -1, nextSpace = -1, endSpace = -1, board = -1, roll = -1, starSpaceIndex = -1;
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

    SetStarSpawnData(starSpaceIndex, board);

    //simulate first 3000 seeds
    for (s32 i = 0; i < 3000; i++) {
        ResetStarSpaces(gGameStatus.boardIndex);
        SetStarSpace(starSpaceIndex, gGameStatus.boardIndex);
        DoPlayerTurn(roll, i, startSpace, nextSpace, endSpace, gGameStatus.boardIndex);
        ADV_SEED(prevSeed);
        cur_rng_seed = prevSeed;
    }

    return EXIT_SUCCESS;
}