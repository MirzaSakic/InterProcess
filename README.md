# Interprocess library
 ## Process
 This library provides easy API towards creating child processes on Linux distributions. Object *Process* represents single process, and uses Linux [fork](http://man7.org/linux/man-pages/man2/fork.2.html) to create child process. New process will be created on object construction but won't run until *Process::start* is called.
When *Process::start* is called, top level function will start executing and it's return value will be **ignored**. There can not be 2 *Process* objects that represent same child process. *Process* is not copy constructible or copy assignable although it is move constructible and move assignable.

If *Process::detach* is not called, *Process* destructor will kill the child process.

 Example of using Process object is shown below:
 ```c++
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
 ```

