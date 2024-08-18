#include "mp3.h"

// #include "board_space_data/chilly_waters_spaces.c"
// #include "board_space_data/deep_blooper_sea_spaces.c"
// #include "board_space_data/spiny_desert_spaces.c"
// #include "board_space_data/woody_woods_spaces.c"
// #include "board_space_data/creepy_cavern_spaces.c"
// #include "board_space_data/waluigis_island_spaces.c"

extern SpaceData chilly_waters_spaces[];
extern SpaceData deep_blooper_sea_spaces[];
extern SpaceData spiny_desert_spaces[];
extern SpaceData woody_woods_spaces[];
extern SpaceData creepy_cavern_spaces[];
extern SpaceData waluigis_island_spaces[];

SpaceData* spacesForBoards[] = {
    chilly_waters_spaces,
    deep_blooper_sea_spaces,
    spiny_desert_spaces,
    woody_woods_spaces,
    creepy_cavern_spaces,
    waluigis_island_spaces
};