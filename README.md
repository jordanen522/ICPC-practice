# ICPC Practice

Practice problems from the ICPC Pacific Northwest Regional, with official
problem statements, judge solutions, and test data.

## Contents

| Folder | What's in it |
| --- | --- |
| [`pnw-2025/div1/`](pnw-2025/div1) | PNW Regional 2025, Division 1 (problems A–M) |
| [`pnw-2025/div2/`](pnw-2025/div2) | PNW Regional 2025, Division 2 (problems A–M) |
| [`div1-baseline/`](div1-baseline) | Three older problems (2011, 2013, 2014) used to decide whether a team belongs in Division 1. See [`README_and_HINTS.txt`](div1-baseline/README_and_HINTS.txt); the algorithm hints are at the very bottom, so scroll only if you want spoilers. |

Each PNW 2025 problem folder looks like this:

```
A-bouquet-of-balloons/
├── statement.pdf   # problem statement
├── sample/         # sample tests from the statement (N.in / N.ans)
└── solutions/      # judge solutions (C++, Java, Python)
```

### Division 1 and Division 2

| Div 1 | Div 2 |
| --- | --- |
| A — Bouquet of Balloons | A — An Elephant Problem |
| B — Bus Seating | B — Call for Problems Round 3 |
| C — Closest Equal Pair | C — GPA Computation |
| D — Farthest City | D — Honkai Stress Relief |
| E — Fractal Painting | E — Missed Alarm |
| F — Friendships | F — Strawberry |
| G — Honkai Stress Relief | G — Bouquet of Balloons |
| H — Kth King | H — Fractal Painting |
| I — Pair Linked Mokepon | I — Server Corridor |
| J — Server Room | J — Shh |
| K — Shh | K — Solidarity of the Happy Cats |
| L — Training Round 4 | L — Training Round 4 |
| M — Triangle of Triangles | M — Triangle of Triangles |

Six problems appear in both divisions with the same tests.

## Hidden test data

The full judge test data (`secret/` folders) is about 1.2 GB, so it isn't
stored in git. Download it from the
[Releases page](../../releases/tag/pnw-2025-tests) and unzip it **at the root
of this repo**; each problem's `secret/` folder lands in the right place:

```sh
unzip pnw-2025-div1-hidden-tests.zip
unzip pnw-2025-div2-hidden-tests.zip
```

`secret/` is in `.gitignore`, so the extracted files won't show up as changes.

## Testing a solution

Compile, then compare your output against each `.ans` file:

```sh
g++ -O2 -std=c++17 -o sol mysolution.cpp
for t in sample/*.in; do
  ./sol < "$t" | diff -q - "${t%.in}.ans" > /dev/null && echo "PASS $t" || echo "FAIL $t"
done
```

Some problems accept floating-point answers within a tolerance, or more than one
correct output. Check the statement if `diff` reports a mismatch you think is
correct.

## Credits

Problems, test data, and judge solutions are by the ICPC Pacific Northwest
Regional judges and problem setters. This repo is an unofficial copy for
practice.
