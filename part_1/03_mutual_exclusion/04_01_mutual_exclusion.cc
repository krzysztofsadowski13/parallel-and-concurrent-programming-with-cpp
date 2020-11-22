#include <iostream>
#include <mutex>
#include <thread>

using std::cout;
using std::mutex;
using std::thread;

size_t garlic_counter{};
mutex counter{};

void shopper() {
  counter.lock();

  for (int i = 0; i < 10000000; i++) {
    garlic_counter++;
  }

  counter.unlock();
}

int main(int argc, char const *argv[]) {
  thread paco(shopper);
  thread rocky(shopper);

  paco.join();
  rocky.join();

  cout << "Packo and Rocky should buy " << garlic_counter << " garlic." << '\n';
}
