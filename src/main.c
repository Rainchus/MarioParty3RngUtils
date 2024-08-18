#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/mp3.h"

u32 cur_rng_seed = 0x0000D9ED; //initial starting seed D_80097650

void simduel(int argc, char *argv[]);
void simduel2(int argc, char *argv[]);
void simduel3(int argc, char *argv[]);
void rngadv(int argc, char *argv[]);
void rollchain();
void cpuitemspacewatch(int argc, char *argv[]);
void hiddenblockgen(int argc, char *argv[]);
void SimDuelMode(void);
void SimDuelMode2(void);
void SimDuelMode3(void);
void CPUGetWatchChillyWaters(s32 rollValue, s32 jumpsBeforeJunction, s32 jumpsAfterJunction, s32 itemSlot1);
void CPUGetWatchSpinyDesert(s32 rollValue, s32 jumpsBeforeJunction, s32 jumpsAfterJunction, s32 itemSlot1);
void CPUGetWatchWoodyWoods(s32 rollValue, s32 jumpsBeforeJunction, s32 jumpsAfterJunction, s32 itemSlot1);
void CPUGetWatchDeepBlooperSea(s32 rollValue, s32 jumpsBeforeJunction, s32 jumpsAfterJunction, s32 itemSlot1);
void CPUGetWatchCreepyCavern(s32 rollValue, s32 jumpsBeforeJunction, s32 jumpsAfterJunction, s32 itemSlot1);
void cpu_item_space_watch_deep_blooper_sea(int argc, char* argv[]);
void cpu_item_space_watch_chilly_waters(int argc, char* argv[]);
void cpu_item_space_watch_spiny_desert(int argc, char* argv[]);
void cpu_item_space_watch_woody_woods(int argc, char* argv[]);
void cpu_item_space_watch_creepy_cavern(int argc, char* argv[]);
void cpu_item_space_watch_generic(int argc, char* argv[]);
void hidden_block_gen_main(void);
void find_hidden_block(s32 cpuRoll, s32 cpuWantedSpaceIndex);
void SetStarSpawnDataChillyWaters(s32 index);
void SetStarSpawnDataDeepBlooperSea(s32 index);
void SetStarSpawnDataWoodyWoods(s32 index);
void SetStarSpawnDataCreepyCavern(s32 index);

void tempFunction(char *argv[]) {
    char* hexValue1 = argv[2];

    // Check if the hexadecimal value starts with "0x" or "0X"
    if (strncmp(hexValue1, "0x", 2) == 0 || strncmp(hexValue1, "0X", 2) == 0) {
        hexValue1 += 2; // Move the pointer past the prefix
    }
    
    int res2 = atoi(hexValue1);
    for (s32 i = 0; i < 3000; i++) {
        u32 prevSeed = cur_rng_seed;
        u8 diceRollValue = RollDice();
        if (i < 800) {
            continue;
        }

        if (res2 != 0) {
            if (diceRollValue != res2) {
                continue;
            }
        }

        printf("Calls: %ld, Seed: %08lX Rolls: %d\n", i, prevSeed, diceRollValue);
    }
}

// Structure to hold command and function pointer
typedef struct {
    const char *cmd;
    void (*func)(int, char**);
} Command;

// Array of commands and corresponding functions
Command commands[] = {
    {"--simduel", simduel},
    {"--simduel2", simduel2},
    {"--simduel3", simduel3},
    {"--rngadv", rngadv},
    {"--roll_chain", rollchain},
    {"--cpu_watch_chilly_waters", cpu_item_space_watch_chilly_waters},
    {"--cpu_watch_deep_blooper_sea", cpu_item_space_watch_deep_blooper_sea},
    {"--cpu_watch_woody_woods", cpu_item_space_watch_woody_woods},
    {"--cpu_watch_creepy_cavern", cpu_item_space_watch_creepy_cavern},
    {"--cpu_watch_generic", cpu_item_space_watch_generic},
    {"--hiddenblockgen", hiddenblockgen},
    {NULL, NULL} // Sentinel value to mark the end of the array
};

