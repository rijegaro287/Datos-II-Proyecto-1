//
// Created by yordi on 29/3/21.
//

#ifndef DATOS_II_PROYECTO_1_SERVIDOR_NODE_H
#define DATOS_II_PROYECTO_1_SERVIDOR_NODE_H

//template <typename T>

#include <string>

class Node{
private:
    std::string dataType; //Tipo de dato
    std::string variableName;  //Nombre de la variable
    std::string structName;  //Nombre de la estructura a la que pertenece (si pertenece)
    void* ptr;             //Puntero al dato almacenado
    Node *next;
public:
    Node(){
        structName = "";
        next = 0;
        ptr = 0;
    }
    Node* getNext(){return next;}
    void setNext(Node* nodo){ next = nodo;}
    void* getPointer(){return ptr;}
    void setPtr(void* ptr){ Node::ptr = ptr;}
    std::string getVariableType() const {return dataType;}
    void setDataType(std::string varType) { Node::dataType = varType;}
    const std::string &getVarName() const {return variableName;}
    void setVariableName(const std::string &varName) { Node::variableName = varName;}
    void setStructName(std::string structName) {
        Node::structName= structName;
    }

    void setPointerType(std::string pointerType) {

    }
};
#endif //DATOS_II_PROYECTO_1_SERVIDOR_NODE_H

