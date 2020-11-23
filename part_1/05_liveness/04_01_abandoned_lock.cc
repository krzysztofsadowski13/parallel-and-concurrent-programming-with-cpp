#include <iostream>
#include <mutex>
#include <thread>

using std::cout;
using std::mutex;
using std::ref;
using std::thread;

int sushi_count{5000};

void philosopher(mutex& chopsticks) {
  while (sushi_count > 0) {
    chopsticks.lock();

    if (sushi_count) {
      sushi_count--;
    }

    if (sushi_count == 10) {
      cout << "This philosopher has had enough!" << '\n';
      break;
    }

    chopsticks.unlock();
  }
}

int main(int argc, char const* argv[]) {
  mutex chopsticks{};

  // one of philosophers has had enough but other philosopher never finishes 
  // eating because mutex never gets unlocked.
  thread paco(philosopher, ref(chopsticks));
  thread rocky(philosopher, ref(chopsticks));

  paco.join();
  rocky.join();

  cout << "The philosophers are done eating." << '\n';
}
