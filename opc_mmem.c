//
//  opc_mmem.c
//  NSVM
//
//  Created by Noah Whiteis on 1/6/13.
//  Copyright (c) 2013 Noah Whiteis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "cpu_exception_handler.h"
#include "dy_register_caller.h"
struct b_info{
    int mode;
    int arch;
};
struct f_def{
    float f_temp[4];
    unsigned int x32_temp[4];
    unsigned long long x64_temp[4];
};
enum ddr{
    X32, X64, FFN,  DIRECT, DYREGISTER, MEMORY
};
void (*op[100])(void* op1, void* op2, void* op3);

struct b_info ffp;
struct f_def f_temp;

void BREAK(void* op1, void* op2, void* op3){
    break_p();
}
void MOV(void* op1, void* op2, void* op3){
    cpy(*(unsigned long long int*)op1, *(unsigned long long int*)op2, *(unsigned long long int*)op3);
}
void MOVRTR(void* op1, void* op2, void* op3){
    switch(ffp.arch){
        case 4:
            write_to_dyReg(*(unsigned int*)op1, *(unsigned long long int*)op2, 4);
            break;
        case 8:
            write_to_dyReg(*(unsigned long long int*)op1, *(unsigned long long int*)op2, 8);
            break;
        case FFN:
            break;
    }
}
void MOVTD(void* op1, void* op2, void* op3){
    // All I have to say is brainfuck
}
void CRCHUNK(void* op1, void* op2, void* op3){
    createChunk();
}
void MKREG(void* op1, void* op2, void* op3){
    createReg();
}
void DELREG(void* op1, void* op2, void* op3){
    
}
void ADD(void* op1, void* op2, void* op3){
    switch(ffp.arch){
        case 8:
            f_temp.x32_temp[0] = read_from_dyReg(*(int*)op1);
            
            break;
        case 4:
            break;
    }
}
void SUB(void* op1, void* op2, void* op3){
    
}
void MULT(void* op1, void* op2, void* op3){
    
}
void DIV(void* op1, void* op2, void* op3){
    
}
void BXOR(void* op1, void* op2, void* op3){
    
}
void BOR(void* op1, void* op2, void* op3){
    
}
void BAND(void* op1, void* op2, void* op3){
    
}
void BEQUAL(void* op1, void* op2, void* op3){
    
}
void BNOT(void* op1, void* op2, void* op3){
    
}
void SHIFT_LEFT(void* op1, void* op2, void* op3){
    
}
void SHIFT_RIGHT(void* op1, void* op2, void* op3){
    
}
void BRANCH(void* op1, void* op2, void* op3){
    
}
void CLBRANCH(void* op1, void* op2, void* op3){
    
}
void SYSCALL(void* op1, void* op2, void* op3){ // Make A Direct Syscall 
    
}
void LOADSYSCALL(void* op1, void* op2, void* op3){
    //Load Specified SysCall syscall group in op1, arg 1 in op2 arg2 in op3
    //Remember SysCalls a use a struct to set the group
    
}
void ROAR(void* op1, void* op2, void* op3){
    
}
void SROAR(void* op1, void* op2, void* op3){
    
}
void DATAOF(void* op1, void* op2, void* op3){
    
}
void STUB(void* op1, void* op2, void* op3){
    
}
void R_STUB(void* op1, void* op2, void* op3){
    
}
void NOP(void * op1, void* op2, void* op3){
    //Do Nothing
}
void setupPtr(){
    op[0] =  &BREAK;
    op[1] =  &MOV;
    op[2] =  &MOVTD;
    op[3] =  &CRCHUNK;
    op[5] =  &MKREG;
    op[6] =  &DELREG;
    op[7] =  &ADD;
    op[8] =  &SUB;
    op[9] =  &MULT;
    op[10] = &DIV;
    op[11] = &BXOR;
    op[12] = &BOR;
    op[13] = &BAND;
    op[14] = &BEQUAL;
    op[15] = &BNOT;
    op[16] = &SHIFT_LEFT;
    op[17] = &SHIFT_RIGHT;
    op[18] = &BRANCH;
    op[19] = &CLBRANCH;
    op[20] = &SYSCALL;
    op[21] = &LOADSYSCALL;
    op[22] = &ROAR; // Free Function (Read Offset And Return)
    op[23] = &SROAR; // Read Stub Use Sub Function
    op[24] = &DATAOF; // Struct Data Offset
    op[25] = &STUB; // Stub Function
    op[26] = &R_STUB; // Remote Stub
    op[27] = &NOP;
    if(sizeof(int) == 8){
        ffp.arch = 32;
    }
    if(sizeof(int) == 4){
        ffp.arch = 64;
    }
}
void process_opcode(int *opcode,void* op1, void* op2, void* op3){
    (*op[*opcode])(op1,op2,op3);
}