#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"
#include "util.h"

u32 debug_seed_before_junction = 0;
u32 debug_seed_before_dice_roll = 0;
u32 debug_seed_item_space = 0;

#define ITERATIONS_TO_RUN 3000

#define ERROR -1
#define OPTION_YES 1
#define OPTION_NO 0

char* ShopOptions[] = {
    "None", //-1
    "Mushroom",
    "Skeleton Key",
    "Poison Mushroom",
    "Reverse Mushroom",
    "Cellular Shopper",
    "Warp Block",
    "Plunder Chest",
    "Bowser Phone",
    "Dueling Glove",
    "Lucky Lamp",
    "Golden Mushroom",
    "Boo Bell",
    "Boo Repellant",
    "Bowser Suit",
    "Magic Lamp",
    "Koopa Kard",
    "Barter Box",
    "Lucky Charm",
    "Wacky Watch",
};

s16 absSpacesWalked[20] = {0};

void DoBankAdvancements(s32 messageSpeed);
void PlayerFaceForward(void);
u32 MeasureRngCalls(u32 seedStart, u32 seedEnd);
u8 rand8(void);
s32 GetSpaceIndexFromChainAndSpace(s32 curChainIndex, s32 curSpaceIndex);
s32 HandleLogicFromItemSpace(s32);
u32 GetChainAndSpaceFromAbsSpace(s32 space);
void ResetStarSpaces(void);
void SetStarSpace(s32 starSpaceIndex);
void SetStarSpawnData(s32 starSpawnIndex);
extern DecisionTreeNonLeafNode ShopDecisionNode[];
s32 rng_advancements_walking_between_spaces[] = {6, 11, 16};
s32 rng_advancements_jump_extra[] = {2, 5, 15}; //extra frames that jumping to a space takes
s32 gForceJunctionDecision = -1; //used to force junction decision (when we dont care about advancing rng)
u32 VALID_SEEDS = 0;
extern s16 CurBoardHiddenBlockBlacklistCount;
extern s16 D_801054B6;

//D_80105210
u16 boardSpaceCounts[] = {
    0x94, //chilly_waters_total_board_spaces
    0x8A, //deep_blooper_total_sea_board_spaces
    0x8F, //spiny_desert_total_board_spaces
    0x90, //woody_woods_total_board_spaces
    0x98, //creepy_cavern_total_board_spaces
    0x9A, //waluigis_island_total_board_spaces
};

char* speedsText[] = {
    "FAST",
    "NORMAL",
    "SLOW",
};

void DebugPrint(char* format, ...) {
    #ifdef DEBUG
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    #endif
}

void DoShop(void) {
    //turn to face shop
    AdvanceRng(FACE_SPACE_TIME);

    s32 ShopHostDecision = RNGPercentChance(66);

    //after shop host appears and ask player/cpu wants anything
    for (int i = 0; i < 19; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //arbitrary shop node total number
    if (aiMain(ShopDecisionNode, 5) == OPTION_YES) {
        //advancements to enter
        
    } else {
        //advancements to leave shop
        
    }

    //both yes and no options should be synced at this point


}

s32 HandleSpaceType(u8 spaceType, s32 messageSpeed) {
    //TODO: fill in logic for rng advancements
    switch (spaceType) {
    case SPACE_SHOP:
        DoShop();
        return FALSE;
    case SPACE_STAR:
    case SPACE_UNK_8: //for woody woods junctions??
    case SPACE_INVISIBLE:
        return FALSE;
    case SPACE_BANK:
        DoBankAdvancements(messageSpeed);
        return TRUE;
    default:
        return TRUE;
    }
}

void DoJumpAdvancements(s32 walkSpeed) {
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

//used for finding the next space for the cpu on initial setup so the user doesn't have to enter it
s32 CpuFindNextSpace(void) {
    Player* player = GetPlayerStruct(-1); //get current player struct
    SpaceChain* curBoardChains = BoardChains[gGameStatus.boardIndex].boardChainData;
    s32 spaceID = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index);
    SpaceData* space = &spacesForBoards[gGameStatus.boardIndex][spaceID];

    //players cannot be placed on invisible spaces, throw error
    switch (space->space_type) {
        case SPACE_INVISIBLE: //usually a junction
        case SPACE_SHOP:
        case SPACE_UNK_8: //woody woods junctions?
            return ERROR;
    }

    if (player->cur_space_index + 1 >= curBoardChains[player->cur_chain_index].amountOfSpaces) {
        if (space->eventFunction == 0) {
            printf(ANSI_RED "Error: End of chain reached at space 0x%02lX with no known link to next chain\n" ANSI_RESET, spaceID);
            return ERROR;
        }
        //the next chain index and space index were set by a function, use this to get the next space
        return GetSpaceIndexFromChainAndSpace(player->next_chain_index, player->next_space_index);
    } else {
        //the given space wasn't the end of a chain, just do +1
        return GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index + 1);
    }
}

