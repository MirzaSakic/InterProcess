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
  Process(Process&&);
  Process& operator=(const Process&) = delete;
  Process& operator=(Process&&);

  int GetProcessId() const { return _processId; }

  void start() const;
  void release();

  ~Process();

private:
  int _processId;
  bool _isReleased = false;
  std::string _processIdString;
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
