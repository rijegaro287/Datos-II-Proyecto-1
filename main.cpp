#include <json/json.h>
#include "Memory/MemoryPool.h"
#include "Scope/VariableManager.h"
#include "Communication/HTTPServer.h"
#include <list>


using namespace std;
int main(){
  HTTPServer *mserver = HTTPServer::createServer(9090);
}