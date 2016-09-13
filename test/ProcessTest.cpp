#include <gtest/gtest.h>
#include <Process.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <signal.h>

using namespace testing;
using namespace std::chrono_literals;

void writeToFile(const std::string& fileName, const std::string& strForFile)
{
  std::ofstream out(fileName);
  out<<strForFile;
  out.close();
}

TEST(InterprocessTest, ExpectChildProcessToWriteToFile)
{
  std::string expected = "This is test";
  Interprocess::Process process(writeToFile, "TestFile.txt", expected);
  process.start();
  std::this_thread::sleep_for(50ms);
  std::ifstream input("TestFile.txt");
  std::string result ((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
  input.close();
  ASSERT_EQ(expected, result);
  system("rm -rf TestFile.txt");
}

void dummyFunction(){}

TEST(InterprocessTest, ExpectToKillChildOnProcessDestructor)
{
  int processID;
  {
    Interprocess::Process process(dummyFunction);
    processID = process.GetProcessId();
  }
  int result = kill(processID, SIGINT);
  ASSERT_TRUE(result < 0);
}

TEST(InterprocessTest, ExpectNotToKillChildWhenProcessIsReleased)
{
  int processID;
  {
    Interprocess::Process process(dummyFunction);
    processID = process.GetProcessId();
    process.release();
  }
  int result = kill(processID, SIGINT);
  ASSERT_TRUE(result >= 0);
}
