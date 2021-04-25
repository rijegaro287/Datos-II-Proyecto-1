//
// Created by yordi on 29/3/21.
//

#ifndef DATOS_II_PROYECTO_1_SERVIDOR_NODE_H
#define DATOS_II_PROYECTO_1_SERVIDOR_NODE_H

//template <typename T>

#include <string>
#include <json/value.h>

class Node{
private:
    std::string dataType;   //Tipo de dato
    std::string variableName;  //Nombre de la variable
    std::string structName;
    std::string pointerType;  //Nombre de la estructura a la que pertenece (si pertenece)
    int referenceCount;    // Conteo de referencias
    void* ptr;             //Puntero al dato almacenado
public:
    Node *next;
    Node(){
        referenceCount = 0;
        next = 0;
        ptr = nullptr;
    }
    Node* getNext(){return next;}
    void setNext(Node* nodo){ next = nodo;}
    void* getPointer(){return ptr;}
    void setPtr(void* ptr){ Node::ptr = ptr;}
    std::string getVariableType() const {return dataType;}
    void setDataType(std::string varType) { Node::dataType = varType;}
    const std::string &getVariableName() const {return variableName;}
    void setVariableName(const std::string &varName) { Node::variableName = varName;}
    void setStructName(std::string structName) {
        Node::structName= structName;
    }

    const std::string &getDataType() const {
        return dataType;
    }

    void setPointerType(std::string pointerType) {
        Node::pointerType = pointerType;
    }

    const std::string &getPointerType() const {
        return pointerType;
    }
    void setPointerPointer(void* pVoid){
        if (pointerType == "")
            perror("Puntero sin tipo, tal vez esta variable no sea un puntero");
        *((void**)ptr) = pVoid;
    }
    void* getPointerPointer(){
        if(pointerType=="")
            perror("Puntero sin tipo, tal vez esta variable no sea un puntero");
        void* pVoid = *(void**)ptr;
        return pVoid;
    }

    int getReferenceCount() const {
        return referenceCount;
    }

    void increaseCount(){
        referenceCount++;
    }

    void decreaseCount(){
        referenceCount--;
        if(referenceCount < 0){
            perror("Conteo de referencias negativas");
        }
    }

    void setPointerValue(Json::Value jsonObject){
        if(dataType == "int"){
            int value = jsonObject.get("valor", "ValueError").asInt();
            (*(int*)ptr) = value;
        }else if (dataType == "char") {
            std::string stringChar = jsonObject.get("valor", "ValueError").asString();
            const char *ptrChar = stringChar.c_str();
            char value = *ptrChar;
            (*(char*)ptr) = value;
        }else if (dataType == "long"){
            long value = jsonObject.get("valor", "ValueError").asLargestInt();
            (*(long*)ptr) = value;
        }else if (dataType == "float"){
            float value = jsonObject.get("valor", "ValueError").asFloat();
            (*(float*)ptr) = value;
        }else if (dataType == "double"){
            double value = jsonObject.get("valor", "ValueError").asDouble();
            (*(double*)ptr) = value;
        }
    }

    const std::string &getStructName() const {
        return structName;
    }
};
#endif //DATOS_II_PROYECTO_1_SERVIDOR_NODE_H

