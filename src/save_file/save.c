#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"
#include "util.h"

//WIP create a custom save file

s32 D_800BBAA0 = 0;
s32 D_800BBAA4 = 0;

u8 D_800CD0C0[220]; //

void func_8004F83C_5043C(s32 arg0) {
    D_800CD0C0[D_800BBAA0] *= 2;
    D_800CD0C0[D_800BBAA0] |= arg0 ? 1 : 0;
    
    if (++D_800BBAA4 >= 8) {
        D_800BBAA0++;
        D_800BBAA4 = 0;
    }
}

//SaveFileEncode
s32 func_8004F5A4(u8* arg0, u8* arg1) {
    s16 temp_s4;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v1_2;
    s32 temp_v0_3;
    u8 temp_a0;
    u8 temp_v1;
    u8* temp_a1;
    u8* temp_s2;
    u8* temp_s2_2;
    s32 phi_s0;
    s16 phi_v1_2;
    u8* phi_s2_2;
    s16 i, j, k, l;

    for (l = 0; l < 220; l++) {
        D_800CD0C0[l] = 0;
    }

    D_800BBAA4 = 0;
    D_800BBAA0 = 0;

    while (*arg1 != 0) {
        for (phi_s2_2 = &arg0[arg1[2]], i = 0; i < arg1[1]; i++) {
            if (arg1[0] >= 0x11U) {
                for (j = 0; j < (arg1[0] >> 3); j++, phi_s2_2++) {
                    phi_s0 = *phi_s2_2;
                    for (k = 0; k < 8; k++, phi_s0 *= 2) {
                        func_8004F83C_5043C(phi_s0 & 0x80);
                    }
                }
                continue;
            } else {
                if (arg1[0] >= 9U) {
                    phi_s0 = *phi_s2_2 << (0x10 - arg1[0]);
                    phi_v1_2 = arg1[0] - 8;
                    for (k = 0; k < phi_v1_2; k++, phi_s0 *=2) {
                        func_8004F83C_5043C(phi_s0 & 0x80);
                    }
                    phi_s2_2++;
                    phi_s0 = *phi_s2_2;
                    phi_v1_2 = 8;
                } else {
                    phi_s0 = *phi_s2_2 << (8 - arg1[0]);
                    phi_v1_2 = arg1[0];
                }
                for (k = 0; k < phi_v1_2; k++, phi_s0 *= 2) {
                    func_8004F83C_5043C(phi_s0 & 0x80);
                }     
            }
            phi_s2_2++;
        }
        arg1 += 3;
        if (arg1[0] == 0) {
            break;
        }
    }
    

    D_800CD0C0[D_800BBAA0] <<= 8 - D_800BBAA4;
    if (D_800BBAA4 == 0) {
        D_800BBAA0--;
    }
    if (D_800BBAA0 >= 0xDD) {
        //osSyncPrintf("SaveCompBuffer Max Over!\n");
    }
    return D_800BBAA0 + 1;
}