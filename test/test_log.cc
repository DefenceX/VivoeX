//
// MIT License
//
// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the 'Software'), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial
// portions of the Software.
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
#include "gva.h"

namespace gva {

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
// Tests that Foo does Xyz.
TEST_F(LogTest, CheckingLogs) {
  int counter = 0;

  if (std::ifstream fs("/var/log/gva.log"); fs.is_open()) {
    for (std::string line; getline(fs, line);) {
      counter++;
    }
  } else {
    FAIL() << "Could not open log file.";
  }
  // We dont expect LOG_DEBUG messages if code not compiled with DEBUG
  EXPECT_EQ(counter, 6);
}

}  // namespace gva

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}