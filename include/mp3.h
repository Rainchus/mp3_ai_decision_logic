#ifndef _MP3_H
#define _MP3_H

#define ARRAY_COUNT(arr) (sizeof(arr) / sizeof(arr[0]))

#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"
#define ANSI_BLUE "\x1b[34m"

#define ANSI_BLACK "\x1b[30m"
#define ANSI_RED "\x1b[31m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN "\x1b[36m"
#define ANSI_WHITE "\x1b[37m"

typedef unsigned long u32;
typedef long s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;

typedef struct DecisionTreeNonLeafNode {
    u8 type;
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
        s32 *node_data;
        u8 data_u8[4];
    } node_data2;
} DecisionTreeNonLeafNode;

typedef s32 func_ptr(void);


///////////////////////////////////////////
s16 GetTurnsElapsed(void);
s32 IsFlagSet(s32);
s16 RNGPercentChance(s8);
s32 func_8004FEBC(s16);
extern s16 D_800ED154[];
extern s32 D_800F3FF0;
extern s16 D_80100D50_114970[8];
extern u32 D_800D41C0;

// extern s16 D_800CD096[][1];
// extern s8 gCurrentPlayerIndex;

//starts at 0x800CD058
typedef struct GameStatus { //TODO: type correctly
/* 0x00 - 800CD058 */ s8 unk0;
/* 0x01 - 800CD059 */ s8 boardIndex;
/* 0x02 - 800CD05A */ s8 TotalTurns;
/* 0x03 - 800CD05B */ s8 CurrentTurn;
/* 0x04 - 800CD05C */ s8 curGameLength;
/* 0x05 - 800CD05D */ u8 curStarSpawnIndex;
/* 0x06 - 800CD05E */ u8 starSpawnIndicies[8];
// /* 0x07 - 800CD05F */ u8 unk7;
// /* 0x08 - 800CD060 */ u8 unk8;
// /* 0x09 - 800CD061 */ u8 unk9;
// /* 0x0A - 800CD062 */ u8 unkA;
// /* 0x0B - 800CD063 */ u8 unkB;
// /* 0x0C - 800CD064 */ u8 unkC;
// /* 0x0D - 800CD065 */ u8 unkD;
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

s32 func_80035F98_36B98(s16);
s16 RNGPercentChance(s8);
s16 func_800ECEE4_100B04(void);
s32 CalcPlayerPlacement(s32);
s16 GetCurrentPlayerIndex(void);

s32 PlayerHasCoins(s32 playerIndex, s32 coinAmount);
extern Player gPlayers[4];
extern s16 D_80102BC2;
Player* GetPlayerStruct(s32);

#define CHILLY_WATERS 0
#define DEEP_BLOOPER_SEA 1
#define SPINY_DESERT 2
#define WOODY_WOODS 3
#define CREEPY_CAVERN 4
#define WALUIGIS_ISLAND 5

#endif