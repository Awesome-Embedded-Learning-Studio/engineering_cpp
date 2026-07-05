# 🎬 engineering-cpp

**C++23 | CMake 3.25+ | MIT License**

> **用工程实践的方式学 C++，而不只是刷语法。**

本仓库是 B 站系列教程 **[现代C++工程实践](https://space.bilibili.com/294645890/lists/7045956)** 的配套代码仓库。

---

## 🚀 从这里开始

| 你想... | 去这里 |
|---------|--------|
| 📺 看视频 | [B 站《现代 C++ 工程实践》46 期合集](https://space.bilibili.com/294645890/lists/7045956) |
| 🌱 第一次来，跟着学 | 从 [ArgParser](./src/ArgParser/) 开始（🌱 入门 ~2h） |
| 💻 直接跑代码 | `git clone` → `cmake -B build && cmake --build build`（纯 CMake，零依赖） |
| 🗺️ 看完整规划 | [ROADMAP.md](./ROADMAP.md)（当前进度 + 长期愿景） |

---

## ✨ 为什么这个教程

如果你：
- 会C++了，但是不知道拿他干啥
- 写了一段时间 C++，却不知道如何组织"真正的工程"
- 想学现代 C++ 特性（C++11 ~ C++23），但找不到合适的实战项目

说不定，这个教程适合你！笔者希望不只是教语法，而是手带你走过从需求分析、设计方案、到编码实现、再到工程落地的完整过程。每一步"为什么这样设计"都有交代。

---

## 📦 快速开始

### 环境要求

| 项目 | 最低版本 | 推荐版本 |
|------|----------|----------|
| C++ 标准 | C++23 | C++23 |
| GCC | 11+ | 13+ |
| Clang | 13+ | 16+ |
| MSVC | 193+ | 最新 |
| CMake | 3.25+ | 3.28+ |

### 克隆仓库

```bash
# 克隆主仓库
git clone https://github.com/Awesome-Embedded-Learning-Studio/engineering_cpp
cd engineering_cpp

# 初始化子模块（spoke 专栏仓：IniParser / MemoryPool）
git submodule update --init
```

### 选择你的第一个项目

如果你是 C++ 初学者，建议按以下顺序学习：

| 项目 | 难度 | 耗时 | 你将学到 |
|------|:----:|------|----------|
| **[ArgParser](./src/ArgParser/)** | 🌱 | ~2h | 命令行参数解析、模板编程、STL 容器、异常处理 |
| **[FileCopier](./src/FileCopier/)** | 🌱 | ~2h | 文件操作、进度条显示、性能测量 |
| **[IniParser](./project/IniParser/)** | ⚡ | ~6h | `string_view`、`optional`、字符串处理、CMake |
| **[MemoryPool](./project/memory_pool/)** | 🔥 | ~8h | 内存管理、线程安全、性能优化、benchmark |
| [Mimalloc](./video/mimalloc.md) · [拉取](./scripts/fetch_mimalloc.sh) | 💎 | ~4h | 开源项目源码阅读（需先拉取上游 mimalloc） |

### 构建与运行

本仓使用根 `CMakeLists.txt` 统一构建，每个子项目可用 CMake option 单独开关：

```bash
# 一键构建全部（纯 CMake，零外部依赖，clone 即 build）
cmake -B build
cmake --build build

# 跑测试（Catch2，BUILD_TESTING 默认 ON）
ctest --test-dir build --output-on-failure

# 单独关掉某个子项目
cmake -B build -DHUB_BUILD_DIRSCANNER=OFF
```

> **说明**
> - 根 `CMakeLists.txt` 统一管理所有 target：`HUB_BUILD_ARGPARSER` / `HUB_BUILD_FILECOPIER` / `HUB_BUILD_DIRSCANNER` / `HUB_BUILD_TESTS`，默认均为 `ON`
> - `argparser` 提成共享库（`src/ArgParser/`），`DirScanner` 复用它——不再有重复拷贝
> - 深度话题以 **Git Submodule** 形式链接独立 spoke 仓（IniParser / MemoryPool）
> - `documentation/` 存放 hub-native 子项目的中文教程

---

## 📚 项目清单

> **架构（hub-and-spoke）：** 本仓是 **hub**——横向技能 + 新手上路。小型教学专题内置在 `src/`（hub-native）；垂直深度话题独立成仓（spoke），通过 submodule 引入。
> 完整学习路径见 [ROADMAP.md](./ROADMAP.md)。

**难度说明**：🌱 入门 | ⚡ 初级 | 🔥 中级 | 💎 进阶

### 🌱 hub-native 小专题（本仓 `src/` 内置，统一构建）

| 项目 | 一句话简介 | 路径 | 视频 | 文档 | 状态 | 难度 |
|------|-----------|------|------|------|------|------|
| **ArgParser** | 从零实现命令行参数解析器 | [src/ArgParser/](./src/ArgParser/) | [📺](./video/argparser.md) | [📄](./documentation/tutorial/ArgParser/) | ✅ 已完结 | 🌱 |
| **FileCopier** | 带进度条的文件拷贝工具 | [src/FileCopier/](./src/FileCopier/) | [📺](./video/filecopier.md) | [📄](./documentation/tutorial/filecopier/) | ✅ 已完结 | 🌱 |
| **DirScanner** | 目录扫描与 Top-K 分析 | [src/DirScanner/](./src/DirScanner/) | [📺](./video/dirscanner.md) | [📄](./src/DirScanner/TUTORIAL.md) | ✅ 已完结 | ⚡ |

### 🔥 spoke 专栏仓（独立仓 + submodule，单独宣传）

| 项目 | 一句话简介 | 路径 | 视频 | 状态 | 难度 |
|------|-----------|------|------|------|------|
| **IniParser** | INI 配置文件解析器 | [project/IniParser/](./project/IniParser/) | [📺](./video/iniparser.md) | ✅ v1 完结 | ⚡ |
| **anatomy_memory** | 解剖内存 · C++ 内存分配器（FreeList→ThreadCache→CentralPool 三层） | [project/memory_pool/](./project/memory_pool/) | [📺](./video/memory_pool.md) | 🔥 长期开发中 · 持续填充 | 🔥 |

> **anatomy_memory** 长期开发中，会逐步接住「读开源项目」（原 Mimalloc 系列）的工程价值——mimalloc 不再作为本仓 submodule，转由 anatomy_memory 专栏承接。

### 📦 外部子模块

| 路径 | 仓库 | 说明 |
|------|------|------|
| [project/memory_pool](./project/memory_pool) | [anatomy_memory](https://github.com/Awesome-Embedded-Learning-Studio/anatomy_memory) | 解剖内存 · C++ 内存分配器（spoke，长期开发中） |
| [project/IniParser](./project/IniParser) | [Tutorial_cpp_SimpleIniParser](https://github.com/Awesome-Embedded-Learning-Studio/Tutorial_cpp_SimpleIniParser) | INI 配置文件解析器（spoke） |

---

## 📺 视频系列

### 🎬 现代C++工程实践

👉 **[是的一个城管](https://space.bilibili.com/294645890)**

| 项目 | 视频数 | 专题列表 |
|------|--------|----------|
| [ArgParser](./video/argparser.md) | 6 | 命令行参数解析器 |
| [IniParser](./video/iniparser.md) | 12 | INI配置文件解析器 |
| [FileCopier](./video/filecopier.md) | 5 | 文件拷贝与进度条 |
| [MemoryPool](./video/memory_pool.md) | 9 | 高性能内存池实现 |
| [DirScanner](./video/dirscanner.md) | 9 | 目录扫描与 Top-K 分析 |
| [Mimalloc](./video/mimalloc.md) | 5 | 开源项目源码阅读 |

<details>
<summary><b>📝 完整播放列表</b></summary>

**[现代C++工程实践](https://space.bilibili.com/294645890/lists/7045956)** — 第一季 5 系列 46 期已完结（2026-03），第二季筹备中

</details>

---

## 📖 文档说明

### 教程文档

`documentation/tutorial/` 目录下每个项目配套独立的 Markdown 文档，内容包括：

- **动机篇**：为什么需要这个组件？解决了什么问题？
- **设计篇**：数据结构如何设计？有哪些权衡？
- **实现篇**：核心逻辑的实现细节
- **回顾篇**：总结与扩展方向

每篇文档都对应视频的一个章节，既可以配合视频学习，也可以作为独立的技术文章阅读。

### 视频目录

`video/` 目录下存放各项目的视频列表和学习路线：

- [video/argparser.md](./video/argparser.md) - ArgParser 系列视频
- [video/filecopier.md](./video/filecopier.md) - FileCopier 系列视频
- [video/iniparser.md](./video/iniparser.md) - IniParser 系列视频
- [video/memory_pool.md](./video/memory_pool.md) - MemoryPool 系列视频
- [video/mimalloc.md](./video/mimalloc.md) - Mimalloc 源码阅读视频

---

## 🤝 参与贡献

欢迎提交 Issue 和 Pull Request！

### 反馈与建议

如果你在学习过程中遇到问题：

- 📺 **B站视频留言** - 响应最快，优先处理
- 🐛 **GitHub Issue** - 描述具体问题，附上复现代码
- 💬 **讨论区** - 交流学习心得，提出建议

非常感谢来自 B 站评论区的各位建议。以下为历史建议存档（暂未纳入 ROADMAP，保留溯源）:

| 平台 | 用户名 | 原评论 | 状态 |
|------|--------|--------|------|
| B站 | cache是什么 | 来自 C++26 反射机制有助于写更好用的 argparser，等编译器支持再写 | 📌 历史建议：待 GCC 支持静态反射，可能出 ArgParser v2 |

### 贡献方式

- 修正文档错别字或表述不清之处
- 补充更多使用示例
- 优化代码实现或添加测试用例
- 提出新项目建议

---

## 📜 许可证

本仓库代码以 [MIT License](./LICENSE) 开源，可自由使用、修改和分发。

文档内容保留所有权利，转载请注明出处。

---

## 🌟 如果对你有帮助

如果这个项目对你有帮助，欢迎：

- 点个 ⭐ Star，这是对我最大的鼓励
- 分享给身边学习 C++ 的朋友（然后一起开喷代码写的好烂）（逃
- 在 B 站关注我，获取更新通知

## 🔗 相关资源

> 想学 C++ 原理？配套姊妹仓 **[Tutorial_AwesomeModernCPP](https://github.com/Awesome-Embedded-Learning-Studio/Tutorial_AwesomeModernCPP)** 讲原理，本仓把原理组装成能跑的工程。

- 🧠 **[Tutorial_AwesomeModernCPP](https://github.com/Awesome-Embedded-Learning-Studio/Tutorial_AwesomeModernCPP)** — 现代 C++ 原理（偏嵌入式方向）
- 🧩 **[anatomy_memory](https://github.com/Awesome-Embedded-Learning-Studio/anatomy_memory)** — 解剖内存 · C++ 内存分配器专栏（本仓 MemoryPool spoke 的独立仓，长期开发中）

---

<p align="center">
  <i>"代码不仅是写出来的，更是设计出来的。"</i><br>
  <i>"把简单的事情做好，就是不简单。"</i><br><br>
  <a href="https://space.bilibili.com/294645890">📺 B站：是的一个城管</a>
</p>
