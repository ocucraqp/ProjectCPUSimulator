/*
 *	Project-based Learning II (CPU)
 *
 *	Program:	instruction set simulator of the Educational CPU Board
 *	File Name:	cpuboard.h
 *	Descrioption:	resource definition of the educational computer board
 */

#ifndef CPUBOARD_H
#define CPUBOARD_H

/*=============================================================================
 *   Architectural Data Types
 *===========================================================================*/
typedef signed char Sword;
typedef unsigned char Uword;
typedef unsigned short Addr;
typedef unsigned char Bit;

/*=============================================================================
 *   CPU Board Resources
 *===========================================================================*/
#define    MEMORY_SIZE    256*2
#define    IMEMORY_SIZE    256

typedef struct iobuf {
    Bit flag;
    Uword buf;
} IOBuf;

typedef struct cpuboard {
    Uword pc;
    Uword acc;
    Uword ix;
    Bit cf, vf, nf, zf;
    IOBuf *ibuf;
    IOBuf obuf;
    /*
     *   [ add here the other CPU resources if necessary ]
     */
    Uword mem[MEMORY_SIZE]; /* 0XX:Program, 1XX:Data */
} Cpub;

/*=============================================================================
 *   Top Function of an Instruction Simulation
 *===========================================================================*/
#define    RUN_HALT    0
#define    RUN_STEP    1

int step(Cpub *);

/*=============================================================================
 *   Sub-Functions of an Instruction Simulation
 *===========================================================================*/
//OUTput
void OUT(Cpub *);

//INput
void IN(Cpub *);

//Reset Carry Flag
void RCF(Cpub *);

//Set Carry Flag
void SCF(Cpub *);

//LoaD
void LD(Cpub *);

//STore
void ST(Cpub *);

//ADD
void ADD(Cpub *);

//ADd with Carry flag
void ADC(Cpub *);

//SUBtract
void SUB(Cpub *);

//SuBtract with Carry flag
void SBC(Cpub *);

//CoMPare
void CMP(Cpub *);

//AND
void AND(Cpub *);

//OR
void OR(Cpub *);

//Exculusive OR
void EOR(Cpub *);

//Shift or Rotate ....
void SRsm(Cpub *);

//Shift ....
void Ssm(Cpub *);

//Rotate ....
void Rsm(Cpub *);

//Shift Right Arthmetic
void SRA(Cpub *);

//Shift Left Arthmetic
void SLA(Cpub *);

//Shift Right Logical
void SRL(Cpub *);

//Shift Left Logical
void SLL(Cpub *);

//Rotate Right Arthmetic
void RRA(Cpub *);

//Rotate Left Arthmetic
void RLA(Cpub *);

//Rotate Right Logical
void RRL(Cpub *);

//Rotate Left Logical
void RLL(Cpub *);

//Branch ....
int Bbc(Cpub *);

//Jump And Link
void JAL(Cpub *);

//Jamp Register
void JR(Cpub *);

/* JudgeArgA() and JudgeArgB()
 * Judge proper A and B
 * for LD, ST, ADD, ADC, SUB, SBC, CMP, AND, OR, EOR, Bbc, JAL*/
Uword *JudgeArgA(Cpub *);

Uword *JudgeArgB(Cpub *);

//Read The second word as B
Uword *ReadNextPC(Cpub *, int);

//Set flag by argument condition
void SetFlag(Cpub *, Uword, Uword, int, int, int, int, int);

Uword Convert2sComplement(Uword);

#endif
