/*************************************************************************
 * Copyright (C) [2024] by Cambricon, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *************************************************************************/
#ifndef TEST_MLU_OP_GTEST_INCLUDE_CHECK_TOOLS_H_
#define TEST_MLU_OP_GTEST_INCLUDE_CHECK_TOOLS_H_

#include <string>
#include <sstream>

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

namespace {  // NOLINT
std::string fmt() { return ""; }
template <typename lhs, typename... T>
std::string fmt(lhs first, T... args) {
  std::ostringstream oss;
  oss << first << fmt(args...);
  return oss.str();
}
}  // namespace

#define GTEST_CHECK(condition, ...)                                          \
  if (unlikely(!(condition))) {                                              \
    ADD_FAILURE() << fmt("Check failed: ", #condition, ". ", ##__VA_ARGS__); \
    throw std::invalid_argument(std::string(__FILE__) + " +" +               \
                                std::to_string(__LINE__));                   \
  }

#define GTEST_WARNING(condition, ...)                                     \
  if (unlikely(!(condition))) {                                           \
    LOG(WARNING) << "Check failed: " #condition ". " << fmt(__VA_ARGS__); \
  }

#endif  // TEST_MLU_OP_GTEST_INCLUDE_CHECK_TOOLS_H_
