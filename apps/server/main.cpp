#include <hv/TcpServer.h>
#include <entt/entt.hpp>
#include <thread>
#include <concurrentqueue.h>
#include <thread>

struct ClientInput
{
    uint64_t client_id;
};

class GameLoop
{
public:
    GameLoop() {
        thread = std::jthread([this](std::stop_token st){run(st);});
    }

private:
    std::jthread thread;

    void run(std::stop_token st) {

    }
};

class NetIO
{
    //NetIO(moodycamel::ConcurrentQueue<> queue) {

    //}
};

class Server
{
public:
    Server() {

    }

    void start() {

    }
private:
    hv::TcpServer server;
    entt::registry entities;
};

int main() {
    Server server;

    return 0;
}
