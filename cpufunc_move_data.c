/*
 *	Project-based Learning II (CPU)
 *
 *	Program:	instruction set simulator of the Educational CPU Board
 *	File Name:	cpufunc_move_data.c
 *	Descrioption:	simulation(emulation) of data movement
 */

#include "cpuboard.h"

void LD(Cpub *cpub) {
	Uword *argA, *argB;
	argA = JudgeArgA(cpub);
	argB = JudgeArgB(cpub);
	*argA = *argB;
}

void ST(Cpub *cpub) {
	Uword *argA, *argB;
	argA = JudgeArgA(cpub);
	argB = JudgeArgB(cpub);
	*argB = *argA;
}
