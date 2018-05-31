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
    //aaaaa//
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
            Bbc(cpub);
            break;
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

}

void IN(Cpub *cpub) {

}

void RCF(Cpub *cpub) {

}

void SCF(Cpub *cpub) {

}

void LD(Cpub *cpub) {

}

void ST(Cpub *cpub) {

}

void ADD(Cpub *cpub) {
    int* argA, argB;
    argA = JudgeArgA(cpub);
    argB = JudgeArgB(cpub);


}

void ADC(Cpub *cpub) {

}

void SUB(Cpub *cpub) {

}

void SBC(Cpub *cpub) {

}

void CMP(Cpub *cpub) {

}

void AND(Cpub *cpub) {

}

void OR(Cpub *cpub) {

}

void EOR(Cpub *cpub) {

}

void SRsm(Cpub *cpub) {

}

void Bbc(Cpub *cpub) {

}

void JAL(Cpub *cpub) {

}

void JR(Cpub *cpub) {

}

int* JudgeArgA(Cpub *cpub){
    order_code = cpub->mem[cpub->pc] & 0x08;
    //ACC or IX
    if (order_code == 0x00) {
        return &cpub->acc;
    }else{
        return &cpub->ix;
    }
}

int* JudgeArgB(Cpub *cpub){
    order_code = cpub->mem[cpub->pc] & 0x07;
    //ACC or IX
    switch (order_code){
        case 0x00:
            //000 ACC
            return &cpub->acc;
        case 0x01:
            //001 IX
            return &cpub->ix;
        case 0x02:
        case 0x03:
            //01- d
            cpub->pc++;
            return ReadNextPC(cpub);
        case 0x04:
            //100 [d]
            cpub->pc++;
            return ReadNextPC(cpub);

            //todo 処理
    }
}