#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>

using std::cout;

// a simple function that wastes CPU cycles "forever"
void cpu_waster() {
  cout << "CPU Waster Process ID: " << getpid() << '\n';
  cout << "CPU Waster Thread ID: " << std::this_thread::get_id() << "\n\n";

  while (true) {
    continue;
  }
}

int main(int argc, char const *argv[]) {
  cout << "Main Process ID: " << getpid() << '\n';
  cout << "Main Thread ID: " << std::this_thread::get_id() << "\n\n";

  std::thread thread_1(cpu_waster);
  std::thread thread_2(cpu_waster);

  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
