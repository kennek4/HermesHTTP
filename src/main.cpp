#include <Hermes.h>
#include <HermesHTTP.h>

int main(int argc, char *argv[]) {
    HMS::Server server;
    server.run();
    server.stop();
}
