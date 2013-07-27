//
//  dy_register_caller.c
//  NSVM
//
//  Created by Noah Whiteis on 1/16/13.
//  Copyright (c) 2013 Noah Whiteis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "cpu_exception_handler.h"
typedef struct {
    char DefaultSize;
    char isProtected;
    unsigned long long amountRegisters;
    unsigned long long amountUseRegisters;
}reg_handle;
typedef struct{
    unsigned long long int uli_ret;
    unsigned int ui_ret;
    long long int li_ret;
    int i_ret;
    float f_ret;
}return_handle;

enum n_enum {
    X32_int , X64_int, float_is
    };dev_t

void **reg_table;
char *type_table;
reg_handle reg_nHandle;
return_handle ret_handle;
void CreateRegTable(unsigned long long chunks, char typeSize){
    reg_nHandle.DefaultSize = typeSize;
    if(reg_nHandle.DefaultSize != 8 || reg_nHandle.DefaultSize != 4){
        throw_cpu_fatal(14);
    }
    reg_nHandle.amountRegisters = (chunks*10)+reg_nHandle.amountRegisters;
    reg_nHandle.amountUseRegisters = 0;
    reg_table = calloc((size_t)typeSize,(size_t)chunks);
    if(reg_table == NULL){
        throw_cpu_fatal(15);
    }
}
unsigned long long createReg(){ // Return Semaphore
    if(reg_nHandle.amountUseRegisters != reg_nHandle.amountUseRegisters+1){
        reg_table[reg_nHandle.amountUseRegisters++] = (int)0x000;
        return reg_nHandle.amountUseRegisters;
    }
    else{ // Well That Was Weird...
        if(reg_nHandle.amountRegisters == reg_nHandle.amountUseRegisters){
            if(reg_nHandle.DefaultSize == 4){
                void* failsafe = realloc(reg_table,4*reg_nHandle.amountRegisters+10);
                if(failsafe == NULL){ // Darnit Not Enough Chunk Memory Left In The Data Segment
                    throw_cpu_fatal(15);
                }
                reg_table[reg_nHandle.amountUseRegisters++] = (int)0x000;
                return reg_nHandle.amountUseRegisters;
            }
            if(reg_nHandle.DefaultSize == 8){
                void* failsafe = realloc(reg_table,8*reg_nHandle.amountRegisters+10);
                if(failsafe == NULL){ // Ecalloc Probally Overflowed
                    throw_cpu_fatal(15);
                }
                reg_table[reg_nHandle.amountUseRegisters++] = (int)0x000;
                return reg_nHandle.amountUseRegisters;
            }
        }// Lets Do A RPC?
    }
    return 0;
}
void DelChunk(unsigned long long int chunk_num){
    if(chunk_num > reg_nHandle.amountRegisters){
        throw_cpu_fatal(20);
    }
    else{
        switch(reg_nHandle.DefaultSize){
            case 4:
                realloc(reg_table, (reg_nHandle.amountRegisters-10)*4);
                break;
            case 8:
                realloc(reg_table, (reg_nHandle.amountRegisters-10)*8);
                break;
        }
    }
}
void write_to_dyReg(void** val, unsigned long long int reg_num, char d_type){ // Theres Allot Of Overhead
    switch(d_type){
        case 0:
            if(reg_nHandle.isProtected == 1){
                throw_cpu_fatal(16);
            }
            if(reg_num == reg_nHandle.amountRegisters){
                createReg();
            }
            else{
                reg_table[reg_num] = val;
                type_table[reg_num] = d_type;
            }
    }
}
int read_from_dyReg(unsigned long long int reg_num){ // Returns Struct Access ex 1=int 2=float
    switch(type_table[reg_num]){ // Hotspot Look Here
        case X32_int:
            ret_handle.i_ret = reg_table[reg_num];
            return X32_int;
        case X64_int:
            ret_handle.li_ret = reg_table[reg_num];
            return X64_int;
        case float_is:
            ret_handle.f_ret = *(float*)reg_table[reg_num];
            return float_is;
    }
}
void cpy(unsigned long long int src_reg_num, unsigned long long int dest_reg_num, char type){
    if(dest_reg_num > reg_nHandle.amountRegisters){
        throw_cpu_fatal(20);
    }
    else{
    reg_table[dest_reg_num] = reg_table[src_reg_num];
    LogDataType(type, dest_reg_num); // If You Log Zero Your A Asshole!!
    }
}
void LoadDataTable(){
    type_table = calloc(sizeof(char),reg_nHandle.amountRegisters);
    if(type_table == NULL){
        throw_cpu_fatal(15);
    }
}
void ResizeDataTable(unsigned long long int size){
    void *nvs = realloc(type_table,size);
    if(type_table == NULL){
        throw_cpu_fatal(15);
    }
}
void LogDataType(char data_type, long long unsigned int Pos){
    type_table[Pos] = data_type;
}
void AutoLogDataType(char data_type){
    type_table[reg_nHandle.amountUseRegisters] = data_type;
}
void createChunk(){
    reg_nHandle.amountRegisters+10;
    switch(reg_nHandle.DefaultSize){
        case 4:
            realloc(reg_table,4*10);
            break;
        case 8:
            realloc(reg_table,8*10);
            break;
    }
}