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

//spawn 0
    //0x88, 0xBF

//spawn 1
    //0x48, 0xBF

//spawn 2
    //0xC8, 0xBE

//spawn 3
    //0xC8, 0xBD

//spawn 4
    //0xC8, 0xBB

//spawn 5
    //0xC8, 0xB7

//spawn 6
    //0xC8, 0xAF

//spawn 7
    //0xC8, 0x9F

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

u32 D_800D41C0 = 0; //cur spaces remaining to walk
s16 D_80102BC2 = 0; //TODO: tracks current player index a second time?
s16 D_80100D50_114970[] = {6, 7, 8, 9, 10, 11, 12, 13}; //unknown, extract from chilly waters
s32 func_800E4978_F8598(s32 playerIndex, s32 item);
s16 RunDecisionTree(DecisionTreeNonLeafNode* currentNode, s32 nodeTotal);

extern u32 rnd_seed;

//decision tree nodes for chilly waters first junction
DecisionTreeNonLeafNode ChillyWatersJunction0Nodes[] = {
    {
        .type = 0x02,
        .node_data1.data = 0x00000001,
        .node_data2.data = 0x1C96A846
    },
    {
        .type = 0x02,
        .node_data1.data = 0x00000042,
        .node_data2.data = 0x0C96A846
    },
    {
        .type = 0,
        .node_data1.data = 0x00,
        .node_data2.data = 0x064C9932
    }
};

void SetStarSpawnData(s32 index) {
    for (s32 i = 0; i < 4; i++) {
        gGameStatus.D_800CD0B6[i] = ChillyWatersStarSpawnFlags[index][i];
    }
}

int main(int arc, char* argv[]) {
    rnd_seed = 0x0000D9ED; //starting seed
    u32 rnd_seed_copy = rnd_seed;

    for (s32 i = 0; i < 8; i++) {
        SetStarSpawnData(i);
        s32 aiJunctionResult = RunDecisionTree(ChillyWatersJunction0Nodes, ARRAY_COUNT(ChillyWatersJunction0Nodes));
        printf(ANSI_CYAN "Ai Decision: %d\n\n" ANSI_RESET, aiJunctionResult);
        //rnd_seed_copy = rnd_seed_copy * 0x41C64E6D + 0x3039;
        rnd_seed = rnd_seed_copy;
    }

    // //SetStarSpawnData is very important for the ai decisions to work correctly!
    // s32 starSpawnIndex = 5;
    // SetStarSpawnData(starSpawnIndex);

    // rnd_seed = 0xB8C969DA;
    // s32 result = RunDecisionTree(ChillyWatersJunction0Nodes, ARRAY_COUNT(ChillyWatersJunction0Nodes));
    // printf("AI Decision: %ld, Seed: %08lX", result, rnd_seed & 0xFFFFFFFF);

    return EXIT_SUCCESS;
}