#include <iostream>
#include <string>
#include <thread>

class XThread {
 public:
  XThread() {};
  virtual ~XThread() {};

  // 启动线程
  virtual void Start() {
    this->is_exit_ = false;
    th_ = std::thread(&XThread::main, this);
  }

  // 等待线程
  virtual void Wait() {
    if (th_.joinable()) {
      th_.join();
    }
  }

  // 终止线程
  virtual void Stop() {
    is_exit_ = true;
    Wait();
  }

  bool is_exit() const { return is_exit_; }

 private:
  virtual void main() = 0;  // interface
  std::thread th_;
  bool is_exit_ = false;
};

class TestXThrad : public XThread {
 public:
  void main() override {
    std::cout << "Class TestXThread main" << std::endl;
    while (!is_exit()) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "." << std::flush;
    }
    std::cout << "\nThread exit" << std::endl;
  }
};

class MyThread {
 public:
  MyThread() {};
  ~MyThread() {};
  void main() {
    std::cout << "name: " << this->name << " Age: " << this->age << std::endl;
  }

 public:
  std::string name = "";
  int age = 100;
};

int main() {
  MyThread my_thread;
  my_thread.age = 99;
  my_thread.name = "GGBoom";

  //                成员函数      成员
  std::thread th(&MyThread::main, &my_thread);
  th.join();

  TestXThrad test_th;
  test_th.Start();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  test_th.Stop();

  test_th.Wait();

  return 0;
}
