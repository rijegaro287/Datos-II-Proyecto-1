#include <json/json.h>
#include "Memory/MemoryPool.h"
#include "VariableManager.h"
#include "Communication/HTTPServer.h"


using namespace std;
int main(){
//    HTTPServer *mserver = HTTPServer::createServer(9999);

    Json::Value jsonObject;
    jsonObject["nombre"] = "num";
    jsonObject["valor"] = "h";
    jsonObject["tipoDeDato"] = "char";
    std::string jsonString = VariableManager::jsonToString(jsonObject);
    VariableManager::getInstance()->createVariable(jsonString);
    std::cout<<MemoryPool::getInstance()->ObjectCount<<std::endl;

    Node* nodo = VariableManager::searchNode("num");
    std::cout << (*(char*)nodo->getPointer())<< std::endl;

    Json::Value jsonObject2;
    jsonObject2["nombre"] = "num";
    jsonObject2["valor"] = "k";
    std::string jsonString2 = VariableManager::jsonToString(jsonObject2);
    VariableManager::getInstance()->updateVariableValue(jsonString2);

    nodo = VariableManager::searchNode("num");
    std::cout << (*(char*)nodo->getPointer())<< std::endl;



}