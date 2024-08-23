#include "mp3.h"

//decision tree nodes for chilly waters first junction
DecisionTreeNonLeafNode ChillyWatersJunction0Nodes[3] = {
    {
        .type = 0x02,
        .node_data1.data = 0x00000001,
        .node_data2.data = 0x1C96A846,
        .isPointer = 0,
    },
    {
        .type = 0x02,
        .node_data1.data = 0x00000042,
        .node_data2.data = 0x0C96A846,
        .isPointer = 0,
    },
    {
        .type = 0,
        .node_data1.data = 0x00,
        .node_data2.data = 0x064C9932,
        .isPointer = 0,
    }
};