//
//  processorMain.c
//  NSVM
//
//  Created by Noah Whiteis on 12/31/12.
//  Copyright (c) 2012 Noah Whiteis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int DWORD;
typedef unsigned int U_DWORD;
typedef long long int DWORD64;
typedef unsigned long long int U_DWORD64;
typedef float S_FLOAT;

typedef struct{
    
    
    U_DWORD FA; // Program Counter       ***THESE ARE RESERVED REGISTERS***
    DWORD FB; // Stack Frame
    DWORD FC; // Machine State
    DWORD FD; // VM Mode!
    DWORD FE; // Code Segment Begining
    DWORD FF; // Data Segment Begining
    DWORD FG; // Stack Segment
    DWORD FH; // Interrupt Dump Control
    DWORD FI; // Execution State
    DWORD FJ; // Current Excution Program
    DWORD FK; // What Architecture?
    
    //All The Segment Stuff
    
    DWORD GA; // Using Multiprogram Mode
    DWORD GB; // Memory Segment Size
    DWORD GC; // Code Segment Offset
    DWORD GD; // Data Segment Offset
    DWORD DS; // Stack Segment Offset
    DWORD DP; // Data Protection Mode
    DWORD DF; // Stack High Point
    
    // Stack Pointer Stuff 
    DWORD SP; // Stack 32 Bit Pointer
    DWORD64 ESP; // Extended 64 Bit Stack Pointer
    DWORD SS; // Standard 32 Bit Stack Size
    DWORD64 ESS; // Extended 64 Bit Stack Size
    U_DWORD HS; // Current Top Heap Size
    U_DWORD64 EHS; // Current Extended Heap Size
    
    /*
     Some Notes On The Protection Modes 1=Realtime(Only Available On Some Os's)
     2=Segmented Programs(Only In Multiprogram Mode 3=Direct Pointers Not Allowed As Well As No 
     Direct Memory Access 3= 2+ Complete Protection And Sandboxing Native IO Interfaces Must Be Signed
     */
}proc_memory;

// The Main Memory ***
void **p_stack;
void **p_heap; // Prototype
int nativeStack[100]; // Only 100 Values
// End Main Memory ***
//Just A Null Pointer On Startup And Reallocated 
proc_memory *RegBaseHolder; // Globalize A Pointer TO The S

void InitCPU(short Arch, int StackSize, int HeapSize){ //1=32Bit 2=64Bit
    //Function Prototypes
    void AllocateMem(int HeapMegaBytes, int StackMegaBytes);
    //End Function Prototypes
        RegBaseHolder = malloc(sizeof(proc_memory));
        //A Null Pointer Is Equal To 0 Compiler Will Complain Since Not Implicitly Typecasting Variable */
        //Init Program Counter To 1 And Excute First Instruction
    RegBaseHolder->FA=1;
    AllocateMem(StackSize, HeapSize);
    switch(Arch){
        case 1:
            //32 Bit
            RegBaseHolder->FK = (U_DWORD) 0;
            RegBaseHolder->SP = 0;
            RegBaseHolder->HS = 0;
        case 2:
            RegBaseHolder->FK = (U_DWORD) 1;
            RegBaseHolder->ESP = 0;
            RegBaseHolder->EHS = 0;
    }
}
void DumpCPU(char Report){
    if(Report == 1){
        // Do Reporting....
        asm("movl $1,%eax");
    }
    else{
        // Do Nothing And Return Sucess!
    }
    free(RegBaseHolder); // Free The Registers
    free(p_stack);
    free(p_heap);
}
void AllocateMem(int HeapMegabytes, int StackMegabytes){ 
    if(RegBaseHolder->FK == 0){
        p_heap = calloc(sizeof(int),(HeapMegabytes*262144));
        //32 Bit 
        p_stack = calloc(sizeof(int),(StackMegabytes*262144));
    }
    if(RegBaseHolder->FK == 1){
        p_heap = calloc(sizeof(long long),(HeapMegabytes*131072));
        //64 Bit
        p_stack = calloc(sizeof(long long),(StackMegabytes*131072));
    }
} /* 1Mb = (262144) 32 Bit Int's (32Bit Mode)
     1Mb = (131072) 64 Bit Int's (64Bit Mode) */
// App Pr_ Functions Must Not Be Allowed To Be Implemented In Bytecode
// Non r_ and P Must Be Protected From Buffer Overflows

/* r_ Functions */
void r_inode_placeinmem(void* data, void* addr, int datatype){
    switch (RegBaseHolder->FK){
        case 0: // 32 Bit
            switch(datatype){
                case 1: // Long
                    
                    break;
                case 2: // Float 
                    
                    break;
            }
        case 1: // 64Bit
            switch(datatype){ // This Is So We Can Log In The Data Table
                case 1: // Long
                    
                    break;
                case 2: // Float  *planning for custom float*
                    
                    break;
            }
    }
}
unsigned int getDataType(){
    switch(RegBaseHolder->FK){
        case 1:
            return 4;
            break;
        case 2:
            return 8;
            break;
    };
    return NULL;
}
void r_stack_placemem(void *data, int offset){
    memcpy(p_stack[offset], data, getDataType());
}
void  r_heap_placemem(void *data, int offset){
    memcpy(p_heap[offset], data, getDataType());
}
/* end r_ Functions */
void resize_down(unsigned int size_down){
    realloc(p_heap,size_down);
}
proc_memory *p_getPtrToReg(){
    return RegBaseHolder;
}
void** p_getPtrToMem(){
    return p_heap;
}
void push(void *mem){
    p_stack[RegBaseHolder->SS] = mem; // Simple Just Push Onto ** void pointer
}
void pop(){
    RegBaseHolder->SS--;
    p_stack[RegBaseHolder->SS+1] = (void*)0;
}
void ssp(int position){
    RegBaseHolder->ESP = position;
}
void* dsp(){
    return p_stack[RegBaseHolder->SS];
}
void clearpage(int bytes, int section){         // Very Process Intensive You Have To Move The Whole Stack Down 4 Bytes
    int page_counter = 0;
}
