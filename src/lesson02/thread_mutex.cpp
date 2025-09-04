#include <iostream>
#include <mutex>
#include <string>
#include <thread>

static std::mutex mutex;

void TestThread(int i) {
  for (;;) {
    // mutex.lock(); // 获取锁资源，没有则等待
    if (!mutex.try_lock()) {  // 资源消耗
      std::cout << '.' << std::flush;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      continue;
    }
    std::cout << std::string(20, '=') << std::endl;
    std::cout << "Hello " << i << std::endl;
    std::cout << std::string(20, '=') << std::endl;
    mutex.unlock();
  }
}

int main() {
  for (int i = 1; i < 5;) {
    std::thread th(&TestThread, i++);
    th.detach();
  }

  // std::cout << std::string(60,'*') << std::endl;

  return 0;
}
