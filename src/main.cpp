#include <iostream>

#include "Block.h"

int main(){
    Block testBlock(0, 0, "A small step for man.", {"Hello", "World"}, 0.00);
    testBlock.viewBlock();
    return 0;
}