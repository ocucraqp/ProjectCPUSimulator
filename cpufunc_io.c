/*
 *	Project-based Learning II (CPU)
 *
 *	Program:	instruction set simulator of the Educational CPU Board
 *	File Name:	cpufunc_io.c
 *	Descrioption:	simulation(emulation) of I/O control
 */

#include "cpuboard.h"

void OUT(Cpub *cpub) {
	cpub->obuf.buf = cpub->acc;
	cpub->obuf.flag = 1;
	//todo
}

void IN(Cpub *cpub) {
	cpub->acc = cpub->ibuf->buf;
	cpub->obuf.flag = 0;
	//todo
}
