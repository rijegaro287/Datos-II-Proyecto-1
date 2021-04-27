

#ifndef DATOS_II_PROYECTO_1_SERVIDOR_NODE_H
#define DATOS_II_PROYECTO_1_SERVIDOR_NODE_H

//template <typename T>

#include <string>
#include <json/value.h>
#include <list>
#include <iostream>


/**
 * @file Node.h
 * @brief Clase que almacena las caracateristicas de
 * las variables. Pertenece a los scopes.
 * @date 27/04/2021
 * @version 1.0
 * @author Yordi Brenes
 * @tittle Node
 */
class Node{
private:
    std::string dataType;   //Tipo de dato
    std::string variableName;  //Nombre de la variable
    std::list<std::string> structName;
    std::string pointerType;  //Nombre de la estructura a la que pertenece (si pertenece)
    int referenceCount;    // Conteo de referencias
    int usageCount;
    void* pointer;             //Puntero al dato almacenado
public:
    Node *next;
    /**
     * @brief Constructor de la clase Node
     */
    Node(){
        referenceCount = 0;
        next = 0;
        usageCount = 0;
        pointer = nullptr;
    }
    /**
     * @brief Devulve el puntero al siguiente Node.
     * @return El puntero al siguiente nodo Node.
     */
    Node* getNext(){return next;}
    /**
     * @brief Establecer el puntero al siguiente nodo Node.
     * @param nodo Puntero de Node.
     */
    void setNext(Node* nodo){ next = nodo;}
    /**
     * Devuelve el puntero almacenado.
     * @return Puntero almacenado.
     */
    void* getPointer(){return pointer;}
    /**
     * @brief Establece el valor del puntero almcenado.
     * @param ptr Puntero por almacenar
     */
    void setPointer(void* ptr){ Node::pointer = ptr;}
    /**
     * @brief Retorna el tipo de dato almacenado.
     * @return Tipo de dato almacenado
     */
    std::string getDataType() const {return dataType;}
    /**
     * @brief Establecer el tipo de dato almacenado.
     * @param varType Tipo de dato.
     */
    void setDataType(std::string varType) { Node::dataType = varType;}
    /**
     * @brief Retorna el nombre de la variable.
     * @return Nombre de la variable
     */
    const std::string &getVariableName() const {return variableName;}
    /**
     * @brief Establece el nombre de la variable.
     * @param varName Nombre de la variable.
     */
    void setVariableName(const std::string &varName) { Node::variableName = varName;}
    /**
     * @brief Agrega el nombre de un struct.
     * @param structName Nombre de struct.
     */
    void setStructName(std::string structName) {
        Node::structName.push_front(structName);
    }
    /**
     * @brief Retorna los nombres de struct a las que pertence
     * @return Nombres de structs.
     */
    const std::list<std::string> &getStructName() const {
        return Node::structName;
    }
    /**
     * @brief Establece el tipo de puntero
     * @param pointerType Tipo de puntero
     */
    void setPointerType(std::string pointerType) {
        Node::pointerType = pointerType;
    }
    /**
     * @brief Retorna el tipo de puntero.
     * @return Tipo de puntero
     */
    const std::string &getPointerType() const {
        return pointerType;
    }
    /**
     * @brief Establecer el puntero al que apunta un puntero.
     * @param pVoid Puntero al que apuntar
     */
    void setPointerPointer(void* pVoid){
        if (pointerType == "")
            perror("Puntero sin tipo, tal vez esta variable no sea un puntero");
        *((void**)pointer) = pVoid;
    }
    /**
     * @brief Retornar el puntero al que apunta un puntero.
     * @return Puntero al que apunta un puntero
     */
    void* getPointerPointer(){
        if(pointerType=="")
            perror("Puntero sin tipo, tal vez esta variable no sea un puntero");
        void* pVoid = *(void**)pointer;
        return pVoid;
    }
    /**
     * @brief Retorna el conteo de referencias que apuntan a esa variable.
     * @return Numero de referencias.
     */
    int getReferenceCount() const {
        return referenceCount;
    }
    /**
     * @brief Aumenta el contador de referencias.
     */
    void increaseReferenceCount(){
        referenceCount++;
    }
    /**
     * @brief Disminuye el contador de referencias.
     */
    void decreaseReferenceCount(){
        referenceCount--;
        if(referenceCount < 0){
            perror("Conteo de referencias negativas");
        }
    }

    int getUsageCount() const {
        return usageCount;
    }
    void increaseUsagesCount(){
        usageCount++;
    }
    void decreaseUsagesCount(){
        usageCount++;
        if(usageCount < 0) {
            std::cout << "algo anda mal, numero de usos negativos" << std::endl;
        }
    }

    /**
     * @brief Cambia el valor al que apunta el puntero del Node.
     * @param jsonObject Objeto json con el valor nuevoy el tipo de dato.
     */
    void setPointerValue(Json::Value jsonObject){
        if(dataType == "int"){
            int value = jsonObject.get("valor", "ValueError").asInt();
            (*(int*)pointer) = value;
        }else if (dataType == "char") {
            std::string stringChar = jsonObject.get("valor", "ValueError").asString();
            const char *ptrChar = stringChar.c_str();
            char value = *ptrChar;
            (*(char*)pointer) = value;
        }else if (dataType == "long"){
            long value = jsonObject.get("valor", "ValueError").asLargestInt();
            (*(long*)pointer) = value;
        }else if (dataType == "float"){
            float value = jsonObject.get("valor", "ValueError").asFloat();
            (*(float*)pointer) = value;
        }else if (dataType == "double"){
            double value = jsonObject.get("valor", "ValueError").asDouble();
            (*(double*)pointer) = value;
        }
    }

};
#endif //DATOS_II_PROYECTO_1_SERVIDOR_NODE_H

