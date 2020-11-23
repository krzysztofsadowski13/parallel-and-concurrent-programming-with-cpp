#include <iostream>
#include <mutex>
#include <thread>

using std::cout;
using std::mutex;
using std::ref;
using std::scoped_lock;
using std::thread;

int sushi_count{5000};

void philosopher(mutex& first_chopstick, mutex& second_chopstick) {
  while (sushi_count > 0) {
    scoped_lock lock{first_chopstick, second_chopstick};

    if (sushi_count) {
      sushi_count--;
    }
  }
}

int main(int argc, char const* argv[]) {
  mutex chopstick_a{};
  mutex chopstick_b{};

  // scoped_lock require both mutexes and automatically gets destructed
  // at the end of a scope and mutexes are released.
  thread paco(philosopher, ref(chopstick_a), ref(chopstick_b));
  thread rocky(philosopher, ref(chopstick_b), ref(chopstick_a));

  paco.join();
  rocky.join();

  cout << "The philosophers are done eating." << '\n';
}