//similar to CpuWalkSpaces but it doesn't advance rng and it needs to check both paths from a junction for a specific space
s32 CalculateCpuNeededRoll(void) {
    Player* player = GetPlayerStruct(-1); //get current player struct
    SpaceChain* curBoardChains = BoardChains[gGameStatus.boardIndex].boardChainData;
    s32 spaceID = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index);
    SpaceData* space = &spacesForBoards[gGameStatus.boardIndex][spaceID];

    // while (1) {
    //     if (player->cur_space_index + 1 >= curBoardChains[player->cur_chain_index].amountOfSpaces) {
    //         if (space->eventFunction == 0) {
    //             printf(ANSI_RED "Error: End of chain reached at space %02lX with no known link to next chain\n" ANSI_RESET, spaceID);
    //             return ERROR;
    //         }
    //         //the next chain index and space index were set by a function, use this to get the next space
    //         return GetSpaceIndexFromChainAndSpace(player->next_chain_index, player->next_space_index);
    //     } else {
    //         //the given space wasn't the end of a chain, just do +1
    //         return GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index + 1);
    //     }
    // }
    return 0;
}

s32 CPUWalkSpaces(s32 diceRoll, s32 walkSpeed, s32 messageSpeed, s32 endSpace, s32 hiddenBlockBool) {
    Player* player = GetPlayerStruct(-1); //get current player struct
    s32 spaceID;
    s32 funcEventResult;
    s16* spacesWalked = absSpacesWalked;

    D_800D41C0 = diceRoll;

    // for (int i = 0; i < 12; i++) {
    //     absSpacesWalked[i] = 0;
    // }

    //time to roll dice and start moving
    AdvanceRng(ROLL_DICE_BLOCK_TIME);

    while (diceRoll > 0) {
        //check if we should jump to the next space, and if so, add rng advancements as needed
        if (func_800F9A68_10D688(0) == 1) {
            AdvanceRng(rng_advancements_jump_extra[walkSpeed]);
        }

        //printf("Roll: %02d, 0x%04X -> 0x%04X\n", diceRoll, GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index), GetSpaceIndexFromChainAndSpace(player->next_chain_index, player->next_space_index));

        //move player to next space
        player->cur_chain_index = player->next_chain_index;
        player->cur_space_index = player->next_space_index;

        //advance rng seed by +1 each frame of walking to the space
        //skip 1 frame if manipulating hidden block
        if (diceRoll == 1 && hiddenBlockBool == 1) {
            AdvanceRng(rng_advancements_walking_between_spaces[walkSpeed] - 1);
        } else {
            AdvanceRng(rng_advancements_walking_between_spaces[walkSpeed]);
        }
        
        //check if next space would be out of array bounds
        //+1 to convert index -> non index
        SpaceChain* curBoardChains = BoardChains[gGameStatus.boardIndex].boardChainData;
        if (player->cur_space_index + 1 >= curBoardChains[player->cur_chain_index].amountOfSpaces) {
            //if it is the end of a chain, get function pointer for space to appropriately set the next space
            spaceID = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index);
            SpaceData* space = &spacesForBoards[gGameStatus.boardIndex][spaceID];

            if (space->eventFunction == 0) {
                printf(ANSI_RED "Error: End of chain reached at space 0x%02lX with no known link to next chain\n" ANSI_RESET, spaceID);
                return ERROR;
            }
            //function pointer does exist, run function
            //TODO: be sure to fill in *all* rng advacements here
            funcEventResult = space->eventFunction(space->functionData);
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
            D_800D41C0--;
        }
    }
    spaceID = GetSpaceIndexFromChainAndSpace(player->cur_chain_index, player->cur_space_index);
    if (spaceID != endSpace) {
        return 0;
    } else {
        return 1;
    }
}

void CpuItemLogicCheck(void) {

}

