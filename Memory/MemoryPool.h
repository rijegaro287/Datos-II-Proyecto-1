//
// Created by yordi on 28/3/21.
//

#ifndef DATOS_II_PROYECTO_1_SERVIDOR_MEMORYPOOL_H
#define DATOS_II_PROYECTO_1_SERVIDOR_MEMORYPOOL_H

#include "MemoryBlock.h"
#include "MemoryNode.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>


/**
 * @file MemoryPool.h
 * @brief Creacion y gestion de la memoria
 * @version 1.0
 * @date 20/04/2021
 * @author Yordi Brenes
 * @title Memory Pool
 */

    static const std::size_t DEFAULT_MEMORY_POOL_SIZE = 1000;                          //Bytes de memomoria default
    static const std::size_t DEFAULT_MEMORY_NODE_SIZE = 10;                           //Tamaño default de cada nodo de momoria
    static const std::size_t DEFAULT_MEMORY_SIZE_TO_ALLOCATE =
            DEFAULT_MEMORY_NODE_SIZE * 2;

class MemoryPool : public MemoryBlock {
    private:
        static MemoryPool* memoryPool;
        MemoryNode *ptrFirstNode;  //Puntero al primer nodo de memoria (puntero del malloc inicial).
        MemoryNode *ptrLastNode;   //Puntero al último nodo de memoria.
        MemoryNode *ptrCursorNode; // Cursor-Node. Para agilizar el desplazamiento por la lista
        std::size_t totalMemoryPoolSize;  //Memoria Total del MemoryPool
        std::size_t usedMemoryPoolSize;   //Memoria usada
        std::size_t freeMemoryPoolSize;   //Memoria libre
        std::size_t memoryNodeSize;     //Memoria por nodo
        unsigned int memoryNodeCount;  //Numero de nodos de momoria en el memori pool
        unsigned int objectCount;       //Numero de objetos en el memory pool (#getMemory()-#freeMemory())
        bool setMemoryData;              //Si es igual al true, al alocar o delocar setea la memoria a un valor definido (Para debugging)

        /**
        * @brief Ejecuta el malloc() inicial y ajusta los valores iniciales de memoria.
        * @param MemorySize
        * @return
        */
        bool allocateMemory(const std::size_t &MemorySize);
        /**
         * @brief Libera toda la memoria almacenada.
         */
        void freeAllAllocatedMemory();
        /**
         * @brief Calcula el numero de nodos necesarios para almacenar
         * un cierto espacio en memoria.
         * @param MemorySi-ze Espacio en memoria (en bytes) que se va a almacenar.
         * @return Número de nodos.
         */
        unsigned int calculateNeededNodes(const std::size_t &MemorySize);
        /**
         * @brief Calcula: (# nodos necesarios) * (tamaño de cada nodo).
         * @param RequestedMemoryBlockSize Número de nodos necesarios.
         * @return Resultado del cálculo (# nodos necesarios) * (tamaño de cada nodo).
         */
        std::size_t calculateBestMemoryBlockSize(const std::size_t &RequestedMemoryBlockSize);
        /**
         * @brief Recorre la lista de MemoryNodes en busca de el nodo que
         * pueda almacenar la memoria recibida.
         * @param MemorySize Tamaño de memoria (en bytes) que se quiere almacenar.
         * @return MemoryNode* que puede almacenar el espacio en memoria.
         */
        MemoryNode *findNodeSuitableToHoldMemory(const std::size_t &MemorySize);
        /**
         * @brief Recorre el nodo en busca del nodo que tenga el puntero recibido.
         * @param ptrMemoryBlock Puntero de nodo que se desea encontrar.
         * @return MemoryNode* con el puntero de entrada.
         */
        MemoryNode *findNodeHoldingPointerTo(void *ptrMemoryBlock);
        /**
         * @brief Omite cierto numero de MemoryNodes. Recibe un  y el
         * @param ptrStartNode Puntero de MemoryNode
         * @param NodesToSkip Número de MemoryNodes a omitir.
         * @return El MemoryNode* siguiente a los omitidos.
         */
        MemoryNode *skipNodes(MemoryNode *ptrStartNode, unsigned int NodesToSkip);
        /**
         * @brief Establece los valores predetermandos al MemoryNode de entrada.
         * @param ptrNode MemoryNode*.
         * @return MemoryNode*.
         */
        MemoryNode *setNodeDefaults(MemoryNode *ptrNode);
        /**
         * @brief Libera la memoria del MemoryPool.
         * @param ptrNode MemoryNode*
         */
        void freeNodes(MemoryNode *ptrNode);
        /**
         * @brief Libera los MemoryNodes de memoria
         */
        void deallocateAllNodes();
        /**
         * @brief Vincula los bloques de memoria con los MemoryNodes.
         * @param ptrNewNodes El puntero del espacio almacenado para los MemoryNode.
         * @param NodeCount Número de nodos que se crearán.
         * @param ptrNewMemBlock Puntero del malloc de memoria inicial.
         * @return
         */
        bool linkNodeToData(MemoryNode *ptrNewNodes, unsigned int NodeCount, TByte *ptrNewMemBlock);
        /**
         * @brief Asigna los valores a un MemoryNode.
         * @param ptrNode Puntero del MemoryNode.
         * @param MemBlockSize Porción de momoria usada.
         */
        void setMemoryNodeValues(MemoryNode *ptrNode, const std::size_t &MemBlockSize);
        /**
         * @brief Calcula y asigna el valor de espacio de memoria de cada nodo.
         * @param ptrNodes
         * @param NodeCount
         * @return verdadero si no hubo ningún problema.
         */
        bool recalcNodeMemorySize(MemoryNode *ptrNodes, unsigned int NodeCount);
    public:

        MemoryPool(const std::size_t &MemoryPoolSize = DEFAULT_MEMORY_POOL_SIZE,
                   const std::size_t &MemoryNodeSize = DEFAULT_MEMORY_NODE_SIZE,
                   const std::size_t &MinimalMemorySizeToAllocate = DEFAULT_MEMORY_SIZE_TO_ALLOCATE,
                   bool SetMemoryData = false);
        virtual ~MemoryPool();
        /**
         * @brief Devuelve la instancia única de MemoryPool.
         * @return La instancia de la clase MemoryPool.
         */
        static MemoryPool* getInstance();
        /**
        * @brief Almacena un espacio en memoria del tamaño del parametro de entrada.
        * @param sMemorySize Tamaño de memoria en bytes que se almacena.
        * @return El puntero vacio que apunta al espacio almacenado
        */
        virtual void* getMemory(const std::size_t &MemorySize);
        /**
        * @brief Libera la memoria almacenada.
        * @param ptrMemoryBlock Puntero que apunta al esapacio
        * alamcenado que se va a liberar.
        */
        virtual void freeMemory(void *ptrMemoryBlock);
        /**
        * @brief Libera el espacio en todos los MemoryNodes.
        */
        void setAllNodesEmpty();
};

#endif //DATOS_II_PROYECTO_1_SERVIDOR_MEMORYPOOL_H
