//
//  preint.c
//  NSVM
//
//  Created by Noah Whiteis on 1/8/13.
//  Copyright (c) 2013 Noah Whiteis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preint_info.h"
#include "ex_file_loader.h"

typedef struct{
    short arch_type;
    short endian_ness;
    short vm_mode;
    short sh_counter;
}arguments;
void preint(int argc, char **argv){
    arguments arg_struct;
    /*All The Argument Processing Stuff*/
    for(int i=0; i < argc-1; i++){
        arg_struct.sh_counter++;
        if(strcmp(argv[i],"-64")){
            arg_struct.arch_type = 64;
        }
        if(strcmp(argv[i],"-le")){
            arg_struct.endian_ness = LITTLE_ENDIAN;
        }
        if(strcmp(argv[i],"-be")){
            arg_struct.endian_ness = BIG_ENDIAN;
        }
        if(strcmp(argv[i],"-32")){
            arg_struct.arch_type = 32;
        }
        if(strcmp(argv[i],"-u")){
            arg_struct.vm_mode = 2;
        }
    }
    /*Argument Processing Done*/
    printf("%s %s\n",vm_name, version);
    if(isLocked==1){
        printf("Status:%s\n",vm_lsc); //Locked
    }
    if(isLocked==2){
        printf("Status:%s\n",lvm_ulsc); //Unlocked
    }
    if(isLocked==3){
        printf("Status:%s\n",uvm_ulsc); //Debug
    }
    printf("%s",vm_copyinfo);
    printf("%s",vm_copyright);
    printf("%s",vm_engineering);
    printf("%s\n",vm_warrent);
    printf("Using Built In NEF Intrepter....");
    char* filepath[] = {"helloworld"};
    dyLoad(0);
    return;
    
}