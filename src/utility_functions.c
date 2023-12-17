#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/mp3.h"

u8 HuGetRandomByte(void);
s16 func_800EB5DC_FF1FC(s32 arg0, u8 arg1);

//probably only 4 entries but 10 for safety
u8 D_800CD0B6[] = {0xC8, 0xBD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

u8 RNGPercentChance(s8 arg0) { //func_800EB9D4 in duel mode
    return arg0 > ((HuGetRandomByte() * 0x63) >> 8);
}

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

s16 func_800EBCD4_FF8F4(u8 arg0) {
    return func_800EB5DC_FF1FC(2, arg0);
}

u8 HuGetRandomByte(void) {
    ADV_SEED(cur_rng_seed);
    return (cur_rng_seed + 1) >> 16;
}

s32 func_800EEF80_102BA0(f32 arg0) { //800EFE20 in duel mode
    // HuGetRandomByte returns an unsigned byte
    u8 randomByte1 = HuGetRandomByte();
    u8 randomByte2 = HuGetRandomByte();
    s32 shiftedByte1 = (randomByte1 << 8);

    // Normalize the 16-bit number to the range [0, 1), then multiply by arg0
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;
    
    return scaledRandom;
}

SpaceData* func_800EB160_FED80(s16 arg0) {
    return &spaces[arg0];
}

s32 MeasureRngCalls(u32 seedStart, u32 seedEnd) {
    s32 calls = 0;
    cur_rng_seed = seedStart;
    while (cur_rng_seed != seedEnd) {
        if (calls > 10000000) {
            printf("Is more than 10 million calls away...\n");
            return -1;
        }
        HuGetRandomByte();
        calls++;
    }
    return calls;
}

u8 rollDice(void) { //func_800DB148 in duel mode
    return (((HuGetRandomByte() & 0xFF) % 10) + 1);
}