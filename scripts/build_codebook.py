#!/usr/bin/env python3
"""Discover C++ templates and write the Typst build manifest."""

from __future__ import annotations

import argparse
import json
import re
import sys
import tomllib
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
CONFIG_PATH = ROOT / "codebook.toml"
BUILD_DIR = ROOT / ".build"
MANIFEST_PATH = BUILD_DIR / "manifest.json"

META_RE = re.compile(r"^\s*//\s*@(?P<key>title|brief|complexity|author)\s+(?P<value>.+?)\s*$")
STRIPPED_META_RE = re.compile(
    r"^\s*//\s*@(title|brief|complexity|author|tags)\s+.+?\s*$"
)
ORDER_PREFIX_RE = re.compile(r"^\d+[\s._-]*")
TOKEN_RE = re.compile(r"(\d+)")


def natural_key(value: str) -> tuple[object, ...]:
    return tuple(int(token) if token.isdigit() else token.casefold() for token in TOKEN_RE.split(value))


def display_name(value: str) -> str:
    value = ORDER_PREFIX_RE.sub("", value)
    value = value.replace("_", " ").replace("-", " ").strip()
    if not value:
        return "General"
    if any("a" <= char.casefold() <= "z" for char in value):
        return value.title()
    return value


def metadata_from(source: str) -> dict[str, str]:
    metadata = {"title": "", "brief": "", "complexity": "", "author": ""}
    for line in source.splitlines()[:40]:
        match = META_RE.match(line)
        if match:
            metadata[match.group("key")] = match.group("value")
    return metadata


def printable_source(source: str) -> str:
    lines = source.splitlines()
    kept = [
        line
        for index, line in enumerate(lines)
        if not (index < 40 and STRIPPED_META_RE.match(line))
    ]
    while kept and not kept[0].strip():
        kept.pop(0)
    while kept and not kept[-1].strip():
        kept.pop()

    compacted: list[str] = []
    for line in kept:
        if line.strip() or not compacted or compacted[-1].strip():
            compacted.append(line)
    return "\n".join(compacted)


def is_excluded(path: Path, excluded: set[str]) -> bool:
    return any(part in excluded or part.startswith(".") for part in path.parts)


def build_manifest(config: dict[str, object]) -> dict[str, object]:
    excluded = set(config.get("exclude_dirs", []))
    line_limit = int(config.get("warn_line_length", 92))
    team_name = str(config.get("team", "Team Template"))
    sources = sorted(
        (
            path
            for path in ROOT.rglob("*.cpp")
            if not is_excluded(path.relative_to(ROOT), excluded)
        ),
        key=lambda path: natural_key(path.relative_to(ROOT).as_posix()),
    )
    if not sources:
        raise RuntimeError("No .cpp files found. Add at least one template before building.")

    categories: dict[str, list[dict[str, object]]] = {}
    warnings: list[str] = []
    total_lines = 0

    for path in sources:
        relative = path.relative_to(ROOT)
        source = path.read_text(encoding="utf-8")
        metadata = metadata_from(source)
        printed = printable_source(source)
        lines = printed.splitlines()
        total_lines += len(lines)

        rendered_path = BUILD_DIR / "sources" / relative
        rendered_path.parent.mkdir(parents=True, exist_ok=True)
        rendered_path.write_text(printed, encoding="utf-8")

        parent_parts = relative.parent.parts
        category = " / ".join(display_name(part) for part in parent_parts) if parent_parts else "General"
        title = metadata["title"] or display_name(path.stem)
        longest = max((len(line.expandtabs(4)) for line in lines), default=0)
        if longest > line_limit:
            warnings.append(f"{relative.as_posix()}: longest line is {longest} columns (limit {line_limit})")

        categories.setdefault(category, []).append(
            {
                "title": title,
                "brief": metadata["brief"],
                "complexity": metadata["complexity"],
                "author": metadata["author"] or team_name,
                "path": relative.as_posix(),
                "render_path": rendered_path.relative_to(ROOT).as_posix(),
                "lines": len(lines),
            }
        )

    grouped = [
        {"name": category, "entries": entries}
        for category, entries in categories.items()
    ]
    return {
        "title": str(config.get("title", "ICPC Team Codebook")),
        "team": team_name,
        "footer_note": str(config.get("footer_note", "ICPC Codebook")),
        "categories": grouped,
        "stats": {
            "categories": len(grouped),
            "templates": len(sources),
            "lines": total_lines,
        },
        "warnings": warnings,
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--strict", action="store_true", help="fail when a source line exceeds warn_line_length")
    args = parser.parse_args()

    with CONFIG_PATH.open("rb") as config_file:
        config = tomllib.load(config_file)

    manifest = build_manifest(config)
    BUILD_DIR.mkdir(exist_ok=True)
    MANIFEST_PATH.write_text(
        json.dumps(manifest, ensure_ascii=False, indent=2) + "\n",
        encoding="utf-8",
    )

    stats = manifest["stats"]
    print(
        f"Discovered {stats['templates']} templates in {stats['categories']} categories "
        f"({stats['lines']} source lines)."
    )
    for warning in manifest["warnings"]:
        print(f"warning: {warning}", file=sys.stderr)
    if args.strict and manifest["warnings"]:
        return 2
    print(f"Wrote {MANIFEST_PATH.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
