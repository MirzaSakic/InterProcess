#include <Process.h>
#include <gtest/gtest.h>
#include <thread>
#include <fstream>

using namespace testing;
using namespace Interprocess;
using namespace std::chrono_literals;

class ChildConfirmationTest : public Test
{
public:
  static void writeToFile(const std::string& fileName, const std::string& strForFile)
  {
    std::ofstream out(fileName);
    out<<strForFile;
    out.close();
  }

  std::string readFromFile(const std::string& fileName) const
  {
    std::ifstream input(fileName);
    std::string result ((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    input.close();
    return result;
  }

  void TearDown() override
  {
    auto removeFileCommand = "rm -rf " + FileName;
    system(removeFileCommand.c_str());
  }

  std::string expected = "This is test";
  const std::string FileName = "TestFile.txt";
  Process process{writeToFile, FileName, expected};
};

TEST_F(ChildConfirmationTest, ExpectChildProcessToWriteToFile)
{
  process.start();
  std::this_thread::sleep_for(10ms);
  auto result = readFromFile(FileName);
  ASSERT_EQ(expected, result);
}
