#include <Hermes.h>

int main(int argc, char *argv[]) {
    std::filesystem::path configPath = std::filesystem::current_path();
    configPath.append("data/hermes_config.yaml");

    HMS::Server server(configPath.c_str());
    server.run();
}
