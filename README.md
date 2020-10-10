# Npuzzle

<a href="https://en.wikipedia.org/wiki/15_puzzle">Npuzzle game</a>

### Get started
```
git clone https://github.com/go0h/Npuzzle.git && cd Npuzzle && make
```

### Usage
```
Usage: ./Npuzzle puzzle_file [OPTION]... [FILE]...

	-h, --help			display this help and exit
    -s, --source <source_file>	start state of puzzle
	-t, --target <target_file>	final state of puzzle
	-p, --print			print moves
	-H, --heuristic heuristic_method:
	   [M]   - only Manhattan distance between tiles
	   [LC]  - Manhattan distance and Linear conflicts
	   [OPT] - Optimal (M + LC + Corners + Last move)
	-a, --algo algorithm:
	   [A]   - for A* algorithm
	   [IDA] - for Iterative A* algorithm
	   [G]   - for Greedy algorithm

```

### Solver

#### Default target board state SNAIL:
```
1  2  3  4
12 13 14 5
11 0  15 6
10 9  8  7
```

The following algorithms are implemented: <a href="https://en.wikipedia.org/wiki/A*_search_algorithm">AStar</a>, <a href="https://en.wikipedia.org/wiki/Iterative_deepening_A*">IDAStar</a>, <a href="https://en.wikipedia.org/wiki/Greedy_algorithm">Greedy search</a>.

The following heuristics functions are implemented: 
  1. Manhattan distance
  2. Linear conflicts
  3. Corners conflict
  4. Last move

Finding the optimal path is used by default.
If you need quickly to find a path or board side more than 4, then you need to use the Greedy search. 
