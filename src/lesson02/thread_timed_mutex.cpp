 #include <iostream>
#include <mutex>
#include <string>
#include <thread>

// static std::mutex mutex;
static std::timed_mutex t_mux;

void TestThread(int i) {
  for (;;) {
    if (!t_mux.try_lock_for(std::chrono::milliseconds(500))){
      std::cout << i << "[try_lock_for Timeout]" << std::endl;
      continue;
    }
    std::cout << i << " [in]" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    t_mux.unlock();

    // 为 unlock 预留时间
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

int main() {
  for (int i = 0; i < 3; ++i) {
    std::thread th(&TestThread, i);
    th.detach();
  }

  std::getchar();
  return 0;
}
