#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <functional>

namespace Interprocess
{

class Process
{
public:
  Process() = delete;
  template<typename FunctionType, typename... Args>
  Process(FunctionType&&, Args&&...);
  Process(const Process&) = delete;
  Process(Process&&) noexcept;
  Process& operator=(const Process&) = delete;
  Process& operator=(Process&&) noexcept;

  int GetProcessId() const { return _processId; }

  void start();
  void detach();

  ~Process();

private:
  int _processId = -1;
  bool _isReleased = false;
  std::string _processIdString = "-1";
  std::function<void()> _mainFunction;


  void childProcessRunner();
};

template<typename FunctionType, typename... Args>
Process::Process(FunctionType&& mainFunction, Args&&... args)
  : _mainFunction(std::bind(std::forward<FunctionType>(mainFunction), std::forward<Args>(args)...)) 
{ 
  childProcessRunner(); 
}

}

#endif
