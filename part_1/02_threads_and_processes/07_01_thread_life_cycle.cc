#include <chrono>
#include <iostream>
#include <thread>

using std::cout;
using std::thread;
using std::chrono::seconds;
using std::this_thread::sleep_for;

void chef_paco() {
  cout << "Paco started and waiting for sausage to thaw..." << '\n';
  sleep_for(seconds(3));
  cout << "Paco is done cutting sausage." << '\n';
}

int main(int argc, char const *argv[]) {
  cout << "Rocky requests Paco's help." << '\n';
  thread paco(chef_paco);

  cout << "Rocky continues cooking soup." << '\n';
  sleep_for(seconds(1));

  cout << "Rocky patiently waits for Paco to finish and join..." << '\n';
  paco.join();

  cout << "Rocky and Paco are both done!" << '\n';
}
