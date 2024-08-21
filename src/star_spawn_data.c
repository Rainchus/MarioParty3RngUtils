#include <stdio.h>
#include <stdlib.h>
#include "mp3.h"

#define CHILLY_WATERS 0


//these spawn indicies are arbitrary based on the order i got when getting this data
/* https://cdn.discordapp.com/attachments/450961364362592262/1273882797727285258/Screenshot_1.png?ex=66c03b4e&is=66bee9ce&hm=3ea26677a384fbf0a355a173d45db0f4f8b676f1ae27c9231193bcf619828130& */

u8 ChillyWatersStarSpawn0[] = {0x88, 0xBF, 0x00, 0x00};
u8 ChillyWatersStarSpawn1[] = {0x48, 0xBF, 0x00, 0x00};
u8 ChillyWatersStarSpawn2[] = {0xC8, 0xBE, 0x00, 0x00};
u8 ChillyWatersStarSpawn3[] = {0xC8, 0xBD, 0x00, 0x00};
u8 ChillyWatersStarSpawn4[] = {0xC8, 0xBB, 0x00, 0x00};
u8 ChillyWatersStarSpawn5[] = {0xC8, 0xB7, 0x00, 0x00};
u8 ChillyWatersStarSpawn6[] = {0xC8, 0xAF, 0x00, 0x00};
u8 ChillyWatersStarSpawn7[] = {0xC8, 0x9F, 0x00, 0x00};

u8* ChillyWatersStarSpawnFlags[] = {
    ChillyWatersStarSpawn0,
    ChillyWatersStarSpawn1,
    ChillyWatersStarSpawn2,
    ChillyWatersStarSpawn3,
    ChillyWatersStarSpawn4,
    ChillyWatersStarSpawn5,
    ChillyWatersStarSpawn6,
    ChillyWatersStarSpawn7
};


u8 DeepBlooperSeaStarSpawn0[] = {0x89, 0xBF, 0x00, 0x00};
u8 DeepBlooperSeaStarSpawn1[] = {0x49, 0xBF, 0x00, 0x00};
u8 DeepBlooperSeaStarSpawn2[] = {0xC9, 0xBE, 0x00, 0x00};
u8 DeepBlooperSeaStarSpawn3[] = {0xC9, 0xAF, 0x00, 0x00};
u8 DeepBlooperSeaStarSpawn4[] = {0xC9, 0xBD, 0x00, 0x00};
u8 DeepBlooperSeaStarSpawn5[] = {0xC9, 0x9F, 0x00, 0x00};
u8 DeepBlooperSeaStarSpawn6[] = {0xC9, 0xBB, 0x00, 0x00};
u8 DeepBlooperSeaStarSpawn7[] = {0xC9, 0xB7, 0x00, 0x00};

u8* DeepBlooperSeaStarSpawnFlags[] = {
    DeepBlooperSeaStarSpawn0,
    DeepBlooperSeaStarSpawn1,
    DeepBlooperSeaStarSpawn2,
    DeepBlooperSeaStarSpawn3,
    DeepBlooperSeaStarSpawn4,
    DeepBlooperSeaStarSpawn5,
    DeepBlooperSeaStarSpawn6,
    DeepBlooperSeaStarSpawn7
};


u8 WoodyWoodsStarSpawn0[] = {0xC9, 0xBB, 0x00, 0x00};
u8 WoodyWoodsStarSpawn1[] = {0xC9, 0xB7, 0x00, 0x00};
u8 WoodyWoodsStarSpawn2[] = {0xC9, 0xBD, 0x00, 0x00};
u8 WoodyWoodsStarSpawn3[] = {0xC9, 0x9F, 0x00, 0x00};
u8 WoodyWoodsStarSpawn4[] = {0x89, 0xBF, 0x00, 0x00};
u8 WoodyWoodsStarSpawn5[] = {0x49, 0xBF, 0x00, 0x00};
u8 WoodyWoodsStarSpawn6[] = {0xC9, 0xBE, 0x00, 0x00};
u8 WoodyWoodsStarSpawn7[] = {0xC9, 0xAF, 0x00, 0x00};

u8* WoodyWoodsStarSpawnFlags[] = {
    WoodyWoodsStarSpawn0,
    WoodyWoodsStarSpawn1,
    WoodyWoodsStarSpawn2,
    WoodyWoodsStarSpawn3,
    WoodyWoodsStarSpawn4,
    WoodyWoodsStarSpawn5,
    WoodyWoodsStarSpawn6,
    WoodyWoodsStarSpawn7
};


u8 CreepyCavernStarSpawn0[] = {0xC9, 0xBD, 0x00, 0x00};
u8 CreepyCavernStarSpawn1[] = {0xC9, 0xBB, 0x00, 0x00};
u8 CreepyCavernStarSpawn2[] = {0xC9, 0xBE, 0x00, 0x00};
u8 CreepyCavernStarSpawn3[] = {0xC9, 0x9F, 0x00, 0x00};
u8 CreepyCavernStarSpawn4[] = {0xC9, 0xB7, 0x00, 0x00};
u8 CreepyCavernStarSpawn5[] = {0x89, 0xBF, 0x00, 0x00};
u8 CreepyCavernStarSpawn6[] = {0x49, 0xBF, 0x00, 0x00};
u8 CreepyCavernStarSpawn7[] = {0xC9, 0xAF, 0x00, 0x00};

u8* CreepyCavernStarSpawnFlags[] = {
    CreepyCavernStarSpawn0,
    CreepyCavernStarSpawn1,
    CreepyCavernStarSpawn2,
    CreepyCavernStarSpawn3,
    CreepyCavernStarSpawn4,
    CreepyCavernStarSpawn5,
    CreepyCavernStarSpawn6,
    CreepyCavernStarSpawn7
};