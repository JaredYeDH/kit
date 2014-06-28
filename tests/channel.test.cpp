#include <catch.hpp>
#include "../include/kit/channel/taskqueue.h"
#include "../include/kit/channel/channel.h"
#include "../include/kit/channel/multiplexer.h"
using namespace std;

TEST_CASE("Channel","[channel]") {
    SECTION("basic usage"){
        Channel<int> chan;
        REQUIRE(chan.size() == 0);
        chan << 42;
        REQUIRE(chan.size() == 1);
        int num = 0;
        bool b = (chan >> num);
        REQUIRE(b);
        REQUIRE(num == 42);
    }
}

TEST_CASE("TaskQueue","[taskqueue]") {

    SECTION("basic task queue") {
        TaskQueue<void> tasks;
        REQUIRE(!tasks);
        REQUIRE(tasks.empty());
        tasks([]{});
        REQUIRE(!tasks.empty());
    }
        
    SECTION("run_once w/ futures") {
        TaskQueue<int> tasks;
        auto fut0 = tasks([]{
            return 0;
        });
        auto fut1 = tasks([]{
            return 1;
        });
        
        REQUIRE(tasks.size() == 2);
        REQUIRE(tasks);
        
        REQUIRE(fut0.wait_for(std::chrono::seconds(0)) == 
            std::future_status::timeout);

        tasks.run_once();
        
        REQUIRE(fut0.get() == 0);
        REQUIRE(fut1.wait_for(std::chrono::seconds(0)) == 
            std::future_status::timeout);
        REQUIRE(!tasks.empty());
        REQUIRE(tasks.size() == 1);
        
        tasks.run_once();
        
        REQUIRE(fut1.get() == 1);
        REQUIRE(tasks.empty());
        REQUIRE(tasks.size() == 0);
    }

    SECTION("run_all"){
        TaskQueue<void> tasks;
        
        tasks([]{});
        tasks([]{});
        tasks([]{});
        
        REQUIRE(tasks.size() == 3);
        
        tasks.run();
        
        REQUIRE(tasks.size() == 0);
    }
}

TEST_CASE("Multiplexer","[multiplexer]") {
    SECTION("task queue"){
        TaskQueue<void> tasks;
        tasks([]{});
        tasks([]{});
        Multiplexer plexer;
        plexer.poll.connect([&tasks]{
            tasks.poll();
        });
        REQUIRE(tasks);
        while(tasks)
            plexer.poll();
        REQUIRE(!tasks);
    }
}

