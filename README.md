# Interprocess library
 ##Process
 This library provides easy API towards creating child processes on Linux distributions. Example of using Process object is shown below:
 '''c++
  #include <Process.h>
  #include <iostream>
  using namespace Interprocess;
  void fun()
  {
    std::cout<<"Child process."<<std::endl;
  }
  int main()
  {
    Process process p(fun);
    p.start();
  }
 '''

