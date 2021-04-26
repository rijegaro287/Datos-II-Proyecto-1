//
// Created by yordi on 28/3/21.
//

#ifndef DATOS_II_PROYECTO_1_SERVIDOR_MEMORYBLOCK_H
#define DATOS_II_PROYECTO_1_SERVIDOR_MEMORYBLOCK_H


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>

typedef unsigned char TByte;

/**
 * @file MemoryBlock.h
 * @brief Interfaz del MemoryPool
 * @version 1.0
 * @date 20/04/2021
 * @author Yordi Brenes
 * @title Memory Block
 */
class MemoryBlock {
public:
    virtual ~MemoryBlock() {};
    virtual void *getMemory(const std::size_t &sMemorySize) = 0;
    virtual void freeMemory(void *ptrMemoryBlock) = 0;
};


#endif //DATOS_II_PROYECTO_1_SERVIDOR_MEMORYBLOCK_H
