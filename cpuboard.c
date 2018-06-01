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
    }

    order_code = cpub->mem[cpub->pc] & 0xf0;
    switch (order_code) {
        case 0x60: //0110---- LD
            LD(cpub);
            return RUN_STEP;
        case 0x70: //0111---- ST
            ST(cpub);
            return RUN_STEP;
        case 0xb0: //1011---- ADD
            ADD(cpub);
            return RUN_STEP;
        case 0x90: //1001---- ADC
            ADC(cpub);
            return RUN_STEP;
        case 0xa0: //1010---- SUB
            SUB(cpub);
            return RUN_STEP;
        case 0x80: //1000---- SBC
            SBC(cpub);
            return RUN_STEP;
        case 0xf0: //1111---- CMP
            CMP(cpub);
            return RUN_STEP;
        case 0xe0: //1110---- AND
            AND(cpub);
            return RUN_STEP;
        case 0xd0: //1101---- OR
            OR(cpub);
            return RUN_STEP;
        case 0xc0: //1100---- EOR
            EOR(cpub);
            return RUN_STEP;
        case 0x40: //0100---- Shift or Rotate
            SRsm(cpub);
            return RUN_STEP;
        case 0x30: //0011---- Bbc
            Bbc(cpub);
            return RUN_STEP;
    }

    order_code = cpub->mem[cpub->pc] & 0xfc;
    if (order_code == 0x0a) {
        //00001010 JAL
        JAL(cpub);
    }
    if (order_code == 0x0b) {
        //00001011 JR
        JR(cpub);
    }

    cpub->pc++;
    return RUN_STEP;
}

void OUT(Cpub *cpub) {
    cpub->obuf.buf = cpub->acc;
    cpub->obuf.flag = 1;
}

void IN(Cpub *cpub) {
    cpub->acc = cpub->ibuf->buf;
    cpub->obuf.flag = 0;
}

void RCF(Cpub *cpub) {
    cpub->cf = 0;
}

void SCF(Cpub *cpub) {
    cpub->cf = 1;
}

void LD(Cpub *cpub) {
    Uword *argA, *argB;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    *argB = *argA;
}

void ST(Cpub *cpub) {
    Uword *argA, *argB;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    *argA = *argB;
}

void ADD(Cpub *cpub) {
    Uword *argA, *argB;
    Uword result;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    result = *argA + *argB;
    SetFlag(cpub, *argA, result, -1, 2, 2, 2);
    if (cpub->cf) {
        result -= 0x100;
    }
    *argA = result;
}

void ADC(Cpub *cpub) {
    Uword *argA, *argB;
    Uword result;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    result = *argA + *argB + cpub->cf;
    SetFlag(cpub, *argA, result, 2, 2, 2, 2);
    if (cpub->cf) {
        result -= 0x100;
    }
    *argA = result;
}

void SUB(Cpub *cpub) {
    Uword *argA, *argB;
    Uword result;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    result = *argA - *argB;
    SetFlag(cpub, *argA, result, -1, 2, 2, 2);
    if (cpub->cf) {
        result -= 0x100;
    }
    *argA = result;
}

void SBC(Cpub *cpub) {
    Uword *argA, *argB;
    Uword result;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    result = *argA + *argB;
    SetFlag(cpub, *argA, result, 2, 2, 2, 2);
    if (cpub->cf) {
        result -= 0x100;
    }
    *argA = result;
}

void CMP(Cpub *cpub) {
    Uword *argA, *argB;
    Uword result;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    result = *argA - *argB;
    SetFlag(cpub, *argA, result, -1, 2, 2, 2);
}

void AND(Cpub *cpub) {
    Uword *argA, *argB;
    Uword result;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    result = *argA & *argB;
    SetFlag(cpub, *argA, result, -1, 0, 2, 2);
    *argA = result;
}

void OR(Cpub *cpub) {
    Uword *argA, *argB;
    Uword result;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    result = *argA | *argB;
    SetFlag(cpub, *argA, result, -1, 0, 2, 2);
    *argA = result;
}

void EOR(Cpub *cpub) {
    Uword *argA, *argB;
    Uword result;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);
    result = *argA ^ *argB;
    SetFlag(cpub, *argA, result, -1, 0, 2, 2);
    *argA = result;
}

void SRsm(Cpub *cpub) {
    Uword order_code = 0;
    order_code = cpub->mem[cpub->pc] & 0x07;
    switch (order_code) {
        case 0x00 :
            Ssm(cpub);
            break;
        case 0x03 :
            Rsm(cpub);
            break;

    }
}

void Ssm(Cpub *cpub) {
    Uword order_code = 0;
    order_code = cpub->mem[cpub->pc] & 0x03;
    switch (order_code) {
        case 0x00 :
            SRA(cpub);
            break;
        case 0x01 :
            SLA(cpub);
            break;
        case 0x02 :
            SRL(cpub);
            break;
        case 0x03 :
            SLL(cpub);
            break;
    }
}

