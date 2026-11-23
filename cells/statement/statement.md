---
title: "Cells Blocking"
---

| Time limit | Memory limit | Input | Output |
|:-:|:-:|:-:|:-:|
| 3 seconds | 512 MiB | standard input | standard output |

You are given a grid with $n$ rows and $m$ columns. Rows are numbered $1$ to $n$ from top to bottom and columns $1$ to $m$ from left to right. Every cell is either *free* or *blocked*.

A *correct path* is a path from cell $(1,1)$ to cell $(n,m)$ that, at every step, moves either one cell **down** or one cell **right**, and that visits only free cells (including its first and last cell).

You must count the number of ways to choose **two different free cells** and block them so that, afterwards, **no correct path exists**. Choices are unordered: blocking cells $A$ and $B$ is the same as blocking $B$ and $A$.

Note that it is allowed to block cells $(1,1)$ and $(n,m)$. They may also already be blocked in the initial grid. If no correct path exists initially, every choice of two free cells counts.

## Input

The first line contains two integers $n$ and $m$ — the number of rows and columns.

Each of the next $n$ lines contains a string of exactly $m$ characters. The $j$-th character of the $i$-th of these lines is `.` if cell $(i,j)$ is free and `*` if it is blocked.

## Output

Print one integer — the number of unordered pairs of different free cells whose blocking leaves no correct path from $(1,1)$ to $(n,m)$.

Note that the answer may not fit into a 32-bit integer type.

## Constraints

* $1 \le n, m \le 3000$
* Each grid character is `.` or `*`.

## Subtasks

| Subtask | Points | Additional constraints |
|:-:|:-:|:--|
| 1 | 8  | All cells of the grid are free. |
| 2 | 12 | $n, m \le 15$ |
| 3 | 15 | $n, m \le 50$ |
| 4 | 25 | $n, m \le 300$ |
| 5 | 40 | No additional constraints. |

## Examples

### Example 1

Input:
```
3 3
...
...
...
```

Output:
```
17
```

Blocking $(1,1)$ or $(3,3)$ together with any other cell destroys all paths; there are $8+8-1=15$ such pairs. Additionally, the pairs $\{(1,2),(2,1)\}$ and $\{(3,2),(2,3)\}$ work, so the answer is $15+2=17$.

### Example 2

Input:
```
3 3
.**
.*.
...
```

Output:
```
15
```

Blocking any two of the $6$ free cells works, so the answer is $\binom{6}{2}=15$.

### Example 3

Input:
```
3 4
****
....
****
```

Output:
```
6
```

There is no correct path initially, so any two of the $4$ free cells can be chosen: $\binom{4}{2}=6$.
