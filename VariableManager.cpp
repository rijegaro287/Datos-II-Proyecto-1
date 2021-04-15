//
// Created by yordi on 29/3/21.
//

#include "VariableManager.h"

/*
 * Gestiona la creacion y eliminación de scopes y sus variables.
 * Procesa lo que recibe la clase Socket.
 * FALTA:
 *      -Almacenar punteros y structs.
 *      -Identificar erroes.
 *      -Enviar mensajes de error por medio de la clase Socket.
 */

VariableManager* VariableManager::variableManager = nullptr;
std::list<Scope *> VariableManager::scopes;

VariableManager::VariableManager() {
    Scope* list = new Scope();
    scopes.push_front(list);
    mainScope = scopes.front();
}

VariableManager* VariableManager::getInstance() {
    if(variableManager == nullptr){
        variableManager = new VariableManager();
    }
    return variableManager;
}

/*
 * Añade una variable nueva al scope
 */
void VariableManager::add(void* ptr, std::string dataType,std::string varName) {
    Scope* list = scopes.front();
    list->add(ptr, dataType, varName);
}

/*
 * Elimina el scope más reciente
 */
void VariableManager::endScope(){
    Scope* lastScope = scopes.front();
    lastScope->freeAllMemory();
    if (lastScope != mainScope){
        delete lastScope;
        scopes.pop_front();
    }
}

/*
 * Crea un Scope
 */
void VariableManager::newScope() {
    Scope* list = new Scope();
    scopes.push_front(list);
}

/*
 * Busca un Node con el mismo nombre de variable que el de entreada.
 * Recorre todos los scopes hasta encontrarlo. Si no encuentra la variable
 * devuleve un nullptr.
 * FALTA:
 *      -Que el problema verifique si el nodo es nulo y envié
 *      un error al IDE.
 */
Node* VariableManager::searchNode(std::string varName) {
    Node* nodo = nullptr;
    for (auto list : scopes){
        nodo = list->searchNode(varName);
        if (nodo)
            break;
    }
    return nodo;
}


/*
 * Gestiona lo que recibe el socket. Recibe objetos Json y
 * los añade a un scope. De momento crea variables.
 * Falta:
 *      -Guardar datos tipo long.
 *      -Gestionar pedidos de variables existentes.
 *      -Gestionar pedidos de creación y cierre de scopes.
 *      -Gestionar pedidos de creacion de punteros y structs.
 */
std::string VariableManager::createVariable(std::string jsonString) {
    Json::Value jsonObject = stringToJson(jsonString);

    std::string name = jsonObject.get("nombre", "noName").asString();
    std::string dataType = jsonObject.get("tipoDeDato", "typeError").asString();
    int memorySize = jsonObject.get("espacioEnMemoriaDeTipoDeReferencia", "typeError").asInt();

    void* ptr;
    //Verifica si la variable es un puntero
    if(dataType == "referencia"){
        std::string pointerType = jsonObject.get("tipoDeReferencia", "typeError").asString();
        void *IDEpointer = MemoryPool::getInstance()->GetMemory(memorySize);
        ptr = MemoryPool::getInstance()->GetMemory(4);
        *(void**)ptr = IDEpointer;

        addPointer(ptr,dataType, name, pointerType);
    }else {
        //Asigna al valor un puntero disponible
        ptr = assignPointer(dataType, stringToJson(jsonString));
    }

    add(ptr,dataType, name);

    Json::Value jsonVariable;
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    jsonVariable["direccion"] = addr;
    return jsonToString(jsonVariable);
}

std::string VariableManager::jsonToString(Json::Value jsonObject) {
    Json::FastWriter writer;
    std::string jsonString = writer.write(jsonObject);
    std::cout << jsonString << std::endl;
    return jsonString;
}