void Rsm(Cpub *cpub) {
    Uword order_code = 0;
    order_code = cpub->mem[cpub->pc] & 0x03;
    switch (order_code) {
        case 0x00 :
            RRA(cpub);
            break;
        case 0x01 :
            RLA(cpub);
            break;
        case 0x02 :
            RRL(cpub);
            break;
        case 0x03 :
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
    SetFlag(cpub, *argA, result, -1, 0, 2, 2);
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
    SetFlag(cpub, *argA, result, -1, 2, 2, 2);
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
    SetFlag(cpub, *argA, result, -1, 0, 2, 2);
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
    SetFlag(cpub, *argA, result, -1, 0, 2, 2);
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
    SetFlag(cpub, *argA, result, -1, 0, 2, 2);
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
    SetFlag(cpub, *argA, result, -1, 2, 2, 2);
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
    SetFlag(cpub, *argA, result, -1, 0, 2, 2);
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
    SetFlag(cpub, *argA, result, -1, 0, 2, 2);
    *argA = result;
}

void Bbc(Cpub *cpub) {
    Uword order_code = 0;
    order_code = cpub->mem[cpub->pc] & 0x0f;
    cpub->pc++;
    switch (order_code) {
        case 0x00 :
            //A
            cpub->pc = cpub->mem[cpub->pc];
            break;
        case 0x08 :
            //VF
            if (cpub->vf == 1) {
                cpub->pc = cpub->mem[cpub->pc];
            }
            break;
        case 0x01 :
            //NZ
            if (cpub->zf == 0) {
                cpub->pc = cpub->mem[cpub->pc];
            }
            break;
        case 0x09 :
            //Z
            if (cpub->zf == 1) {
                cpub->pc = cpub->mem[cpub->pc];
            }
        case 0x02 :
            //ZP
            if (cpub->nf == 0) {
                cpub->pc = cpub->mem[cpub->pc];
            }
            break;
        case 0x0a :
            //N
            if (cpub->nf == 1) {
                cpub->pc = cpub->mem[cpub->pc];
            }
            break;
        case 0x03 :
            //P
            if ((cpub->nf) | ((cpub->zf)) == 0) {
                cpub->pc = cpub->mem[cpub->pc];
            }
            break;
        case 0x0b :
            //ZN
            if ((cpub->nf) | ((cpub->zf)) == 1) {
                cpub->pc = cpub->mem[cpub->pc];
            }
            break;
        case 0x04 :
            //NI
            if (cpub->ibuf->flag == 0) {
                cpub->pc = cpub->mem[cpub->pc];
            }
            break;
        case 0x0c :
            //NO
            if (cpub->obuf.flag == 1) {
                cpub->pc = cpub->mem[cpub->pc];
            }
            break;
        case 0x05 :
            //NC
            if (cpub->cf == 0) {
                cpub->pc = cpub->mem[cpub->pc];
            }
            break;
        case 0x0d :
            //C
            if (cpub->cf == 1) {
                cpub->pc = cpub->mem[cpub->pc];
            }
            break;
        case 0x06 :
            //GE
            if ((cpub->vf) ^ ((cpub->nf)) == 0) {
                cpub->pc = cpub->mem[cpub->pc];
            }
            break;
        case 0x0e :
            //LT
            if (((cpub->vf) ^ (cpub->nf)) == 1) {
                cpub->pc = cpub->mem[cpub->pc];
            }
            break;
        case 0x07 :
            //GT
            if ((((cpub->vf) ^ (cpub->nf)) | (cpub->zf)) == 0) {
                cpub->pc = cpub->mem[cpub->pc];
            }
            break;
        case 0x0f :
            //LE
            if ((((cpub->vf) ^ (cpub->nf)) | (cpub->zf)) == 1) {
                cpub->pc = cpub->mem[cpub->pc];
            }
            break;
    }

}


void JAL(Cpub *cpub) {
    cpub->acc = cpub->pc + 2;
    cpub->pc++;
    cpub->pc = cpub->mem[cpub->pc];


}

void JR(Cpub *cpub) {
    cpub->pc = cpub->acc;
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
     * 5:(d)	Absolute address (data area)
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
            return 0;
    }
}

void SetFlag(Cpub *cpub, Uword argA, Uword flagSource, int cfFlag, int vfFlag,
             int nfFlag, int zfFlag) {
    /* xfFlag
     * -1:  no effect
     *  0:	reset
     *  1:	set
     *  2:	Depends on argA and flagSource
     * */

    //set/reset CF
    if (cfFlag >= 0) {
        if (flagSource >= 0x100 | cfFlag == 1) {
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
        if (((argA & 0x80) ^ (flagSource & 0x80)) | vfFlag == 1) {
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
        if ((flagSource & 0x80) == 0x80 | nfFlag == 1) {
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
        if (flagSource == 0x00 | zfFlag == 1) {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
        if (zfFlag == 0) {
            cpub->zf = 0;
        }
    }
}
