//
//  build_producer.c
//  NSVM
//
//  Created by Noah Whiteis on 1/7/13.
//  Copyright (c) 2013 Noah Whiteis. All rights reserved.
//

#include <stdio.h>
#include <time.h>
typedef struct {
    int isDebug;
    int isFirstBuild;
    int isDevKit;
    unsigned int publicKey;
    unsigned int resKey;
}build_stats;

void ActivateBuild(short BuildType){ // 1 = Restricted 2 = Debug 3 
}
