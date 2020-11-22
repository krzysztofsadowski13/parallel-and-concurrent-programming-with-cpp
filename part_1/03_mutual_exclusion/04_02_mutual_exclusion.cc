#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using std::cout;
using std::mutex;
using std::thread;
using std::chrono::milliseconds;
using std::this_thread::get_id;
using std::this_thread::sleep_for;

size_t garlic_counter{};
mutex counter{};

void shopper() {
  for (int i = 0; i < 10; i++) {
    cout << "Shopper " << get_id() << " is thinking..." << '\n';
    sleep_for(milliseconds(500));

    counter.lock();
    garlic_counter++;
    counter.unlock();
  }
}

int main(int argc, char const *argv[]) {
  thread paco(shopper);
  thread rocky(shopper);

  paco.join();
  rocky.join();

  cout << "Paco and Rocky should buy " << garlic_counter << " garlic." << '\n';
}