void print_debug_stats(void) {
    printf("Seed before dice roll: %08X\n", debug_seed_before_dice_roll);
    printf("Seed before junction: %08X\n", debug_seed_before_junction);
    printf("Seed before item space: %08X\n", debug_seed_item_space);
}

//starts from placement of hidden blocks
void DoPlayerTurnHiddenBlock(s32 wantedRoll, s32 iteration, s32 absSpaceStart, s32 absSpaceNext, s32 absSpaceEnd) {
    Player* player = GetPlayerStruct(-1);
    Blocks blockData;
    u8 diceRoll;
    u32 startingSeed = cur_rng_seed;
    u32 prevSeed;
    u16 spaceCount = boardSpaceCounts[gGameStatus.boardIndex];

    blockData.coinBlockSpaceIndex = -1;
    blockData.itemBlockSpaceIndex = -1;
    blockData.starBlockSpaceIndex = -1;
    PlaceHiddenBlocksMain(&blockData, spaceCount); //place hidden blocks

    //calls until cpu makes decision on whether or not to use an item
    for (int j = 0; j < 58; j++) {
        ADV_SEED(cur_rng_seed);
    }

    //TODO: implement
    CpuItemLogicCheck();

    //rest of calls until dice block is hit
    for (int j = 0; j < 12; j++) {
        ADV_SEED(cur_rng_seed);
    }

    //get rolled number
    debug_seed_before_dice_roll = cur_rng_seed;
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
            SetPlayerNextChainAndSpaceFromAbsSpace(absSpaceStart, SET_CURRENT, 0);

            //set player next chain and space
            SetPlayerNextChainAndSpaceFromAbsSpace(absSpaceNext, SET_NEXT, 0);

            //move cpu across the board
            s32 cpuTurnResult = CPUWalkSpaces(diceRoll, i, j, absSpaceEnd, 1); //try all walk and message speed combinations
            if (cpuTurnResult == ERROR) {
                return;
            }

            if (cpuTurnResult == 0) {
                continue;
            }

            s32 spaceID = GetSpaceIndexFromChainAndSpace(gPlayers[0].cur_chain_index, gPlayers[0].cur_space_index);
            if (spaceID != blockData.itemBlockSpaceIndex) {
                continue;
            }
            u32 seedBeforeRand = cur_rng_seed;
            //cpu landed on correct space
            u8 randByte = func_800EEF80_102BA0(100.0f) + 1;

            if (randByte > 85 && randByte < 91) {
                //printf("Seed before rand: %08X\n", seedBeforeRand);
                printf("Calls: "ANSI_YELLOW"%ld"ANSI_WHITE", Seed: %08X, Roll: "ANSI_MAGENTA"%d"ANSI_WHITE" \t| Walk: "ANSI_RED"%s"ANSI_WHITE" \t| Message: "ANSI_RED"%s"ANSI_WHITE"\n", iteration, startingSeed, diceRoll, speedsText[i], speedsText[j]);
                VALID_SEEDS++;
            }

            // //face player foward in 8 frames
            // AdvanceRng(8);
            // if (HandleLogicFromItemSpace(j) == 1) {
            //     //print_debug_stats();
            //     printf("Calls: "ANSI_YELLOW"%ld"ANSI_WHITE", Seed: %08X, Roll: "ANSI_MAGENTA"%d"ANSI_WHITE" \t| Walk: "ANSI_RED"%s"ANSI_WHITE" \t| Message: "ANSI_RED"%s"ANSI_WHITE"\n", iteration, startingSeed, diceRoll, speedsText[i], speedsText[j]);
            //     VALID_SEEDS++;
            // }
            cur_rng_seed = prevSeed;
        }
    }
}

