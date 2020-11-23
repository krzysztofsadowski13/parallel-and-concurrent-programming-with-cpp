#include <iostream>
#include <mutex>
#include <thread>

using std::cout;
using std::mutex;
using std::ref;
using std::scoped_lock;
using std::thread;

int sushi_count{5000};

void philosopher(mutex& chopsticks) {
  while (sushi_count > 0) {
    scoped_lock lock{chopsticks};

    if (sushi_count) {
      sushi_count--;
    }

    if (sushi_count == 10) {
      cout << "This philosopher has had enough!" << '\n';
      break;
    }
  }
}

int main(int argc, char const* argv[]) {
  mutex chopsticks{};

  // both philosophers finished eating because scoped_lock automatically 
  // releases lock on a mutex.
  thread paco(philosopher, ref(chopsticks));
  thread rocky(philosopher, ref(chopsticks));

  paco.join();
  rocky.join();

  cout << "The philosophers are done eating." << '\n';
}
