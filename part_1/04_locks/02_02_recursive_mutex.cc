#include <iostream>
#include <mutex>
#include <thread>

using std::cout;
using std::recursive_mutex;
using std::thread;

size_t garlic_counter{};
size_t potato_counter{};
recursive_mutex counter{};

void add_garlic() {
  counter.lock();
  garlic_counter++;
  counter.unlock();
}

void add_potato() {
  counter.lock();
  potato_counter++;
  add_garlic();  // counter locked twice in a row
  counter.unlock();
}

void shopper() {
  for (size_t i = 0; i < 10000; i++) {
    add_garlic();
    add_potato();
  }
}

int main(int argc, char const *argv[]) {
  thread paco(shopper);
  thread rocky(shopper);

  paco.join();
  rocky.join();

  cout << "Paco and Rocky should buy " << garlic_counter << " garlic." << '\n';
  cout << "Paco and Rocky should buy " << potato_counter << " potato." << '\n';
}
