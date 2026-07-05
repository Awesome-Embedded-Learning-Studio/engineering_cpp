# ROADMAP — 现代 C++ 工程实践 · 长期发展愿景

> **定位：** 从「能写 C++ 代码」到「能用 C++ 独立解决真实工程问题」。
> **本文档：** 当前进度速览 + 已交付项目 + 长期学习路径愿景。
> **⚠️ 重要：** 下方「学习路径」是**长期愿景**（62 章规划，用于「我想学 X 该看哪」的导航），**不是已交付承诺**。当前实际交付见顶部「进度速览」。

---

## 📊 当前进度速览

**✅ 已交付（第一季，2026-03 完结）：**

| 维度 | 数量 | 内容 |
|------|------|------|
| 📺 视频 | **46 期** | [B 站《现代 C++ 工程实践》](https://space.bilibili.com/294645890/lists/7045956) |
| 🧩 项目 | **5 个 + 1 阅读** | ArgParser / FileCopier / DirScanner / IniParser / anatomy_memory / mimalloc(读开源) |
| 📝 教程 | 各项目配套 | `documentation/tutorial/` + 各子项目 `TUTORIAL.md` |
| 🧪 测试 | Catch2 | ArgParser 8 用例 + DirScanner 已知夹具真测 |

**📋 长期规划（0 章交付，愿景而非承诺）：** 见下方「学习路径」。

**第二季：** 筹备中。anatomy_memory 独立长期开发；miniwget 实验品已封存待将来拉取。

---

## ✅ 已交付项目（推荐学习顺序）

> **推荐顺序：** ArgParser → FileCopier → DirScanner → IniParser → anatomy_memory → mimalloc（读开源）

### 🌱 hub-native 小专题（本仓 `src/`）

| 项目 | 路径 | 难度 | 视频 | 教程 |
|------|------|:----:|------|------|
| **ArgParser** | [src/ArgParser/](./src/ArgParser/) | 🌱 | [6 期](./video/argparser.md) | [ArgParser/](./documentation/tutorial/ArgParser/) |
| **FileCopier** | [src/FileCopier/](./src/FileCopier/) | 🌱 | [5 期](./video/filecopier.md) | [filecopier/](./documentation/tutorial/filecopier/) |
| **DirScanner** | [src/DirScanner/](./src/DirScanner/) | ⚡ | [9 期](./video/dirscanner.md) | [TUTORIAL.md](./src/DirScanner/TUTORIAL.md) |

### 🔥 spoke 专栏仓（独立仓 + submodule）

| 项目 | 路径 | 难度 | 视频 | 状态 |
|------|------|:----:|------|------|
| **IniParser** | [project/IniParser/](./project/IniParser/) | ⚡ | [12 期](./video/iniparser.md) | ✅ v1 完结 |
| **anatomy_memory** | [project/memory_pool/](./project/memory_pool/) | 🔥 | [9 期](./video/memory_pool.md) | 长期开发中 |

### 💎 延伸阅读

| 项目 | 难度 | 视频 | 说明 |
|------|:----:|------|------|
| **mimalloc** | 💎 | [5 期](./video/mimalloc.md) | 读开源项目；代码用 [scripts/fetch_mimalloc.sh](./scripts/fetch_mimalloc.sh) 拉取上游 |

---

## 🗺️ 学习路径（长期愿景）

> ⚠️ 以下是长期愿景，用于导航「我想学 X 该看哪个项目/章节」，**不是已交付清单**。✅ = 已有配套项目可学；📋 = 待落地。

### Part 1：语言层 — Modern C++ 系统导读

| 知识点 | 状态 | 已交付项目 |
|--------|:----:|-----------|
| 模板编程 / 泛型 | ✅ | ArgParser |
| 标准库精讲（filesystem/chrono） | ✅ | FileCopier / DirScanner |
| 错误处理（异常/optional） | ✅ | IniParser |
| 并发基础 | ✅ | anatomy_memory |
| 智能指针 / RAII | 📋 | — |
| 值类型 / move semantics | 📋 | — |
| 类型擦除 / variant | 📋 | — |

### Part 2：工程层 — 构建可维护系统

| 知识点 | 状态 | 已交付 |
|--------|:----:|--------|
| CMake 工程组织 | ✅ | 本仓根 CMakeLists + 各项目 |
| 测试体系（Catch2） | ✅ | ArgParser / DirScanner 测试 |
| 配置系统（INI 解析） | ✅ | IniParser |
| CLI 框架设计 | ✅ | ArgParser |
| 包管理（vcpkg/Conan） | 📋 | — |
| CI/CD / Sanitizer / clang-tidy | 📋 | — |
| 日志 / 线程池 | 📋 | — |

### Part 3：系统层 — 真正懂系统

| 知识点 | 状态 | 已交付 |
|--------|:----:|--------|
| 文件系统接口 | ✅ | DirScanner |
| 内存管理 / 性能 | ✅ | anatomy_memory |
| 编译链接原理 | 📋 | — |
| IO 模型 / epoll | 📋 | — |
| 性能分析（perf） | 📋 | — |
| SIMD / 向量化 | 📋 | — |

### Part 4-7：远期方向（愿景，未交付）

- **Part 4 网络：** Socket / HTTP / JSON / RPC / io_uring
- **Part 5 高级特性：** 模板元编程 / 协程 / 设计模式 / PMR
- **Part 6 生产工程：** ABI / 安全 / Fuzzing / FFI / 调试
- **Part 7 整合：** sysmon 贯穿项目（Linux 系统监控工具，**0 章交付**，远期愿景，不设时间表）

> sysmon 是长期愿景：把所有章节组装成一个完整 Linux 系统监控工具。当前 0 章交付，作为远期方向。

---

## 🧭 进阶方向（完成上述后）

**🔧 系统方向：** 内核模块 → 文件系统驱动 → 容器运行时 → 数据库引擎
**🌐 网络方向：** HTTP Server → RPC 框架 → 分布式 KV → 消息队列
**🎮 游戏方向：** 2D 引擎 → ECS → 物理引擎 → 渲染管线
**🤖 AI 方向：** 矩阵库 → 神经网络推理 → ONNX → CUDA

**推荐开源项目阅读：**
- 系统：[muduo](https://github.com/chenshuo/muduo) / [brpc](https://github.com/apache/brpc)
- 工具：[MyTinySTL](https://github.com/Alinshans/MyTinySTL) / [fmt](https://github.com/fmtlib/fmt)
- 框架：[LLVM](https://github.com/llvm/llvm-project) / [ClickHouse](https://github.com/ClickHouse/ClickHouse)

---

## 下一步行动

- [x] DirScanner 完成集成（README + video + ROADMAP）
- [x] anatomy_memory 改名同步 + mimalloc 死链修复（拉取脚本方案）
- [ ] 第二季主题确定（anatomy_memory 长期推进 / miniwget 拉回 / 新方向）
- [ ] hub VitePress 索引站（待启动）
