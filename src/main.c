#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/mp3.h"

u32 cur_rng_seed = 0x0000D9ED; //initial starting seed D_80097650

// Function declarations
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
void CPUGetWatchChillyWaters(s32 rollValue, u32 numOfJumps);
void CPUGetWatchSpinyDesert(s32 rollValue, u32 numOfJumps);
void CPUGetWatchWoodyWoods(s32 rollValue, u32 numOfJumps);
void CPUGetWatchDeepBlooperSea(s32 rollValue, u32 numOfJumps);
void cpu_item_space_watch_deep_blooper_sea(int argc, char* argv[]);
void cpu_item_space_watch_chilly_waters(int argc, char* argv[]);
void cpu_item_space_watch_spiny_desert(int argc, char* argv[]);
void cpu_item_space_watch_woody_woods(int argc, char* argv[]);
void cpu_item_space_watch_generic(int argc, char* argv[]);
void hidden_block_gen_main(void);

void tempFunction(char *argv[]) {
    char* hexValue1 = argv[2];

    if (hexValue1[0] == '0') {
        if (hexValue1[1] == 'x' || hexValue1[1] == 'X'){ 
            hexValue1 += 2; //iterate over prefix
        }
    }
    
    int res2 = atoi(hexValue1);
    for (s32 i = 0; i < 3000; i++) {
        u32 prevSeed = cur_rng_seed;
        u8 diceRollValue = rollDice();
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

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf(
        "Args:\n"
        "--simduel\n"
        "--simduel2\n"
        "--simduel3\n"
        "--rngadv\n"
        "--roll_chain\n"
        "--cpu_watch_chilly_waters\n"
        "--cpu_watch_deep_blooper_sea\n"
        "--cpu_watch_generic\n"
        "--hiddenblockgen\n"
        );
        return 0;
    }

    if (strncmp("--temp", argv[1], sizeof("--temp")) == 0) {
        tempFunction(argv);
        return 0;
    }
    // Loop through the command-line arguments
    for (int i = 1; i < argc; i++) {
        // Check the argument and call the corresponding function
        if (strcmp(argv[i], "--simduel") == 0) {
            simduel(argc, argv);
            return 0;
        } else if (strcmp(argv[i], "--simduel2") == 0) {
            simduel2(argc, argv);
            return 0;
        } else if (strcmp(argv[i], "--simduel3") == 0) {
            simduel3(argc, argv);
            return 0;
        } else if (strcmp(argv[i], "--rngadv") == 0) {
            rngadv(argc, argv);
            return 0;
        } else if (strcmp(argv[i], "--roll_chain") == 0) {
            rollchain(argc, argv);
            return 0;
        } else if (strcmp(argv[i], "--cpu_watch_chilly_waters") == 0) {
            cpu_item_space_watch_chilly_waters(argc, argv);
            return 0;
        } else if (strcmp(argv[i], "--cpu_watch_deep_blooper_sea") == 0) {
            cpu_item_space_watch_deep_blooper_sea(argc, argv);
            return 0;
        } else if (strcmp(argv[i], "--cpu_watch_spiny_desert") == 0) {
            cpu_item_space_watch_spiny_desert(argc, argv);
            return 0;
        } else if (strcmp(argv[i], "--cpu_watch_woody_woods") == 0) {
            cpu_item_space_watch_woody_woods(argc, argv);
            return 0;
        } else if (strcmp(argv[i], "--cpu_watch_generic") == 0) {
            cpu_item_space_watch_generic(argc, argv);
            return 0;
        } else if (strcmp(argv[i], "--hiddenblockgen") == 0) {
            hiddenblockgen(argc, argv);
            return 0;
        } else {
            printf("Unknown argument: %s\n", argv[i]);
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
    s32 callTotal = MeasureRngCalls(seed1, seed2);
    printf("Calls: %ld", callTotal);   
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
        u8 diceRollValue = rollDice();
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
    u32 rollValue;
    u32 numOfJumps;

    if (argc == 2) {
        rollValue = 0;
        printf("numOfJumps not set! assuming none\n");
        numOfJumps = 0;
    } else if (argc == 3) {
        char* buffer = ParseStringIfHex(argv[2]);
        sscanf(buffer, "%08lX", &rollValue);
        printf("numOfJumps not set! assuming none\n");
        numOfJumps = 0;   
    } else if (argc == 4) {
        char* buffer = ParseStringIfHex(argv[2]);
        sscanf(buffer, "%08lX", &rollValue);

        char* buffer2 = ParseStringIfHex(argv[3]);
        sscanf(buffer2, "%08lX", &numOfJumps);

        if (numOfJumps >= 4) {
            printf("numOfJumps too high! Defaulting to 3\n");
            numOfJumps = 3;
        }     
    }
    CPUGetWatchGeneric(rollValue, numOfJumps);
}

void cpu_item_space_watch_chilly_waters(int argc, char* argv[]) {
    u32 rollValue;
    u32 numOfJumps;

    if (argc == 2) {
        rollValue = 0;
        printf("numOfJumps not set! assuming none\n");
        numOfJumps = 0;
    } else if (argc == 3) {
        char* buffer = ParseStringIfHex(argv[2]);
        sscanf(buffer, "%08lX", &rollValue);
        printf("numOfJumps not set! assuming none\n");
        numOfJumps = 0;   
    } else if (argc == 4) {
        char* buffer = ParseStringIfHex(argv[2]);
        sscanf(buffer, "%08lX", &rollValue);

        char* buffer2 = ParseStringIfHex(argv[3]);
        sscanf(buffer2, "%08lX", &numOfJumps);
        if (numOfJumps >= 4) {
            printf("numOfJumps too high! Defaulting to 3\n");
            numOfJumps = 3;
        }     
    }
    CPUGetWatchChillyWaters(rollValue, numOfJumps);
}

void cpu_item_space_watch_deep_blooper_sea(int argc, char* argv[]) {
    u32 rollValue;
    u32 numOfJumps;

    if (argc == 2) {
        rollValue = 0;
        printf("numOfJumps not set! assuming none\n");
        numOfJumps = 0;
    } else if (argc == 3) {
        char* buffer = ParseStringIfHex(argv[2]);
        sscanf(buffer, "%08lX", &rollValue);
        printf("numOfJumps not set! assuming none\n");
        numOfJumps = 0;   
    } else if (argc == 4) {
        char* buffer = ParseStringIfHex(argv[2]);
        sscanf(buffer, "%08lX", &rollValue);

        char* buffer2 = ParseStringIfHex(argv[3]);
        sscanf(buffer2, "%08lX", &numOfJumps);
        if (numOfJumps >= 4) {
            printf("numOfJumps too high! Defaulting to 3\n");
            numOfJumps = 3;
        }     
    }
    CPUGetWatchDeepBlooperSea(rollValue, numOfJumps);
}

void cpu_item_space_watch_spiny_desert(int argc, char* argv[]) {
    u32 rollValue;
    u32 numOfJumps;

    if (argc == 2) {
        rollValue = 0;
        printf("numOfJumps not set! assuming none\n");
        numOfJumps = 0;
    } else if (argc == 3) {
        char* buffer = ParseStringIfHex(argv[2]);
        sscanf(buffer, "%08lX", &rollValue);
        printf("numOfJumps not set! assuming none\n");
        numOfJumps = 0;   
    } else if (argc == 4) {
        char* buffer = ParseStringIfHex(argv[2]);
        sscanf(buffer, "%08lX", &rollValue);

        char* buffer2 = ParseStringIfHex(argv[3]);
        sscanf(buffer2, "%08lX", &numOfJumps);
        if (numOfJumps >= 4) {
            printf("numOfJumps too high! Defaulting to 3\n");
            numOfJumps = 3;
        }     
    }

    CPUGetWatchSpinyDesert(rollValue, numOfJumps);
}

void cpu_item_space_watch_woody_woods(int argc, char* argv[]) {
    u32 rollValue;
    u32 numOfJumps;

    if (argc == 2) {
        rollValue = 0;
        printf("numOfJumps not set! assuming none\n");
        numOfJumps = 0;
    } else if (argc == 3) {
        char* buffer = ParseStringIfHex(argv[2]);
        sscanf(buffer, "%08lX", &rollValue);
        printf("numOfJumps not set! assuming none\n");
        numOfJumps = 0;   
    } else if (argc == 4) {
        char* buffer = ParseStringIfHex(argv[2]);
        sscanf(buffer, "%08lX", &rollValue);

        char* buffer2 = ParseStringIfHex(argv[3]);
        sscanf(buffer2, "%08lX", &numOfJumps);
        if (numOfJumps >= 4) {
            printf("numOfJumps too high! Defaulting to 3\n");
            numOfJumps = 3;
        }     
    }
    CPUGetWatchWoodyWoods(rollValue, numOfJumps);
}

void hiddenblockgen(int argc, char* argv[]) {
    hidden_block_gen_main();
}