//
//  sys_call_loader.c
//  NSVM
//
//  Created by Noah Whiteis on 1/18/13.
//  Copyright (c) 2013 Noah Whiteis. All rights reserved.
//

#include <unistd.h>
#include <dlfcn.h>
#include <stdio.h>
#include "cpu_exception_handler.h"
/*Note This Is Not Standard But Uses POSIX System
 Calls To Load The Shared Libs
 */
typedef struct{
    int table_count;
    int func_count;
    unsigned long long int return_uval64;
    unsigned int return_uval_32;
    long long int return_val64;
    int returnval_32;
    float returnval_float;
    char *returnval_char;
    void **anon_return_val;
}sys_call_info;
void *lib_table[100];
int (*func_table32S[1000])();
sys_call_info d_lib_info;

void LoadLib(const char *p_path){
    lib_table[d_lib_info.table_count] = dlopen(p_path, RTLD_NOW);
    if(lib_table[d_lib_info.table_count]==NULL){
        throw_cpu_fatal(19);
    }
    d_lib_info.table_count++;
}
// Request A Function Call By Looking Up The Symbol
int RequestFunction(char* function, int arguments[], int Dll, int ReturnType){ // Well Just Request A System Image Symbol Lookup
    d_lib_info.func_count++;
    switch(ReturnType){
        case 132: // Signed 32 Bit
            
            break;
        case 164: // Unsigned 64 Bit
            
            break;
        case 32: // Signed 32 Bit
            
            break;
        case 64: // Signed 64 Bit
            break;
            
        case 200: // Float
            break;
    }
    return d_lib_info.func_count;
} // Returns Semaphore
void RequestDirectCall(int lib_handle , int return_type,const char *func,void *a, void *b, void *c, void *d,
                       void *e,void *f){
    int (*func_direct) (void* a, void* b, void* c, void* d, void* e, void* f, ...) = NULL;
    long long int(*func_direct_a)(void *a, void *b, void *c, void *d, void *e, void *f, ...);
    unsigned int (*func_direct_b)(void *a, void *b, void *c, void *d, void *e, void *f, ...) ;
    unsigned long long int(*func_direct_c)(void *a, void *b, void *c, void *d, void *e, void *f, ...);
    float (*func_direct_d)(void *a, void *b, void *c, void *d, void *e, void *f, ...);
    char* (*func_direct_e)(void *a, void *b, void *c, void *d, void *e, void *f, ...);
    void* (*func_direct_f)(void *a, void *b, void *c, void *d, void *e, void *f, ...);
    switch(return_type){
        case 1: // Signed Int
            func_direct = dlsym(lib_table[lib_handle], func);
            d_lib_info.returnval_32 = (*func_direct)(a,b,c,d,e,f);
            break;
        case 2: // Signed x64 Int
            func_direct_a = dlsym(lib_table[lib_handle], func);
            d_lib_info.return_val64 = (*func_direct_a)(a,b,c,d,e,f);
            break;
        case 3: // Unsigned Int
            func_direct_b = dlsym(lib_table[lib_handle], func);
            d_lib_info.return_uval_32 = (*func_direct_b)(a,b,c,d,e,f);
            break;
        case 4: // Unsigned x64 Int
            func_direct_c = dlsym(lib_table[lib_handle], func);
            d_lib_info.return_uval64 = (*func_direct_c)(a,b,c,d,e,f);
            break;
        case 5: // float
            func_direct_d = dlsym(lib_table[lib_handle], func);
            d_lib_info.returnval_float = (*func_direct_d)(a,b,c,d,e,f);
            break;
        case 6:
            func_direct_e = dlsym(lib_table[lib_handle], func);
            *d_lib_info.returnval_char = (*func_direct)(a,b,c,d,e,f);
            break;
        case 7:
            func_direct_f = dlsym(lib_table[lib_handle], func);
            d_lib_info.anon_return_val = (func_direct)(a,b,c,d,e,f);
            break;
        default:
            throw_cpu_fatal(19);
            break;
    }
}
void ReuseSemaphores(int Semaphore, int arguments[]){ // Just Reuse The Function
    
}
int get_return_int(){
    return d_lib_info.returnval_32;
}
long long int get_return_int64(){
    return d_lib_info.return_val64;
}
unsigned int get_return_uint(){
    return d_lib_info.return_uval_32;
}
unsigned long long int get_return_uint64(){
    return d_lib_info.return_uval64;
}
float get_return_float(){
    return d_lib_info.returnval_float;
}
char* get_return_charptr(){
    return d_lib_info.returnval_char;
}