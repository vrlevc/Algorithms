//
//  main.m
//  Algorithms
//
//  Created by lva on 3/10/18.
//  Copyright © 2018 Pandora. All rights reserved.
//

#define TEST_MATRIX     0

#import <Foundation/Foundation.h>

#if TEST_MATRIX
#include "Matrix.hpp"
#endif//TEST_MATRIX

int main(int argc, const char * argv[])
{
    
#if TEST_MATRIX
    mainMatrix();
#endif//TEST_MATRIX
    
    return 0;
}


























