//
//  cpu_exception_handler.h
//  NSVM
//
//  Created by Noah Whiteis on 1/10/13.
//  Copyright (c) 2013 Noah Whiteis. All rights reserved.
//

#ifndef NSVM_cpu_exception_handler_h
#define NSVM_cpu_exception_handler_h

void throw_cpu_fatal(int errorCode);
void throw_cpu(int errorCode);
void break_p();

#endif
