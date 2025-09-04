#include <iostream>
#include <mutex>
#include <thread>

// static std::mutex mutex;
static std::timed_mutex t_mux;
static std::recursive_mutex r_mux; // 可重入的锁 递归锁

void Task1() {
  r_mux.lock();
  std::cout << "Task1 [in]" << std::endl;
  r_mux.unlock();
}


void Task2() {
  r_mux.lock();
  std::cout << "Task2 [in]" << std::endl;
  r_mux.unlock();
}


void TestThreadRec(int i) {
  for (;;) {
    r_mux.lock();
    // 不再需要 r_mux.unlock()   普通锁需要先解锁再进入
    Task1();
    std::cout << i << "[in]" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Task2();
    r_mux.unlock();
  }
}

int main() {
  for (int i = 0; i < 3; ++i) {
    std::thread th(&TestThreadRec, i);
    th.detach();
  }

  std::getchar();
  return 0;
}
