//
//  MaxArray.m
//  Algorithms
//
//  Created by lva on 4/27/18.
//  Copyright © 2018 Pandora. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "MaxArray.hpp"

// MARK: main

void mainArray()
{
    size_t SIZE = 20;
    
    Array<int> a(SIZE, [](int& v)->void{
        static const long Baundry = 100;
        v  = ( rand() + time(nullptr) ) % Baundry;
        v *= ( rand() + time(nullptr) ) % 2 ? +1 : -1;
    });
    
    printf("A: ");
    a.Foreach( [](int& v)->void{
        printf("%d ", v);
    } );
    printf("\n");
}

// EOF
