void print_help() {
    printf(
        "Args:\n"
        "--simduel\n"
        "--simduel2\n"
        "--simduel3\n"
        "--rngadv\n"
        "--roll_chain\n"
        "--cpu_watch_chilly_waters\n"
        "--cpu_watch_deep_blooper_sea\n"
        "--cpu_watch_woody_woods\n"
        "--cpu_watch_generic\n"
        "--hiddenblockgen\n"
    );
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_help();
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        int found = 0;
        for (Command *cmd = commands; cmd->cmd != NULL; cmd++) {
            if (strcmp(argv[i], cmd->cmd) == 0) {
                cmd->func(argc, argv);
                return 0;
            }
        }
        if (!found) {
            printf("Unknown argument: %s\n", argv[i]);
            print_help();
            return 1; // Indicate an error
        }
    }

    return 0;
}

void simduel(int argc, char* argv[]) {
    SimDuelMode();
}

void simduel2(int argc, char* argv[]) {
    SimDuelMode2();
}

void simduel3(int argc, char* argv[]) {
    SimDuelMode3();
}

void rngadv(int argc, char* argv[]) {
    u32 seed1;
    u32 seed2;

    if (argc != 4) {
        printf("Usage: %s --rngadv <hexadecimal_seed1> <hexadecimal_seed2>\n", argv[0]);
        return;
    }
    char* hexValue1 = argv[2];
    char* hexValue2 = argv[3];

    if (hexValue1[0] == '0') {
        if (hexValue1[1] == 'x' || hexValue1[1] == 'X'){ 
            hexValue1 += 2; //iterate over prefix
        }
    }

    if (hexValue2[0] == '0') {
        if (hexValue2[1] == 'x' || hexValue2[1] == 'X'){ 
            hexValue2 += 2; //iterate over prefix
        }
    }

    if (sscanf(hexValue1, "%08lX", &seed1) != 1 || sscanf(hexValue2, "%08lX", &seed2) != 1) {
        printf("Usage: %s --rngadv <hexadecimal_seed1> <hexadecimal_seed2>\n", argv[0]);
        return;
    }

    //printf("Seed1: %08lX, Seed2: %08lX\n", seed1, seed2);
    u32 callTotal = MeasureRngCalls(seed1, seed2);
    printf("Calls: %lu", callTotal);   
}

void rollchain(int argc, char* argv[]) {
    u32 wantedRoll;
    u32 chain_bound;

    //printf("arg count: %d\n", argc);
    if (argc <= 2) {
        printf("Usage: %s --rollchain <rollValue> <chainAmount(optional, defaults to 2)>\n", argv[0]);
        return;
    }
    if (argc == 4) {
        sscanf(argv[3], "%08lX", &chain_bound);
    } else {
        printf("Chain length defaulting to 2\n");
        chain_bound = 2;
    }

    sscanf(argv[2], "%ld", &wantedRoll);
    u32 prevDiceRoll = 0;
    s32 chain = 0;
    u32 seedChainStart = 0;
    for (s32 i = 0; i < 20000; i++) {
        u32 prevSeed = cur_rng_seed;
        u8 diceRollValue = RollDice();
        if (prevDiceRoll == diceRollValue && diceRollValue == wantedRoll) {
            if (chain == 0) {
                seedChainStart = prevSeed;
            }
            chain++;
        } else {
            if (chain >= chain_bound) {
                printf("Roll %ld, length: %ld, Calls: %ld, Seed: %08lX\n", prevDiceRoll, chain, i - chain, seedChainStart);
            }
            chain = 0;
        }
        prevDiceRoll = diceRollValue;

        cur_rng_seed = prevSeed;
        ADV_SEED(cur_rng_seed);
    }
}

char* ParseStringIfHex(char* string) {
    if (string[0] == '0') {
        if (string[1] == 'x' || string[1] == 'X') {
            string += 2;
        }
    }
    return string;
}

