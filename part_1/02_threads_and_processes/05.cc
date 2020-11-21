#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using std::cout;
using std::string;
using std::thread;
using std::chrono::seconds;
using std::this_thread::sleep_for;

bool chopping{true};

void vegetable_chopper(const string& name) {
  size_t vegetable_counter{};

  while (chopping) {
    vegetable_counter++;
  }

  cout << name << " chopped " << vegetable_counter << " vegetables." << '\n';
}

int main(int argc, char const* argv[]) {
  thread paco(vegetable_chopper, "Paco");
  thread rocky(vegetable_chopper, "Rocky");

  cout << "Paco and Rocky are chopping vegetables..." << '\n';

  sleep_for(seconds(1));
  chopping = false;
  paco.join();
  rocky.join();
}
