#include <ProcessError.h>

namespace Interprocess
{

ProcessError::ProcessError(const char* what) noexcept 
  : std::logic_error(what){}

ProcessError::ProcessError(const std::string& what) noexcept
  : std::logic_error(what) {}

}
