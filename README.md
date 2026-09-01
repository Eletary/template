# ICPC Codebook Template

这是一个可以直接扩展的 ICPC 代码板仓库。把 `.cpp` 文件按算法分类放进目录，构建脚本会按路径自然排序，并生成适合 A4 竖向单栏黑白打印的 `main.pdf`。

## 添加板子

目录名开头可加数字控制大类顺序，例如：

```text
01-data-structures/
02-graph/
03-math/
```

编号不是必须的。没有编号的目录也会被正常扫描，并按目录名自然排序；数字前缀只用于固定分类顺序，生成 PDF 时会从分类标题中自动去掉。可以混用两种命名方式，但建议只给需要固定顺序的顶层大类编号。

每个 C++ 文件开头可写以下元数据；全部都是可选的，缺少 `@title` 时会使用文件名：

```cpp
// @title Dijkstra Shortest Paths
// @brief Single-source shortest paths with non-negative weights.
// @complexity O((n + m) log n)
// @tags graph, shortest-path
```

板子中无需写 `main()`；建议保持每行不超过 `codebook.toml` 中的 `warn_line_length`，避免打印时出现长行换行。`@...` 元数据只进入标题信息条，不会在代码区重复打印。代码区包含连续行号，空行也会显示对应行号。

## 本地构建（WSL）

```bash
python3 scripts/build_codebook.py
typst compile --root . --font-path /mnt/c/Windows/Fonts codebook.typ main.pdf
```

排版固定使用 Consolas。WSL 会直接读取 Windows 字体目录；其他 Linux 环境可用 Fontist 安装 Consolas，再将 `~/.fontist/fonts` 作为 `--font-path`。

## GitHub Actions

推送到 `main` 后，`.github/workflows/codebook.yml` 会：

1. 安装 CJK 字体、Consolas 与 Typst；
2. 扫描仓库内全部 `.cpp` 并生成 PDF；
3. 上传 `icpc-codebook` artifact；
4. 若 `main.pdf` 有变化，用 GitHub Actions bot 自动提交到仓库根目录。

首次使用请确认仓库 `Settings -> Actions -> General -> Workflow permissions` 允许 **Read and write permissions**。工作流通过 Fontist 安装 Consolas，并显式接受其展示的字体许可条款；如团队政策不允许，请改用已获授权的私有字体源。

Pull Request 只构建和上传 artifact，不会写回分支。

## 定制

在 `codebook.toml` 修改封面标题、队名、赛季、忽略目录和行长警告阈值。排版细节在 `codebook.typ` 中，包括 A4 竖向单栏、目录、章节编号、PDF 书签、页眉、页码、连续灰色行号及纯黑代码。
