# Cells Blocking — TPS task

Source: 300iq Petrozavodsk Contest III (Winter 2020), problem C.

* Limits: **3 s**, **512 MiB**, stdin/stdout, `1 ≤ n, m ≤ 3000` (as in the original statement).
* The answer is unique → whitespace-insensitive comparison (`checker/checker.cpp` for TPS;
  CMS uses its built-in white-diff, no checker uploaded).
* Statements: `statement/statement.md` (English) and `statement/statement-fa.md` (Persian, font Vazirmatn under OFL in `statement/fonts/`); PDFs via `statement/build_pdf.sh`.
* CMS package: `cms_upload/` (rebuild with `cms_tools/make_cms_package.sh` after `tps gen`).
* Persian click-by-click upload guide: `CMS_UPLOAD_GUIDE.md`.

## Intended solution — O(nm)

Let F = number of free cells. If no path exists, the answer is C(F,2).

Otherwise call a cell *useful* if it is reachable from (1,1) and reaches (n,m) (two DPs).
Every path visits exactly one cell on each anti-diagonal `i+j = d`.

* **Single cuts.** A cell alone kills all paths iff it is the only useful cell on its diagonal.
  With k such cells, pairs containing at least one of them: `C(F,2) − C(F−k,2)`.
* **Pairs of non-cut cells.** Let L be the leftmost path (prefer *down*) and R the rightmost path
  (prefer *right*). On each diagonal every useful cell lies between L and R. Any 2-cut {a,b}
  has exactly one cell on L (say a) and the other on R. Fix non-cut a ∈ L on diagonal d.
  The new leftmost path L' in G−a passes through c = the next useful cell on diagonal d towards R
  (its usefulness does not depend on a); L' = (leftmost path s→c, built backwards preferring
  the left neighbour) + (leftmost path c→t). The partners of a are exactly the non-cut cells of
  R ∩ L'.
* Naively restoring L' gives O((n+m)²) (`solution/correct_path.cpp`). The model
  (`solution/model.cpp`) precomputes `fw[c]` / `bw[c]` = number of non-cut R-cells on the
  forward / backward leftmost path from c, giving O(nm) total. Answers reach ~4·10¹³ → 64-bit.

## Subtasks

| # | Name | Points | Constraints | Idea rewarded |
|:-:|:--|:-:|:--|:--|
| 0 | samples | 0 | the 3 statement examples | — |
| 1 | allfree | 8 | all cells free | closed formula (cases n=1/m=1, n=2/m=2, general) |
| 2 | n15 | 12 | n, m ≤ 15 | brute force over pairs, O((nm)³) |
| 3 | n50 | 15 | n, m ≤ 50 | fix one cell, count single cuts of the rest, O((nm)²) |
| 4 | n300 | 25 | n, m ≤ 300 | only cells on the leftmost path need fixing, O((n+m)·nm) |
| 5 | full | 40 | n, m ≤ 3000 | fast recomputation of the new leftmost path, O(nm) / O((n+m)²) |

Test inclusion: n15 ⊇ samples, n50 ⊇ n15, n300 ⊇ n50, full ⊇ allfree ∪ n300.

## Solutions

| File | Verdict | Notes |
|:--|:--|:--|
| model.cpp | model | O(nm) |
| correct_path.cpp | correct | editorial O((n+m)²) path restoring |
| brute.cpp | ST2 only | all pairs + reachability DP |
| sub1_formula.cpp | ST1 only | formula for empty grid |
| sub3_fixany.cpp | ST2–3 | O((nm)²) |
| sub4_fixleft.cpp | ST2–4 | O((n+m)·nm) |
| wrong_int.cpp | WA ST4–5 | `int` overflow |
| wrong_doublecount.cpp | WA | counts pairs of two single cuts twice (`k·(F−1)`) |
| wrong_corner.cpp | WA except ST1 | assumes (1,1) and (n,m) are free |
| wrong_samediag.cpp | WA except samples | greedy: 2-cuts only on diagonals with exactly 2 useful cells |

## Generator (`gen/gen.cpp`)

`gen <type> <n> <m> <a> <b> <corner> [tag]`, types: `rand` (block prob a/1000), `free`,
`thick` / `thickn` (dilated random monotone path, optional noise), `paths` (union of a random
monotone paths), `ring` (free border), `ladder` (band around the main diagonal with holes).
`corner`: 1 block (1,1), 2 block (n,m), 4 force both free.
