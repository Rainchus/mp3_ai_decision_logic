#include "mp3.h"
#include <stdio.h>

//TODO: set this value accordingly
u32 rnd_seed = 0;  //(at address 0x80097650)

s32 PlayerHasCoins(s32 index, s32 count) {
    Player* player = GetPlayerStruct(index);
    return player->coins >= count;
}

u8 rand8(void) {
    rnd_seed = rnd_seed * 0x41C64E6D + 0x3039;
    return (rnd_seed + 1) >> 16;
}

s16 RNGPercentChance(s8 percentChance) {
    u32 result;
    u32 randVal;

    printf(ANSI_CYAN "Probability: %d\n" ANSI_RESET, percentChance);
    randVal = rand8();
    result = (percentChance > ((randVal * 99) >> 8));
    printf(ANSI_CYAN "Rand: %ld\n" ANSI_RESET, randVal);
    printf(ANSI_CYAN "Outcome: %ld\n" ANSI_RESET, result);

    return result;
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

s32 IsFlagSet(s32 input) {
    s32 byteValue;
    s32 adjustedIndex;
    s32 byteIndex;
    s32 bitIndex;
    s32 mask;

    byteValue = gGameStatus.D_800CD0B6[input / 8];

    if (input >= 0) {
        adjustedIndex = input;
    } else {
        adjustedIndex = input + 7;
    }

    // Calculate the byte index (divide by 8)
    byteIndex = adjustedIndex >> 3;

    // Calculate the bit index
    bitIndex = input - (byteIndex << 3);

    mask = (1 << bitIndex);

    return byteValue & mask;
}

s16 func_800ECEE4_100B04(void) {
    return (gGameStatus.TotalTurns - gGameStatus.CurrentTurn) + 1;
}

// A heuristic "score" used for player placement calculations.
s32 func_800EECB0_1028D0(s32 playerIndex) {
    return (gPlayers[playerIndex].stars * 1000) + gPlayers[playerIndex].coins;
}

// calculates player placement
s32 CalcPlayerPlacement(s32 playerIndex) {
    s32 i;
    s32 placements[4];
    s32 placement;

    for (i = 0; i < 4; i++) {
        placements[i] = func_800EECB0_1028D0(i);
    }

    placement = 0;
    for (i = 0; i < 4; i++) {
        if (i != playerIndex) {
            placement += placements[playerIndex] < placements[i];
        }
    }

    return placement;
}

s32 func_800E4978_F8598(s32 playerIndex, s32 item) {
    s32 i;

    if (playerIndex == -1) {
        playerIndex = gGameStatus.curPlayerIndex;
    }

    for (i = 0; i < 3; i++) { 
        if (gPlayers[playerIndex].items[i] == item) {
            break;
        }
    }

    if (i == 3) {
        return -1;
    }
    return i;
}

//func_800DA190_EDDB0
s16 RunDecisionTree(DecisionTreeNonLeafNode* currentNode, s32 nodeTotal) {
    s32 var_v0_7;
    s16 temp_a1;
    u32 var_v0_2;
    u8 temp_s0;
    u8 temp_s2;
    u8 temp_s3;
    s16 spaceIndex;
    Player* player;
    s32 i;
    DecisionTreeNonLeafNode* var_s1 = currentNode;
    s32 temp;
    u32 temp2;
    s32 nodeDepth = 0;
    
    for (;;var_s1++, nodeDepth++) {
        if (nodeDepth >= nodeTotal) {
            printf(ANSI_RED "Error: tried to access a node not in bounds of array\n" ANSI_RESET);
            return -1;
        }
        printf("Parsing Node:\n");
        printf(" Type: %d\n node_data1 0x%08lX\n node_data2 0x%08lX\n", var_s1->type, var_s1->node_data1.data, var_s1->node_data2.data);
        switch (var_s1->type) {                              /* switch 1 */
        case 1:                                         /* switch 1 */
            if (PlayerHasCoins(-1, var_s1->node_data1.data) != 0) {
                break;
            }
            continue;
        case 2:
            for (i = 0; i < 8; i++) {
                if (!((1 << i) & var_s1->node_data1.data)) {
                    continue;
                }
                if (gGameStatus.boardIndex == 2) {
                    if ((gGameStatus.D_800CD096_s16[2][0] >> gGameStatus.curPlayerIndex) & 1) {
                        if (IsFlagSet(0x12) == 0) {
                            if (i == gGameStatus.D_800CD096_s16[0][0]) {
                                break;
                            } else {
                                continue;
                            }
                        }
                    }
                }
                if (!IsFlagSet(D_80100D50_114970[i])) {
                    break;
                }
            }
            if (i == 8) {
                continue;
            }
            break;
        case 3:                                         /* switch 1 */
            if ((2 << (D_800D41C0 - 1)) & var_s1->node_data1.data) {
                break;
            }
            continue;
        case 4:                                         /* switch 1 */
            var_v0_2 = (var_s1->node_data1.data >> 0x14) & 0xFF;
            temp_a1 = var_s1->node_data1.data_u16[1];
            switch ((var_s1->node_data1.data >> 0x10) & 0xF) {                          /* switch 2 */
            case 0:                                     /* switch 2 */
                if (gGameStatus.D_800CD096_s16[var_v0_2][0] == temp_a1) {
                    break;
                }
                continue;
            case 1:                                     /* switch 2 */
                if (gGameStatus.D_800CD096_s16[var_v0_2][0] != temp_a1) {
                    break;
                }
                continue;
            case 2:                                     /* switch 2 */
                if (gGameStatus.D_800CD096_s16[var_v0_2][0] < temp_a1) {
                    break;
                }
                continue;
            case 3:                                     /* switch 2 */
                if (gGameStatus.D_800CD096_s16[var_v0_2][0] <= temp_a1) {
                    break;
                }
                continue;
            case 4:                                     /* switch 2 */
                if (gGameStatus.D_800CD096_s16[var_v0_2][0] > temp_a1) {
                    break;
                }
                continue;
            case 5:                                     /* switch 2 */
                if (gGameStatus.D_800CD096_s16[var_v0_2][0] >= temp_a1) {
                    break;
                }
                continue;
            }
            break;
        case 0:
            break;
        case 5:                                         /* switch 1 */
            if ((2 << (CalcPlayerPlacement(GetCurrentPlayerIndex()))) & var_s1->node_data1.data) {
                break;
            }
            continue;
        case 6:                                         /* switch 1 */
            if (var_s1->node_data1.func() != 0) {
                break;
            }
            continue;
        case 7: //TODO: fix tail merge with case 9     /* switch 1 */
            temp = func_800ECEE4_100B04();
            temp2 = var_s1->node_data1.signed_data;
            goto label_0;
        case 8:                                         /* switch 1 */
            if (func_800E4978_F8598(gGameStatus.curPlayerIndex, var_s1->node_data1.data) != -1) {
                break;
            }
            continue;
        case 9:                                         /* switch 1 */
            temp2 = var_s1->node_data1.signed_data;
            temp = D_800D41C0;
            
            label_0:
            if ((temp2 > temp) == 0) {
                break;
            }
            continue;
        case 10:                                        /* switch 1 */
            temp_s0 = var_s1->node_data1.data_u8[1];
            temp_s2 = var_s1->node_data1.data_u8[2];
            temp_s3 = var_s1->node_data1.data_u8[3];
            player = GetPlayerStruct(-1);
            if (player->cur_chain_index != temp_s0) {
                continue;
            }
            spaceIndex = player->cur_space_index;
            if (spaceIndex < temp_s2) {
                continue;
            }
            if (temp_s3 < spaceIndex) {
                continue;
            }
            break;
        case 11:                                        /* switch 1 */
            temp_s0 = var_s1->node_data1.data_u8[1];
            temp_s2 = var_s1->node_data1.data_u8[2];
            temp_s3 = var_s1->node_data1.data_u8[3];
            for (i = 0; i < 4; i++) {
                if (i == GetCurrentPlayerIndex()) {
                    continue;
                }
                player = GetPlayerStruct(i);
                if (player->cur_chain_index != temp_s0) {
                    continue;
                }
                spaceIndex = player->cur_space_index;
                if (spaceIndex < temp_s2) {
                    continue;
                }
                if (temp_s3 < spaceIndex) {
                    continue;
                }
                break;
            }
            if (i >= 4) {
                continue;
            }
            /* fallthrough? */
        case 12:                                        /* switch 1 */
            if (PlayerHasCoins(-1, var_s1->node_data1.data) == 0) {
                break;
            }
            continue;
        case 13:                                        /* switch 1 */
            if ((gPlayers[GetCurrentPlayerIndex()].character != var_s1->node_data1.data) == 0) {
                break;
            }
            continue;
        case 14:                                        /* switch 1 */
            temp_s0 = var_s1->node_data1.data_u8[1];
            temp_s2 = var_s1->node_data1.data_u8[2];
            temp_s3 = var_s1->node_data1.data_u8[3];
            player = GetPlayerStruct(var_s1->node_data1.data_u8[0]);
            if (player->cur_chain_index != temp_s0) {
                continue;
            }
            spaceIndex = player->cur_space_index;
            if (spaceIndex < temp_s2) {
                continue;
            }
            if (temp_s3 < spaceIndex) {
                continue;
            }
            break;
        case 15:
            temp_s0 = var_s1->node_data1.data_u8[1];
            temp_s2 = var_s1->node_data1.data_u8[2];
            temp_s3 = var_s1->node_data1.data_u8[3];
            player = GetPlayerStruct(D_80102BC2);
            if (player->cur_chain_index != temp_s0) {
                continue;
            }
            spaceIndex = player->cur_space_index;
            if (spaceIndex < temp_s2) {
                continue;
            }
            if (temp_s3 < spaceIndex) { 
                continue;
            }
            break;
        case 16:                                        /* switch 1 */
            for (i = 0; i < 4; i++) {
                if (GetCurrentPlayerIndex() != i && PlayerHasCoins(i, var_s1->node_data1.data) != 0) {
                    break;
                }
            }
            continue;
        }
        if ((s32)var_s1->node_data2.node_data < 0) {
            var_s1 = (DecisionTreeNonLeafNode*)(var_s1->node_data2.node_data - 1);
            continue;
        }
        switch (GetPlayerStruct(-1)->cpu_difficulty) {
            case 0:
                var_v0_7 = var_s1->node_data2.data_u8[3] & 0x7F;
                break;
            case 1:
                var_v0_7 = (var_s1->node_data2.data >> 7) & 0x7F;
                break;
            case 2:
                var_v0_7 = (var_s1->node_data2.data >> 0xE) & 0x7F;
                break;
            case 3:
                var_v0_7 = (var_s1->node_data2.data >> 0x15) & 0x7F;
                break;
            default:
                var_v0_7 = 0;
                break;
        }
        //TODO: fix hack here with the s16 cast
        // printf("Value passed to RNGPercentChance is %08X\n", var_v0_7);
        int rngResult = RNGPercentChance(var_v0_7);
        printf("Result %d, Node Data: %08lX\n", rngResult, var_s1->node_data2.data);
        if (rngResult != 0) {
            return (var_s1->node_data2.data >> 0x1C) & 1;
        } else {
            return ((var_s1->node_data2.data >> 0x1C) ^ 1) & 1;
        }
    }
}