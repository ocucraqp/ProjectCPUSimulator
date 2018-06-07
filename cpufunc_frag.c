/*
 *	Project-based Learning II (CPU)
 *
 *	Program:	instruction set simulator of the Educational CPU Board
 *	File Name:	cpufunc_frag.c
 *	Descrioption:	simulation(emulation) of frag control
 */

#include "cpuboard.h"

void RCF(Cpub *cpub) {
	cpub->cf = 0;
}

void SCF(Cpub *cpub) {
	cpub->cf = 1;
}
