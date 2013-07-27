//
//  nef_interpreter.c
//  NSVM
//
//  Created by Noah Whiteis on 1/6/13.
//  Copyright (c) 2013 Noah Whiteis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "processorMain.h"
#include "sys_call_loader.h"
#include "inode_table.h"
enum machine_state{
    UPDATE, NORMAL, DEBUG_VM,PROTECTED, REAL, UNLOCK, FAIL
};
typedef struct{
    int arch;
    int endianType;
    int topHeader;
    int vmMode;
    int instructionVersion;
    int ProtectionMode;
    int IsFailed;
    int top_signature_succeeded;
    int bottom_signature_succeeded;
    int d_offset;
    int i_offset;
    int rd_offset;
    int DataIdentifer;
    int RODataIdentifer;
    int InstructionIdentifer;
    /*Unlock Code 1*/
    int UnlockCodePar1;
    int UnlockCodePar2;
    /*Unlock Code 1*/
    /*Unlock Code 2*/
    int UnlockCode2Par1;
    int UnlockCode2Par2;
    /*Unlock Code 2*/
    
}nef_data;
// vmmode 1=normal 2=update 3=unlock 4=debug
/*Special Unlock Codes*/
long long UnlockCodePar1 = 1;
long long UnlockCodePar2 = 1;
long long UnlockCode1Par1 = 1;
long long UnlockCode1Par2 = 1;
/*Special Unlock Codes*/
nef_data *nef_head;
void **s_head;
void ***memoryptr;
void parse_header(void** data_segment){
    nef_head = (nef_data*)malloc(sizeof(nef_data));
    switch((int)data_segment[0]){
        case 64206:
            nef_head->topHeader = (int)data_segment[0];
            nef_head->vmMode = NORMAL;
            break;
        case 0xcafe:
            nef_head->vmMode = UPDATE;
        case 0xcab:
            nef_head->vmMode = REAL;
        default:
            nef_head->vmMode = FAIL;
            break;
    }
    nef_head->DataIdentifer = 0x7E;
    nef_head->RODataIdentifer =  0x7F;
    nef_head->InstructionIdentifer = 0x80;
    switch((int)data_segment[1])
    {
        case 0x302E3130:
            // 0.1
            break;
        default:
            // I Dont Recoginze Any Other Version
            break ;
    }
    switch((int)data_segment[2]){
        case 0x40000000:
            //64Bit
            nef_head->arch = 0x400000;
            break;
        case 0x20000000:
            //32Bit
            nef_head->arch = 0x200000;
            break;
        default:
            // What The Fuck! 128? 225?
            break;
    }
    switch((unsigned long)data_segment[3]){ // 4
            case 80305197:
            nef_head->top_signature_succeeded=1;
            break;
            case 0:
            nef_head->top_signature_succeeded=0;
            break;
    }
    switch((unsigned long)data_segment[3]){
            case 80305197:
            nef_head->bottom_signature_succeeded =1;
            break;
            case 0:
            nef_head->bottom_signature_succeeded =0;
            break;
    }
    switch((unsigned long)data_segment[4]){
        case 2:
            if(nef_head->top_signature_succeeded == 1 && nef_head->bottom_signature_succeeded == 1){
                nef_head->vmMode = UPDATE;
            }
            break;
        case 1:
            nef_head->vmMode = NORMAL;
            break;
    }
    switch(nef_head->vmMode){
        case NORMAL: // Normal
            
            break;
        case UPDATE: // Update
            
            break;
        case DEBUG_VM: // Unlock
            
            break;
        case UNLOCK: // Debug
            
            break;
    }
    switch((unsigned long)data_segment[5]){ // 7-8-9
        case 0x7E: // Data Segment Identifer
            nef_head->i_offset = ((int)data_segment[6]);
            nef_head->d_offset = (((int)data_segment[nef_head->i_offset+7]));
            build_table(20000);
            // Ignore The 9th Number *Its Magical*
            if(nef_head->arch == 0x200000){
                InitCPU(1, 1, 1);
                memoryptr = p_getPtrToMem();
            }
            if(nef_head->arch == 0x400000){
                InitCPU(1, 1, 1);
                memoryptr = p_getPtrToMem();
            }
            for(int i=0 ; i < nef_head->i_offset; i++){
                if(i==0){
                    setISSegmentPos(0, nef_head->i_offset);
                    memoryptr[0] = (void**)0x7E;
                    memoryptr[1] = (void**)nef_head->i_offset;
                }
                else{
                register_type_manual(sizeof(data_segment[5+i]),
                                        5+i);
                memoryptr[i] = data_segment[i+5];
                }
            }
            break;
    }
    switch((unsigned long)data_segment[nef_head->i_offset+7]){
        case 0x7f:
            for(int i=0 ; i < nef_head->d_offset; i++){
                if(i==0){
                    setDSSegmentPos(nef_head->d_offset);
                    memoryptr[nef_head->i_offset+1] = (void**)0x7f;
                    memoryptr[nef_head->i_offset+2] = data_segment[nef_head->i_offset];
                    
                    // Let Captian Noah Log A Entry In The Virtual MU Segment Table arghhhhh...
                }
                else{
                    register_type_manual(sizeof(data_segment[5+nef_head->i_offset+i]),
                                         nef_head->i_offset+i);
                    memoryptr[nef_head->i_offset+i] = data_segment[5+nef_head->i_offset+i];
                }
            }
            break;
    }
    switch((unsigned long)data_segment[nef_head->i_offset+6]){
        //Lets Run Through The CheckList For Launch Houstin
    }
    
    LoadLib("libbasicIONative.dylib"); // This Is Hardcoded But Can Be Changed
    /* Lets Begin The Loading Cycle */
    if(nef_head->vmMode == UPDATE){
        printf("Update Mode Initated!"); // I Hear You Loud And Clear
        if(nef_head->vmMode == NORMAL){
            // Shhhh... Be Quiet!
        }
        if(nef_head->vmMode == REAL){
            
        }
}
}
