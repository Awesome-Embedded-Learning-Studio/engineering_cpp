// =============================================================================
// DirScanner 单元测试(Catch2)
// 替代原 assert(result.file_count >= 0)(size_t 恒真,等于没测)。
// 用已知夹具目录断言具体 file_count / dir_count / ext_count。
// =============================================================================
#include "dir_scan.h"

#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

namespace {
// 构造已知夹具:
//   <root>/a.txt     (1 byte)
//   <root>/b.cpp     (2 bytes)
//   <root>/c.md      (3 bytes)
//   <root>/sub/d.txt (1 byte)
//   <root>/sub/e.cpp (2 bytes)
// 期望:file_count = 5, dir_count = 1 (只有 sub;root 自身不计入)
//      ext_count: .txt=2, .cpp=2, .md=1
fs::path make_fixture() {
  const auto root =
      fs::temp_directory_path() / "engineering_cpp_dirscanner_test";
  fs::remove_all(root);
  fs::create_directories(root / "sub");

  // 命名 ofstream 变量:rvalue 不能绑定到 operator<<(ostream&, const char*)
  // 的非 const 左值引用,必须用 lvalue。
  const auto write = [](const fs::path &p, const std::string &content) {
    std::ofstream f(p);
    f << content;
  };
  write(root / "a.txt", "a");
  write(root / "b.cpp", "bb");
  write(root / "c.md", "ccc");
  write(root / "sub" / "d.txt", "d");
  write(root / "sub" / "e.cpp", "ee");
  return root;
}
}  // namespace

TEST_CASE("DirScanner 统计已知夹具", "[dirscanner]") {
  const auto root = make_fixture();
  DirScanner scanner(3);
  const ScanResult result = scanner.scan(root);

  REQUIRE(result.file_count == 5);
  REQUIRE(result.dir_count == 1);
  REQUIRE(result.ext_count.at(".txt") == 2);
  REQUIRE(result.ext_count.at(".cpp") == 2);
  REQUIRE(result.ext_count.at(".md") == 1);
  REQUIRE(result.largest_files.size() == 5);

  fs::remove_all(root);
}

TEST_CASE("DirScanner 不存在的路径不崩溃", "[dirscanner]") {
  DirScanner scanner(3);
  const ScanResult result =
      scanner.scan("/no/such/path/__engineering_cpp_test__");
  REQUIRE(result.file_count == 0);
}
