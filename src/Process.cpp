#include <Process.h>
#include <boost/interprocess/sync/named_semaphore.hpp>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

namespace Interprocess
{

using Semaphore = boost::interprocess::named_semaphore;
using namespace boost::interprocess;
using namespace std;

Process::Process(Process&& otherProcess)
  : _processId(otherProcess._processId), _mainFunction(otherProcess._mainFunction)
{
  otherProcess._processId = -1;
}

Process& Process::operator=(Process&& otherProcess)
{
  _processId = otherProcess._processId;
  _mainFunction = otherProcess._mainFunction;
  otherProcess._processId = -1;
  return *this;
}

void Process::start() const
{
  Semaphore semaphore(open_or_create, _processIdString.c_str(), 0);
  semaphore.post();
}

void Process::release()
{
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
}

Process::~Process()
{
  if(_isReleased == false)
  {
    kill(_processId, SIGKILL);
    int status;
    waitpid(_processId, &status, 0);
    Semaphore::remove(_processIdString.c_str());
  }
}

}
