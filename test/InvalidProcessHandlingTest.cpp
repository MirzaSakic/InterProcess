#include <gtest/gtest.h>
#include <Process.h>
#include <ProcessError.h>

using namespace testing;
using namespace Interprocess;

class InvalidProcessHandlingTest : public Test
{
public:
  static void dummyFunction(){}
  Process invalidProcess{dummyFunction};
  std::unique_ptr<Process> regularProcess;
  void SetUp() override
  {
    regularProcess = std::make_unique<Process>(std::move(invalidProcess));
  }
};

TEST_F(InvalidProcessHandlingTest, ExpectToThrowWhenStartIsCalledOnInvalidObject)
{
  ASSERT_THROW(invalidProcess.start(), ProcessError);
}

TEST_F(InvalidProcessHandlingTest, ExpectToThrowWhenDetachIsCalledOnInvalidObject)
{
  ASSERT_THROW(invalidProcess.detach(), ProcessError);
}
