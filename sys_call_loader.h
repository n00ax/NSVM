//
//  sys_call_loader.h
//  NSVM
//
//  Created by Noah Whiteis on 1/21/13.
//  Copyright (c) 2013 Noah Whiteis. All rights reserved.
//

#ifndef NSVM_sys_call_loader_h
#define NSVM_sys_call_loader_h

void RequestDirectCall(int lib_handle , int return_type,const char *func,void *a, void *b, void *c, void *d,
                       void *e,void *f);
void LoadLib(const char *p_path);
int get_return_int();
long long int get_return_int64();
unsigned int get_return_uint();
unsigned long long int get_return_uint64();
float get_return_float();
char* get_return_charptr();
#endif

