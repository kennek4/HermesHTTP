#include "HermesHTTP.h"
#include "iostream"
#include <Hermes.h>
#include <functional>

int main(int argc, char *argv[]) {
    HMS::Server server;

    server.run();

    server.stop();
}
