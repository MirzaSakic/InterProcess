#include <gtest/gtest.h>
#include <Process.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <signal.h>

using namespace testing;
using namespace std::chrono_literals;
using namespace Interprocess;

class InterprocessTest : public Test
{
public:
  static void writeToFile(const std::string& fileName, const std::string& strForFile)
  {
    std::ofstream out(fileName);
    out<<strForFile;
    out.close();
  }

  static void dummyFunction(){}
};

TEST_F(InterprocessTest, ExpectChildProcessToWriteToFile)
{
  std::string expected = "This is test";
  Process process(writeToFile, "TestFile.txt", expected);
  process.start();
  std::this_thread::sleep_for(10ms);
  std::ifstream input("TestFile.txt");
  std::string result ((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
  input.close();
  ASSERT_EQ(expected, result);
  system("rm -rf TestFile.txt");
}

TEST_F(InterprocessTest, ExpectToKillChildOnProcessDestructor)
{
  int processID;
  {
    Process process(dummyFunction);
    processID = process.GetProcessId();
  }
  int result = kill(processID, SIGINT);
  ASSERT_TRUE(result == -1);
}

TEST_F(InterprocessTest, ExpectNotToKillChildWhenProcessIsReleased)
{
  int processID;
  {
    Process process(dummyFunction);
    processID = process.GetProcessId();
    process.detach();
  }
  int result = kill(processID, SIGINT);
  ASSERT_TRUE(result == 0);
}