//starts from placement of hidden blocks
void DoPlayerTurn(s32 wantedRoll, s32 iteration, s32 absSpaceStart, s32 absSpaceNext, s32 absSpaceEnd) {
    Player* player = GetPlayerStruct(-1);
    Blocks blockData;
    u8 diceRoll;
    u32 startingSeed = cur_rng_seed;
    u32 prevSeed;
    u16 spaceCount = boardSpaceCounts[gGameStatus.boardIndex];

    blockData.coinBlockSpaceIndex = -1;
    blockData.itemBlockSpaceIndex = -1;
    blockData.starBlockSpaceIndex = -1;
    PlaceHiddenBlocksMain(&blockData, spaceCount); //place hidden blocks

    //calls until cpu makes decision on whether or not to use an item
    for (int j = 0; j < 58; j++) {
        ADV_SEED(cur_rng_seed);
    }

    //TODO: implement
    CpuItemLogicCheck();

    //rest of calls until dice block is hit
    for (int j = 0; j < 12; j++) {
        ADV_SEED(cur_rng_seed);
    }

    //get rolled number
    debug_seed_before_dice_roll = cur_rng_seed;
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
            SetPlayerNextChainAndSpaceFromAbsSpace(absSpaceStart, SET_CURRENT, 0);

            //set player next chain and space
            SetPlayerNextChainAndSpaceFromAbsSpace(absSpaceNext, SET_NEXT, 0);

            //move cpu across the board
            s32 cpuTurnResult = CPUWalkSpaces(diceRoll, i, j, absSpaceEnd, 0); //try all walk and message speed combinations
            if (cpuTurnResult == ERROR) {
                return;
            }

            if (cpuTurnResult == 0) {
                continue;
            }

            //face player foward in 8 frames
            AdvanceRng(8);
            if (HandleLogicFromItemSpace(j) == 1) {
                //print_debug_stats();
                printf("Calls: "ANSI_YELLOW"%ld"ANSI_WHITE", Seed: %08X, Roll: "ANSI_MAGENTA"%d"ANSI_WHITE" \t| Walk: "ANSI_RED"%s"ANSI_WHITE" \t| Message: "ANSI_RED"%s"ANSI_WHITE"\n", iteration, startingSeed, diceRoll, speedsText[i], speedsText[j]);
                VALID_SEEDS++;
            }
            cur_rng_seed = prevSeed;
        }
    }
}

void ReadParametersFromFile2(const char* filename, u32* board, u32* starSpace, u32* startSpace, u32* nextSpace, u32* endSpace, u32* roll, u32* items, u32* numItems, u32* p2Space, u32* p3Space, u32* p4Space) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    char valueStr[256];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "Board: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", board);
            } else {
                *board = (u32)atoi(valueStr);
            }
        } else if (sscanf(line, "Star: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", starSpace);
            } else {
                *starSpace = (u32)atoi(valueStr);
            }
        } else if (sscanf(line, "StartSpace: %s", valueStr) == 1) {
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
        } else if (sscanf(line, "Roll: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", roll);
            } else {
                *roll = (u32)atoi(valueStr);
            }
        } else if (sscanf(line, "Items: %[^\n]", valueStr) == 1) {
            // Split the string by commas and parse each item
            *numItems = 0;
            char* token = strtok(valueStr, ",");
            while (token != NULL && *numItems < 3) {
                items[*numItems] = (s32)atoi(token);
                (*numItems)++;
                token = strtok(NULL, ",");
            }
        } else if (sscanf(line, "P2 Space: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", p2Space);
            } else {
                *p2Space = (u32)atoi(valueStr);
            }
        } else if (sscanf(line, "P3 Space: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", p3Space);
            } else {
                *p3Space = (u32)atoi(valueStr);
            }
        } else if (sscanf(line, "P4 Space: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", p4Space);
            } else {
                *p4Space = (u32)atoi(valueStr);
            }
        }
    }

    fclose(file);
}

void ReadParametersFromFile(const char* filename, u32* startSpace, u32* endSpace, u32* p2Space, u32* p3Space, u32*p4Space, u32* board, u32* roll, u32* starSpaceIndex, s32* items, s32* numItems) {
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
        } else if (sscanf(line, "EndSpace: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", endSpace);
            } else {
                *endSpace = (u32)atoi(valueStr);
            }
        } else if (sscanf(line, "P2 Space: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", p2Space);
            } else {
                *p2Space = (u32)atoi(valueStr);
            }
        } else if (sscanf(line, "P3 Space: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", p3Space);
            } else {
                *p3Space = (u32)atoi(valueStr);
            }
        } else if (sscanf(line, "P4 Space: %s", valueStr) == 1) {
            if (strstr(valueStr, "0x") == valueStr) {
                sscanf(valueStr, "0x%x", p4Space);
            } else {
                *p4Space = (u32)atoi(valueStr);
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
        } else if (sscanf(line, "Item: %[^\n]", valueStr) == 1) {
            // Split the string by commas and parse each item
            *numItems = 0;
            char* token = strtok(valueStr, ",");
            while (token != NULL && *numItems < 3) {
                items[*numItems] = (s32)atoi(token);
                (*numItems)++;
                token = strtok(NULL, ",");
            }
        }
    }

    fclose(file);
}

