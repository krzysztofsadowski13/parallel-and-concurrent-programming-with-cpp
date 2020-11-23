#include <iostream>
#include <mutex>
#include <thread>

using std::array;
using std::cout;
using std::mutex;
using std::ref;
using std::scoped_lock;
using std::thread;
using std::this_thread::get_id;

int sushi_count{5000};

void philosopher(mutex& chopsticks) {
  int sushi_eaten{};

  while (sushi_count > 0) {
    scoped_lock lock{chopsticks};

    if (sushi_count) {
      sushi_count--;
      sushi_eaten++;
    }
  }

  cout << "Philosopher " << get_id() << " has eaten " << sushi_eaten
       << " sushi." << '\n';
}

int main(int argc, char const* argv[]) {
  mutex chopsticks{};
  array<thread, 200> philosophers{};

  // some philosophers get decent amount of sushi, but some don't get it
  // at all because there are so many threads that some never get scheduled.
  for (size_t i = 0; i < philosophers.size(); i++) {
    philosophers[i] = thread(philosopher, ref(chopsticks));
  }

  for (size_t i = 0; i < philosophers.size(); i++) {
    philosophers[i].join();
  }

  cout << "The philosophers are done eating." << '\n';
}
