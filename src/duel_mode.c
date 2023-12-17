#include <stdio.h>
#include <string.h>
#include "../include/mp3.h"

//1
char PowerUpString[] = "Power Up";

//2
char SwitchPlacesString[] = "Switch Places";

//3
char Minus10CoinsString[] = "Minus 10 Coins";

//4
char Plus10CoinsString[] = "Plus 10 Coins";

//5
char ReturnToStartString[] = "Return To Start";

//6
char GetOpponentSpacesString[] = "Get Opponent Spaces";

//7
char PowerUp2String[] = "Power Up";

//8
char PowerDownString[] = "Power Down";

//9
char SwapPartnerPositionsString[] = "Swap Partner Positions";

//A
char ClearAllSpacesString[] = "Clear All Spaces";

s32 DecidePlayerOrder(void) {
    //if 0, player is first. if 1, player is second
    return func_800EEF80_102BA0(2.0f);
}

void SimDuelMode3(void) {
    for (u32 i = 0; i < 100000; i++) {
        u32 startSeed = cur_rng_seed;
        u8 diceRoll1 = rollDice();

        if (diceRoll1 != 9) {
            cur_rng_seed = startSeed;
            ADV_SEED(cur_rng_seed);
            continue;
        }
    }
}

void SimDuelMode2(void) {
    u32 chain = 0;
    u32 startSeed = 0;
    u32 prevSeed = 0;
    u32 iterationChainStart = 0;
    u32 cpuStartDiceRoll = 0;
    for (u32 i = 0; i < 20000; i++){ 
        prevSeed = cur_rng_seed;
        u8 cpuReverseDiceRoll = rollDice();
        if (cpuReverseDiceRoll == 1 || cpuReverseDiceRoll == 2 || cpuReverseDiceRoll == 3) {
            if (cpuReverseDiceRoll == 1) {
                for (s32 j = 0; j < 274; j++) {
                    ADV_SEED(cur_rng_seed);
                }
            } else if (cpuReverseDiceRoll == 2){ 
                for (s32 j = 0; j < 287; j++) {
                    ADV_SEED(cur_rng_seed);
                }
            } else if (cpuReverseDiceRoll == 3) {
                for (s32 j = 0; j < 301; j++) {
                    ADV_SEED(cur_rng_seed);
                }
            }

            u8 playerDiceRoll = rollDice();
            u8 temp = 4 - cpuReverseDiceRoll;
            if (playerDiceRoll == temp) {
                if (chain == 0) {
                    startSeed = prevSeed;
                    iterationChainStart = i;
                    cpuStartDiceRoll = cpuReverseDiceRoll;
                }
                chain++;
            } else {
                if (chain >= 2) {
                    printf("CPU Roll: %ld, Chain length %ld, Iterations %ld, Seed: %08lX\n", cpuStartDiceRoll, chain, iterationChainStart, startSeed);
                }
                chain = 0;
            }
        } else {
            if (chain >= 2) {
                printf("CPU Roll: %ld, Chain length %ld, Iterations %ld, Seed: %08lX\n", cpuStartDiceRoll, chain, iterationChainStart, startSeed);
            }
            chain = 0;            
        }
        cur_rng_seed = prevSeed;
        ADV_SEED(cur_rng_seed);
    }
}

//we want the CPU to go first
void SimDuelMode(void) {
    // u8 playerOrder = DecidePlayerOrder();
    // for (s32 i = 0; i < 244; i++) {
    //     ADV_SEED(cur_rng_seed);
    // }
    // s32 someResultDuringMillenniumSpin = func_800EEF80_102BA0(20.0f);

    // for (u32 i = 0; i < 100000; i++) {
    //     u32 chain = 0;
    //     u32 prevRequirements = 0;
    //     u32 startSeed = cur_rng_seed;
    //     u8 diceRoll1 = rollDice();

    //     if (diceRoll1 != 9) {
    //         cur_rng_seed = startSeed;
    //         ADV_SEED(cur_rng_seed);
    //         prevRequirements = 0;
    //         chain = 0;
    //         continue;
    //     }

    //     for (s32 j = 0; j < 94; j++) {
    //         ADV_SEED(cur_rng_seed);
    //     }

    //     if (RNGPercentChance(70) == 0){
    //         cur_rng_seed = startSeed;
    //         ADV_SEED(cur_rng_seed);
    //         prevRequirements = 0;
    //         chain = 0;
    //         continue;
    //     }

    //     for (s32 j = 0; j < 369; j++) {
    //         ADV_SEED(cur_rng_seed);
    //     }


    //     if (prevRequirements == 1) {
    //         chain++;
    //     }

    //     if (chain >= 2) {
    //         printf("Chain of: %d, Seed: %08lX, Iteration: %d\n", chain, startSeed, i);
    //     }
        
        
        

        // //CPU landed on reverse
        // cur_rng_seed = startSeed;
        // ADV_SEED(cur_rng_seed);



    // u32 prevDiceRoll = 0;
    // s32 chain = 0;
    // u32 seedChainStart = 0;
    // u8 diceRoll2Value = 0;
    // for (s32 i = 0; i < 100000; i++) {
    //     u32 prevSeed = cur_rng_seed;
    //     u8 diceRollValue = rollDice();
    //     if (prevDiceRoll == diceRollValue && prevDiceRoll == 9 && diceRollValue == 9) {
    //         for (s32 j = 0; j < 94; j++) {
    //             ADV_SEED(cur_rng_seed);
    //         }

    //         if (RNGPercentChance(70) == 0){
    //             cur_rng_seed = prevSeed;
    //             ADV_SEED(cur_rng_seed);
    //             chain = 0;
    //             continue;
    //         }
            
    //         for (s32 j = 0; j < 369; j++) {
    //             ADV_SEED(cur_rng_seed);
    //         }

    //         diceRoll2Value = rollDice();

    //         if (diceRoll2Value < 4) {
    //             if (chain == 0) {
    //                 seedChainStart = prevSeed;
    //             }
    //             chain++;
    //         }
    //     } else {
    //         if (chain >= 1) {
    //             printf("Chain for %ld, length %ld, Iterations %ld, Seed: %08lX, roll2: %d\n", prevDiceRoll, chain, i - chain, seedChainStart, diceRoll2Value);
    //         }
    //         chain = 0;
    //     }
    //     prevDiceRoll = diceRollValue;

    //     cur_rng_seed = prevSeed;
    //     ADV_SEED(cur_rng_seed);
    // }
        

    u32 prevPlayerOrder = 0;
    s32 chain = 0;
    u32 seedChainStart = 0;
    for (s32 i = 0; i < 20000; i++) {
        u32 prevSeed = cur_rng_seed;
        u8 playerOrder = DecidePlayerOrder();
        if (prevPlayerOrder == playerOrder) {
            if (chain == 0) {
                seedChainStart = prevSeed;
            }
            chain++;
        } else {
            if (chain >= 3) {
                if (prevPlayerOrder != 0) {
                    printf("Chain for %ld, length %ld, Iterations %ld, Seed: %08lX\n", prevPlayerOrder, chain, i - chain, seedChainStart);
                }
                
            }
            chain = 0;
        }
        prevPlayerOrder = playerOrder;

        cur_rng_seed = prevSeed;
        cur_rng_seed = cur_rng_seed * 0x41C64E6D + 0x3039; //advance seed
    }
}