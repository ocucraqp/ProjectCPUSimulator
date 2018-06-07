/*
 *	Project-based Learning II (CPU)
 *
 *	Program:	instruction set simulator of the Educational CPU Board
 *	File Name:	cpufunc_logical.c
 *	Descrioption:	simulation(emulation) of logical operation
 */

#include "cpuboard.h"

void AND(Cpub *cpub) {
	Uword *argA, *argB;
	Uword result;
	argA = JudgeArgA(cpub);
	argB = JudgeArgB(cpub);
	result = *argA & *argB;
	SetFlag(cpub, *argA, *argB, result, -1, 0, 2, 2);
	*argA = result;
}

void OR(Cpub *cpub) {
	Uword *argA, *argB;
	Uword result;
	argA = JudgeArgA(cpub);
	argB = JudgeArgB(cpub);
	result = *argA | *argB;
	SetFlag(cpub, *argA, *argB, result, -1, 0, 2, 2);
	*argA = result;
}

void EOR(Cpub *cpub) {
	Uword *argA, *argB;
	Uword result;
	argA = JudgeArgA(cpub);
	argB = JudgeArgB(cpub);
	result = *argA ^ *argB;
	SetFlag(cpub, *argA, *argB, result, -1, 0, 2, 2);
	*argA = result;
}
