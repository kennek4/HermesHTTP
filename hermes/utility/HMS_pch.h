#pragma once

#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <cassert>
#include <condition_variable>
#include <cstring>
#include <filesystem>
#include <functional>
#include <iostream>
#include <mutex>
#include <netdb.h>
#include <netinet/in.h>
#include <queue>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <tuple>
#include <unistd.h>
#include <utility>

// Extern
#include <yaml-cpp/yaml.h>
