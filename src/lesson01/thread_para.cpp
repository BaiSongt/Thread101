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

void threadMain(int p1, float p2, string str, Para p4) {
  this_thread::sleep_for(100ms);
  cout << "function thread ID:" << this_thread::get_id() << endl;
  cout << "function(" << " p1 = " << p1 << " p2 = " << p2 << " p3 = " << str
       << " p4 = " << p4.s_name << endl;
}

void threadPtr(Para* p) {
  this_thread::sleep_for(100ms);
  cout << "function thread ID:" << this_thread::get_id() << endl;
  cout << "function(" << " p* -> " << p->s_name << endl;
}

void threadRef(Para& p) {
  this_thread::sleep_for(100ms);
  cout << "function thread ID:" << this_thread::get_id() << endl;
  cout << "function(" << " &p " << p.s_name << endl;
}

int main(int argc, char const* argv[]) {
  cout << "Main thread ID:" << this_thread::get_id() << endl;

  cout << "\nRef ================= " << endl;
  {  // 引用传递
    Para p;
    thread th(threadRef, ref(p));
    cout << "threadRef th ID:" << th.get_id() << endl;
    th.join();
  }

  cout << "\nPtr ================= " << endl;
  {  // 指针传递
    Para p;
    thread th(threadPtr, &p);
    cout << "threadPtr th ID:" << th.get_id() << endl;
    th.join();
  }

  cout << "\nVal copy ================= " << endl;
  {
    float f1 = 12.3f;
    Para p;
    // 所有参数做复制
    thread th(threadMain, 103, f1, "TestPara ", p);
    cout << "threadMain th ID:" << th.get_id() << endl;
    th.join();
  }

  return 0;
}
