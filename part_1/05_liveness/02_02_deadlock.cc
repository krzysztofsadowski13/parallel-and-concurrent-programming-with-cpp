#include <iostream>
#include <mutex>
#include <thread>

using std::cout;
using std::mutex;
using std::ref;
using std::thread;

int sushi_count{5000};

void philosopher(mutex& first_chopstick, mutex& second_chopstick) {
  while (sushi_count > 0) {
    first_chopstick.lock();
    second_chopstick.lock();

    if (sushi_count) {
      sushi_count--;
    }

    second_chopstick.unlock();
    first_chopstick.unlock();
  }
}

int main(int argc, char const* argv[]) {
  mutex chopstick_a{};
  mutex chopstick_b{};

  // philosophers could stop eating because of prioritizing the locks and
  // each of philosophers should always take the highest priority lock.
  thread paco(philosopher, ref(chopstick_a), ref(chopstick_b));
  thread rocky(philosopher, ref(chopstick_a), ref(chopstick_b));

  paco.join();
  rocky.join();

  cout << "The philosophers are done eating." << '\n';
}
