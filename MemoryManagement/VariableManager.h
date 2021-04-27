#ifndef DATOS_II_PROYECTO_1_SERVIDOR_VARIABLEMANAGER_H
#define DATOS_II_PROYECTO_1_SERVIDOR_VARIABLEMANAGER_H

#include <list>
#include "MemoryManagement/Scopes/Scope.h"
#include <json/json.h>
#include "Communication/HTTPServer.h"

/**
 * @file VariableManager.h
 * @brief Gestión de scopes Scopes y nodos Node
 * @version 1.0
 * @date 27/04/2021
 * @author Yordi Brenes
 * @title Variable Manager
 */
class VariableManager {
    private:
        static VariableManager* variableManager;
        static bool boolOverview;
        static std::list<Scope *> scopes;
        Scope* mainScope;
        /**
         * @brief Contructor de VariableManager.
         */
        VariableManager();
        /**
         * @brief Agrega una variable a un scope.
         * @param ptr Puntero al MemoryPool.
         * @param dataType Tipo de dato.
         * @param variableName Nombre de la variable.
         */
        static void add(void* ptr, std::string dataType, std::string variableName);
        /**
         * @brief Agrega una estructura a un scope.
         * @param ptr Puntero al MemoryPool.
         * @param dataType Tipo de dato.
         * @param variableName Nombre de la variable.
         * @param structName Nombre de la estructura
         */
        void addStruct(void* ptr, std::string dataType, std::string variableName, std::string structName);
        /**
         * @brief Agrega un puntero a un scope
         * @param ptr Puntero al MemoryPool
         * @param dataType Tipo de dato.
         * @param variableName Nombre de variable.
         * @param pointerType Tipo de puntero.
         */
        static void addPointer(void *ptr, std::string dataType, std::string variableName, std::string pointerType);
        /**
         * @brief LLama la funcion freeAllMemory() del scope y luego lo elimina.
         * @return Lista con los nombres de las variables eliminadas
         */
        std::string endScope();
        /**
         * @brief Crea un nuevo scope.
         * @return
         */
        std::string newScope();
        /**
         * @brief Busca un nodo Node en los diferentes scopes.
         * @param ptr Puntero del nodo Node que apunta al espacio en memoria
         * almacenado.
         * @return Nodo
         */
        static Node* searchNode(void* ptr);
        /**
         * @brief Almacena un espacio en memoria.
         * @param dataType Tipo de dato.
         * @param jsonObject Objeto json que contiene el valor
         * @return Puntero que apunta al espacio de memoria.
         */
        static void* allocateValue(std::string dataType, Json::Value jsonObject);
        /**
         * @brief Agrega al scope, un dato primitivo no vinculado a una variable.
         * @param jsonObject Objeto json con el tipo de dato.
         * @return Puntero que apunta al espacio de memoria.
         */
        static void *spaceForPrimitiveData(Json::Value jsonObject);
        /**
         * @brief Devuelve el valor al que apunta un puntero que apunta al
         * MemoryPool.
         * @param jsonObject Objeto json en el que se almacenará el valor.
         * @param variableType Tipo de variable
         * @param pointer Puntero que apunda al dato
         * @return Objeto json con el valor
         */
        static Json::Value getPointerValue(Json::Value jsonObject, std::string variableType, void *pointer);


public:
        /**
         * @brief Devuelve la instancie de VariableManager.
         * @return VariableManager*
         */
        static VariableManager* getInstance();
        /**
         * @brief Busca un nodo Node en los diferentes scopes.
         * @param varName Nombre de la variable.
         * @return Nodo
         */
        static Node* searchNode(std::string varName);
        /**
         * @brief Crea una variable y almacena el valor en el MemoryPool.
         * @param jsonString Objeto json con los datos necesarios para crear la variable
         * @return Objeto json con todos los datos de la variable creada
         */
        static std::string createVariable(std::string jsonString);
        /**
         * @brief Actualiza el valor de una variable.
         * @param jsonString Objeto json con el nombre de la variable y el nuevo valor.
         * @return Objeto json con los datos necesarios para crear la variable.
         */
        std::string updateVariableValue(std::string jsonString);
        /**
         * @brief Retorna el valor de la variable.
         * @return Objeto json con el valor.
         */
        std::string returnVariableValue(std::string);
        /**
         * @brief Crea un struct y almacena el valor en el MemoryPool.
         * @return Objeto json con todos los datos de la variable creada
         */
        std::string createStruct(std::string);
        /**
         * @brief Retorna el valor del atributo de un struct.
         * @param jsonString Nombre del struct y nombre de la variable
         * @return Valor de la variable
         */
        std::string returnStructAttribute(std::string jsonString);
        /**
         * @brief Asigna una direccion a una variable de puntero.
         * @param jsonString objeto json
         * @return objeto json con las direcciones y conteo de referencias de las variables alteradas.
         */
        static std::string assignAddress(std::string jsonString);
        /**
         * @brief Retorna el valor de una variable de puntero.
         * @param jsonString Un objeto json con el nombre del puntero
         * @return Valor del dato apuntado por el puntero
         */
        static std::string dereferencePointer(std::string jsonString);
        /**
         * @brief Retorna la direccion donde se almacena el dato de la variable.
         * @param jsonString Objeto json con el nombre de la variable.
         * @return Objeto json con la direccion
         */
        std::string returnAddress(std::string jsonString);
        /**
         * @brief Convierte un objeto json a su representacion a string
         * @param jsonObject Objeto json
         * @return String de un objeto json
         */
        static std::string jsonToString(Json::Value jsonObject);
        /**
         * @brief Convierte un string a json.
         * @param jsonString string que representa un objeto json
         * @return Objeto json
         */
        static Json::Value stringToJson(std::string jsonString);
        /**
         * @brief Crea o cierra scopes dependiendo del parametro recibido
         * @param scope
         * @return objeto json con la lista de variables eliminadas
         */
        std::string updateScopes(std::string scope);
        /**
         * @brief Elimina todos los scopes y vacía la
         * memoria almacenada del MemoryPool.
         */
        void endRun();

        static std::string updateUsagesCount(Node* node);
        std::string changeBoolOverview(Node *node);
        std::string lookForGarbage();
};



#endif //DATOS_II_PROYECTO_1_SERVIDOR_VARIABLEMANAGER_H
