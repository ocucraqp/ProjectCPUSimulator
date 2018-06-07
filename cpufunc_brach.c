/*
 *	Project-based Learning II (CPU)
 *
 *	Program:	instruction set simulator of the Educational CPU Board
 *	File Name:	branch
 *	Descrioption:	simulation(emulation) of branch
 */

#include "cpuboard.h"

int Bbc(Cpub *cpub) {
	Uword order_code = 0;
	order_code = cpub->mem[cpub->pc] & 0x0f;
	cpub->pc++;
	switch (order_code) {
	case 0x00:
		//A Always
		cpub->pc = cpub->mem[cpub->pc];
		return 1;
	case 0x08:
		//VF oVerFlow
		if (cpub->vf == 1) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	case 0x01:
		//NZ Not Zero
		if (cpub->zf == 0) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	case 0x09:
		//Z Zero
		if (cpub->zf == 1) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	case 0x02:
		//ZP Zero or Positive
		if (cpub->nf == 0) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	case 0x0a:
		//N Negative
		if (cpub->nf == 1) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	case 0x03:
		//P Positive
		if ((cpub->nf) || ((cpub->zf) == 0)) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	case 0x0b:
		//ZN Zero or Negative
		if ((cpub->nf) || ((cpub->zf) == 1)) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	case 0x04:
		//NI No Input
		if (cpub->ibuf->flag == 0) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	case 0x0c:
		//NO No Output
		if (cpub->obuf.flag == 1) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	case 0x05:
		//NC No Carry
		if (cpub->cf == 0) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	case 0x0d:
		//C Carry
		if (cpub->cf == 1) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	case 0x06:
		//GE Greater than or Equal
		if (((cpub->vf) ^ (cpub->nf)) == 0) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	case 0x0e:
		//LT Less Than
		if (((cpub->vf) ^ (cpub->nf)) == 1) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	case 0x07:
		//GT Greater Than
		if ((((cpub->vf) ^ (cpub->nf)) || (cpub->zf)) == 0) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	case 0x0f:
		//LE Less than or Equal
		if ((((cpub->vf) ^ (cpub->nf)) || (cpub->zf)) == 1) {
			cpub->pc = cpub->mem[cpub->pc];
			return 1;
		}
		break;
	}

	return 0;
}

void JAL(Cpub *cpub) {
	cpub->acc = cpub->pc + 2;
	cpub->pc++;
	cpub->pc = cpub->mem[cpub->pc];
}

void JR(Cpub *cpub) {
	cpub->pc = cpub->acc;
}
