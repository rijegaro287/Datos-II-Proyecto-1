#include <json/json.h>
#include "Memory/MemoryPool.h"
#include "VariableManager.h"
#include "Communication/HTTPServer.h"
#include <list>


using namespace std;
int main(){
//  HTTPServer *mserver = HTTPServer::createServer(9090);

    Json::Value jsonObject;
    jsonObject["nombre"] = "num";
    jsonObject["valor"] = 635;
    jsonObject["tipoDeDato"] = "int";
    std::string jsonString = VariableManager::jsonToString(jsonObject);
    VariableManager::getInstance()->createVariable(jsonString);

    VariableManager::getInstance()->updateScopes("{");


    Json::Value jsonObject2;
    jsonObject2["nombre"] = "num2";
    jsonObject2["valor"] = 635;
    jsonObject2["tipoDeDato"] = "int";
    std::string jsonString2 = VariableManager::jsonToString(jsonObject2);
    VariableManager::getInstance()->createVariable(jsonString2);


    VariableManager::getInstance()->updateScopes("}");

    Json::Value jsonObject1;
    jsonObject1["nombre"] = "pointer0";
    jsonObject1["tipoDeReferencia"] = "int";
    jsonObject1["tipoDeDato"] = "referencia";
    jsonObject1["espacioEnMemoriaDeTipoDeReferencia"] = 4;
    jsonObject1["valor"] = "num";
    std::string jsonString1 = VariableManager::jsonToString(jsonObject1);
    VariableManager::getInstance()->createVariable(jsonString1);



}