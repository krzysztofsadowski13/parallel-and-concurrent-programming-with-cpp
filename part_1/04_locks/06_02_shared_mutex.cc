#include <chrono>
#include <iostream>
#include <shared_mutex>
#include <string>
#include <thread>

using std::array;
using std::cout;
using std::shared_mutex;
using std::string;
using std::thread;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

const string kWeekdays[7]{"Sunday",   "Monday", "Tuesday", "Wednesday",
                          "Thursday", "Friday", "Saturday"};
int today{};
shared_mutex marker{};

void calendar_reader(const int id) {
  for (int i = 0; i < 7; i++) {
    marker.lock_shared();
    cout << "Reader " << id << " sees today is " << kWeekdays[today] << '\n';

    sleep_for(milliseconds(100));
    marker.unlock_shared();
  }
}

void calendar_writer(const int id) {
  for (int i = 0; i < 7; i++) {
    marker.lock();
    today = (today + 1) % 7;

    cout << "Writer " << id << " updated date to " << kWeekdays[today] << '\n';

    sleep_for(milliseconds(100));
    marker.unlock();
  }
}

int main(int argc, char const *argv[]) {
  array<thread, 10> readers{};
  array<thread, 2> writers{};

  for (size_t i = 0; i < readers.size(); i++) {
    readers[i] = thread(calendar_reader, i);
  }

  for (size_t i = 0; i < writers.size(); i++) {
    writers[i] = thread(calendar_writer, i);
  }

  for (size_t i = 0; i < readers.size(); i++) {
    readers[i].join();
  }

  for (size_t i = 0; i < writers.size(); i++) {
    writers[i].join();
  }
}