void cpu_item_space_watch_generic(int argc, char* argv[]) {
    s32 rollValue = 0;
    s32 jumps = 0;

    switch (argc) {
        case 4:
            sscanf(argv[3], "%ld", &jumps);
            if (jumps > 10 || jumps < 0) {
                printf("Invalid value passed for jumps\n");
                return;
            } 
        case 3:
            sscanf(argv[2], "%ld", &rollValue);
            if (rollValue > 10 || rollValue < 0) {
                printf("Invalid value passed for rollValue\n");
                return;
            }
    }

    printf("rollValue: %ld, jumps: %ld\n", rollValue, jumps);
    CPUGetWatchGeneric(rollValue, jumps);
}

// Constants
#define MAX_JUMPS 10
#define MAX_ROLL 10
#define INVALID_VALUE -1

void cpu_item_space_watch_chilly_waters(int argc, char* argv[]) {
    s32 rollValue = INVALID_VALUE;
    s32 jumpsBeforeJunction = INVALID_VALUE;
    s32 jumpsAfterJunction = INVALID_VALUE;
    char bufferForItem[32];
    s32 itemSlot1 = INVALID_VALUE;
    s32 starSpawnIndex = INVALID_VALUE;

    if (argc < 3 || argc > 7) {
        printf("Error: unexpected arg count\n");
        return;
    }

    // Parse arguments based on their count
    switch (argc) {
        case 7:
            if (sscanf(argv[6], "%ld", &starSpawnIndex) != 1 || starSpawnIndex < 0 || starSpawnIndex >= 8) {
                printf("Invalid value passed for starSpawnIndex\n");
                return;
            }
        case 6:
            sscanf(argv[5], "%31s", bufferForItem);
            if (strcmp(bufferForItem, "--mushroom") == 0) {
                itemSlot1 = MUSHROOM;
            } else {
                printf("Invalid item specified, setting to no item\n");
                itemSlot1 = -1;
            }
        case 5:
            if (sscanf(argv[4], "%ld", &jumpsAfterJunction) != 1 || jumpsAfterJunction < 0 || jumpsAfterJunction > MAX_JUMPS) {
                printf("Invalid value passed for jumpsAfterJunction\n");
                return;
            }
        case 4:
            if (sscanf(argv[3], "%ld", &jumpsBeforeJunction) != 1 || jumpsBeforeJunction < 0 || jumpsBeforeJunction > MAX_JUMPS) {
                printf("Invalid value passed for jumpsBeforeJunction\n");
                return;
            }
        case 3:
            if (sscanf(argv[2], "%ld", &rollValue) != 1 || rollValue < 0 || rollValue > MAX_ROLL) {
                printf("Invalid value passed for rollValue\n");
                return;
            }
            break;
        default:
            printf("Error: unexpected arg count\n");
            return;
    }

    gGameStatus.boardIndex = CHILLY_WATERS;
    SetStarSpawnDataChillyWaters(starSpawnIndex);
    
    // Display the parsed values
    printf("rollValue: %ld, jumpsBefore: %ld, jumpsAfter: %ld\n", rollValue, jumpsBeforeJunction, jumpsAfterJunction);
    CPUGetWatchChillyWaters(rollValue, jumpsBeforeJunction, jumpsAfterJunction, itemSlot1);
}

