#include <chrono>
#include <iostream>
#include <thread>

using std::cout;
using std::thread;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::this_thread::sleep_for;

void kitchen_cleaner() {
  while (true) {
    cout << "Paco cleaned a kitchen." << '\n';
    sleep_for(seconds(1));
  }
}

int main(int argc, char const *argv[]) {
  thread paco(kitchen_cleaner);

  for (int i = 0; i < 3; i++) {
    cout << "Rocky is cooking..." << '\n';
    sleep_for(milliseconds(600));
  }

  cout << "Rocky is done!" << '\n';
  paco.join();
}
