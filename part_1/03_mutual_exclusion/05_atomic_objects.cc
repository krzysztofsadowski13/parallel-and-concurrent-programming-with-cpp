#include <atomic>
#include <iostream>
#include <thread>

using std::atomic;
using std::cout;
using std::thread;

atomic<size_t> garlic_counter{};

void shopper() {
  for (int i = 0; i < 10000000; i++) {
    garlic_counter++;
  }
}

int main(int argc, char const *argv[]) {
  thread paco(shopper);
  thread rocky(shopper);

  paco.join();
  rocky.join();

  cout << "Paco and Rocky should buy " << garlic_counter.load() << " garlic."
       << '\n';
}
