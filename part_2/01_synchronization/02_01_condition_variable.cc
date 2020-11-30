#include <iostream>
#include <mutex>
#include <thread>

using std::cout;
using std::mutex;
using std::thread;
using std::unique_lock;

int soup_servings{10};
mutex slow_cooker_lid{};

void hungry_person(int id) {
  int put_lid_back{};

  while (soup_servings > 0) {
    unique_lock<mutex> lid_lock(slow_cooker_lid);

    if ((id == soup_servings % 2) && (soup_servings > 0)) {
      soup_servings--;
    } else {
      put_lid_back++;
    }
  }

  cout << "Person " << id << " put the lid back " << put_lid_back << " times."
       << '\n';
}

int main(int argc, char const* argv[]) {
  thread hungry_threads[2]{};

  for (int i = 0; i < 2; i++) {
    hungry_threads[i] = thread(hungry_person, i);
  }

  for (auto& hungry_thread : hungry_threads) {
    hungry_thread.join();
  }
}