void cpu_item_space_watch_deep_blooper_sea(int argc, char* argv[]) {
    s32 rollValue = INVALID_VALUE;
    s32 jumpsBeforeJunction = INVALID_VALUE;
    s32 jumpsAfterJunction = INVALID_VALUE;
    char bufferForItem[32];
    s32 itemSlot1 = INVALID_VALUE;
    s32 starSpawnIndex = INVALID_VALUE;

    switch (argc) {
        case 7:
            if (sscanf(argv[6], "%ld", &starSpawnIndex) != 1 || starSpawnIndex < 0 || starSpawnIndex >= 8) {
                printf("Invalid value passed for starSpawnIndex\n");
                return;
            }
        case 6:
            sscanf(argv[5], "%31s", bufferForItem);
            if (strcmp(bufferForItem, "--mushroom") == 0) {
                itemSlot1 = MUSHROOM;
            } else {
                printf("Invalid item specified, setting to no item\n");
                itemSlot1 = -1;
            }
        case 5:
            sscanf(argv[4], "%ld", &jumpsAfterJunction);
            if (jumpsAfterJunction > 10 || jumpsAfterJunction < 0) {
                printf("Invalid value passed for jumpsAfterJunction\n");
                return;
            } 
        case 4:
            sscanf(argv[3], "%ld", &jumpsBeforeJunction);
            if (jumpsBeforeJunction > 10 || jumpsBeforeJunction < 0) {
                printf("Invalid value passed for jumpsBeforeJunction\n");
                return;
            } 
        case 3:
            sscanf(argv[2], "%ld", &rollValue);
            if (rollValue > 10 || rollValue < 0) {
                printf("Invalid value passed for rollValue\n");
                return;
            }
    }

    gGameStatus.boardIndex = DEEP_BLOOPER_SEA;
    SetStarSpawnDataDeepBlooperSea(starSpawnIndex);

    printf("rollValue: %ld, jumpsBefore: %ld, jumpsAfter: %ld\n", rollValue, jumpsBeforeJunction, jumpsAfterJunction);
    CPUGetWatchDeepBlooperSea(rollValue, jumpsBeforeJunction, jumpsAfterJunction, itemSlot1);
}

void cpu_item_space_watch_spiny_desert(int argc, char* argv[]) {
    s32 rollValue = INVALID_VALUE;
    s32 jumpsBeforeJunction = INVALID_VALUE;
    s32 jumpsAfterJunction = INVALID_VALUE;
    char bufferForItem[32];
    s32 itemSlot1 = INVALID_VALUE;
    s32 starSpawnIndex = INVALID_VALUE;

    switch (argc) {
        case 7:
            if (sscanf(argv[6], "%ld", &starSpawnIndex) != 1 || starSpawnIndex < 0 || starSpawnIndex >= 8) {
                printf("Invalid value passed for starSpawnIndex\n");
                return;
            }
        case 6:
            sscanf(argv[5], "%s", bufferForItem);
            if (strncmp(bufferForItem, "--mushroom", sizeof("--mushroom")) == 0) {
                itemSlot1 = MUSHROOM;
            } else if (strncmp(bufferForItem, "--skeleton_key", sizeof("--skeleton_key")) == 0) {
                itemSlot1 = SKELETON_KEY;
            }
        case 5:
            sscanf(argv[4], "%ld", &jumpsAfterJunction);
            if (jumpsAfterJunction > 10 || jumpsAfterJunction < 0) {
                printf("Invalid value passed for jumpsAfterJunction\n");
                return;
            } 
        case 4:
            sscanf(argv[3], "%ld", &jumpsBeforeJunction);
            if (jumpsBeforeJunction > 10 || jumpsBeforeJunction < 0) {
                printf("Invalid value passed for jumpsBeforeJunction\n");
                return;
            }
        case 3:
            sscanf(argv[2], "%ld", &rollValue);
            if (rollValue > 10 || rollValue < 0) {
                printf("Invalid value passed for rollValue\n");
                return;
            }
    }

    printf("rollValue: %ld, jumpsBefore: %ld, jumpsAfter: %ld item: %ld\n", rollValue, jumpsBeforeJunction, jumpsAfterJunction, itemSlot1);
    CPUGetWatchSpinyDesert(rollValue, jumpsBeforeJunction, jumpsAfterJunction, itemSlot1);
}

