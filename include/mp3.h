#ifndef _MP3_H
#define _MP3_H

#include <stdint.h>
#include "ansi_colors.h"

#define FALSE 0
#define TRUE 1

#define SET_CURRENT 0
#define SET_NEXT 1

typedef uint32_t u32;
typedef long s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;
typedef s32 func_ptr(void);

#define ARRAY_COUNT(arr) (sizeof(arr) / sizeof(arr[0]))
#define ADV_SEED(seed) seed = (seed * 0x41C64E6D + 0x3039)
#define CHILLY_WATERS 0
#define DEEP_BLOOPER_SEA 1
#define SPINY_DESERT 2
#define WOODY_WOODS 3
#define CREEPY_CAVERN 4
#define WALUIGIS_ISLAND 5

#define NORMAL_RETURN -1
#define BAD_JUNCTION_RESULT -2

enum Items {
    ITEM_MUSHROOM = 0,
    ITEM_SKELETON_KEY = 1,
    ITEM_POISON_MUSHROOM = 2,
    ITEM_REVERSE_MUSHROOM = 3,
    ITEM_CELLULAR_SHOPPER = 4,
    ITEM_WARP_BLOCK = 5,
    ITEM_PLUNDER_CHEST = 6,
    ITEM_BOWSER_PHONE = 7,
    ITEM_DUELING_GLOVE = 8,
    ITEM_LUCKY_LAMP = 9,
    ITEM_GOLDEN_MUSHROOM = 10,
    ITEM_BOO_BELL = 11,
    ITEM_BOO_REPELLANT = 12,
    ITEM_BOWSER_SUIT = 13,
    ITEM_MAGIC_LAMP = 14,
    ITEM_KOOPA_KARD = 15,
    ITEM_BARTER_BOX = 16,
    ITEM_LUCKY_CHARM = 17,
    ITEM_WACKY_WATCH = 18,
};

enum {
    SPACE_BLUE = 1,
    SPACE_RED = 2,
    SPACE_INVISIBLE = 3,
    SPACE_HAPPENING = 4,
    SPACE_CHANCE_TIME = 5,
    SPACE_ITEM = 6,
    SPACE_BANK = 7,
    SPACE_UNK_8 = 8,
    SPACE_BATTLE = 9,
    SPACE_UNK_A = 10,
    SPACE_UNK_B = 11,
    SPACE_BOWSER = 12,
    SPACE_SHOP = 13,
    SPACE_STAR = 14,
};

enum Partners {
    PARTNER_KOOPA = 0,
    PARTNER_GOOMBA = 1,
    PARTNER_TOAD = 2,
    PARTNER_BOB_OMB = 3,
    PARTNER_BOO = 4,
    PARTNER_WHOMP = 5,
    PARTNER_SNIFIT = 6,
    PARTNER_PIRANHA_PLANT = 7,
    PARTNER_CHOMP = 8,
    PARTNER_THWOMP = 9,
    PARTNER_MR_BLIZZARD = 10,
    PARTNER_BABY_BOWSER = 11,
};

typedef struct SpaceChain {
    s16 amountOfSpaces;
    s16* spaceChainArray;
} SpaceChain;

typedef struct Vec2f {
    f32 x;
    f32 y;
} Vec2f;

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct SpaceData {
/* 0x00 */ s8 unk_00;
/* 0x01 */ u8 space_type; // enum board_space_type
/* 0x02 */ s16 unk_02;
/* 0x04 */ s32 unk_04;
/* 0x08 */ Vec3f coords;
/* 0x14 */ Vec3f rot;
// /* 0x20 */ void* event_list;
/* 0x20 */ s32 (*eventFunction)(void*);
//Custom struct members
/* 0x24 */ void* functionData; //usually next space to go to
} SpaceData; //sizeof 0x28 for custom struct (normal struct size is 0x24)

typedef struct Blocks {
    s16 coinBlockSpaceIndex;
    s16 starBlockSpaceIndex;
    s16 itemBlockSpaceIndex;
} Blocks;

typedef struct DecisionTreeNonLeafNode {
    u32 type;
    union {
        s32 (*func) ();
        u32 data;
        s32 signed_data;
        u16 data_u16[2];
        u8 data_u8[4];
        s8 data_s8[4];
    } node_data1;
    union {
        u32 data;
        struct DecisionTreeNonLeafNode *node_data;
        u8 data_u8[4];
    } node_data2;
    u32 isPointer;
} DecisionTreeNonLeafNode;



//starts at 0x800CD058
typedef struct GameStatus { //TODO: type correctly
/* 0x00 - 800CD058 */ s8 unk0;
/* 0x01 - 800CD059 */ s8 boardIndex;
/* 0x02 - 800CD05A */ s8 TotalTurns;
/* 0x03 - 800CD05B */ s8 CurrentTurn;
/* 0x04 - 800CD05C */ s8 curGameLength;
/* 0x05 - 800CD05D */ u8 curStarSpawnIndex;
/* 0x06 - 800CD05E */ u8 starSpawnIndicies[8];
/* 0x0E - 800CD066 */ u8 unkE;
/* 0x0F - 800CD067 */ s8 curPlayerIndex;
    union {
    /* 0x10 - 800CD068 */ s16 unkArray_s16[23]; //unk size
    /* 0x10 - 800CD068 */ s8 unkArray_s8[46]; //unk size
    } unkData;
    /* 800CD096 */ s16 D_800CD096_s16[16][1];
    /* 800CD0B6 */ u8 D_800CD0B6[4]; //no idea how long this is
} GameStatus;

