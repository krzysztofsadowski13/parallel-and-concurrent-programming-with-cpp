#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using std::cout;
using std::mutex;
using std::string;
using std::thread;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
using std::this_thread::sleep_for;

size_t items_on_notepad{};
mutex counter{};

void shopper(const string& name) {
  size_t items_to_add{};

  while (items_on_notepad <= 20) {
    if (items_to_add && counter.try_lock()) {
      items_on_notepad += items_to_add;

      cout << name << " added "
           << " item(s) to notepad." << '\n';

      items_to_add = 0;
      sleep_for(milliseconds(300));
      counter.unlock();
    } else {
      sleep_for(milliseconds(100));
      items_to_add++;

      cout << name << " found something else to buy." << '\n';
    }
  }
}

int main(int argc, char const* argv[]) {
  auto start_time{steady_clock::now()};
  thread paco(shopper, "Paco");
  thread rocky(shopper, "Rocky");

  paco.join();
  rocky.join();

  auto elapsed_time{
      duration_cast<milliseconds>(steady_clock::now() - start_time).count()};

  cout << "Elapsed time: " << (elapsed_time / 1000.0) << " seconds." << '\n';
}
