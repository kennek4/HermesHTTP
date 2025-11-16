#pragma once

#include "socket/HMS_Socket.h"
#include <charconv>
#include <format>

namespace HMS {
namespace HTTP {

enum class RequestMethod {
    NOT_SUPPORTED,
    GET,
    POST,
};

enum class Code {
    OK                 = 200,
    NO_CONTENT         = 204,
    BAD_REQUEST        = 400,
    UNAUTHORIZED       = 401,
    FORBIDDEN          = 403,
    NOT_FOUND          = 404,
    METHOD_NOT_ALLOWED = 405
};

enum class ContentType {
    APPLICATION_JSON,
    TEXT_CSS,
    TEXT_CSV,
    TEXT_HTML,
    TEXT_PLAIN,
    TEXT_XML,
};

template <typename K, typename V, std::size_t N> struct ConstexprMap {
    std::array<std::pair<K, V>, N> data;
    constexpr V at(const K &key) const {
        for (const auto &pair : data) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw std::out_of_range("Not a valid key!");
    }
};

constexpr ConstexprMap<Code, const char *, 7> CodeToString =
    ConstexprMap<Code, const char *, 7> {{{
        {Code::OK, "200 OK"},
        {Code::NO_CONTENT, "204 No Content"},
        {Code::BAD_REQUEST, "400 Bad Request"},
        {Code::UNAUTHORIZED, "401 Unauthorized"},
        {Code::FORBIDDEN, "403 Forbidden"},
        {Code::NOT_FOUND, "400 Not Found"},
        {Code::METHOD_NOT_ALLOWED, "405 Method Not Allowed"},
    }}};

constexpr ConstexprMap<ContentType, const char *, 6> ContentTypeToString =
    ConstexprMap<ContentType, const char *, 6> {{{
        {ContentType::APPLICATION_JSON, "application/json"},
        {ContentType::TEXT_CSS, "text/css"},
        {ContentType::TEXT_CSV, "text/csv"},
        {ContentType::TEXT_HTML, "text/html"},
        {ContentType::TEXT_PLAIN, "text/plain"},
        {ContentType::TEXT_XML, "text/xml"},
    }}};

struct Request {
    RequestMethod method;
    std::string url;
};

struct Content {
    const char *data;
    uint32_t length;
};

struct Response {
    Code code;
    ContentType contentType;
    Content content;

    std::string toString() {
        std::string resp;

        resp += std::format("HTTP/1.1 {}\r\n", CodeToString.at(this->code));
        resp += std::format("Content-Type: {}\r\n",
                            ContentTypeToString.at(this->contentType));
        resp += std::format("Content-Length: {}\r\n\r\n", this->content.length);
        resp += content.data;

        return resp;
    };
};

Request getRequest(std::string &&rl);

void handleConnection(const Socket &server, const Socket &client);
void sendResponse(const Socket &server, const Socket &client);
} // namespace HTTP
}; // namespace HMS
