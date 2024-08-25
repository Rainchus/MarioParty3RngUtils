#include "mp3.h"
#include "util.h"
#include <stdio.h>
#include <math.h>

#define FAST_TEXT 0
#define NORMAL_TEXT 1
#define SLOW_TEXT 2

#define FAST_WALK 0
#define NORMAL_WALK 1
#define SLOW_WALK 2

#define RARE_ITEM_WATCH 3
#define TOAD_QUESTION 0

#define GREEDY_OPTION 0
#define MIDDLE_OPTION 1
#define BOTTOM_OPTION 2

u32 cur_rng_seed = 0x0000D9ED; //initial starting seed D_80097650

Vec2f D_80101D5C_11597C[] = {
    {0.0f, 0.0f},
    {200.0f, 250.0f},
    {110.0f, 250.0f},
    {70.0f, 290.0f},
    {0.0f, 360.0f},
};

Vec2f D_80101D84_1159A4[] = {
    {0.0f, 0.0f},
    {20.0f, 70.0f},
    {-70.0f, 70.0f},
    {70.0f, 290.0f},
    {0.0f, 360.0f}
};

s32 framesForInitialTextBoxes[] = {648, 728, 868};

//advancements that happen during cpu selection on each message speed
s32 CpuSelectionArray0[] = {116, 196, 336};
s32 CpuSelectionArray1[] = {184, 264, 404};

//advancements that happen before rare item is decided
s32 CpuSelectionArray2[] = {108, 188, 328};

//advancements that happen while a cpu is at a bank at all 3 message speeds
s32 CpuBankRngAdvancements[] = {159, 199, 269};

GameStatus gGameStatus = {
    .unk0 = 1,
    .boardIndex = CHILLY_WATERS,
    .TotalTurns = 20,
    .CurrentTurn = 1,
    .curGameLength = 0, //20 turns
    .curStarSpawnIndex = 0, //TODO, verify this
    //does the game randomize these on board load and then randomly pick from one?
    .starSpawnIndicies = {1, 3, 2, 0, 4, 6, 5, 7}, //TODO, verify this
    .unkE = 0,
    .curPlayerIndex = 0,
    .unkData.unkArray_s16 = {0},
    .D_800CD096_s16 = {{0}},
    .D_800CD0B6 = {0x00, 0x00, 0x00, 0x00}, //is this longer?
};

u8 StarSpaceFlagArray[][2] = {
    {0x89, 0xBF}, //star space index 0
    {0x49, 0xBF}, //star space index 1
    {0xC9, 0xBE}, //star space index 2
    {0xC9, 0xBD}, //star space index 3
    {0xC9, 0xBB}, //star space index 4
    {0xC9, 0xB7}, //star space index 5
    {0xC9, 0xAF}, //star space index 6
    {0xC9, 0x9F}, //star space index 7
};


void SetStarSpawnData(s32 starSpawnIndex, s32 boardIndex) {
    //only first 2 bytes matter
    gGameStatus.D_800CD0B6[0] = StarSpaceFlagArray[starSpawnIndex][0];
    gGameStatus.D_800CD0B6[1] = StarSpaceFlagArray[starSpawnIndex][1];

    printf("[0]: %02X, [1]: %02X, [2]: %02X, [3]: %02X\n", gGameStatus.D_800CD0B6[0], gGameStatus.D_800CD0B6[1], gGameStatus.D_800CD0B6[2], gGameStatus.D_800CD0B6[3]);
}

s16 GetCurrentPlayerIndex(void) {
    return gGameStatus.curPlayerIndex;
}

Player* GetPlayerStruct(s32 index) {
    if (index < 0) {
        index = GetCurrentPlayerIndex();
    }
    return &gPlayers[index];
}

u8 rand8(void) {
    cur_rng_seed = cur_rng_seed * 0x41C64E6D + 0x3039;
    return (cur_rng_seed + 1) >> 16;
}

