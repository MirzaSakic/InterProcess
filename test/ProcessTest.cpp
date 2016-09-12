#include <gtest/gtest.h>
#include <Process.h>
#include <fstream>
#include <chrono>
#include <thread>

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
  process.startProcess();
  std::this_thread::sleep_for(50ms);
  std::ifstream input("TestFile.txt");
  std::string result ((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
  input.close();
  ASSERT_EQ(expected, result);
  system("rm -rf TestFile.txt");
}
