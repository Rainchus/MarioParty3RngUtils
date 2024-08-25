#include <stdio.h>
#include <stdlib.h>
#include "mp3.h"

u32 D_800D41C0 = 0; //cur spaces remaining to walk
s16 D_80102BC2 = 0; //TODO: tracks current player index a second time?
s32 func_800E4978_F8598(s32 playerIndex, s32 item);
s16 RunDecisionTree(DecisionTreeNonLeafNode* currentNode, s32 nodeTotal);

int aiMain(DecisionTreeNonLeafNode* node, s32 nodeCount) {
    return RunDecisionTree(node, nodeCount);
}