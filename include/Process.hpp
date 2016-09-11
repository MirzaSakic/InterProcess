#ifndef __PROCESS_HPP__
#define __PROCESS_HPP__

#include <boost/interprocess/sync/named_semaphore.hpp>
#include <unistd.h>
#include <functional>

namespace Interprocess
{

template<typename FunctionType = void()>
class Process
{
  using Semaphore = boost::interprocess::named_semaphore;
  boost::interprocess::open_or_create_t OpenCreate = boost::interprocess::open_or_create;
public:
  Process() = delete;
  Process(FunctionType mainFunction);
  Process(const Process<FunctionType>&) = delete;
  Process(Process<FunctionType>&&);
  Process<FunctionType>& operator=(const Process<FunctionType>&) = delete;
  Process<FunctionType>& operator=(Process<FunctionType>&&);

  void startProcess() const;

private:
  int _processId;
  std::function<FunctionType> _mainFunction;

  void childProcessRunner();
};

template<typename FunctionType>
Process<FunctionType>::Process(FunctionType mainFunction)
  : _mainFunction(mainFunction) { childProcessRunner(); }

template<typename FunctionType>
Process<FunctionType>::Process(Process<FunctionType>&& otherProcess)
  : _processId(otherProcess._processId), _mainFunction(otherProcess._mainFunction)
{
  otherProcess._processId = -1;
}

template<typename FunctionType>
Process<FunctionType>& Process<FunctionType>::operator=(Process<FunctionType>&& otherProcess)
{
  _processId = otherProcess._processId;
  _mainFunction = otherProcess._mainFunction;
}

template<typename FunctionType>
void Process<FunctionType>::startProcess() const
{
  auto pIDString = std::to_string(_processId);
  Semaphore semaphore(OpenCreate, pIDString.c_str(), 0);
  semaphore.post();
}

template<typename FunctionType>
void Process<FunctionType>::childProcessRunner()
{
  _processId = fork();
  if( ! _processId)
  {
    auto pIDString = std::to_string(getpid());
    Semaphore semaphore(OpenCreate, pIDString.c_str(), 0);
    semaphore.wait();
    _mainFunction();
    exit(0);
  }
}

}

#endif
