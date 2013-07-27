//
//  smm_main.c
//  NSVM
//
//  Created by Noah Whiteis on 1/13/13.
//  Copyright (c) 2013 Noah Whiteis. All rights reserved.
//

#include <stdio.h>
#include "processorMain.h"
typedef struct {
    int master_cpu_mode;
    int cpu_count;
    int is_running;
}m_mode;
m_mode m_handle;
void** vdma;

void start_cpu(int targetArch, int mode){
    vdma = p_getPtrToMem();
}   
void add_cpu(int mode){
    
}
void reset(){
    
}
void cycle(int desired_cpu){
    while(m_handle.is_running==1){
        
    }
}