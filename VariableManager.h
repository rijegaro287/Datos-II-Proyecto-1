//
// Created by yordi on 29/3/21.
//

#ifndef DATOS_II_PROYECTO_1_SERVIDOR_VARIABLEMANAGER_H
#define DATOS_II_PROYECTO_1_SERVIDOR_VARIABLEMANAGER_H

#include <list>
#include "Scope/Scope.h"
#include <json/json.h>
#include "Communication/HTTPServer.h"

class VariableManager {
    private:
        Scope* mainScope;
        VariableManager();
        static std::list<Scope *> scopes;
        static VariableManager* variableManager;
        static std::string jsonToString(Json::Value);
        static Json::Value stringToJson(std::string);
        void endScope();
        void newScope();
        static void add(void*, std::string, std::string);
        void addStruct(void*, std::string, std::string, std::string);
//        Node* searchNode(std::string variableName);
        static void* assignPointer(std::string, Json::Value);
    public:
        static Node* searchNode(std::string varName);
        static VariableManager* getInstance();
        static std::string createVariable(std::string);
        std::string returnVariableValue(std::string);
        std::string createStruct(std::string);

    static void addPointer(void *ptr, std::string basicString, std::string basicString1, std::string basicString2);
};



#endif //DATOS_II_PROYECTO_1_SERVIDOR_VARIABLEMANAGER_H
