#include <hv/HttpServer.h>
#include <entt/entt.hpp>
#include <thread>
#include <concurrentqueue.h>
#include <thread>
#include <iostream>
#include <chrono>
#include <future>

void sleep(const int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

typedef enum {
    Join
} NetMessage;

class NetIO
{
public:
    NetIO(int port) {
        _port = port;
    }

    void start() {
        setup_routes();
        server = hv::HttpServer(&router);
        server.setPort(_port);
        server.setThreadNum(4);
        thread = std::jthread([this](std::stop_token st){run(st);});
    }

    void stop() {
        server.stop();
    }

private:
    std::jthread thread;
    hv::HttpServer server;
    hv::HttpService router;
    int listenfd;
    int _port;
    
    void run(std::stop_token st) {
        server.run();
    }

    void setup_routes() {
        router.GET("/ping", [](HttpRequest* request, HttpResponse* response) {
            return response->String("pong :D");
        });

        router.GET("/join", [this](HttpRequest* request, HttpResponse* response) {
            
            handleHttpReq(request, response);
            return response->String("Joining isn't implemented ya nonce.");
        });
    }

    void handleHttpReq(HttpRequest* request, HttpResponse* response) {
        std::promise<HttpResponse*> promise;

    }

    void attempt_join() {
    //    std::chrono::
    }
};

class Scene
{
    entt::registry entities;
};

class Server
{
public:
    Server(int port) :  io(port) {
        _port = port;
    }

    void start() {
        io.start();
    }

    void stop() {
        io.stop();
    }

private:
    entt::registry registry;
    NetIO io;
    int _port;
};

class Session
{
public:
    Session(uint64_t id) : id(id) {

    };

private:
    uint64_t id;
};

class SessionManager
{
private:
    std::vector<Session> sessions;
};

using namespace std::chrono;

int start_game() {
    Server server(30000);
    //server.start();
    const duration tick = nanoseconds(16'666'667); // Number in of nanoseconds in 1/60th of a second
    time_point last = steady_clock::now();

    bool running = true;

    duration accumulator = nanoseconds(0);

    int tick_count = 0;
    while(running) {
        time_point now = steady_clock::now();
        auto frame = now - last;
        last = now;
        accumulator += frame; // Accumulates 

        int updates = 0;
        const int max_updates = 5;
        while(accumulator >= tick && updates < max_updates) {
            updates++;
            accumulator -= tick;
            std::cout << "Tick: " << tick_count  << "\n";
            tick_count++;
        }
    };

    std::this_thread::sleep_for(tick - accumulator);

    return 0;
}

int main() {
    return start_game();
}
