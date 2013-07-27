//
//  processorMain.h
//  NSVM
//
//  Created by Noah Whiteis on 12/31/12.
//  Copyright (c) 2012 Noah Whiteis. All rights reserved.
//

#ifndef NSVM_processorMain_h
#define NSVM_processorMain_h

void InitCPU(short Arch, int StackSize, int HeapSize);
void DumpCPU(char Report);
void movtr(void* val1, int registernum);
void resize_down(unsigned int size_down);
void** p_getPtrToMem();
void **p_heap;
int getr();
void DumpCPU(char Report);
#endif

