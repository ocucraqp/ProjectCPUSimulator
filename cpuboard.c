/*
 *	Project-based Learning II (CPU)
 *
 *	Program:	instruction set simulator of the Educational CPU Board
 *	File Name:	cpuboard.c
 *	Descrioption:	simulation(emulation) of an instruction
 */

#include    "cpuboard.h"

/*=============================================================================
 *   Simulation of a Single Instruction
 *===========================================================================*/
int step(Cpub *cpub) {
    //   [ return RUN_STEP or RUN_HALT ]
    Uword order_code = 0;

    order_code = cpub->mem[cpub->pc] & 0xfc;
    if (order_code == 0x0c) {
        //000011-- HALT
        cpub->pc++;
        return RUN_HALT;
    }

    order_code = cpub->mem[cpub->pc] & 0xf8;
    switch (order_code) {
        case 0x00: //00000--- NOP
            break;
        case 0x10: //00010--- OUT
            OUT(cpub);
            break;
        case 0x18: //00011--- IN
            IN(cpub);
            break;
        case 0x20: //00010--- RCF
            RCF(cpub);
            break;
        case 0x28: //00011--- SCF
            SCF(cpub);
            break;
        default:
            /* never reach here */
            break;
    }

    order_code = cpub->mem[cpub->pc] & 0xf0;
    switch (order_code) {
        case 0x60: //0110---- LD
            LD(cpub);
            break;
        case 0x70: //0111---- ST
            ST(cpub);
            break;
        case 0xb0: //1011---- ADD
            ADD(cpub);
            break;
        case 0x90: //1001---- ADC
            ADC(cpub);
            break;
        case 0xa0: //1010---- SUB
            SUB(cpub);
            break;
        case 0x80: //1000---- SBC
            SBC(cpub);
            break;
        case 0xf0: //1111---- CMP
            CMP(cpub);
            break;
        case 0xe0: //1110---- AND
            AND(cpub);
            break;
        case 0xd0: //1101---- OR
            OR(cpub);
            break;
        case 0xc0: //1100---- EOR
            EOR(cpub);
            break;
        case 0x40: //0100---- Shift or Rotate
            SRsm(cpub);
            break;
        case 0x30: //0011---- Bbc
            if (Bbc(cpub)) {
                return RUN_STEP;
            }
        default:
            /* never reach here */
            break;
    }

    order_code = cpub->mem[cpub->pc] & 0x0f;
    if (order_code == 0x0a) {
        //00001010 JAL
        JAL(cpub);
        return RUN_STEP;
    }
    if (order_code == 0x0b) {
        //00001011 JR
        JR(cpub);
        return RUN_STEP;
    }

    cpub->pc++;
    return RUN_STEP;
}

Uword *JudgeArgA(Cpub *cpub) {
    Uword order_code = 0;
    order_code = cpub->mem[cpub->pc] & 0x08;
    //ACC or IX
    if (order_code == 0x00) {
        return &cpub->acc;
    } else {
        return &cpub->ix;
    }
}

Uword *JudgeArgB(Cpub *cpub) {
    Uword order_code = 0;
    order_code = cpub->mem[cpub->pc] & 0x07;
    //ACC or IX
    switch (order_code) {
        case 0x00:
            //000 ACC
            return &cpub->acc;
        case 0x01:
            //001 IX
            return &cpub->ix;
        case 0x02:
        case 0x03:
            //01- d
            return ReadNextPC(cpub, 2);
        case 0x04:
            //100 [d]
            return ReadNextPC(cpub, 4);
        case 0x05:
            //101 (d)
            return ReadNextPC(cpub, 5);
        case 0x06:
            //110 [IX+d]
            return ReadNextPC(cpub, 6);
        case 0x07:
            //111 (IX+d)
            return ReadNextPC(cpub, 7);
        default:
            /* never reach here */
            return 0;
    }
}

Uword *ReadNextPC(Cpub *cpub, int addrMode) {
    /* addrMode
     * 2:d		Immediate address
     * 4:[d]	Absolute address (program area)
     * 5:(d)	Absolute address (data area)1
     * 6:[IX+d]	IX qualified address (program area)
     * 7:(IX+d)	IX qualified address (data area)
     * */

    cpub->pc++;

    switch (addrMode) {
        case 2:
            return &cpub->mem[cpub->pc];
        case 4:
            return &cpub->mem[cpub->mem[cpub->pc]];
        case 5:
            return &cpub->mem[cpub->mem[cpub->pc] + 0x100];
        case 6:
            return &cpub->mem[cpub->ix + cpub->mem[cpub->pc]];
        case 7:
            return &cpub->mem[cpub->ix + cpub->mem[cpub->pc] + 0x100];
        default:
            /* Unexpected behavior */
            return 0;
    }
}

void SetFlag(Cpub *cpub, Uword argA, Uword argB, int flagSource, int cfFlag,
             int vfFlag, int nfFlag, int zfFlag) {
    /* xfFlag
     * -1:  no effect
     *  0:	reset
     *  1:	set
     *  2:	Depends on argA and flagSource
     * */
    Uword argA_80 = argA & 0x80;
    Uword argB_80 = argB & 0x80;
    int flagSource_80 = flagSource & 0x80;

    //set/reset CF
    if (cfFlag >= 0) {
        if ((flagSource >= 0x100) || (cfFlag == 1)) {
            cpub->cf = 1;
        } else {
            cpub->cf = 0;
        }
        if (cfFlag == 0) {
            cpub->cf = 0;
        }
    }

    //set/reset VF
    if (vfFlag >= 0) {
        if ((vfFlag == 1)
            || ((argA_80 == argB_80) && (argA_80 != flagSource_80))) {
            cpub->vf = 1;
        } else {
            cpub->vf = 0;
        }
        if (vfFlag == 0) {
            cpub->vf = 0;
        }
    }

    //set/reset NF
    if (nfFlag >= 0) {
        if (((flagSource_80) == 0x80) || (nfFlag == 1)) {
            cpub->nf = 1;
        } else {
            cpub->nf = 0;
        }
        if (nfFlag == 0) {
            cpub->nf = 0;
        }
    }

    //set/reset ZF
    if (zfFlag >= 0) {
        if (((flagSource & 0xff) == 0x00) || (zfFlag == 1)) {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
        if (zfFlag == 0) {
            cpub->zf = 0;
        }
    }
}

Uword Convert2sComplement(Uword arg) {
    Uword result = 0;
    result = (arg ^ 0xff) + 1;
    return result;
}
