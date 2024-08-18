#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/mp3.h"

u8 rand8(void);
s16 func_800EB5DC_FF1FC(s32 arg0, u8 arg1, s32 numOfBoardSpaces, s32 boardIndex);

//probably only 4 entries but 10 for safety
u8 D_800CD0B6[] = {0xC8, 0xBD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// u8 RNGPercentChance(s8 arg0) { //func_800EB9D4 in duel mode
//     return arg0 > ((rand8() * 0x63) >> 8);
// }

s32 func_80035F98_36B98(s32 input) {
    s32 byteValue;
    s32 adjustedIndex;
    s32 byteIndex;
    s32 bitIndex;
    s32 mask;

    if (input < 0) {
        byteValue = D_800CD0B6[(input + 7) >> 3];
    } else {
        byteValue = D_800CD0B6[input >> 3];
    }

    if (input >= 0) {
        adjustedIndex = input;
    } else {
        adjustedIndex = input + 7;
    }

    // Calculate the byte index (divide by 8)
    byteIndex = adjustedIndex >> 3;

    // Calculate the bit index
    bitIndex = input - (byteIndex << 3);

    mask = (1 << bitIndex);

    return byteValue & mask;
}

s16 func_800EBCD4_FF8F4(u8 arg0, s32 numOfBoardSpaces, s32 boardIndex) {
    return func_800EB5DC_FF1FC(2, arg0, numOfBoardSpaces, boardIndex);
}

s32 func_800EEF80_102BA0(f32 arg0) { //800EFE20 in duel mode
    // rand8 returns an unsigned byte
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);

    // Normalize the 16-bit number to the range [0, 1), then multiply by arg0
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;
    
    return scaledRandom;
}

SpaceData* func_800EB160_FED80(s16 arg0, s32 boardIndex) {
    SpaceData* boardSpaces = spacesForBoards[boardIndex];
    return &boardSpaces[arg0];
}

u32 MeasureRngCalls(u32 seedStart, u32 seedEnd) {
    u32 calls = 0;
    cur_rng_seed = seedStart;
    while (cur_rng_seed != seedEnd) {
        if (calls > 10000000) {
            printf("Is more than 10 million calls away...\n");
            return -1;
        }
        rand8();
        calls++;
    }
    return calls;
}

u8 RollDice(void) { //func_800DBC2C in board play, func_800DB148 in duel mode
    u8 randByte = rand8();
    return ((randByte % 10) + 1);
}