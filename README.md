*This project has been created as part of the 42 curriculum by bhernand, mdiakono.*

---

## Description

`push_swap` is a sorting algorithm project that sorts a stack of integers using a limited set of operations on two stacks, `A` and `B`. The goal is to sort the numbers present in stack `A` in ascending order with the fewest possible operations.

The project implements four distinct sorting strategies, each suited to a different input size or disorder profile. A built-in adaptive mode selects the optimal strategy automatically by measuring how disordered the input is before any moves are made.

---

## Instructions

### Compilation

```bash
make
```

This produces the `push_swap` executable. No external libraries are required. Only `write`, `malloc`, `free`, and `exit` are used from the C standard library.

To clean object files:

```bash
make clean
```

To remove all build artifacts including the executable:

```bash
make fclean
```

To recompile from scratch:

```bash
make re
```

---

### Execution

```bash
./push_swap [FLAGS] <integers>
```

The integers can be passed as separate arguments or as a single quoted string:

```bash
./push_swap 5 3 1 4 2
./push_swap "5 3 1 4 2"
```

---

### Flags


| `--simple` | Force the O(n²) selection/insertion sort strategy |

| `--medium` |  Force the O(n√n) chunk-based sort strategy |

| `--complex` |  Force the O(n log n) LSD radix sort strategy |

| `--adaptive` |  (Default) Automatically select the strategy based on the disorder metric |

| `--bench` |  Print benchmarking data to `stderr`: disorder percentage, chosen strategy and complexity class, total operation count, and individual counts for all 11 operations |

If no strategy flag is provided, `--adaptive` is used by default.

Flags can be combined. For example, to benchmark while forcing the complex strategy:

```bash
./push_swap --complex --bench 42 17 8 99 3
```
---

### Operations

The program produces a sequence of the following operations, one per line, on `stdout`:

| Operation | Effect |
|-----------|--------|
| `sa` | Swap the first two elements of stack A |
| `sb` | Swap the first two elements of stack B |
| `ss` | `sa` and `sb` simultaneously |
| `pa` | Push the top of B onto A |
| `pb` | Push the top of A onto B |
| `ra` | Rotate A upward (top goes to bottom) |
| `rb` | Rotate B upward (top goes to bottom) |
| `rr` | `ra` and `rb` simultaneously |
| `rra` | Reverse rotate A (bottom goes to top) |
| `rrb` | Reverse rotate B (bottom goes to top) |
| `rrr` | `rra` and `rrb` simultaneously |

---

### Performance Targets

| Input size | Excellent threshold |
|------------|---------------------|
| 100 numbers | < 700 operations |
| 500 numbers | < 5 500 operations |

---
### Error Handling
The program strictly validates all inputs. It will output Error to stderr if:Any argument is not a valid integer.Any value exceeds the minimum or maximum bounds of a standard 32-bit signed integer ($\pm 2,147,483,647$).There are duplicate values across the inputs.

## Algorithms

### 1. Simple — O(n²) — Selection/Insertion Sort

**Invoked by:** `--simple`, or `--adaptive` when disorder < 0.2

#### Behavior

For inputs of five elements or fewer, the algorithm pushes the minimums to B iteratively, sorts the remaining three elements in A using a hardcoded decision tree (`sort_three`), then pushes all elements from B back to A. This covers the special cases (3, 4, 5 elements) exhaustively and optimally without any rotation overhead.

For larger inputs with low disorder (the adaptive trigger), the algorithm performs an insertion-sort-like pass: it checks for the minimum number and pass it to B doing ra and pb, once we have all the numbers in B in descending order we push them back into A.

#### Why O(n²)

Each element that needs repositioning may require up to O(n) rotations to reach its target position in A. Since up to n elements may need to be repositioned, the worst case is O(n) × O(n) = **O(n²)** total operations.

#### Why this strategy for low disorder

When fewer than 20% of pairs are inverted, the input is nearly sorted. The O(n²) algorithm has a very low constant factor on nearly-ordered data because most elements are already in place and require few or no moves. Applying a heavier algorithm (chunk sort or radix) would spend more operations on bookkeeping than the simple pass spends on actual displacement.

---

### 2. Medium — O(n√n) — Chunk-Based Sort

**Invoked by:** `--medium`, or `--adaptive` when 0.2 ≤ disorder < 0.5

#### Behavior

**Coordinate compression** is applied first: all input values are mapped to their rank indices 0..n-1. This eliminates gaps between values and negative numbers, making range-based reasoning straightforward.

**Phase 1 — Partition into B:**
The sorted range 0..n-1 is divided into chunks of size ~√n (chunk size 15 for n ≤ 100, chunk size 30 for n > 100). A sliding window advances through the chunks. For each window, any element in A that belongs to the current chunk is pushed to B (`pb`). Elements that belong to an earlier chunk (already below the current threshold) are sent to the bottom of B via `rb`, so that B remains roughly ordered with larger indices at the top.

**Phase 2 — Reconstruct A:**
The algorithm loops through Stack A. It looks at the number currently at env->top_a.
If that number belongs to Chunk 1, it immediately executes pb to throw it into Stack B.
If it does not belong to Chunk 1, it checks the bottom of Stack A using rra or rotates using ra to find an element that does.

