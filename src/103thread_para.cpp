#include <iostream>
#include <string>
#include <thread>

using namespace std;

class Para {
 public:
  Para() { cout << "Para ctor " << endl; };
  Para(const Para&) { cout << "Para Cp ctor " << endl; };
  ~Para() { cout << "Para dtor " << endl; };
  const string s_name = "Class(Para)";
};


void threadMain(int p1, float p2, string str, Para p4){
  this_thread::sleep_for(100ms);
  cout << "threadMain thread ID:" << this_thread::get_id() << endl;
  cout << "threadMain(" << " p1 = " << p1
                        << " p2 = " << p2
                        << " p3 = " << str
                        << " p4 = " << p4.s_name << endl;
}


int main(int argc, char const *argv[])
{

  cout << "Main thread ID:" << this_thread::get_id() << endl;

  thread th;
  {
    float f1 = 12.3f;
    Para p;
    // 所有参数做复制
    th = thread(threadMain, 103, f1, "TestPara ", p);
    cout << "th ID:" << th.get_id() << endl;
  }

  th.join();
  return 0;
}

