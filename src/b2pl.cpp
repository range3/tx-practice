#include <cstdlib>
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <array>
#include <chrono>

#include "txp/elapsed_time.hpp"

struct item {
  int val;
  std::mutex mutex;
};

int main(int argc, char* argv[]) {

  int nthreads = 2;
  if(argc == 2) {
    nthreads = std::atoi(argv[1]);
  }

  std::vector<std::thread> workers;
  std::array<item, 100> items;

  txp::elapsed_time t;

  for(int i = 0; i < nthreads; ++i) {
    workers.emplace_back([=, &items](){
      std::vector<size_t> tasks;
      const int id = i;

      tasks.push_back(id);
      items[id].mutex.lock();
      items[id].val = id;

      tasks.push_back(id+1);
      items[id+1].mutex.lock();
      items[id+1].val = id;

      for(auto task: tasks) {
        items[task].mutex.unlock();
      }
    });
  }

  for(auto& worker : workers) {
    worker.join();
  }

  t.freeze();

  std::cout << "Elapsed time (sec): " << t.sec() << std::endl;
  std::cout << "Throuput (trans/sec): " << nthreads / t.sec() << std::endl;
  return 0;
}
