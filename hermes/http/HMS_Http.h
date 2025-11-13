#pragma once

#include "socket/HMS_Socket.h"

namespace HMS {
namespace HTTP {
void processRequest(const Socket &server, const Socket &client);
void sendResponse(const Socket &server, const Socket &client);
} // namespace HTTP
}; // namespace HMS
