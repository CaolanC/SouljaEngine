#include <hv/HttpServer.h>
#include <entt/entt.hpp>
#include <thread>
#include <concurrentqueue.h>
#include <thread>
#include <iostream>
#include <chrono>
#include <future>
#include <mutex>
using namespace std::chrono;
using namespace std::chrono_literals;

using RequestID = uint64_t;

typedef enum {
    JoinRequest
} NetMsgType;

struct NetMsg
{
    uint64_t id;
};

template <typename T>
class Bridge
{
    moodycamel::ConcurrentQueue<T> queue;
};

class NetworkBus
{
public:
    NetworkBus() {
    
    }

    unsigned int send_in(NetMsg msg) {
        msg.id = next_id;
        in_q.enqueue(msg);

        return next_id++;
    }

    void try_get_in(NetMsgType type) {
        // in_queue.try_dequeue();
    }


    int get_next_id() {
        return next_id;
    }

    moodycamel::ConcurrentQueue<NetMsg> out_q;
    moodycamel::ConcurrentQueue<NetMsg> in_q;
private:
    unsigned int next_id{1};

};

void sleep(const int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

typedef enum {
    Join
} NetMessage;

class ReplyPayload
{
public:
    ReplyPayload(NetMsgType type) : type(type) {

    }

    NetMsgType type;
};

class JoinReplyPayload : ReplyPayload
{
public:
    JoinReplyPayload() : ReplyPayload(JoinRequest) {

    }
};

class NetIO
{
public:
    NetIO(int port, NetworkBus& bus) : port(port), bus(bus) {

    }

    ~NetIO() {
        running = false;
        thr_webserver.join();
    }

    void start() {
        setup_routes();
        server = hv::HttpServer(&router);
        server.setPort(port);
        server.setThreadNum(4);
        thr_webserver = std::jthread([this](std::stop_token st){async_run(st);});
        thr_reply_dispatch = std::jthread(
            [this](std::stop_token st) {async_reply_dispatcher();
            
            }
        );

        running = true;
    }

    void stop() {
        server.stop();
    }

private:
    std::jthread thr_reply_dispatch, thr_webserver;
    hv::HttpServer server;
    hv::HttpService router;
    int listenfd;
    int port;
    bool running = false;
    NetworkBus& bus;
    std::unordered_map<RequestID, std::promise<JoinReplyPayload>> waiting_joiners;
    std::mutex req_prom_mut;
    std::atomic<int> req_id{1};

    void async_run(std::stop_token st) {
        server.run();
    }

    void setup_routes() {
        router.GET("/ping", [](HttpRequest* request, HttpResponse* response) {
            return response->String("pong :D");
        });

        router.GET("/join", [this](HttpRequest* request, HttpResponse* response) {

            std::promise<JoinReplyPayload> promise;
            auto fut = promise.get_future();

            {
                //std::lock_guard(req_prom_mut);
                waiting_joiners.emplace(req_id, std::move(promise));
                req_id++;
            }

            bus.send_in(NetMsg{});

            if (fut.wait_for(3s) == std::future_status::ready) {

            }
            return response->String("Server side error joining the server.");
        });
    }

    void async_reply_dispatcher() {

    }
};

class Scene
{
    entt::registry entities;
};

class NetFilter
{

};

class Server
{
public:
    Server(int port) :  port(port), io(port, bus) {

    }

    void start() {
        io.start();
        thr_bus = std::jthread([this](std::stop_token st) {
                circulate_messages(st);
            }
        );
    }

    void stop() {
        io.stop();
    }

private:
    NetworkBus bus = NetworkBus();
    entt::registry registry;
    NetIO io;
    int port;
    std::jthread thr_bus;

    void circulate_messages(std::stop_token st) {
        while(!st.stop_requested()) {
            int dispatches = 0;
            const int max_dispatches = 120;
            NetMsg msg;
            while(dispatches < max_dispatches && bus.in_q.try_dequeue(msg)) {
                std::cout << msg.id << '\n';
                dispatches++;
            }
            std::this_thread::sleep_for(5ms);
        }
    }
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

    SessionManager(NetworkBus& bus) : bus(bus) {

    }

    ~SessionManager() {
        running = false;
        thread.join();
    }
private:

    void start() {
        thread = std::jthread([this]{run_async();});
    }

    void run_async() {
        running = true;
        while (running) {
            std::this_thread::sleep_for(1s);
        }
    }

    NetworkBus& bus;
    std::vector<Session> sessions;
    std::jthread thread;
    bool running = true;
};

int start_game() {
    Server server(30000);
    server.start();
    const duration tick = nanoseconds(16'666'667); // Number in of nanoseconds in 1/60th of a second
    const duration physics_tick = nanoseconds(0); // Need to find a good physics tick
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
            //std::cout << "Tick: " << tick_count  << "\n";
            tick_count++;
        }
    };

    std::this_thread::sleep_for(tick - accumulator);

    return 0;
}

int main() {
    return start_game();
}
