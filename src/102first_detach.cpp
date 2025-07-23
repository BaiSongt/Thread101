#include <thread>
// linux -lpthread
#include <iostream>

// 线程任务
void ThreadMain() {
  std::cout << "Begin Sub thread main." << std::this_thread::get_id()
            << std::endl;

  for (size_t i = 0; i < 3; i++) {
    std::cout << "in thread " << i << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));  //  1000 ms
  }

  std::cout << "End Sub thread main." << std::this_thread::get_id()
            << std::endl;
}

int main(int argc, char* argv[]) {
  std::cout << "main thread ID: " << std::this_thread::get_id() << std::endl;

  {
    // thread th(ThreadMain);
    // error: th对象被销毁，子线程还在运行
  }

  {
    std::thread th(ThreadMain);
    th.detach();  // 子线程与主线程分离 守护线程
    // 问题： 主线程结束，子线程不一定退出
  }

  {
    // 线程创建启动
    std::thread th(ThreadMain);

    std::cout << "begin wait sub thread " << std::endl;
    // 阻塞，等待子线程退出。
    th.join();
    std::cout << "end wait sub thread " << std::endl;
  }

  return 0;
}
