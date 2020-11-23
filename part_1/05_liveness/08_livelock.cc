#include <iostream>
#include <mutex>
#include <thread>

using std::array;
using std::cout;
using std::mutex;
using std::ref;
using std::thread;
using std::this_thread::yield;

int sushi_count{5000};

void philosopher(mutex& first_chopstick, mutex& second_chopstick) {
  while (sushi_count > 0) {
    first_chopstick.lock();

    if (!second_chopstick.try_lock()) {
      first_chopstick.unlock();
      yield();
    } else {
      if (sushi_count) {
        sushi_count--;
      }

      second_chopstick.unlock();
      first_chopstick.unlock();
    }
  }
}

int main(int argc, char const* argv[]) {
  mutex chopstick_a{};
  mutex chopstick_b{};

  // this excercise doesn't work properly on Linux, but main idea is that
  // threads are too polite to each other and they unlock first_chopstick mutex
  // everytime so none of threads get second_chopstick mutex.
  // std::this_thread::yield() prevents livelock by making thread wait a little
  // so another thread could grab both chopsticks and get job done.
  thread paco(philosopher, ref(chopstick_a), ref(chopstick_b));
  thread rocky(philosopher, ref(chopstick_b), ref(chopstick_a));
  thread manu(philosopher, ref(chopstick_a), ref(chopstick_b));
  thread koles(philosopher, ref(chopstick_b), ref(chopstick_a));

  paco.join();
  rocky.join();
  manu.join();
  koles.join();

  cout << "The philosophers are done eating." << '\n';
}
