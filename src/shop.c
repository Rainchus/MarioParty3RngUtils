#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"
#include "util.h"

//8011DE30
DecisionTreeNonLeafNode ShopDecisionNode2[] = {
};

//8011DE48
DecisionTreeNonLeafNode ShopDecisionNode1[] = {
    {
        .type = 0x09000000,
        .node_data1.data = 0x00000002,
        .node_data2.node_data = ShopDecisionNode2, //0x8011DE30
        .isPointer = 0,
    },
};

//8011DE84
DecisionTreeNonLeafNode ShopDecisionNode[] = {
    {
        .type = 0x02000000,
        .node_data1.data = 0x00000001,
        .node_data2.node_data = ShopDecisionNode1, //0x8011DE48,
        .isPointer = 0,
    },
    {
        .type = 0x00000001,
        .node_data1.data = 0x00000019,
        .node_data2.data = 0x0C96A846, //
        .isPointer = 0,
    },
    {
        .type = 0x00000000,
        .node_data1.data = 0x00000000,
        .node_data2.data = 0x0B54233C, //
        .isPointer = 0,
    },
};