s32 ConvertAbsSpaceToStarSpaceIndex(s32 spaceID) {
    s16* curBoardStarSpaces = HiddenBlockSpacesBlacklist[gGameStatus.boardIndex];
    s32 i = 0;
    for (; i < CurBoardHiddenBlockBlacklistCount; i++) {
        if (curBoardStarSpaces[i] == spaceID) {
            return i;
        } 
    }
    return -1; //didnt find star space in current board's star space array
    
}

void handle_item_space_mode(void) {
    u32 prevSeed;
    u32 startSpace, nextSpace, endSpace, board, roll, starSpace, p2Space, p3Space, p4Space = -1;
    u32 items[3];
    u32 numItems = 0;
    printf("Item space mode activated.\n");
    ReadParametersFromFile2("input.txt", &board, &starSpace, &startSpace, &nextSpace, &endSpace, &roll, &items, &numItems, &p2Space, &p3Space, &p4Space);

    //ReadParametersFromFile("input.txt", &startSpace, &endSpace, &p2Space, &p3Space, &p4Space, &board, &roll, &starSpace, items, &numItems);
    gGameStatus.boardIndex = board;
    if (board == WALUIGIS_ISLAND) {
        D_801054B6 = 1;
        CurBoardHiddenBlockBlacklistCount = 0x17;
    } else {
        D_801054B6 = 0;
        CurBoardHiddenBlockBlacklistCount = 8;
    }

    SetPlayerNextChainAndSpaceFromAbsSpace(startSpace, SET_CURRENT, 0);
    SetPlayerNextChainAndSpaceFromAbsSpace(nextSpace, SET_NEXT, 0);
    // s32 nextSpaceResult = CpuFindNextSpace();

    // if (nextSpaceResult == ERROR) {
    //     printf(ANSI_RED "Error: Invalid next space index\n" ANSI_RESET);
    //     return EXIT_FAILURE;        
    // }

    printf(
        "Board: 0x%02X\n"
        "StartSpace: 0x%02X\n"
        "NextSpace: 0x%02X\n"
        "EndSpace: 0x%02X\n"
        "Star: 0x%02X\n"
        "P2 Space: 0x%02X\n"
        "P3 Space: 0x%02X\n"
        "P4 Space: 0x%02X\n",
        board, startSpace, nextSpace, endSpace, starSpace, p2Space, p3Space, p4Space 
    );

    // printf(
    //     "StartSpace: 0x%02X\n"
    //     "NextSpace: 0x%02X\n"
    //     "EndSpace: 0x%02X\n"
    //     "P2 Space: 0x%02X\n"
    //     "P3 Space: 0x%02X\n"
    //     "P4 Space: 0x%02X\n"
    //     "Board: %d\n"
    //     "Roll: %d\n"
    //     "Star: %d\n",
    //     startSpace, nextSpaceResult, endSpace,  p2Space, p3Space, p4Space, board, roll, starSpaceIndex
    //     );

    printf("Items: ");

    for (int i = 0; i < numItems; i++) {
        gPlayers[0].items[i] = items[i]; //copy items to p1
        //dont print ", "after last entry
        if (i+1 == numItems) {
            printf("%s\n", ShopOptions[items[i] + 1]);
        } else {
            printf("%s, ", ShopOptions[items[i] + 1]);
        }
    }

    printf("\n");

    //shouldn't need to set other players next spaces, but current spaces are used for if the player should jump to the net space or not
    SetPlayerNextChainAndSpaceFromAbsSpace(p2Space, SET_CURRENT, 1);
    SetPlayerNextChainAndSpaceFromAbsSpace(p3Space, SET_CURRENT, 2);
    SetPlayerNextChainAndSpaceFromAbsSpace(p4Space, SET_CURRENT, 3);

    s32 starSpaceIndex = ConvertAbsSpaceToStarSpaceIndex(starSpace);
    printf("Star: %02lX\n", starSpaceIndex);

    if (starSpaceIndex >= 8) {
        printf(ANSI_RED "Error: Invalid star space index of %ld passed. max is 7\n" ANSI_RESET, starSpaceIndex);
        return;
    }

    SetStarSpawnData(starSpaceIndex);
    VALID_SEEDS = 0;

    //it takes approximately 900 frames to load into a board, show only results after this
    // for (s32 i = 0; i < 962; i++) {
    //     ADV_SEED(cur_rng_seed);
    // }

    prevSeed = cur_rng_seed;
    //simulate ITERATIONS_TO_RUN seeds
    for (s32 i = 0; i < ITERATIONS_TO_RUN; i++) {
        ResetStarSpaces();
        SetStarSpace(starSpaceIndex);
        DoPlayerTurn(roll, i, startSpace, nextSpace, endSpace);
        ADV_SEED(prevSeed);
        cur_rng_seed = prevSeed;
    }
    printf("Valid Seeds Found: %d\n", VALID_SEEDS);
}

