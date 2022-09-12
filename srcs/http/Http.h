#pragma once

#include <string>

#define CR                  (char) '\r'
#define LF                  (char) '\n'
#define CRLF                "\r\n"
#define CRLF_LEN            2
#define DELIMITERS          " \f\n\r\t\v" /// from std::isspace

#define CONTENT_LENGTH "content-length"

#define TRANSFER_ENCODING "transfer-encoding"
#define CHUNKED "chunked"

#define HOST "host"

#define CONNECTION "connection"
#define KEEP_ALIVE "keep-alive"

#define CLOSE "close"
#define TIMEOUT "timeout"

#define COOKIE "cookie"

namespace Http {

    class Header {
    public:
        Header(const std::string& key, const std::string& value)
                : key(key), value(value) {}

        std::string key;
        std::string value;
    };

    enum Method {
        UNKNOWN = 0,
        GET,
        HEAD,
        POST,
        DELETE,
        PUT,
        CONNECT,
        OPTIONS,
        TRACE,
        PATCH
    };

    enum Version {
        Http1_0 = 0,
        Http1_1,
    };

    enum Code {
        OK = 200,
        BadRequest = 400,
        NotFound = 404,
        MethodNotAllowed = 405,
        LengthRequired = 411,
        PayloadTooLarge = 413,
        InternalServerError = 500,
        NotImplemented = 501,
        HttpVersionNotSupported = 505,
    };

    Method GetMethod(const std::string& method);

    const std::string& ToString(Http::Version http_version);
}
