# ICPC Codebook Template

A ready-to-use repository for building a printable ICPC team codebook. Organize your C++ templates by algorithm category, and the build script will collect every `.cpp` file, sort them naturally by path, and generate `main.pdf` in the repository root.

The generated codebook is designed for A4 portrait printing with a single-column layout, Consolas code, continuous line numbers, and high-contrast monochrome syntax highlighting.

## Adding Templates

Create directories for your algorithm categories and place C++ files inside them. You may add numeric prefixes to control the order of top-level categories:

```text
01-data-structures/
02-graph/
03-math/
```

Numeric prefixes are optional. Directories without a prefix are also included and sorted naturally by name. Prefixes are removed from the category titles shown in the PDF. Both styles can be mixed, although numbering only the top-level categories whose order matters is usually the clearest approach.

Each C++ file may start with the following optional metadata:

```cpp
// @title Dijkstra Shortest Paths
// @brief Single-source shortest paths with non-negative edge weights.
// @complexity O((n + m) log n)
// @author Your Name
```

If `@title` is omitted, the filename is used as the template title. If `@author` is omitted, the team name from `codebook.toml` is used. Metadata is displayed in the information bar above the template and is not repeated in the printed code.

Templates do not need a `main()` function. Keep lines within the configured `warn_line_length` limit to avoid wrapping when printed. Every source line receives a continuous line number, including blank lines.

## Building Locally

Install Python 3 and Typst 0.15.1 or later. Then run:

```bash
python3 scripts/build_codebook.py
typst compile --root . --font-path /path/to/your/fonts codebook.typ main.pdf
```

The directory passed to `--font-path` must contain Consolas. If your metadata or comments use characters not covered by Consolas, also provide a suitable fallback font in that directory. You may instead select a different installed monospace font in `codebook.typ`.

The generated PDF is written to `main.pdf` in the repository root.

## Configuration

All general codebook settings are stored in `codebook.toml`:

| Option | Description |
| --- | --- |
| `title` | Main title shown on the cover and stored in the PDF metadata. |
| `team` | Team name shown on the cover and page footer. It is also the default author for templates without `@author`. |
| `season` | Season or year shown on the cover. |
| `footer_note` | Short label displayed in the page header. |
| `exclude_dirs` | Directory names skipped while recursively scanning for `.cpp` files. |
| `warn_line_length` | Source lines longer than this value produce a build warning but do not fail the build. |

Example:

```toml
title = "ICPC Team Codebook"
team = "Team Template"
season = "2026"
footer_note = "ICPC Codebook"
exclude_dirs = [".git", ".build", ".github", "scripts"]
warn_line_length = 92
```

## GitHub Actions

When relevant codebook files are pushed to `main`, `.github/workflows/codebook.yml` automatically:

1. Installs the required fonts and Typst.
2. Scans all `.cpp` files and generates the codebook manifest.
3. Compiles `main.pdf`.
4. Uploads the PDF as an artifact named `icpc-codebook`.
5. Commits the refreshed `main.pdf` to the repository when its contents have changed.

Pull requests build and upload the PDF for verification but never write changes back to the branch. README-only changes do not trigger a PDF rebuild.

Before using the workflow for the first time, open **Settings → Actions → General → Workflow permissions** and enable **Read and write permissions**.

The default workflow installs Consolas through Fontist and explicitly accepts the displayed font license terms. If your team policy does not allow this, replace that step with an approved font source or select a freely licensed monospace font in `codebook.typ`.

## Further Customization

Edit `codebook.typ` to customize the A4 portrait layout, table of contents, section numbering, PDF bookmarks, headers, page numbers, line numbers, fonts, and code presentation. The printer-friendly syntax highlighting theme is defined in `monochrome.tmTheme`.

## Repository Structure

```text
.
├── .github/workflows/codebook.yml  # Automated PDF build
├── scripts/build_codebook.py       # C++ scanner and manifest generator
├── codebook.toml                   # Team and build settings
├── codebook.typ                    # Typst document layout
├── monochrome.tmTheme              # Print-friendly syntax highlighting
├── main.pdf                        # Generated codebook
└── category/*.cpp                  # Your algorithm templates
```
