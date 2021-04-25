#include <json/json.h>
#include "Memory/MemoryPool.h"
#include "VariableManager.h"
#include "Communication/HTTPServer.h"


using namespace std;
int main(){
//  HTTPServer *mserver = HTTPServer::createServer(9999);

    Json::Value jsonObject;
    jsonObject["variables"][0]["nombre"] = "num2";
    jsonObject["variables"][0]["valor"] = "h";
    jsonObject["variables"][0]["tipoDeDato"] = "char";

    jsonObject["variables"][1]["nombre"] = "num1";
    jsonObject["variables"][1]["valor"] = 89;
    jsonObject["variables"][1]["tipoDeDato"] = "int";

    jsonObject["variables"][2]["nombre"] = "num4";
    jsonObject["variables"][2]["valor"] = 34;
    jsonObject["variables"][2]["tipoDeDato"] = "long";
    jsonObject["nombreDeStruct"] = "estructura";
    std::string jsonString = VariableManager::jsonToString(jsonObject);

    VariableManager::getInstance()->createStruct(jsonString);
    std::cout<<MemoryPool::getInstance()->ObjectCount<<std::endl;

    Json::Value jsonObject1;
    jsonObject1["nombre"] = "num1";
    jsonObject1["nombreDeStruct"] = "estructura";
    std::string jsonString1 = VariableManager::jsonToString(jsonObject1);
    VariableManager::getInstance()->getStructAttribute(jsonString1);



}