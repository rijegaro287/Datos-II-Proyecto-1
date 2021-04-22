#include <json/json.h>
#include "Memory/MemoryPool.h"
#include "VariableManager.h"
#include "Communication/HTTPServer.h"


using namespace std;
int main(){
    HTTPServer *mserver = HTTPServer::createServer(9999);

//    Json::Value jsonObject;
//    jsonObject["nombre"] = "num";
//    jsonObject["valor"] = "h";
//    jsonObject["tipoDeDato"] = "char";
//    std::string jsonString = VariableManager::jsonToString(jsonObject);
//    VariableManager::getInstance()->createVariable(jsonString);
//
//    Json::Value jsonObject2;
//    jsonObject2["nombre"] = "num1";
//    jsonObject2["valor"] = "h";
//    jsonObject2["tipoDeDato"] = "char";
//    std::string jsonString2 = VariableManager::jsonToString(jsonObject2);
//    VariableManager::getInstance()->createVariable(jsonString2);

//    Json::Value jsonObject3;
//    jsonObject3["nombre"] = "num2";
//    jsonObject3["valor"] = 5435;
//    jsonObject3["tipoDeDato"] = "int";
//    std::string jsonString3 = VariableManager::jsonToString(jsonObject3);
//    VariableManager::getInstance()->createVariable(jsonString3);

//    std::cout<<MemoryPool::getInstance()->ObjectCount << std::endl;

}