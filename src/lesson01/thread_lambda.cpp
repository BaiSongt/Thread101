#include <iostream>
#include <string>
#include <thread>


class TestLambda
{
public:
  TestLambda() = default;
  ~TestLambda() = default;

  void start()
  {
    std::thread th( [this]() {std::cout << "class Lambda name: " << name_ << std::endl;});
    th.join();
  }

private:
 const std::string name_ = "TestLambda";

};


int main() {
  std::thread th(
      [](int i) { std::cout << i << " Lambda from thread" << std::endl; }, 123);
  th.join();


  TestLambda test_lambda;
  test_lambda.start();

  return 0;
}
