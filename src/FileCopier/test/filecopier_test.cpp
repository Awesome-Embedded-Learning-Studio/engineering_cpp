// =============================================================================
// FileCopier 单元测试(Catch2)
// 覆盖:正常拷贝(内容/大小一致)/ 大文件分块 / 空文件 / 源不存在
// =============================================================================
#include "fcopy.h"

#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>

namespace fs = std::filesystem;

namespace {
const fs::path fixture_root() {
  return fs::temp_directory_path() / "engineering_cpp_filecopier_test";
}

std::string make_src(const std::string &name, const std::string &content) {
  fs::create_directories(fixture_root());
  const auto path = fixture_root() / name;
  std::ofstream f(path);
  f << content;
  return path.string();
}

std::string dst(const std::string &name) {
  fs::create_directories(fixture_root());
  return (fixture_root() / name).string();
}

std::string read_all(const std::string &path) {
  std::ifstream f(path);
  return std::string((std::istreambuf_iterator<char>(f)),
                     std::istreambuf_iterator<char>());
}
}  // namespace

TEST_CASE("FileCopier 正常拷贝内容一致", "[filecopier]") {
  fs::remove_all(fixture_root());
  const auto src = make_src("src_normal.txt", "hello filecopier\n");
  const auto d = dst("dst_normal.txt");

  FileCopier fc;
  REQUIRE(fc.copy(src, d));
  REQUIRE(fs::exists(d));
  REQUIRE(fs::file_size(d) == fs::file_size(src));
  REQUIRE(read_all(d) == "hello filecopier\n");

  fs::remove_all(fixture_root());
}

TEST_CASE("FileCopier 大文件分块(1KB chunk,触发多轮)", "[filecopier]") {
  fs::remove_all(fixture_root());
  const std::string big(100000, 'X');
  const auto src = make_src("src_big.bin", big);
  const auto d = dst("dst_big.bin");

  FileCopier fc(1024);  // 1KB chunk,默认 8KB,触发多次分块
  REQUIRE(fc.copy(src, d));
  REQUIRE(fs::file_size(d) == big.size());
  REQUIRE(read_all(d) == big);

  fs::remove_all(fixture_root());
}

TEST_CASE("FileCopier 空文件", "[filecopier]") {
  fs::remove_all(fixture_root());
  const auto src = make_src("src_empty.txt", "");
  const auto d = dst("dst_empty.txt");

  FileCopier fc;
  REQUIRE(fc.copy(src, d));
  REQUIRE(fs::exists(d));
  REQUIRE(fs::file_size(d) == 0);

  fs::remove_all(fixture_root());
}

TEST_CASE("FileCopier 源不存在返回 false", "[filecopier]") {
  fs::remove_all(fixture_root());
  FileCopier fc;
  REQUIRE_FALSE(fc.copy("/no/such/__engineering_cpp_test__.txt", dst("dst_nope.txt")));
  fs::remove_all(fixture_root());
}
