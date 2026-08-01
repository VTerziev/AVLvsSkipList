# AVLvsSkipList

Implementation of a AVL tree and a Skip-List and comparing their performance for different scenarios.

## Running the performance tests

generate_scenario- generates the tests scenarios, on which the performance of the two data structures will be evaluated
run_scenario- runs the two structures against the generated test scenarios

## Sample results

These are the results I got from generating the scenarios and running them against each data structure. The numbers show time taken in milliseconds.
| # | AVL | Skip-List |
| - | ----- | --------- |
| 1 | 442 | 293 |
| 2 | 331 | 150 |
| 3 | 780 | 1105 |
| 4 | 49 | 106 |
| 5 | 616 | 706 |
| 6 | 594 | 380 |
| 7 | 42 | 190 |
| 8 | 49 | 281 |
| 9 | 2105 | 3417 |
| 10 | 1764 | 2840 |
| 11 | 501 | 764 |
| 12 | 497 | 834 |
| 13 | 503 | 787 |
| 14 | 466 | 410 |
| 15 | 457 | 381 |
| 16 | 1343 | 2858 |
| 17 | 1420 | 1958 |

## TODOs

- Tests should have scaling. Run a tests with 100 inserts, 1k inserts, 10k inserts, etc.
- The test runs should have description, should be in a more usable format.
- The test times should be visualized
- The test memory usage should be visualized. How to get the memory used by an unordered_set, for example?
- Containers should be template-able on keys and values
- Allocator should be able to release sub-types, passed via a super-type ptr.
