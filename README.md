# HW 3 — Procedural Land-Mass Generator  
*Author : **Hongju Son***  

## Overview  
This program randomly “drops” a configurable number of **dirt-balls** onto a 2-D grid and evolves their overlapping impacts into a height-map.  
After **normalising** the heights to the range 0 – 255 it converts them into ASCII terrain symbols (water → `#`, coast → `~`, plains → `.`, hills → `-`, highlands → `*`, mountains → `^`). Three text files are written so you can inspect every stage. :contentReference[oaicite:0]{index=0}  

| Stage | File | Contents |
|-------|------|----------|
| 1. Raw height values | `raw_landmass.txt` | Un-normalised integer heights |
| 2. Normalised height values | `normalized_landmass.txt` | 0 – 255 scaled heights |
| 3. Final map | `final_landmass.txt` | Single ASCII character per cell |

All three maps are also echoed to `stdout` so you can watch the progression live.  

---

## Build instructions  

```bash
# C++ (links libstdc++ automatically)
g++ -std=c++11 -Wall -Wextra -O2 -o terrain son_hongju_hw3.cpp

# C (if you prefer C and have removed <iostream>/<vector> etc.)
# gcc -std=c11 -Wall -Wextra -O2 -o terrain son_hongju_hw3.cpp -lm

The only external dependency is the C/C++ standard library; no third-party libraries are required.
Running the program

./terrain [-s SEED]

If the optional -s SEED flag is given, all random numbers are produced with that seed, ensuring deterministic output (useful for grading and debugging).
After the executable starts, it interactively asks for:

    Grid width

    Grid height

    Water-line threshold (40 – 200)

    Dirt-ball radius (≥ 2)

    Dirt-ball power (≥ radius)

    Number of dirt-balls to drop

Example session:

$ ./terrain -s 1234
Enter grid width:
20
Enter grid heigth:
10
Enter value for waterline (40-200)
100
Enter dirtball radius (minimum 2):
3
Enter dirtball power rating (minimum = radius):
3
Enter number of dirtballs to drop:
8

When the program finishes you will find raw_landmass.txt, normalized_landmass.txt, and final_landmass.txt in the same directory, alongside a nicely printed ASCII map in the terminal.
Important implementation details
Function	Responsibility
dropDirtBall	Adds a power-weighted hemisphere of height around a random center; uses Euclidean distance to taper the impact.
boundsCheck	Ensures indices never leave the grid.
normalizeMap	Linearly rescales heights so the global maximum becomes 255.
finalizeMap	Converts numeric heights to symbols using the user’s water-line as the main threshold.
frand	Thin wrapper around rand() that returns a floating-point number ∈ [0, 1).
See the source for more in-depth comments.
Tips & hints

    Re-seeding – run with different seeds to discover wildly different continents.

    Performance – for very large grids consider switching the inner loops to row-major order for better cache locality.

    Visualisation – import final_landmass.txt into an editor that supports ANSI colours and do a global search/replace (#→blue, ~→cyan, etc.) for a quick coloured map.

    Metadata
    Submission ID : 184213910 • Score : 50/50 • Timestamp : 2023-06-27 23:07 (PDT) 
