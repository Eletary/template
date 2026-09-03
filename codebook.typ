#let book = json(".build/manifest.json")

#set document(
  title: book.title,
  author: book.team,
  keywords: ("ICPC", "competitive programming", "codebook"),
)

#set page(
  paper: "a4",
  margin: (top: 13mm, bottom: 13mm, inside: 13mm, outside: 10mm),
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
  size: 9pt,
  fill: black,
)
#set par(leading: 0.56em)
#set heading(numbering: "1.1")
#set outline(indent: 1.15em)
#set outline.entry(fill: repeat([.], gap: 0.18em))
#show outline.entry.where(level: 1): set text(weight: "bold")
#show heading.where(level: 1): set text(size: 11pt, weight: "bold")
#show heading.where(level: 2): set text(size: 9.5pt, weight: "bold")
#show raw: set text(font: "Consolas", size: 8.5pt)
#set raw(theme: "monochrome.tmTheme", tab-size: 4)

#show raw.line: line => {
  box(
    width: 2.4em,
    align(right, text(size: 6.5pt, fill: luma(58%), str(line.number))),
  )
  h(0.55em)
  line.body
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
  #set text(size: 7pt, fill: luma(30%))
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
  #if entry.author != "" [
    #v(1.5pt)
    *AUTHOR* #entry.author
  ]
]

#align(center)[
  #v(7mm)
  #text(size: 27pt, weight: "bold", tracking: 0.06em)[#book.title]
  #v(5mm)
  #line(length: 76%, stroke: 0.8pt + black)
  #v(4mm)
  #text(size: 11pt, weight: "bold", tracking: 0.04em)[#book.team]
  #v(7mm)
  #block(width: 76%)[
    #line(length: 100%, stroke: 0.45pt + luma(45%))
    #v(4pt)
    #grid(
      columns: (1fr, 1fr, 1fr),
      [
        #text(size: 16pt, weight: "bold")[#book.stats.categories]
        #h(3pt)
        #text(size: 6.5pt, fill: luma(35%))[CATEGORIES]
      ],
      [
        #text(size: 16pt, weight: "bold")[#book.stats.templates]
        #h(3pt)
        #text(size: 6.5pt, fill: luma(35%))[TEMPLATES]
      ],
      [
        #text(size: 16pt, weight: "bold")[#book.stats.lines]
        #h(3pt)
        #text(size: 6.5pt, fill: luma(35%))[SOURCE LINES]
      ],
    )
    #v(4pt)
    #line(length: 100%, stroke: 0.45pt + luma(45%))
  ]
]

#pagebreak()

#if book.checklist.title != "" {
  align(center, text(size: 18pt, weight: "bold")[#book.checklist.title])
  v(3mm)
  for paragraph in book.checklist.intro {
    align(center, text(size: 8pt, fill: luma(35%))[#paragraph])
    v(2pt)
  }
  v(2mm)
  grid(
    columns: (1fr, 1fr),
    column-gutter: 7mm,
    row-gutter: 4mm,
    ..book.checklist.sections.map(section => block(
      breakable: false,
      inset: 5pt,
      stroke: 0.4pt + luma(72%),
      radius: 2pt,
    )[
      #if section.title != "" {
        text(size: 10pt, weight: "bold")[#section.title]
        v(2pt)
        line(length: 100%, stroke: 0.35pt + luma(75%))
        v(2pt)
      }
      #for paragraph in section.paragraphs {
        text(size: 7.5pt)[#paragraph]
        v(2pt)
      }
      #for item in section.items {
        grid(
          columns: (0.9em, 1fr),
          column-gutter: 1pt,
          text(size: 8pt, weight: "bold")[!],
          text(size: 7.5pt)[#item],
        )
        v(2.5pt)
      }
    ]),
  )
  pagebreak()
}

#outline(title: [Quick Index], depth: 2)

#pagebreak()

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
