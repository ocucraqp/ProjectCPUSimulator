/*
 *	Project-based Learning II (CPU)
 *
 *	Program:	instruction set simulator of the Educational CPU Board
 *	File Name:	cpufunc_shift.c
 *	Descrioption:	simulation(emulation) of shift operation
 */

#include "cpuboard.h"

void SRsm(Cpub *cpub) {
	Uword order_code = 0;
	order_code = cpub->mem[cpub->pc] & 0x04;
	switch (order_code) {
	case 0x00:
		Ssm(cpub);
		break;
	case 0x04:
		Rsm(cpub);
		break;

	}
}

void Ssm(Cpub *cpub) {
	Uword order_code = 0;
	order_code = cpub->mem[cpub->pc] & 0x03;
	switch (order_code) {
	case 0x00:
		SRA(cpub);
		break;
	case 0x01:
		SLA(cpub);
		break;
	case 0x02:
		SRL(cpub);
		break;
	case 0x03:
		SLL(cpub);
		break;
	}
}

void Rsm(Cpub *cpub) {
	Uword order_code = 0;
	order_code = cpub->mem[cpub->pc] & 0x03;
	switch (order_code) {
	case 0x00:
		RRA(cpub);
		break;
	case 0x01:
		RLA(cpub);
		break;
	case 0x02:
		RRL(cpub);
		break;
	case 0x03:
		RLL(cpub);
		break;
	}
}

void SRA(Cpub *cpub) {
	Uword *argA;
	Uword result;
	argA = JudgeArgA(cpub);
	result = *argA >> 1;
	//keep most significant bit
	if ((*argA & 0x80) == 0x80) {
		result |= 0x80;
	} else {
		result &= 0x7f;
	}

	if ((*argA & 0x01) == 0x01) {
		cpub->cf = 1;
	} else {
		cpub->cf = 0;
	}
	SetFlag(cpub, *argA, 0, result, -1, 0, 2, 2);
	*argA = result;
}

void SLA(Cpub *cpub) {
	Uword *argA;
	Uword result;
	argA = JudgeArgA(cpub);
	result = *argA << 1;
	result &= 0xfe;

	if ((*argA & 0x80) == 0x80) {
		cpub->cf = 1;
	} else {
		cpub->cf = 0;
	}

	if ((*argA & 0x80) == (result & 0x80)) {
		cpub->vf = 1;
	} else {
		cpub->vf = 0;
	}

	SetFlag(cpub, *argA, 0, result, -1, -1, 2, 2);
	*argA = result;
}

void SRL(Cpub *cpub) {
	Uword *argA;
	Uword result;
	argA = JudgeArgA(cpub);
	result = *argA >> 1;
	result &= 0x7f;

	if ((*argA & 0x01) == 0x01) {
		cpub->cf = 1;
	} else {
		cpub->cf = 0;
	}
	SetFlag(cpub, *argA, 0, result, -1, 0, 2, 2);
	*argA = result;
}

void SLL(Cpub *cpub) {
	Uword *argA;
	Uword result;
	argA = JudgeArgA(cpub);
	result = *argA << 1;
	result &= 0xfe;

	if ((*argA & 0x80) == 0x80) {
		cpub->cf = 1;
	} else {
		cpub->cf = 0;
	}
	SetFlag(cpub, *argA, 0, result, -1, 0, 2, 2);
	*argA = result;
}

void RRA(Cpub *cpub) {
	Uword *argA;
	Uword result;
	argA = JudgeArgA(cpub);
	result = *argA >> 1;
	if (cpub->cf) {
		result |= 0x80;
	} else {
		result &= 0x7f;
	}

	if ((*argA & 0x01) == 0x01) {
		cpub->cf = 1;
	} else {
		cpub->cf = 0;
	}
	SetFlag(cpub, *argA, 0, result, -1, 0, 2, 2);
	*argA = result;
}

void RLA(Cpub *cpub) {
	Uword *argA;
	Uword result;
	argA = JudgeArgA(cpub);
	result = *argA << 1;
	if (cpub->cf) {
		result |= 0x01;
	} else {
		result &= 0xfe;
	}

	if ((*argA & 0x80) == 0x80) {
		cpub->cf = 1;
	} else {
		cpub->cf = 0;
	}

	if ((*argA & 0x80) == (result & 0x80)) {
		cpub->vf = 1;
	} else {
		cpub->vf = 0;
	}

	SetFlag(cpub, *argA, 0, result, -1, -1, 2, 2);
	*argA = result;
}

void RRL(Cpub *cpub) {
	Uword *argA;
	Uword result;
	argA = JudgeArgA(cpub);
	result = *argA >> 1;
	if ((*argA & 0x01) == 0x01) {
		result |= 0x80;
	} else {
		result &= 0x7f;
	}

	if ((*argA & 0x01) == 0x01) {
		cpub->cf = 1;
	} else {
		cpub->cf = 0;
	}
	SetFlag(cpub, *argA, 0, result, -1, 0, 2, 2);
	*argA = result;
}

void RLL(Cpub *cpub) {
	Uword *argA;
	Uword result;
	argA = JudgeArgA(cpub);
	result = *argA << 1;
	if ((*argA & 0x80) == 0x80) {
		result |= 0x01;
	} else {
		result &= 0xfe;
	}

	if ((*argA & 0x80) == 0x80) {
		cpub->cf = 1;
	} else {
		cpub->cf = 0;
	}
	SetFlag(cpub, *argA, 0, result, -1, 0, 2, 2);
	*argA = result;
}
