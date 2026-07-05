// =============================================================================
// ArgParser 单元测试(Catch2)
// 覆盖:--key=value / --key value / 短参数解析、unknown flag 抛异常、
//       required 未传抛错、非法值类型抛错、string 特化、布尔开关
// =============================================================================
#include "ArgParser.h"

#include <catch2/catch_test_macros.hpp>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
// 把 string 列表喂给 ArgParser::parse(int, char**)。
// 注意 parse 签名要求 char** 而非 const char**,这里做一次 const_cast。
void parse_args(cc::ArgParser &p,
                std::initializer_list<const char *> argv) {
  std::vector<char *> v;
  v.reserve(argv.size());
  for (const char *s : argv) {
    v.push_back(const_cast<char *>(s));
  }
  p.parse(static_cast<int>(v.size()), v.data());
}
}  // namespace

TEST_CASE("--key=value 拆分", "[argparser]") {
  cc::ArgParser p;
  p.add_argument("-n", "--count", "count", false);
  parse_args(p, {"prog", "--count=42"});
  REQUIRE(p.get<int>("count") == 42);
}

TEST_CASE("--key value 拆分", "[argparser]") {
  cc::ArgParser p;
  p.add_argument("-n", "--count", "count", false);
  parse_args(p, {"prog", "--count", "7"});
  REQUIRE(p.get<int>("count") == 7);
}

TEST_CASE("短参数 -n value", "[argparser]") {
  cc::ArgParser p;
  p.add_argument("-n", "--count", "count", false);
  parse_args(p, {"prog", "-n", "9"});
  REQUIRE(p.get<int>("count") == 9);
}

TEST_CASE("unknown flag 抛 invalid_argument", "[argparser]") {
  cc::ArgParser p;
  p.add_argument("-n", "--count", "count", false);
  REQUIRE_THROWS_AS(parse_args(p, {"prog", "--nope=1"}),
                    std::invalid_argument);
}

TEST_CASE("required 未传抛 invalid_argument", "[argparser]") {
  cc::ArgParser p;
  p.add_argument("-n", "--count", "count", /*required=*/true);
  REQUIRE_THROWS_AS(parse_args(p, {"prog"}), std::invalid_argument);
}

TEST_CASE("非法整数值 get<int> 抛 invalid_argument", "[argparser]") {
  cc::ArgParser p;
  p.add_argument("-n", "--count", "count", false);
  parse_args(p, {"prog", "--count=abc"});
  REQUIRE_THROWS_AS(p.get<int>("count"), std::invalid_argument);
}

TEST_CASE("string 特化保留空格", "[argparser]") {
  cc::ArgParser p;
  p.add_argument("-m", "--msg", "message", false);
  parse_args(p, {"prog", "--msg=hello world"});
  REQUIRE(p.get<std::string>("msg") == "hello world");
}

TEST_CASE("布尔开关 get_flag", "[argparser]") {
  cc::ArgParser p;
  p.add_flag("-v", "--verbose", "verbose");
  REQUIRE_FALSE(p.get_flag("verbose"));
  parse_args(p, {"prog", "-v"});
  REQUIRE(p.get_flag("verbose"));
}
