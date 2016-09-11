#include <iostream>
#include <Process.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>

using namespace boost::interprocess;

void fun()
{
  for(auto i = 0; i < 4; ++i)
  {
    std::cout<<"I'm child process "<<i<<"."<<std::endl;
  }
}

int main(int argc, char *argv[])
{
  std::cout<<"I'm parent process."<<std::endl;
  Interprocess::Process<> process(fun);
  std::cout<<"Starting child process..."<<std::endl;
  process.startProcess();
  std::cout<<"Parent exiting..."<<std::endl;
  return 0;
}
