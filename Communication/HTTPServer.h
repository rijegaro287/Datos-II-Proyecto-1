#pragma once
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "MemoryManagement/VariableManager.h"

#define log(msg) std::cout << msg << std::endl
/**
 * @file HTTPServer.h
 * @brief Controla la comunicación IDE-Server.
 * @version 1.0
 * @date 20/04/2021
 * @author Yordi Brenes
 * @title HTTPServer
 */
using namespace Pistache;
class HTTPServer
{
public:
    static HTTPServer* createServer(int port);
private:
    std::shared_ptr<Http::Endpoint> httpEndpoint;
    Rest::Router router;
    static int port;
    explicit HTTPServer(Address addr) : httpEndpoint(std::make_shared<Http::Endpoint>(addr)){}
    void init(size_t thr = 1);
    void start();
    void setupRoutes();
    /**
     * @brief conexionInicial Ruta para verificar la conexion entre el cliente y el servidor.
     * @param request
     * @param response
     */
    void conexionInicial(const Rest::Request &request, Pistache::Http::ResponseWriter response);

    /**
     * @brief crearVariable Ruta para crear variables de datos primitivos y  referencias.
     * @param request
     * @param response
     */
    void crearVariable(const Rest::Request &request, Pistache::Http::ResponseWriter response);
    /**
     * @brief devolverVariable Ruta para buscar el valor almacenado de una variable.
     * @param request
     * @param response
     */
    void devolverVariable(const Rest::Request &request, Pistache::Http::ResponseWriter response);
    /**
     * @brief crearStruct Ruta para crear variables struct.
     * @param request
     * @param response
     */
    void crearStruct(const Rest::Request &request, Pistache::Http::ResponseWriter response);
    /**
     * @brief asignarDireccion Ruta para asignar una dirección a un puntero.
     * @param request
     * @param response
     */
    void asignarDireccion(const Rest::Request &request, Pistache::Http::ResponseWriter response);
    /**
     * @brief desreferenciarPuntero Ruta para obtener el valor al que apunta una referencia.
     * @param request
     * @param response
     */
    void desreferenciarPuntero(const Rest::Request &request, Http::ResponseWriter response);

    /**
     * @brief actualizarScopes Ruta para crear o eliminar un scope.
     * @param request
     * @param response
     */
    void actualizarScopes(const Rest::Request &request, Http::ResponseWriter response);

    /**
     * @brief actualizarValorVariable Ruta para actualizar el valor de una variable.
     * @param request
     * @param response
     */
    void actualizarValorVariable(const Rest::Request &request, Http::ResponseWriter response);

    /**
     * @brief retornarDireccion Ruta que devuelve la dirección de una dato almacenado.
     * @param request
     * @param response
     */
    void retornarDireccion(const Rest::Request &request, Http::ResponseWriter response);

    /**
     * @brief finalizarEjecucion Ruta para finalizar la ejecucion y eliminar toda la memoria
     * almacenada en el MemoryPool.
     * @param request
     * @param response
     */
    void finalizarEjecucion(const Rest::Request &request, Http::ResponseWriter response);

    void retornarTimeline(const Rest::Request &request, Http::ResponseWriter response);
    /**
     * @brief retornarAtributoDeStruct Ruta para retornar el valor de
     * un atributo perteneciente a un struct.
     * @param request
     * @param response
     */
    void retornarAtributoDeStruct(const Rest::Request &request, Http::ResponseWriter response);

    void finalizarOverview(const Rest::Request &request, Http::ResponseWriter response);
};