void hidden_block_gen_main(int starSpace, int curSpaceID, int nextSpaceID, int endSpaceID, int board, int wantedRoll) {
    u32 starting_seed = cur_rng_seed;
    u32 prev_seed;
    u32 prev_seed2;
    Blocks blockData;
    s32 diceRoll;
    u32 prevSeed;
    u16 spaceCount = boardSpaceCounts[gGameStatus.boardIndex];

    VALID_SEEDS = 0;
    gGameStatus.boardIndex = board;
    if (board == WALUIGIS_ISLAND) {
        D_801054B6 = 1;
        CurBoardHiddenBlockBlacklistCount = 0x17;
    } else {
        D_801054B6 = 0;
        CurBoardHiddenBlockBlacklistCount = 8;
    }
    SetStarSpawnData(starSpace);
    prevSeed = cur_rng_seed;
    //simulate ITERATIONS_TO_RUN seeds
    for (s32 i = 0; i < ITERATIONS_TO_RUN; i++) {
        ResetStarSpaces();
        SetStarSpace(starSpace);
        DoPlayerTurnHiddenBlock(wantedRoll, i, curSpaceID, nextSpaceID, endSpaceID);
        s32 spaceID = GetSpaceIndexFromChainAndSpace(gPlayers[0].cur_chain_index, gPlayers[0].cur_space_index);
        ADV_SEED(prevSeed);
        cur_rng_seed = prevSeed;
    }

    printf("Valid Seeds Found: %d\n", VALID_SEEDS);
}

void handle_hidden_block_main(void) {
    u32 prevSeed;
    u32 startSpace, nextSpace, endSpace, board, roll, starSpace, p2Space, p3Space, p4Space = -1;
    u32 items[3];
    u32 numItems = 0;
    printf("hidden block mode activated.\n");
    ReadParametersFromFile2("input.txt", &board, &starSpace, &startSpace, &nextSpace, &endSpace, &roll, &items, &numItems, &p2Space, &p3Space, &p4Space);
    printf(
        "Board: 0x%02X\n"
        "Star: 0x%02X\n"
        "StartSpace: 0x%02X\n"
        "NextSpace: 0x%02X\n"
        "EndSpace: 0x%02X\n"
        "P2 Space: 0x%02X\n"
        "P3 Space: 0x%02X\n"
        "P4 Space: 0x%02X\n",
        board, starSpace, startSpace, nextSpace, endSpace, p2Space, p3Space, p4Space 
    );
    hidden_block_gen_main(starSpace, startSpace, nextSpace, endSpace, board, roll);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s --item_space\n", argv[0]);
        fprintf(stderr, "       %s --hidden_block\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "--item_space") == 0) {
        handle_item_space_mode();
    } else if (strcmp(argv[1], "--hidden_block") == 0) {
        handle_hidden_block_main();
    }

    // if (strcmp(argv[1], "--item_space") == 0) {
    //     if (argc != 2) {
    //         fprintf(stderr, "Error: --item_space does not require additional arguments.\n");
    //         return EXIT_FAILURE;
    //     }
    //     handle_item_space_mode();
    // } else if (strcmp(argv[1], "--hidden_block") == 0) {
    //     if (argc != 7) {
    //         fprintf(stderr, "Error: --hidden_block requires exactly 5 integer arguments.\n");
    //         return EXIT_FAILURE;
    //     }
    //     int curSpaceID = atoi(argv[2]);
    //     int nextSpaceID = atoi(argv[3]);
    //     int endSpaceID = atoi(argv[4]);
    //     int boardIndex = atoi(argv[5]);
    //     int wantedRoll = atoi(argv[6]);
    //     hidden_block_gen_main(curSpaceID, nextSpaceID, endSpaceID, boardIndex, wantedRoll);
    // } else {
    //     fprintf(stderr, "Error: Unknown argument '%s'.\n", argv[1]);
    //     return EXIT_FAILURE;
    // }

    return EXIT_SUCCESS;
}