#include <gtest/gtest.h>
#include <Process.h>
#include <signal.h>

using namespace testing;
using namespace Interprocess;

class ChildDestructionTest : public Test
{
public:
  static void dummyFunction(){}
  std::unique_ptr<Process> process;
  int processID;
  void SetUp() override
  {
    process = std::make_unique<Process>(dummyFunction);
    processID = process->GetProcessId();
  }
};

TEST_F(ChildDestructionTest, ExpectToKillChildOnProcessDestructor)
{
  process.reset(nullptr);
  int result = kill(processID, SIGINT);
  ASSERT_TRUE(result == -1);
}

TEST_F(ChildDestructionTest, ExpectNotToKillChildWhenProcessIsReleased)
{
  process->detach();
  process.reset(nullptr);
  int result = kill(processID, SIGINT);
  ASSERT_TRUE(result == 0);
}
