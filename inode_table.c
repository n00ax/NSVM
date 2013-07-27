//
//  inode_table.c
//  NSVM
//
//  Created by Noah Whiteis on 1/3/13.
//  Copyright (c) 2013 Noah Whiteis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "cpu_exception_handler.h"
#include "processorMain.h"
char *page_table;
typedef struct{
    unsigned int DSOffset;
    unsigned int ISOffset;
    unsigned int RODSOffset;
    unsigned int DSOPos;
    unsigned int ISPos;
    unsigned int RODSPos;
    unsigned int PageCounter;
    unsigned int TotalPagesSize;
}page_data;
page_data page_handle;
void build_table(float size){
    page_table = malloc(sizeof(char)*size);
    page_handle.TotalPagesSize = size;
}
void realloc_page_add(float size){
    if(size > page_handle.TotalPagesSize){
        throw_cpu_fatal(14);
    }
    else{
        realloc(page_table, size);
        if(page_table == NULL){
            throw_cpu_fatal(15);
        }
        resize_down(size);
    }
}
void realloc_page_remove(unsigned int size){
    realloc(page_table,size);
    resize_down(size);
}
void setDSSegmentPos(unsigned int offset){
    page_handle.DSOffset = offset;
    page_table[offset] = 126;
}
void setISSegmentPos(unsigned int pos, unsigned int offset){
    page_handle.RODSOffset = offset;
    page_table[page_handle.DSOffset+1] = 127;
}
void setRODSSegmentPos(unsigned int pos, unsigned int offset){ //DNO (DO NOT USE) * For Now *
    page_handle.ISOffset = offset;
    page_table[page_handle.RODSOffset+1] = 128;
}
void register_type_manual(char type, unsigned int mem_pos){
    switch(type){
        case 1: // Type 4 Byte Int
            page_table[mem_pos] = (char)1;
            break;
        case 2: // Type 8 Byte Int
            page_table[mem_pos] = (char)2;
            break;
        case 3: // Type 4 Byte Float
            page_table[mem_pos] = (char)3;
            break;
        case 4: // Type 8 Byte Float
            page_table[mem_pos] = (char)4;
            break;
        case 5: // Type 2 Byte Short
            page_table[mem_pos] = (char)5;
            break;
        case 6: // Type 1 Bit Boolean
            page_table[mem_pos] = (char)3;
            break;
    }
}
void register_type(char type){
    switch(type){
        case 4: // Type 4 Byte Int Or Float
            page_table[page_handle.PageCounter] = (char)1;
            break;
        case 8: // Type 8 Byte Int Or Float
            page_table[page_handle.PageCounter] = (char)2;
            break;
        case 2: // Type 2 Byte Short
            page_table[page_handle.PageCounter] = (char)5;
            break;
        case 1: // Type 1 Bit Boolean
            page_table[page_handle.PageCounter] = (char)6;
            break;
    }
}
int check_Memory(int Pos, char dataType){
    if((page_table[Pos] != dataType)){
        throw_cpu(2);
        return 0;
    }
    if((Pos > page_handle.TotalPagesSize)){
        throw_cpu_fatal(2);
        return 0;
    }
    return 1;
        
}
void cleanup_inode_table(){
    free(page_table);
}