std::string VariableManager::returnVariableValue(std::string jsonString) {
    Json::Value jsonRequest = stringToJson(jsonString);
    std::string variableName = jsonRequest.get("nombre", "valueError").asString();
    Node* variableNode = searchNode(variableName);
    if(!variableNode) {
        perror("Variable Value Error");
        return "Variable Value Error";
    }
    Json::Value jsonVariable;
    jsonVariable["type"] = variableNode->getVariableType();
    uintptr_t addr = reinterpret_cast<uintptr_t>(variableNode->getPointer());
    std::cout << addr << std::endl;
    jsonVariable["direccion"] = addr;
    if(variableNode->getVariableType() == "int"){
        int* p =(int*) variableNode->getPointer();
        jsonVariable["value"] = *p;
    }else if (variableNode->getVariableType() == "char"){
        char* p =(char*) variableNode->getPointer();
        jsonVariable["value"] = *p;
    }else if (variableNode->getVariableType() == "long"){
        long* p =(long*) variableNode->getPointer();
        jsonVariable["value"] = *p;
    }else if (variableNode->getVariableType() == "float"){
        float* p =(float*) variableNode->getPointer();
        jsonVariable["value"] = *p;
    }else if (variableNode->getVariableType() == "double"){
        double* p =(double*) variableNode->getPointer();
        jsonVariable["value"] = *p;
    }
    std::cout << jsonVariable << std:: endl;
    return jsonToString(jsonVariable);
}

Json::Value VariableManager::stringToJson(std::string jsonString) {
    Json::Reader reader;
    Json::Value jsonObject;
    bool parsingSuccessful = reader.parse(jsonString, jsonObject, false);
    if (!parsingSuccessful){
        perror("stringToJson");
    }
    return jsonObject;
}

void *VariableManager::assignPointer(std::string dataType, Json::Value jsonObject) {
    void* ptr;
    if(dataType == "int"){
        int value = jsonObject.get("valor", "ValueError").asInt();
        ptr = MemoryPool::getInstance()->GetMemory(4);
        (*(int*)ptr) = value;
    }else if (dataType == "char") {
        std::string stringChar = jsonObject.get("valor", "ValueError").asString();
        const char *ptrChar = stringChar.c_str();
        char value = *ptrChar;
        ptr = MemoryPool::getInstance()->GetMemory(1);
        (*(char*)ptr) = value;
    }else if (dataType == "long"){
        long value = jsonObject.get("valor", "ValueError").asLargestInt();
        ptr = MemoryPool::getInstance()->GetMemory(4);
        (*(long*)ptr) = value;
    }else if (dataType == "float"){
        float value = jsonObject.get("valor", "ValueError").asFloat();
        ptr = MemoryPool::getInstance()->GetMemory(4);
        (*(float*)ptr) = value;
    }else if (dataType == "double"){
        double value = jsonObject.get("valor", "ValueError").asDouble();
        ptr = MemoryPool::getInstance()->GetMemory(8);
        (*(double*)ptr) = value;
    }
    return ptr;
}

std::string VariableManager::createStruct(std::string jsonString) {
    Json::Value jsonObject = jsonToString(jsonString);
    std::string structName = jsonObject.get("nombre", "noName").asString();
    Json::Value variables = jsonObject["variables"];
    for (int i = 0; i < variables.size(); ++i )
    {
        std::string name = variables[i].get("nombre", "noName").asString();
        std::string dataType = variables[i].get("tipoDeDato", "typeError").asString();
        void* ptr = assignPointer(dataType, variables[i]);
        addStruct(ptr,dataType, name, structName);
    }
    return std::string();
}

void VariableManager::addStruct(void * ptr, std::string dataType, std::string name, std::string structName) {
        Scope* list = scopes.front();
        list->addStruct(ptr, dataType, name, structName);
}

void VariableManager::addPointer(void *ptr, std::string dataType, std::string name, std::string pointerType) {
    Scope* list = scopes.front();
    list->addPointer(ptr, dataType, name, pointerType);
}