extern GameStatus gGameStatus;

typedef struct Player {
    /*  0 (0x00) 800D1108 */ s8 team;
    /*  1 (0x01) 800D1109 */ u8 cpu_difficulty;
    /*  2 (0x02) 800D110A */ u8 controller;
    /*  3 (0x03) 800D110B */ u8 character;
    /**
     * Player flags.
     * 1: Is CPU player
     * 4: ?
     */
    /*  4 (0x04) 800D110C */ u8 flags;
    s8 pad5[1];
    /** Coins collected in a mini-game. */
    /*  6 (0x06) 800D110E */ s16 bonus_coins;
    /** Coins from mini-game wins. */
    /*  8 (0x08) 800D1110 */ s16 coins_won;
    /** Current coin count. */
    /* 10 (0x0A) 800D1112 */ s16 coins;
    /** Coins obtained during a Mini-Game. */
    /* 12 (0x0C) 800D1114 */ s16 minigame_coins;
    /* 14 (0x0E) 800D1116 */ s8 stars;

    /* 15 (0x0F) 800D1117 */ s8 cur_chain_index;
    /* 16 (0x10) 800D1118 */ u8 cur_space_index;
    /* 17 (0x11) 800D1119 */ u8 next_chain_index;
    /* 18 (0x12) 800D111A */ u8 next_space_index;
    /* 19 (0x13) 800D111B */ u8 unk1_chain_index;
    /* 20 (0x14) 800D111C */ u8 unk1_space_index;
    /* 21 (0x15) 800D111D */ s8 reverse_chain_index;
    /* 22 (0x16) 800D111E */ s8 reverse_space_index;

    /**
     * Movement flags.
     * 1: Is moving in reverse.
     */
    /* 23 (0x17) 800D111F */ u8 flags2;
    /* 24 (0x18) 800D1120 */ s8 items[3];
    /* 27 (0x1B) 800D1123 */ s8 bowser_suit_flag;
    /* 28 (0x1C) 800D1124 */ u8 turn_color_status;
    /* 29 (0x1D) 800D1125 */ s8 unk1D;

    s8 unks1E1F[2]; // 20 - 31

    // /* 32 (0x20) 800D1128 */ struct process *process;
    /* 32 (0x20) 800D1128 */ void* process;
    // /* 36 (0x24) 800D112C */ struct object *obj;
    /* 36 (0x24) 800D112C */ void* obj;
    /* 40 (0x28) 800D1130 */ s16 minigame_star;
    /* 42 (0x2A) 800D1132 */ s16 max_coins;
    /* 44 (0x2C) 800D1134 */ s8 happening_space_count;
    s8 red_space_count;
    s8 blue_space_count;
    s8 chance_space_count;
    /* 48 (0x30) 800D1138 */ s8 bowser_space_count;
    s8 battle_space_count;
    s8 item_space_count;
    s8 bank_space_count;
    /* 52 (0x34) 800D113C */ s8 game_guy_space_count;
    s8 unk35;

    // s8 pad2[3];
} Player; // sizeof == 56 | 0x38

//used for save data
typedef struct PackedPlayer {
    u8 cur_chain_index;
    u8 cur_space_index;

    u8 next_chain_index;
    u8 next_space_index;

    //we dont get the reverse chain info, so using a reverse mushroom the first turn after loading in
    //from a reset will yield unpredictable results

} PackedPlayer;

s16 RNGPercentChance(s8);
s16 func_800ECEE4_100B04(void);
s32 CalcPlayerPlacement(s32);
s16 GetCurrentPlayerIndex(void);
s16 GetTurnsElapsed(void);
s32 IsFlagSet(s32);
s32 func_8004FEBC(s16);
s32 PlayerHasCoins(s32 playerIndex, s32 coinAmount);
Player* GetPlayerStruct(s32);
u32 GetChainAndSpaceFromAbsSpace(s32 space);;
u8 RollDice(void);
u8 rollDice2(void);
s32 func_800EEF80_102BA0(f32 arg0);
u32 MeasureRngCalls(u32 seedStart, u32 seedEnd);
SpaceData* GetSpaceData(s16 arg0);
void PlaceHiddenBlocksMain(Blocks* blocks, s32 numOfSpaces);
s16 func_800EBCD4_FF8F4(u8 arg0, s32 numOfBoardSpaces);
s32 IsFlagSet(s32 input);
void hidden_block_gen_main(int starSpace, int curSpaceID, int nextSpaceID, int endSpaceID, int board, int wantedRoll);
void CPUGetWatchGeneric(s32 rollValue, u32 numOfJumps);
int aiMain(DecisionTreeNonLeafNode* node, s32 nodeCount);

extern Player gPlayers[4]; //0x800D1108 on US, 0x800C68E0 on JP
extern s16 D_80102BC2;
extern s16 D_800ED154[];
extern s32 D_800F3FF0;
extern u32 D_800D41C0; //spaces left to move
extern SpaceData* spacesForBoards[];
extern u32 cur_rng_seed;
extern u32 rng_seeds_by_index[];
extern s16* HiddenBlockSpacesBlacklist[6];
#define ENABLE_LOG
#ifdef ENABLE_LOG
    #define LOG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
    #define LOG(fmt, ...) // Empty macro when logging is disabled
#endif

#endif