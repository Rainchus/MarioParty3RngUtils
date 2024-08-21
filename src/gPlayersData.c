#include <stdio.h>
#include <stdlib.h>
#include "mp3.h"

#define EASY 0
#define NORMAL 1
#define HARD 2
#define VERY_HARD 3

Player gPlayers[4] = {
    //p1
    {
        .team = 0,
        .cpu_difficulty = NORMAL,
        .controller = 0,
        .character = 0,
        .flags = 0x5, //cpu player
        .bonus_coins = 0,
        .coins_won = 0,
        .coins = 10,
        .minigame_coins = 0,
        .stars = 0,
        .cur_chain_index = 0,
        .cur_space_index = 0,
        .next_chain_index = 0,
        .next_space_index = 0,
        .unk1_chain_index = 0,
        .unk1_space_index = 0,
        .reverse_chain_index = 0,
        .reverse_space_index = 0,
        .flags2 = 0,
        .items = {-1, -1, -1},
        .bowser_suit_flag = 0,
        .turn_color_status = 0,
        .unk1D = 0,
        .unks1E1F = {0, 0},
        .process = 0,
        // /* 36 (0x24) 800D112C */ struct object *obj;
        .obj = 0,
        .minigame_star = 0,
        .max_coins = 10,
        .happening_space_count = 0,
        .red_space_count = 0,
        .blue_space_count = 0,
        .chance_space_count = 0,
        .bowser_space_count = 0,
        .battle_space_count = 0,
        .item_space_count = 0,
        .bank_space_count = 0,
        .game_guy_space_count = 0,
        .unk35 = 0,
    },
    //p2
    {
        .team = 0,
        .cpu_difficulty = NORMAL,
        .controller = 0,
        .character = 0,
        .flags = 0x5, //cpu player
        .bonus_coins = 0,
        .coins_won = 0,
        .coins = 10,
        .minigame_coins = 0,
        .stars = 0,
        .cur_chain_index = 0,
        .cur_space_index = 0,
        .next_chain_index = 0,
        .next_space_index = 0,
        .unk1_chain_index = 0,
        .unk1_space_index = 0,
        .reverse_chain_index = 0,
        .reverse_space_index = 0,
        .flags2 = 0,
        .items = {-1, -1, -1},
        .bowser_suit_flag = 0,
        .turn_color_status = 0,
        .unk1D = 0,
        .unks1E1F = {0, 0},
        .process = 0,
        // /* 36 (0x24) 800D112C */ struct object *obj;
        .obj = 0,
        .minigame_star = 0,
        .max_coins = 10,
        .happening_space_count = 0,
        .red_space_count = 0,
        .blue_space_count = 0,
        .chance_space_count = 0,
        .bowser_space_count = 0,
        .battle_space_count = 0,
        .item_space_count = 0,
        .bank_space_count = 0,
        .game_guy_space_count = 0,
        .unk35 = 0,
    },
    //p3
        {
        .team = 0,
        .cpu_difficulty = NORMAL,
        .controller = 0,
        .character = 0,
        .flags = 0x5, //cpu player
        .bonus_coins = 0,
        .coins_won = 0,
        .coins = 10,
        .minigame_coins = 0,
        .stars = 0,
        .cur_chain_index = 0,
        .cur_space_index = 0,
        .next_chain_index = 0,
        .next_space_index = 0,
        .unk1_chain_index = 0,
        .unk1_space_index = 0,
        .reverse_chain_index = 0,
        .reverse_space_index = 0,
        .flags2 = 0,
        .items = {-1, -1, -1},
        .bowser_suit_flag = 0,
        .turn_color_status = 0,
        .unk1D = 0,
        .unks1E1F = {0, 0},
        .process = 0,
        // /* 36 (0x24) 800D112C */ struct object *obj;
        .obj = 0,
        .minigame_star = 0,
        .max_coins = 10,
        .happening_space_count = 0,
        .red_space_count = 0,
        .blue_space_count = 0,
        .chance_space_count = 0,
        .bowser_space_count = 0,
        .battle_space_count = 0,
        .item_space_count = 0,
        .bank_space_count = 0,
        .game_guy_space_count = 0,
        .unk35 = 0,
    },
    //p4
        {
        .team = 0,
        .cpu_difficulty = NORMAL,
        .controller = 0,
        .character = 0,
        .flags = 0x5, //cpu player
        .bonus_coins = 0,
        .coins_won = 0,
        .coins = 10,
        .minigame_coins = 0,
        .stars = 0,
        .cur_chain_index = 0,
        .cur_space_index = 0,
        .next_chain_index = 0,
        .next_space_index = 0,
        .unk1_chain_index = 0,
        .unk1_space_index = 0,
        .reverse_chain_index = 0,
        .reverse_space_index = 0,
        .flags2 = 0,
        .items = {-1, -1, -1},
        .bowser_suit_flag = 0,
        .turn_color_status = 0,
        .unk1D = 0,
        .unks1E1F = {0, 0},
        .process = 0,
        // /* 36 (0x24) 800D112C */ struct object *obj;
        .obj = 0,
        .minigame_star = 0,
        .max_coins = 10,
        .happening_space_count = 0,
        .red_space_count = 0,
        .blue_space_count = 0,
        .chance_space_count = 0,
        .bowser_space_count = 0,
        .battle_space_count = 0,
        .item_space_count = 0,
        .bank_space_count = 0,
        .game_guy_space_count = 0,
        .unk35 = 0,
    },
};