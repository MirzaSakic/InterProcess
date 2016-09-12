#include <Process.h>
#include <boost/interprocess/sync/named_semaphore.hpp>
#include <unistd.h>

namespace Interprocess
{

using Semaphore = boost::interprocess::named_semaphore;
boost::interprocess::open_or_create_t OpenCreate = boost::interprocess::open_or_create;
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
  return *this;
}

void Process::startProcess() const
{
  auto pIDString = to_string(_processId);
  Semaphore semaphore(OpenCreate, pIDString.c_str(), 0);
  semaphore.post();
}

void Process::childProcessRunner()
{
  _processId = fork();
  if( ! _processId)
  {
    auto pIDString = to_string(getpid());
    Semaphore semaphore(OpenCreate, pIDString.c_str(), 0);
    semaphore.wait();
    _mainFunction();
    exit(0);
  }
}

}
