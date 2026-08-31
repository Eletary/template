#let book = json(".build/manifest.json")

#set document(
  title: book.title,
  author: book.team,
  keywords: ("ICPC", "competitive programming", "codebook"),
)

#set page(
  paper: "a4",
  flipped: true,
  margin: (top: 13mm, bottom: 13mm, inside: 11mm, outside: 9mm),
  binding: left,
  header-ascent: 8pt,
  footer-descent: 8pt,
  header: context {
    let page-number = counter(page).get().first()
    if page-number > 1 {
      let previous = query(heading.where(level: 2).before(here()))
      let current = if previous.len() > 0 { previous.last().body } else { book.title }
      text(size: 6.5pt, fill: luma(42%))[
        #smallcaps(book.footer_note)
        #h(1fr)
        #current
      ]
      line(length: 100%, stroke: 0.35pt + luma(68%))
    }
  },
  footer: context {
    if counter(page).get().first() > 1 {
      line(length: 100%, stroke: 0.35pt + luma(72%))
      text(size: 6.3pt, fill: luma(42%))[
        #book.team
        #h(1fr)
        #counter(page).display("1 / 1", both: true)
      ]
    }
  },
)

#set text(
  font: ("Arial", "Microsoft YaHei", "Noto Sans CJK SC"),
  size: 8.5pt,
  fill: black,
)
#set par(leading: 0.56em)
#set heading(numbering: "1.1")
#set outline(indent: 1.15em)
#set outline.entry(fill: repeat([.], gap: 0.18em))
#show outline.entry.where(level: 1): set text(weight: "bold")
#show heading.where(level: 1): set text(size: 11pt, weight: "bold")
#show heading.where(level: 2): set text(size: 9.5pt, weight: "bold")
#show raw: set text(font: "Consolas", size: 7pt)
#set raw(theme: none, tab-size: 4)

#show raw.line: line => {
  if line.text.trim() == "" {
    box(height: 2.4pt)[]
  } else {
    box(
      width: 2.35em,
      align(right, text(size: 5.5pt, fill: luma(58%), str(line.number))),
    )
    h(0.55em)
    line.body
  }
}

#let template-meta(entry) = block(
  width: 100%,
  breakable: false,
  inset: (x: 4pt, y: 3pt),
  fill: luma(96%),
  stroke: 0.35pt + luma(76%),
  radius: 1pt,
  below: 3pt,
)[
  #set text(size: 6.2pt, fill: luma(30%))
  #grid(
    columns: (1fr, auto),
    column-gutter: 4pt,
    [*FILE* #entry.path],
    [*LINES* #entry.lines],
  )
  #if entry.brief != "" [
    #v(1.5pt)
    *USE* #entry.brief
  ]
  #if entry.complexity != "" [
    #h(1fr)
    *COST* #entry.complexity
  ]
  #if entry.tags != "" [
    #v(1.5pt)
    *TAGS* #entry.tags
  ]
]

#align(center)[
  #v(7mm)
  #text(size: 25pt, weight: "bold", tracking: 0.04em)[#book.title]
  #v(5mm)
  #line(length: 68%, stroke: 1pt + black)
  #v(5mm)
  #text(size: 13pt, weight: "bold")[#book.team]
  #h(8pt)
  #text(size: 9pt, fill: luma(38%))[Season #book.season]
  #v(8mm)
  #grid(
    columns: (1fr, 1fr, 1fr),
    gutter: 8pt,
    block(inset: 7pt, stroke: 0.5pt + luma(60%))[
      #text(size: 18pt, weight: "bold")[#book.stats.categories]
      #linebreak()
      #text(size: 7pt)[CATEGORIES]
    ],
    block(inset: 7pt, stroke: 0.5pt + luma(60%))[
      #text(size: 18pt, weight: "bold")[#book.stats.templates]
      #linebreak()
      #text(size: 7pt)[TEMPLATES]
    ],
    block(inset: 7pt, stroke: 0.5pt + luma(60%))[
      #text(size: 18pt, weight: "bold")[#book.stats.lines]
      #linebreak()
      #text(size: 7pt)[SOURCE LINES]
    ],
  )
  #v(5mm)
  #text(size: 6.5pt, fill: luma(42%))[
    A4 - two-column - monochrome - Consolas
  ]
]

#v(8mm)
#outline(title: [Quick Index], depth: 2)

#pagebreak()
#set page(columns: 2)
#set columns(gutter: 9pt)

#for category in book.categories {
  heading(level: 1, category.name)
  line(length: 100%, stroke: 0.55pt + black)
  for entry in category.entries {
    heading(level: 2, entry.title)
    template-meta(entry)
    block(
      width: 100%,
      above: 2pt,
      below: 6pt,
      raw(read(entry.render_path), lang: "cpp", block: true),
    )
  }
}
