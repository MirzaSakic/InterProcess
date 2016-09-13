#ifndef __PROCESS_ERROR_H__
#define __PROCESS_ERROR_H__

#include <stdexcept>

namespace Interprocess
{

class ProcessError : public std::logic_error
{
public:
  ProcessError(const char* what) noexcept;
  ProcessError(const std::string& what) noexcept;
  virtual ~ProcessError() = default;
};

}

#endif /* ifndef __PROCESS_ERROR_H__ */
