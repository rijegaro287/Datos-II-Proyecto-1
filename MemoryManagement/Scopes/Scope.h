//
// Created by yordi on 29/3/21.
//

#ifndef DATOS_II_PROYECTO_1_SERVIDOR_SCOPE_H
#define DATOS_II_PROYECTO_1_SERVIDOR_SCOPE_H

#include "Node.h"
#include "Memory/MemoryPool.h"
#include <string>
#include <iostream>
#include <cassert>
#include <json/value.h>

/**
 * @file MemoryManagement.h
 * @brief Almacenage y gestion de nodes Node.
 * @version 1.0
 * @date 27/04/2021
 * @author Yordi Brenes
 * @title MemoryManagement
 */
class Scope{
private:
    Node *head;
    int length;
    /**
     * @brief Elimina un node Node del MemoryManagement.
     */
    void deleteNode(Node*);
public:
    /**
     * @brief Constructor de MemoryManagement
     */
    Scope();
    /**
     * @brief Agrega una nueva variable
     * @param ptr Puntero que apunta al espacio en memoria.
     * @param varType Tipo de dato.
     * @param varName Nombre de la variable.
     */
    void add(void* ptr, std::string varType, std::string varName);
    /**
     * @brief Agrega un struct a un scope
     * @param ptr Puntero que apunta al espacio en memoria.
     * @param varType Tipo de dato.
     * @param structName Nombre de la estructura a la que pertenece
     */
    void addStruct(void* ptr, std::string varType, std::string, std::string structName);
    /**
     * @brief Agrega una variable de un nodo a un scope.
     * @param pVoid ptr Puntero que apunta al espacio en memoria.
     * @param dataType Tipo de dato.
     * @param name Nombre de variable.
     * @param pointerType Tipo de puntero.
     */
    void addPointer(void *pVoid, std::string dataType, std::string name, std::string pointerType);
    /**
     * @brief Borra el nodo en la posición recibida.
     * @param pos Posicion que eliminar
     */
    void deleteInPos(int pos);
    /**
     * @brief Libera el espacio de todas las variable en el MemoryPool y
     * elimina todos los elementos del scope.
     * @return Objeto json con el nombre de las variables alamcenadas.
     */
    Json::Value freeAllMemory();
    /**
     * @brief Busca un nodo Node el el scope.
     * @param varName Nombre de la variable.
     * @return nodo Node.
     */
    Node* searchNode(std::string varName);
    /**
     * @brief Busca un nodo Node en el scope
     * @param ptrNode puntero en el que se almacena el dato almaceado.
     * @return nodo Node.
     */
    Node* searchNode(void* ptrNode);
    /**
     * @brief Imprime el nombre de las variables almacenadas en el scope.
     */
    void print();
    /**
     * @brief Retorna el largo del scope
     * @return Largo
     */
    int getLength();
    /**
     * Retorna el nodo denominado head.
     * @return Nodo Node head.
     */
    Node *getHead() const;
    /**
     * @brief Busca un nodo Node perteneciente a un struct.
     * @param structName Nombre del struct
     * @param name nombre de variable
     * @return
     */
    Node *searchNodeOfStruct(std::string structName, std::string name);
};


#endif //DATOS_II_PROYECTO_1_SERVIDOR_SCOPE_H
