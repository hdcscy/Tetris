#pragma once
#include "const.h"

char szAryTetris_L_A[4][4] = {
    { 0, 0, 0 },
    { 1, 0, 0 },
    { 1, 0, 0 },
    { 1, 1, 0 }
};

char szAryTetris_L_B[4][4] = {
    { 0, 0, 0 },
    { 0, 1, 0 },
    { 0, 1, 0 },
    { 1, 1, 0 }
};

char szAryTetris_T[4][4] = {
    { 0, 0, 0 },
    { 0, 1, 0 },
    { 1, 1, 1 },
    { 0, 0, 0 }
};

char szAryTetris_Z_A[4][4] = {
    { 0, 0, 0 },
    { 1, 1, 0 },
    { 0, 1, 1 },
    { 0, 0, 0 }
};

char szAryTetris_Z_B[4][4] = {
    { 0, 0, 0 },
    { 0, 1, 1 },
    { 1, 1, 0 },
    { 0, 0, 0 }
};

char szAryTetris_Square[4][4] = {
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 1, 1, 0 },
    { 1, 1, 0 }
};

char szAryTetris_I[4][4] = {
    { 0, 1, 0 },
    { 0, 1, 0 },
    { 0, 1, 0 },
    { 0, 1, 0 },
};

char* arys[] = {
    (char*)szAryTetris_L_A,
    (char*)szAryTetris_L_B,
    (char*)szAryTetris_Z_A,
    (char*)szAryTetris_Z_B,
    (char*)szAryTetris_T,
    (char*)szAryTetris_I,
    (char*)szAryTetris_Square
};
