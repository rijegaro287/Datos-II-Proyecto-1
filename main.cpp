#include <json/json.h>
#include "Memory/MemoryPool.h"
#include "VariableManager.h"
#include "Communication/HTTPServer.h"


using namespace std;
int main(){
//  HTTPServer *mserver = HTTPServer::createServer(9999);

    Json::Value jsonObject;
    jsonObject["nombre"] = "num";
    jsonObject["valor"] = 23.23;
    jsonObject["tipoDeDato"] = "float";
    std::string jsonString = VariableManager::jsonToString(jsonObject);
    VariableManager::getInstance()->createVariable(jsonString);

    jsonObject["nombre"] = "num";
    VariableManager::getInstance()->returnVariableValue(jsonString);



}