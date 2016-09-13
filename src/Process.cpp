#include <Process.h>
#include <boost/interprocess/sync/named_semaphore.hpp>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <ProcessError.h>

namespace Interprocess
{

using Semaphore = boost::interprocess::named_semaphore;
using namespace boost::interprocess;
using namespace std;

Process::Process(Process&& otherProcess) noexcept
  : _processId(otherProcess._processId), _mainFunction(otherProcess._mainFunction)
{
  otherProcess._processId = -1;
}

Process& Process::operator=(Process&& otherProcess) noexcept
{
  _processId = otherProcess._processId;
  _mainFunction = otherProcess._mainFunction;
  otherProcess._processId = -1;
  return *this;
}

void Process::start() 
{
  if(_processId == -1)
  {
    throw ProcessError("Couldn't start process. Process does not exist.");
  }
  Semaphore semaphore(open_or_create, _processIdString.c_str(), 0);
  semaphore.post();
}

void Process::detach()
{
  if(_processId == -1)
  {
    throw ProcessError("Couldn't detach process. Process does not exist.");
  }
  _isReleased = true;
}

void Process::childProcessRunner()
{
  _processId = fork();
  if(_processId == 0)
  {
    _processIdString = to_string(getpid());
    Semaphore semaphore(open_or_create, _processIdString.c_str(), 0);
    semaphore.wait();
    _mainFunction();
    exit(0);
  }
  else if(_processId > 0)
  {
    _processIdString = to_string(_processId);
  }
  else
  {
    throw std::system_error(errno, std::system_category());
  }
}

Process::~Process()
{
  if(_isReleased == false && _processId != -1)
  {
    kill(_processId, SIGKILL);
    int status;
    waitpid(_processId, &status, 0);
    Semaphore::remove(_processIdString.c_str());
  }
}

}
