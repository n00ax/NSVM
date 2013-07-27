//
//  ex_file_loader.c
//  NSVM
//
//  Created by Noah Whiteis on 1/5/13.
//  Copyright (c) 2013 Noah Whiteis. All rights reserved.
//

#include <stdio.h>
#include "processorMain.h"
#include "nef_interpreter.h"

//This Is All Standard Code
FILE* file_ptr;
void loadPsF(char* path[]){
    printf("WE READ");
    file_ptr = fopen(*path,"rb");
    fseek(file_ptr,0L,SEEK_END);
    long f_size = ftell(file_ptr);
    fseek(file_ptr, 0L, SEEK_SET);
    void* prog_mem = malloc(sizeof(int)*f_size);
    fread(prog_mem, 4, f_size, file_ptr);
    parse_header(prog_mem);
}
void loadPsM(int* memory[]){
    
}
void dyLoad(int pageSize){
    printf("NSVM Dynamic Instruction Loader (32Bit) 0.01");
    int cur_instruction = 0;
    void **header;
    header = malloc(sizeof(int)*100);
    int hp_data[] = {
        0xface,0x302E3130,0x20000000,0x00,0x00,/*Free*/0x7e,0xa,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    };
    for(int i=0; i < 99; i++){
        header[i] = hp_data[i];
    }
    int P_data_offset = 0;
    int I_data_offset = 0;
    printf("First Config\n");
    printf("Enter Data Page Offset:");
    scanf("%d",&P_data_offset);
    printf("\n");
    printf("Enter Instruction Page Offset:");
    scanf("%d",&I_data_offset);
    printf("\n");
    header[6] = P_data_offset;
    header[6+P_data_offset+1] = 0x7f;
    header[6+P_data_offset+2] = I_data_offset;
    while(1){
        printf(":>");
        scanf("%d",&cur_instruction);
        parse_header(header);
        printf("\n");
    }
    DumpCPU('1');
}
/*64 Bit Implementation */

void loadPsF64(char* path[]){
    file_ptr = fopen(*path,"rb");
    fseek(file_ptr,0L,SEEK_END);
    long f_size = ftell(file_ptr);
    fseek(file_ptr, 0L, SEEK_SET);
    void* prog_mem = malloc(sizeof(long long)*f_size);
    fread(prog_mem, 8, f_size, file_ptr);
    parse_header(prog_mem);
}
void loadPsM64(int* memory[]){
    
}
void dyLoad64(int pageSize){
    
}
