//
//  main.m
//  Algorithms
//
//  Created by lva on 3/10/18.
//  Copyright © 2018 Pandora. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "Matrix.hpp"

typedef Matrix<int>         iMatrix;
typedef Matrix<long>        lMatrix;
typedef Matrix<long long>   llMatrix;
typedef Matrix<float>       fMatrix;
typedef Matrix<double>      dMatrix;

auto Randomize100 = [](auto& v)->void
{
    static const long Baundry = 100;
    v = (rand() + time(nullptr)) % Baundry;
    v *=  ( rand() + time(nullptr) ) % 2 ? +1 : -1;
};

auto Print = [](auto& v, int r, int c, int rN, int cN)->void
{
    auto PrintLine = [&cN]()->void { for (int i=0; i<cN; ++i) printf("-------"); printf("\n"); };
    if ( r+c==0 ) PrintLine();
    printf("% 7d", v);
    if ( c==cN-1 ) printf("\n");
    if ( r==rN-1 && c==cN-1 ) PrintLine();
};

int main(int argc, const char * argv[])
{
    iMatrix A(5,5,Randomize100);
    iMatrix B(5,5,Randomize100);
    
    iMatrix C = A * B;
    
    A.foreach(Print);
    printf("  *\n");
    B.foreach(Print);
    printf("  =\n");
    C.foreach(Print);
    
    return 0;
}


























