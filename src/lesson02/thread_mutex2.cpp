#include <iostream>
#include <mutex>
#include <string>
#include <thread>

static std::mutex mutex;

void TestThread(int i) {
  for (;;) {
    mutex.lock();  // 获取锁资源，没有则等待
    std::cout << i << " [in]" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    mutex.unlock();

    // 为 unlock 预留时间
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

int main() {
  for (int i = 0; i < 10; ++i) {
    std::thread th(&TestThread, i);
    th.detach();
  }

  std::getchar();

  // std::cout << std::string(60,'*') << std::endl;

  return 0;
}