**Phase 3 —  The Sorting and Pulling Phase (Stack B $\rightarrow$ Stack B $\rightarrow$ Stack A):**
Now, Stack A is completely empty, and Stack B holds all 100 elements. They aren't perfectly sorted yet, but they are layered by chunks. Chunk 4 (ranks 75–99) is sitting right at the top of Stack B.The algorithm now reverses the process to reconstruct a perfectly sorted Stack A:It searches Stack B for the absolute maximum value remaining (the first time, this will be rank 99).It calculates whether that maximum value is closer to the top of Stack B or the bottom of Stack B.It spins Stack B using the most efficient path (rb or rrb) until rank 99 is at the very top.It executes pa to push it back to Stack A.


#### Why O(n√n)

There are √n chunks. For each chunk, every element requires an average of O(√n) rotations to be located and moved (since the chunk window holds ~√n elements and B never grows beyond n). The full sort therefore performs √n × n × O(1) push operations plus O(n) × O(√n) rotation operations, giving **O(n√n)** total operations.

#### Why this strategy for intermediate disorder

For moderate disorder (20%–50% of pairs inverted), the input is neither nearly sorted nor fully random. Chunk sort exploits whatever partial order exists by using the chunk window to batch elements that are close in rank together, reducing the average rotation distance significantly compared to pure insertion sort, while avoiding the bit-level overhead of radix sort on inputs that are not large enough to amortize it.

---

### 3. Complex — O(n log n) — LSD Radix Sort

**Invoked by:** `--complex`, or `--adaptive` when disorder ≥ 0.5

#### Behavior

**Coordinate compression** maps all input values to indices 0..n-1, eliminating negative numbers and value gaps that would otherwise interfere with bit operations.

**LSD (Least Significant Digit) radix sort** then processes the compressed indices bit by bit, from the least significant bit to the most significant bit (⌈log₂(n)⌉ passes total):

- For each bit position, iterate through all elements currently in A:
  - If the current element's bit is **0** → push it to B (`pb`)
  - If the current element's bit is **1** → rotate it to the bottom of A (`ra`)
- After processing all elements in A, push everything from B back to A (`pa` repeated)

After ⌈log₂(n)⌉ passes, A is sorted in ascending order.

#### Why O(n log n)

Each pass visits every element exactly once: O(n) operations. The number of passes equals the number of bits needed to represent n − 1, which is ⌈log₂(n)⌉. The total is therefore O(n) × O(log n) = **O(n log n)** operations.

#### Why this strategy for high disorder

When more than 50% of pairs are inverted, the input is highly random. Algorithms that rely on existing order (simple, chunk) degrade toward their worst case. Radix sort is completely order-agnostic: its cost depends only on n, not on the arrangement of the input. For large, heavily shuffled inputs it is the only strategy that reliably meets the performance targets.

---

### 4. Adaptive — Disorder-Driven Strategy Selection

**Invoked by:** `--adaptive` (default when no strategy flag is given)

#### Disorder Metric

Before any moves are made, the algorithm counts the number of **inversions** in the input: pairs (i, j) where i < j but `A[i] > A[j]`. The disorder ratio is:

```
disorder = inversion_count / total_pairs
         = inversion_count / (n * (n - 1) / 2)
```

This produces a value in [0, 1]: 0 means perfectly sorted, 1 means perfectly reverse-sorted. The calculation is O(n²) but is performed once on the original array before any stack operations begin, so it does not affect the complexity class of the chosen strategy.

#### Thresholds and Rationale

| Disorder range | Strategy selected | Rationale |
|----------------|-------------------|-----------|
| < 0.2 | Simple — O(n²) | Fewer than 20% of pairs are inverted. The input is nearly sorted. The simple algorithm's low constant factor outperforms the bookkeeping overhead of heavier strategies. |
| 0.2 ≤ disorder < 0.5 | Medium — O(n√n) | Moderate disorder. Enough partial order remains for chunk batching to reduce rotation cost versus a full insertion sort, but the input is not random enough to require radix sort. |
| ≥ 0.5 | Complex — O(n log n) | More than half of all pairs are inverted. The input is essentially random. Radix sort's order-agnostic cost is the safest guarantee for meeting operation limits. |

#### Space Complexity

All four strategies use O(n) space: the two stacks hold the n input elements at all times, and coordinate compression uses a single auxiliary array of size n. No additional data structures are allocated.

---

## Benchmarking

The `--bench` flag writes the following information to `stderr` (so it does not interfere with the operation list on `stdout`):

All 11 operations are reported individually. This allows direct comparison of strategy efficiency across different input sizes and disorder levels.

---

## Resources

### References

- *Introduction to Algorithms* (CLRS), 4th edition — Chapters on comparison sorts, counting inversions, and radix sort
- [push_swap: feeling the power of the sorting algorithm]https://yannick.eu/push_swap/
- [Peers' comments]
- [Push-Swap-Tester] https://github.com/gemartin99/Push-Swap-Tester
### AI Usage

Artificial intelligence tools were used during this project in the following ways:

- **Algorithm correctness review:** After implementing each strategy, AI was used to review the logic and identify edge cases (e.g., duplicate detection, single-element stacks, already-sorted inputs, all-negative inputs).
- **README structure and documentation:** AI assisted in structuring this README and drafting the algorithm explanations. All technical content was verified against the actual implementation by both learners.
- **No code generation:** AI was used strictly as a review and documentation tool. All code was written, debugged, and understood by both learners independently.

---

## Contributions

| Learner | Contributions |
|---------|---------------|
| **bhernand** | Simple algorithm, medium chunk sort, disorder metric implementation (inversion count), benchmarking system |
| **mdiakono** | Complex algorithm implementation, adaptive routing logic, Makefile, utils, input validation and error handling  |
