//
//  inode_table.h
//  NSVM
//
//  Created by Noah Whiteis on 1/5/13.
//  Copyright (c) 2013 Noah Whiteis. All rights reserved.
//

#ifndef NSVM_inode_table_h
#define NSVM_inode_table_h

int check_Memory(int Pos, char dataType);
void register_type(char type);
void register_type_manual(char type, unsigned int mem_pos);
void setISSegmentPos(unsigned int pos, unsigned int offset);
void setDSSegmentPos(unsigned int offset);
void realloc_page_remove(float size);
void realloc_page_add(float size);
void build_table(float size);

#endif
