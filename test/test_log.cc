//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file test_log.cc
///

#include <glog/logging.h>
#include <unistd.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "hmicore/gva.h"

// The fixture for testing class LogTest.
class LogTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  LogTest() = default;  // You can do set-up work for each test here.

  ~LogTest() override = default;  // You can do clean-up work that doesn't throw exceptions here.

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for LogTest.
};

int CoutLines(const std::string& filename) {
  int counter = 0;
  if (std::ifstream fs(filename); fs.is_open()) {
    for (std::string line; getline(fs, line);) {
      counter++;
    }
  } else {
    LOG(WARNING) << "Could not open log file.";
  }
  return counter;
}

TEST_F(LogTest, LoggingTests) {
  std::string test1 = "This is a string test";
  LOG(WARNING) << test1;
  LOG(INFO) << test1;
  LOG(ERROR) << test1;
  std::string test2 =
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam augue quam, vulputate ac pretium vitae, hendrerit "
      "vitae nibh. Sed nec augue diam. Aenean pretium sodales turpis, at interdum ipsum ornare non. Nam vulputate "
      "neque nulla, condimentum feugiat metus aliquam nec. Nulla vitae ante et mi dapibus lobortis. Aenean consectetur "
      "suscipit nisi, in lobortis turpis ullamcorper placerat. Maecenas tincidunt, urna nec fermentum sodales, tellus "
      "felis dapibus metus, ac tincidunt erat tellus at sem. Vivamus dignissim tempor lectus cursus mattis. "
      "Suspendisse quis urna in felis ultricies congue ut quis nisi. Suspendisse pharetra finibus odio, eu condimentum "
      "magna cursus vel. Nullam dui justo, pulvinar vitae auctor vitae, tincidunt ut enim. Aliquam pellentesque ligula "
      "ipsum, sed posuere massa fermentum vitae.";
  LOG(WARNING) << test2;
  LOG(INFO) << test2;
  LOG(ERROR) << test2;
}

TEST_F(LogTest, CheckingInfoLogs) {
  int before = 0;
  int after = 0;

  google::FlushLogFilesUnsafe(google::GLOG_INFO);
  before = CoutLines("/tmp/test_log.INFO");
  LOG(INFO) << "This is a test 1" << std::flush;
  LOG(INFO) << "This is a test 2" << std::flush;
  LOG(INFO) << "This is a test 3" << std::flush;
  LOG(INFO) << "This is a test 4" << std::flush;
  LOG(INFO) << "This is a test 5" << std::flush;
  google::FlushLogFilesUnsafe(google::GLOG_INFO);
  after = CoutLines("/tmp/test_log.INFO");

  // EXPECT_EQ(after, before + 5);
}

TEST_F(LogTest, CheckingWarningLogs) {
  int before = 0;
  int after = 0;

  google::FlushLogFilesUnsafe(google::GLOG_WARNING);
  before = CoutLines("/tmp/test_log.WARNING");
  LOG(WARNING) << "This is a test 1";
  LOG(WARNING) << "This is a test 2";
  LOG(WARNING) << "This is a test 3";
  LOG(WARNING) << "This is a test 4";
  google::FlushLogFilesUnsafe(google::GLOG_WARNING);
  after = CoutLines("/tmp/test_log.WARNING");

  // EXPECT_EQ(after, before + 4);
}

TEST_F(LogTest, CheckingErrorLogs) {
  int before = 0;
  int after = 0;

  google::FlushLogFilesUnsafe(google::GLOG_ERROR);
  before = CoutLines("/tmp/test_log.ERROR");
  LOG(ERROR) << "This is a test 1";
  LOG(ERROR) << "This is a test 2";
  LOG(ERROR) << "This is a test 3";
  google::FlushLogFilesUnsafe(google::GLOG_ERROR);
  after = CoutLines("/tmp/test_log.ERROR");

  // EXPECT_EQ(after, before + 3);
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}