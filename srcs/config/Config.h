#pragma once

#include "Http.h"
#include "utilities.h"

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#define WEBSERVER_NAME "Webserver-42"

#define DEFAULT_MAX_SESSIONS_NUMBER 1024
#define DEFAULT_READ_BUFFER_SIZE 4096

#define DEFAULT_SESSION_KILLER_DELAY 2 // 2 seconds
#define DEFAULT_CORE_TIMEOUT 1 // 1 seconds

#define DEFAULT_MAX_BODY_SIZE 100000000 // 100 MB
#define DEFAULT_MAX_REQUEST_SIZE 200000000 // 200 MB

#define DEFAULT_KEEP_ALIVE_TIMEOUT 60 // 60 seconds
#define DEFAULT_MAX_KEEP_ALIVE_TIMEOUT 1800 // 30 minutes
#define DEFAULT_HANG_SESSION_TIMEOUT 10 // 10 seconds

struct Location {
    Location(std::string location, std::string root,
             bool autoindex, std::string index,
             std::unordered_set<Http::Method> available_methods,
             std::string redirect);

    const std::string location;

    const std::string root;

    const std::string full_path;

    const bool autoindex;

    const std::string index;

    const std::unordered_set<Http::Method> available_methods;

    const std::string redirect;
};

struct ServerConfig {
    ServerConfig(std::string name, std::string host, unsigned short port,
                 const std::unordered_map<unsigned int, std::string>& error_pages, int max_body_size,
                 int max_request_size,
                 int default_keep_alive_timeout_s, int max_keep_alive_timeout_s,
                 const std::vector<std::shared_ptr<Location>>& locations);

    std::string name;

    const std::string host;

    const unsigned short port;

    std::unordered_map<unsigned int, std::string> error_pages;

    unsigned int max_body_size;

    unsigned int max_request_size;

    unsigned int default_keep_alive_timeout_s;

    unsigned int max_keep_alive_timeout_s;

    std::vector<std::shared_ptr<Location>> locations;
};

/// servers with the same host:port
class EndpointConfig {
public:
    EndpointConfig(std::string host, unsigned short port, std::vector<std::shared_ptr<ServerConfig>> servers);

    [[nodiscard]] std::shared_ptr<ServerConfig> GetServerByNameOrDefault(const std::string& name) const;

    [[nodiscard]] std::shared_ptr<ServerConfig> GetDefaultServer() const;

    const std::string host;

    const unsigned short port;

    const std::vector<std::shared_ptr<ServerConfig>> servers; /// the first one is default

};

class Config {
public:
    Config(unsigned int max_sessions_number,
           unsigned int read_buffer_size,
           unsigned int sessions_killer_delay_s,
           unsigned int hang_session_timeout_s,
           const std::vector<std::shared_ptr<EndpointConfig>>& endpoint_configs);

    const unsigned int max_sessions_number;

    const unsigned int read_buffer_size;

    const unsigned int sessions_killer_delay_s;

    const unsigned int hang_session_timeout_s;

    const std::vector<std::shared_ptr<EndpointConfig>> endpoint_configs;
};

/// TODO check if order stays during reading json
/// TODO check redirect behaviare
/// error not Allow если к недопустимому методу 
/// name для location обязательный?
/// проверить root and location in subject