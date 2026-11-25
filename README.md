# Linked List Sorting Benchmark

A console program in C++ that manages a singly linked list of integers and compares the speed of selection sort on a linked list against selection sort on an array.

## Features

- **Load data from file**: reads integers from `data.txt` and builds a linked list
- **Display list**: prints every value with its position (starting at 1)
- **Find highest value**: scans the list and prints the largest number
- **Sort list**: sorts the list from highest to lowest using selection sort
- **Compare sorting time**: generates 50,000 random numbers, sorts them in both a linked list and an array, and prints the time each took
- **Exit and free memory**: releases all allocated nodes before quitting

## Requirements

- A C++11 (or newer) compiler, such as `g++` or `clang++`

## Build and Run

```bash
g++ -std=c++11 -O2 main.cpp -o listsort
./listsort
```

On Windows, run `listsort.exe` instead.

## Input File

Create a file named `data.txt` in the same directory as the program. It should contain whitespace-separated integers:

```
12 7 45 3
99 18
```

## Usage

```
1 | Load data from file
2 | Display list
3 | Find highest value
4 | Sort list (highest to lowest)
5 | Compare sorting time (list vs array)
6 | Exit and Free Memory
```

Example session:

```
1  -> Data read from file.
2  -> 1 | 12
      2 | 7
      3 | 45
      4 | 3
      5 | 99
      6 | 18
3  -> Highest value: 99
4  -> sorts the list from highest to lowest
2  -> 1 | 99
      2 | 45
      3 | 18
      4 | 12
      5 | 7
      6 | 3
5  -> Sorting 50000 numbers.
      List:  3 ms
      Array: 1 ms
6  -> frees memory and exits
```

The timings shown above are only an illustration of the output format. Real values depend on your machine and compiler settings.

## How It Works

Each node stores an integer and a pointer to the next node:

```cpp
struct customList {
    int id;
    customList *next;
};
```

| Function | Description |
|---|---|
| `readFromFile` | Reads integers from `data.txt` and appends a node for each one |
| `displayList` | Walks the list and prints each value with its position |
| `findMax` | Scans the list once and prints the highest value |
| `sortList` | Selection sort on the list; swaps the stored values, not the nodes |
| `sortArray` | Selection sort on an array, with the same logic as `sortList` |
| `compareSorting` | Fills an array and a list with the same random numbers, sorts both, and prints the elapsed time |
| `truncateList` | Frees every node in the list |

### Sorting

Both sorts are selection sort. For each position, the inner loop finds the largest value in the unsorted remainder, and a single swap moves it into place. The list version swaps the `id` values of two nodes, so no pointers need to be relinked. Both sorts run in O(n²) time, which makes the comparison a fair test of how a contiguous array and a pointer-based list behave on the same algorithm.

### Benchmark

Option 5 does not touch the list loaded from the file. It creates its own array and list of 50,000 random values between 0 and 999999, so the benchmark always runs on fresh data. Times are measured with `time()`, so they have a resolution of one second. Sorting 50,000 numbers can take several seconds.

## Notes and Limitations

- The `data.txt` file is read each time option 1 is chosen, and values are appended to the existing list, so loading twice duplicates the data.
- If `data.txt` is missing, the program still prints "Data read from file." and the list stays empty.
- The benchmark timer has one-second resolution, so very fast sorts show as 0.
- Menu input is not validated: entering a non-numeric choice makes the menu repeat endlessly.
