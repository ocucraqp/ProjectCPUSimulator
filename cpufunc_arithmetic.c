/*
 *	Project-based Learning II (CPU)
 *
 *	Program:	instruction set simulator of the Educational CPU Board
 *	File Name:	cpufunc_arithmetic.c
 *	Descrioption:	simulation(emulation) of arithmetic operation
 */

#include "cpuboard.h"

void ADD(Cpub *cpub) {
    Uword *argA, *argB;
    int result = 0;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    result = *argA + *argB;
    SetFlag(cpub, *argA, *argB, result, -1, 2, 2, 2);
    *argA = result;
}

void ADC(Cpub *cpub) {
    Uword *argA, *argB;
    int result = 0;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    result = *argA + *argB + cpub->cf;
    SetFlag(cpub, *argA, *argB + cpub->cf, result, 2, 2, 2, 2);
    if (cpub->cf) {
        result -= 0x100;
    }
    *argA = result;
}

void SUB(Cpub *cpub) {
    Uword *argA, *argB;
    Uword argB2;
    int result = 0;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    argB2 = Convert2sComplement(*argB);
    result = *argA + argB2;
    SetFlag(cpub, *argA, argB2, result, -1, 2, 2, 2);
    *argA = result;
}

void SBC(Cpub *cpub) {
    Uword *argA, *argB;
    Uword argB2, cf2;
    int result = 0;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    argB2 = Convert2sComplement(*argB);
    cf2 = Convert2sComplement((Uword) cpub->cf);
    result = *argA + argB2 + cf2;
    SetFlag(cpub, *argA, argB2 + cf2, result, 2, 2, 2, 2);
    if (cpub->cf) {
        result -= 0x100;
    }
    *argA = result;
}

void CMP(Cpub *cpub) {
    Uword *argA, *argB;
    Uword argB2;
    int result = 0;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    argB2 = Convert2sComplement(*argB);
    result = *argA + argB2;
    SetFlag(cpub, *argA, argB2, result, -1, 2, 2, 2);
}
