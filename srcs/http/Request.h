#pragma once

#include "SharedPtr.h"
#include "Optional.h"
#include "Config.h"

#include <string>
#include <unordered_map>
#include <vector>

typedef std::unordered_map<std::string, std::vector<std::string> >::iterator HeaderIterator;

namespace RequestHandleStatus {
    enum Status {
        Finish = 0,
        WaitMoreData,
    };
}

namespace RequestHandleState {
    enum State {
        HandleFirstLine = 0,
        HandleHeader,
        AnalyzeBodyHeaders,
        HandleChunkSize,
        HandleChunkBody,
        HandleChunkTrailerPart,
        HandleBodyByContentLength,
        WaitData,
        FinishHandle,
    };
}

struct HttpVersion {
    HttpVersion() : major(0), minor(0) {}
    HttpVersion(int major, int minor) : major(major), minor(minor) {}

    int major;
    int minor;
};

struct RequestTarget {
    std::string full_path;
    std::string directory_path;
    std::string file_name;
    std::string extension;
    std::string query_string;
};

class Request {
public:
    Request(const SharedPtr<ServerConfig>& server_config);

    RequestHandleStatus::Status Handle(SharedPtr<std::string> raw_request_part);

    void AddHeader(const std::string& key, const std::string& value);

private:
    RequestHandleState::State ParseFirstLineHandler();

    RequestHandleState::State ParseHeaderHandler();

    RequestHandleState::State ParseChunkSizeHandler();

    RequestHandleState::State ParseChunkBodyHandler();

    RequestHandleState::State ParseChunkTrailerPartHandler();

    RequestHandleState::State ParseBodyByContentLengthHandler();

    RequestHandleState::State AnalyzeHeadersBeforeParseBodyHandler();

public:
    std::string method;

    HttpVersion http_version;

    std::string body;

    /// TODO limit size on this and on headers and on body
    std::string raw;

    std::unordered_map<std::string, std::vector<std::string> > headers;

    SharedPtr<ServerConfig> server_config;

    RequestTarget target;

    Optional<size_t> content_length;

private: /// handle helpers
    RequestHandleState::State _handle_state;

    size_t _handled_size;

    size_t _chunk_body_size;
};
