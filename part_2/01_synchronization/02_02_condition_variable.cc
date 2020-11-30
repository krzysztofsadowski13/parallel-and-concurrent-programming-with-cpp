#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using std::condition_variable;
using std::cout;
using std::mutex;
using std::thread;
using std::unique_lock;

int soup_servings{10};
mutex slow_cooker_lid{};
condition_variable soup_taken{};

void hungry_person(int id) {
  int put_lid_back{};

  while (soup_servings > 0) {
    unique_lock<mutex> lid_lock(slow_cooker_lid);

    while ((id != soup_servings % 5) && (soup_servings > 0)) {
      put_lid_back++;
      soup_taken.wait(lid_lock);
    }

    if (soup_servings > 0) {
      soup_servings--;
      lid_lock.unlock();
      // notify_all because there is more than one thread to wake up and see if
      // it's turn to take action. For notyfing just one thread use notify_one.
      soup_taken.notify_all();
    }
  }

  cout << "Person " << id << " put the lid back " << put_lid_back << " times."
       << '\n';
}

int main(int argc, char const* argv[]) {
  thread hungry_threads[5]{};

  for (int i = 0; i < 5; i++) {
    hungry_threads[i] = thread(hungry_person, i);
  }

  for (auto& hungry_thread : hungry_threads) {
    hungry_thread.join();
  }
}
