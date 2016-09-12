#include <iostream>

#include <Process.h>

void fun(int argument)
{
  std::cout<<"Child process main function..."<<argument<<std::endl;
  for(auto i = 0; i < 4; ++i)
  {
    std::cout<<"I'm child process "<<i<<"."<<std::endl;
  }
}

int main(int argc, char *argv[])
{
  std::cout<<"I'm parent process."<<std::endl;
  Interprocess::Process process(fun, 5);
  sleep(2);
  std::cout<<"Starting child process..."<<std::endl;
  process.startProcess();
  sleep(2);
  std::cout<<"Parent exiting..."<<std::endl;
  return 0;
}