void cpu_item_space_watch_woody_woods(int argc, char* argv[]) {
    s32 rollValue = INVALID_VALUE;
    s32 jumpsBeforeJunction = INVALID_VALUE;
    s32 jumpsAfterJunction = INVALID_VALUE;
    char bufferForItem[32];
    s32 itemSlot1 = INVALID_VALUE;
    s32 starSpawnIndex = INVALID_VALUE;

    switch (argc) {
        case 7:
            if (sscanf(argv[6], "%ld", &starSpawnIndex) != 1 || starSpawnIndex < 0 || starSpawnIndex >= 8) {
                printf("Invalid value passed for starSpawnIndex\n");
                return;
            }
        case 6:
            sscanf(argv[5], "%s", bufferForItem);
            if (strncmp(bufferForItem, "--mushroom", sizeof("--mushroom")) == 0) {
                itemSlot1 = MUSHROOM;
            }
        case 5:
            sscanf(argv[4], "%ld", &jumpsAfterJunction);
            if (jumpsAfterJunction > 10 || jumpsAfterJunction < 0) {
                printf("Invalid value passed for jumpsAfterJunction\n");
                return;
            } 
        case 4:
            sscanf(argv[3], "%ld", &jumpsBeforeJunction);
            if (jumpsBeforeJunction > 10 || jumpsBeforeJunction < 0) {
                printf("Invalid value passed for jumpsBeforeJunction\n");
                return;
            } 
        case 3:
            sscanf(argv[2], "%ld", &rollValue);
            if (rollValue > 10 || rollValue < 0) {
                printf("Invalid value passed for rollValue\n");
                return;
            }
    }

    gGameStatus.boardIndex = WOODY_WOODS;
    SetStarSpawnDataWoodyWoods(starSpawnIndex);

    printf("rollValue: %ld, jumpsBefore: %ld, jumpsAfter: %ld\n", rollValue, jumpsBeforeJunction, jumpsAfterJunction);
    CPUGetWatchWoodyWoods(rollValue, jumpsBeforeJunction, jumpsAfterJunction, itemSlot1);
}

void cpu_item_space_watch_creepy_cavern(int argc, char* argv[]) {
    s32 rollValue = INVALID_VALUE;
    s32 jumpsBeforeJunction = INVALID_VALUE;
    s32 jumpsAfterJunction = INVALID_VALUE;
    char bufferForItem[32];
    s32 itemSlot1 = INVALID_VALUE;
    s32 starSpawnIndex = INVALID_VALUE;

    switch (argc) {
        case 7:
            if (sscanf(argv[6], "%ld", &starSpawnIndex) != 1 || starSpawnIndex < 0 || starSpawnIndex >= 8) {
                printf("Invalid value passed for starSpawnIndex\n");
                return;
            }
        case 6:
            sscanf(argv[5], "%s", bufferForItem);
            if (strncmp(bufferForItem, "--mushroom", sizeof("--mushroom")) == 0) {
                itemSlot1 = MUSHROOM;
            }
        case 5:
            sscanf(argv[4], "%ld", &jumpsAfterJunction);
            if (jumpsAfterJunction > 10 || jumpsAfterJunction < 0) {
                printf("Invalid value passed for jumpsAfterJunction\n");
                return;
            } 
        case 4:
            sscanf(argv[3], "%ld", &jumpsBeforeJunction);
            if (jumpsBeforeJunction > 10 || jumpsBeforeJunction < 0) {
                printf("Invalid value passed for jumpsBeforeJunction\n");
                return;
            } 
        case 3:
            sscanf(argv[2], "%ld", &rollValue);
            if (rollValue > 10 || rollValue < 0) {
                printf("Invalid value passed for rollValue\n");
                return;
            }
    }

    gGameStatus.boardIndex = CREEPY_CAVERN;
    SetStarSpawnDataCreepyCavern(starSpawnIndex);

    printf("rollValue: %ld, jumpsBefore: %ld, jumpsAfter: %ld\n", rollValue, jumpsBeforeJunction, jumpsAfterJunction);
    CPUGetWatchCreepyCavern(rollValue, jumpsBeforeJunction, jumpsAfterJunction, itemSlot1);
}

void hiddenblockgen(int argc, char* argv[]) {
    s32 cpuRoll;
    s32 cpuWantedIndex;

    // if (argc < 4) {
    //     return;
    // }
    sscanf(argv[2], "%ld", &cpuRoll);
    sscanf(argv[3], "%ld", &cpuWantedIndex);
    find_hidden_block(cpuRoll, cpuWantedIndex);
}