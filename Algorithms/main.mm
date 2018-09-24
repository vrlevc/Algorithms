//
//  main.m
//  Algorithms
//
//  Created by lva on 3/10/18.
//  Copyright © 2018 Pandora. All rights reserved.
//

#define TEST_MATRIX     0
#define TEST_ARRAY      1

#import <Foundation/Foundation.h>

#if TEST_MATRIX
#include "Matrix.hpp"
#endif//TEST_MATRIX

#if TEST_ARRAY
#include "MaxArray.hpp"
#endif//TEST_ARRAY

int main(int argc, const char * argv[])
{
    
#if TEST_MATRIX
    mainMatrix();
#endif//TEST_MATRIX

#if TEST_ARRAY
    mainArray();
#endif//TEST_ARRAY
    
    return 0;
}


























