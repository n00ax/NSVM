//
//  cpu_exception_handler.c
//  NSVM
//
//  Created by Noah Whiteis on 1/10/13.
//  Copyright (c) 2013 Noah Whiteis. All rights reserved.
//

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
char *runMessages[] = {
    "VM Fatal! Error CODE:0001","VM Page Violation Error CODE:0002","VM Page Type Violation Error Code 0003",
    "VM Unknown Instruction Error CODE:0004","VM Stack Memory Reference Error CODE:0005",
    "VM Heap Memory Reference Error CODE:0006","VM NSF Loader Header Not Found? Error Code 0007",
    "VM Code Segment Not Aligned Properly Error CODE:0008","VM Data Segment Not Aligned Properly Error CODE:0009",
    "VM Read Only Segment Not Aligned Properly Error CODE:0010","VM Read Only Segment Write Attempt Error Code:0011","VM Execution Code Segment Write Violation Error CODE:0012", "VM Warning Resizing Heap Downward Can Result In Data Loss Error CODE:0013", "NSVM Was Unable To Reallocate The Data Section! Error CODE:0014","VM Could Not Allocate Dynamic Register Properly ERROR 'SIZE NOT VALID 4? 8? Error Code:0015","VM Could Not Allocate Dynamic Register Properly ERROR 'Calloc,Realloc' Failed Error Code:0016","VM Could Not Write Unmarked Data To Dynamic Register In Protected Mode Error Code:0017","Unrecognized Register NOP Sled Detected Stopping Error Code:0018", "Failed TO Load Shared Libary Error Code:0019","Failed To Load Shared Function Or Header Error Code:0020", "Requested Dynamic Register Does Not Exist? Error Code 0021",
};

void throw_cpu_fatal(int errorCode){
    printf("\n****** A Fatal Error Has Occoured ******\n");
    printf("%s\n",runMessages[errorCode]);
    printf("The Heap And Stack Probally Have Already Been Dumped!\n");
    printf("Heap And Stack Trace Are Being Worked On\n");
    printf(":( Bye!\n");
    printf("****** End Error Trace Exception *******\n");
    raise(4);
}

void throw_cpu(int errorCode){
    printf("Runtime Error:<\n");
    printf("%s\n",runMessages[errorCode]);
}
void break_p(){
    printf("Break called (Warning Please Use Signals)\n");
    raise(4);
}