//func_800ECE9C
s16 RNGPercentChance(s8 percentChance) {
    u32 result;
    u32 randVal;

    randVal = rand8();
    //printf("randVal is %08X\n", randVal);
    result = (percentChance > ((randVal * 99) >> 8));

    return result;
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

u8 RollDice(void) { //func_800DBC2C in board play, func_800DB148 in duel mode
    u8 randByte = rand8();
    return ((randByte % 10) + 1);
}

//8 rng advancements to face fowards
void PlayerFaceForward(void) {
    for (int i = 0; i < 8; i++) {
        ADV_SEED(cur_rng_seed);
    }    
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

s32 GetSpaceIndexFromChainAndSpace(s32 curChainIndex, s32 curSpaceIndex) {
    SpaceChain* curBoardChains = BoardChains[gGameStatus.boardIndex].boardChainData;
    s16* curSpaceChain = curBoardChains[curChainIndex].spaceChainArray;
    return curSpaceChain[curSpaceIndex];
}

void SetPlayerNextChainAndSpaceFromAbsSpace(s32 absSpace, s32 mode, s32 playerIndex) {
    Player* player = &gPlayers[playerIndex];
    u32 AbsSpace = GetChainAndSpaceFromAbsSpace(absSpace);

    switch (mode) {
    case SET_CURRENT:
        player->cur_chain_index = AbsSpace >> 16;
        player->cur_space_index = AbsSpace & 0xFFFF;
        break;
    case SET_NEXT:
        player->next_chain_index = AbsSpace >> 16;
        player->next_space_index = AbsSpace & 0xFFFF;
        break;
    }
}

//handles all rng related things starting at decision of item space event
s32 HandleLogicFromItemSpace(s32 messageSpeed, s16* data) {
    u32 rngBeforeItemSpaceResult = cur_rng_seed;
    
    s32 itemSpaceOutcome = func_800EEF80_102BA0(5.0f);
    if (itemSpaceOutcome != TOAD_QUESTION) {
        return 0;
    }

    //advance rng up to text box based on text speed
    for (int i = 0; i < framesForInitialTextBoxes[messageSpeed]; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //get random question (advances rng twice)
    func_800EEF80_102BA0(5.0f);

    //advance rng through text box popping up
    for (int i = 0; i < 56; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //cpu choosen an option to the question
    s32 cpuChosenIndex = func_800EEF80_102BA0(3);

    s32 textBoxFrames;
    if (cpuChosenIndex == MIDDLE_OPTION) {
        textBoxFrames = CpuSelectionArray0[messageSpeed];
    } else if (cpuChosenIndex == BOTTOM_OPTION) {
        textBoxFrames = CpuSelectionArray1[messageSpeed];
    } else {
        //GREEDY_OPTION
        return 0;
    }

    //advance rng during cpu decision for option index
    for (int i = 0; i < textBoxFrames; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //what happens based on what cpu answers
    s32 questionOutcome = func_800EEF80_102BA0(10.0f);

    if (cpuChosenIndex == MIDDLE_OPTION) {
        if (questionOutcome >= 2) {
            return 0;
        }
    }

    if (cpuChosenIndex == BOTTOM_OPTION) {
        if (questionOutcome >= 3) {
            return 0;
        }
    }

    //cpu got rare item, advance rng for text box
    for (int i = 0; i < CpuSelectionArray2[messageSpeed]; i++) {
        ADV_SEED(cur_rng_seed);
    }

    s32 itemChosen = func_800EEF80_102BA0(4);
    if (itemChosen == RARE_ITEM_WATCH) {
        // for (int j = 0; j < 12; j++) {
        //     printf("Space: %04X\n", data[j]);
        // }
        //printf("Seed Before item space is %08X\n", rngBeforeItemSpaceResult);
        return 1;
    }
    return 0;
    
}

void DoBankAdvancements(s32 messageSpeed) {
    //player face bank when passing it
    for (int i = 0; i < 8; i++) {
        ADV_SEED(cur_rng_seed);
    }

    //time at bank
    for (int i = 0; i < CpuBankRngAdvancements[messageSpeed]; i++) {
        ADV_SEED(cur_rng_seed);
    }
}

int SetStarBitIndex(u32 index) {
    switch (index) {
    case 0x89BF:
        return 0;
    case 0x49BF:
        return 1;
    case 0xC9BE:
        return 2;
    case 0xC9BD:
        return 3;
    case 0xC9BB:
        return 4;
    case 0xC9B7:
        return 5;
    case 0xC9AF:
        return 6;
    case 0xC99F:
        return 7;
    default:
        return -1;
    }
}

int GetStarBitIndex(u32 value) {
    switch (value) {
    case 0x89BF:
        return 0;
    case 0x49BF:
        return 1;
    case 0xC9BE:
        return 2;
    case 0xC9BD:
        return 3;
    case 0xC9BB:
        return 4;
    case 0xC9B7:
        return 5;
    case 0xC9AF:
        return 6;
    case 0xC99F:
        return 7;
    default:
        return -1;
    }
}

void HuVecSubtract(Vec3f * dest, Vec3f * a, Vec3f * b) {
    float x = a->x - b->x;
    float y = a->y - b->y;
    float z = a->z - b->z;

    dest->x = x;
    dest->y = y;
    dest->z = z;
}

typedef struct Chain {
    u16 count;
    s16* spaces;
} Chain;

extern Chain* D_80105218;

f32 D_800A46A0_A52A0[] = {
    0.0f, 1.0f, 0.5f, 0.3333333433f, 0.25f, 0.200000003f, 0.1666666716f, 0.1428571492f, 0.125f, 0.1111111119f, 0.1000000015f, 0.09090909362f, 0.08333333582f, 0.07692307979f, 0.07142857462f, 0.06666667014f, 0.0625f, 0.05882352963f, 0.05555555597f, 0.05263157934f, 0.05000000075f, 0.04761904851f, 0.04545454681f, 0.04347826168f, 0.04166666791f, 0.03999999911f, 0.03846153989f, 0.03703703731f, 0.03571428731f, 0.03448275849f, 0.03333333507f, 0.03225806355f, 0.03125f, 0.03030303121f, 0.02941176482f, 0.02857142873f, 0.02777777798f, 0.02702702768f, 0.02631578967f, 0.02564102598f, 0.02500000037f, 0.02439024299f, 0.02380952425f, 0.02325581387f, 0.0227272734f, 0.02222222276f, 0.02173913084f, 0.02127659507f, 0.02083333395f, 0.02040816285f, 0.01999999955f, 0.01960784383f, 0.01923076995f, 0.01886792481f, 0.01851851866f, 0.01818181761f, 0.01785714366f, 0.01754385978f, 0.01724137925f, 0.01694915257f, 0.01666666754f, 0.01639344171f, 0.01612903178f, 0.01587301679f, 0.015625f, 0.0153846154f, 0.0151515156f, 0.01492537279f, 0.01470588241f, 0.01449275389f, 0.01428571437f, 0.01408450678f, 0.01388888899f, 0.01369863003f, 0.01351351384f, 0.01333333366f, 0.01315789483f, 0.01298701297f, 0.01282051299f, 0.01265822817f, 0.01250000019f, 0.0123456791f, 0.0121951215f, 0.01204819232f, 0.01190476213f, 0.01176470611f, 0.01162790693f, 0.01149425283f, 0.0113636367f, 0.01123595517f, 0.01111111138f, 0.01098901127f, 0.01086956542f, 0.01075268816f, 0.01063829754f, 0.01052631624f, 0.01041666698f, 0.01030927803f, 0.01123595517f, 0.01010101009f
};

f32 D_800A8A34_A9634 = -3.14159f;


f32 func_8008DE10_8EA10(f32 arg0, f32 arg1) {
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f4;
    f32 var_f0;
    f32 var_f2;
    s32 var_v0;
    
    if (arg0 == 0.0f) {
        return (arg1 > 0.0f) ? 0.0f: 3.14159f;
    }
    if (arg1 == 0.0f) {
        return (arg0 > 0.0f) ? 1.5708f: -1.5708f;
    }
    temp_f18 = arg0 / arg1;
    
    if (temp_f18 == 1.0f) {
        return (arg0 > 0.0f) ? 0.785398f: -2.35619f;
    }
    if (temp_f18 == -1.0f) {
        return (arg1 > 0.0f) ? -0.785398f: 2.35619f;
    }
    if ((temp_f18 > 1.0f) || (temp_f18 < -1.0f)) {
        temp_f0 = func_8008DE10_8EA10(arg1, arg0);
        if (arg1 > 0.0f) {
            return 1.5708f - temp_f0;
        }
        return (arg0 > 0.0f) ? 1.5708f - temp_f0 : -4.71239f - temp_f0;
    }
    temp_f16 = temp_f18 * temp_f18;
    var_f2 = 1.0f;
    temp_f4 = 1.0f / (1.0f + temp_f16);
    temp_f14 = temp_f16 * temp_f4;
    var_v0 = 4;
    var_f0 = (2.0f * temp_f14) / 3.0f;
    for (; var_v0 < 100; var_v0+=2) {
        var_f2 += var_f0;
        if (!(var_f0 <= 1e-07f)) {
            var_f0 *= (temp_f14 * (f32) var_v0) * D_800A46A0_A52A0[var_v0+1];
        } else {
            break;
        }
    }

    var_f2 *= (temp_f18 * temp_f4);
    return (arg1 > 0.0f) ? var_f2 : (arg0 > 0.0f) ? 3.14159f + var_f2: -3.14159f + var_f2;
}

f32 func_8008E108_8ED08(f32 zPos, f32 xPos) {
    return func_8008DE10_8EA10(zPos, xPos) * 57.2958f;
}

f32 func_800D8790_EC3B0(Vec3f* arg0) {
    f32 temp_f4;

    if (arg0->x != 0.0f || arg0->z != 0.0f) {
        if (arg0->x == 0.0f) {
            if (arg0->z > 0.0f) {
                return 0.0f;
            }
            return 180.0f;
        }
        if (arg0->z == 0.0f) {
            if (arg0->x > 0.0f) {
                return 90.0f;
            } else {
                return 270.0f;
            }
        }

        temp_f4 = func_8008E108_8ED08(arg0->z, arg0->x);
        if (arg0->z < 0.0f) {
            temp_f4 = 90.0f - temp_f4;
        } else {
            temp_f4 = 90.0f - temp_f4;
            if (temp_f4 < 0.0f) {
                temp_f4 += 360.0f;
            }
        }
        return temp_f4;
    } else {
        return -1.0f;
    }
}

//if player should jump to next space
s32 func_800F9A68_10D688(s32 arg0) {
    Vec3f sp10;
    Player* curPlayer;
    Player* player;
    f32 var_f4;
    SpaceData* space;
    SpaceData* nextSpace;
    s32 var_s2;
    s32 var_s4;
    s32 i;
    Vec3f* temp;

    curPlayer = GetPlayerStruct(arg0);
    var_s2 = 0;
    var_s4 = 0;

    for (i = 0; i < 4; i++) {
        if (i == arg0) {
            continue;
        }
        player = GetPlayerStruct(i);
        if (curPlayer->cur_chain_index == player->cur_chain_index) {
            var_s4 += curPlayer->cur_space_index == player->cur_space_index;
        }
        if (curPlayer->next_chain_index == player->cur_chain_index) {
            var_s2 += curPlayer->next_space_index == player->cur_space_index;
        }        
    }

    s32 spaceIDCur = GetSpaceIndexFromChainAndSpace(curPlayer->cur_chain_index, curPlayer->cur_space_index);
    space = GetSpaceData(spaceIDCur);
    s32 spaceIDNext = GetSpaceIndexFromChainAndSpace(curPlayer->next_chain_index, curPlayer->next_space_index);
    nextSpace = GetSpaceData(spaceIDNext);
    HuVecSubtract(&sp10, &nextSpace->coords, &space->coords);
    var_f4 = func_800D8790_EC3B0(&sp10);

    if ((var_s4 == 0) || (!(D_80101D5C_11597C[var_s4].x < var_f4)) || (!(var_f4 <= D_80101D5C_11597C[var_s4].y))) {
        if (var_s2 != 0) {
            if (D_80101D84_1159A4[var_s2].x < 0.0f) {
                var_f4 -= 360.0f;
            }
            if (!(D_80101D84_1159A4[var_s2].x < var_f4) || (!(var_f4 <= D_80101D84_1159A4[var_s2].y))) {
                return 0;
            } else {
                return 1;
            }
        } else {
            return 0;
        }
    } else {
        return 1;
    }
}