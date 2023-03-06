#include <Logger.h>
#include <fstream>
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

// Test the logger initialization and default logger settings
TEST(LoggerTest, InitTest) {
  Logger::Init();
  auto logger = Logger::GetLogger();

  // Check that the logger is not null
  EXPECT_NE(logger, nullptr);

  // Check the default log level
  EXPECT_EQ(logger->level(), spdlog::level::trace);

  // Check the logger name
  EXPECT_EQ(logger->name(), "main");

  // Check the size of the sinks
  EXPECT_EQ(logger->sinks().size(), 2);
}

// Test the logger trace function
TEST(LoggerTest, TraceTest) {
  Logger::Init();
  auto logger = Logger::GetLogger();

  // Check that the logger is not null
  EXPECT_NE(logger, nullptr);

  // Check the default log level
  EXPECT_EQ(logger->level(), spdlog::level::trace);

  // search for the message in the log file
  Logger::Trace("trace message");
  Logger::GetLogger()->flush();

  std::ifstream logfile("imdfd.log");
  EXPECT_TRUE(logfile.is_open());

  std::string line;
  bool found = false;
  while (std::getline(logfile, line)) {
    if (line.find("trace message") != std::string::npos) {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test the logger info function
TEST(LoggerTest, InfoTest) {
  Logger::Init();
  auto logger = Logger::GetLogger();

  // Check that the logger is not null
  EXPECT_NE(logger, nullptr);

  // Check the default log level
  EXPECT_EQ(logger->level(), spdlog::level::trace);

  // search for the message in the log file
  Logger::Info("info message");
  Logger::GetLogger()->flush();

  std::ifstream logfile("imdfd.log");
  EXPECT_TRUE(logfile.is_open());

  std::string line;
  bool found = false;
  while (std::getline(logfile, line)) {
    if (line.find("info message") != std::string::npos) {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test the logger warn function
TEST(LoggerTest, WarnTest) {
  Logger::Init();
  auto logger = Logger::GetLogger();

  // Check that the logger is not null
  EXPECT_NE(logger, nullptr);

  // Check the default log level
  EXPECT_EQ(logger->level(), spdlog::level::trace);

  // search for the message in the log file
  Logger::Warn("warn message");
  Logger::GetLogger()->flush();

  std::ifstream logfile("imdfd.log");
  EXPECT_TRUE(logfile.is_open());

  std::string line;
  bool found = false;
  while (std::getline(logfile, line)) {
    if (line.find("warn message") != std::string::npos) {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test the logger error function
TEST(LoggerTest, ErrorTest) {
  Logger::Init();
  auto logger = Logger::GetLogger();

  // Check that the logger is not null
  EXPECT_NE(logger, nullptr);

  // Check the default log level
  EXPECT_EQ(logger->level(), spdlog::level::trace);

  // search for the message in the log file
  Logger::Error("error message");
  Logger::GetLogger()->flush();

  std::ifstream logfile("imdfd.log");
  EXPECT_TRUE(logfile.is_open());

  std::string line;
  bool found = false;
  while (std::getline(logfile, line)) {
    if (line.find("error message") != std::string::npos) {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test the logger critical function
TEST(LoggerTest, CriticalTest) {
  Logger::Init();
  auto logger = Logger::GetLogger();

  // Check that the logger is not null
  EXPECT_NE(logger, nullptr);

  // Check the default log level
  EXPECT_EQ(logger->level(), spdlog::level::trace);

  // search for the message in the log file
  Logger::Critical("critical message");
  Logger::GetLogger()->flush();

  std::ifstream logfile("imdfd.log");
  EXPECT_TRUE(logfile.is_open());

  std::string line;
  bool found = false;
  while (std::getline(logfile, line)) {
    if (line.find("critical message") != std::string::npos) {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Automatically generates a main() function for running all the tests
GTEST_API_ int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
