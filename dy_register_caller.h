//
//  dy_register_caller.h
//  NSVM
//
//  Created by Noah Whiteis on 1/27/13.
//  Copyright (c) 2013 Noah Whiteis. All rights reserved.
//

#ifndef NSVM_dy_register_caller_h
#define NSVM_dy_register_caller_h

void CreateRegTable(unsigned long long chunks, char typeSize);
unsigned long long createReg();
void write_to_dyReg(void** val, unsigned long long int reg_num, char d_type);
int read_from_dyReg(unsigned int reg_num);
void LoadDataTable();
void ResizeDataTable(unsigned long long int size);
void LogDataType(char data_type, long long unsigned int Pos);
void AutoLogDataType(char data_type);
void cpy(unsigned long long int src_reg_num, unsigned long long int dest_reg_num, char type);
void createChunk();

#endif
