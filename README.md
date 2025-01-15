# Multi-Threaded Merge Sort in C

This repository contains a POSIX-compliant multi-threaded implementation of the Merge Sort algorithm in C, designed for Linux distributions.

## Overview

Merge Sort is a classic divide-and-conquer algorithm that divides an array into smaller subarrays, sorts them, and then merges them back together. This implementation enhances the standard Merge Sort by utilizing multiple threads to perform sorting concurrently, improving performance on multi-core systems.

## Features

- **Multi-threading**: The program creates separate threads to sort subarrays concurrently, leveraging the capabilities of multi-core processors.

- **POSIX Threads (pthreads)**: Utilizes the POSIX thread library for thread management, ensuring compatibility with Unix-like operating systems.

- **Efficient Merging**: After sorting the subarrays in parallel, a merging thread combines them into a single sorted array.

## Files

- `sorting.c`: Contains the implementation of the multi-threaded merge sort algorithm.

- `sorting_output.txt`: Sample output demonstrating the program's functionality.

## Compilation and Execution

### Prerequisites

- GCC compiler

- POSIX-compliant operating system (e.g., Linux)

### Compilation

To compile the program, use the following command:

```bash
gcc -pthread -o sorting sorting.c
```

### Execution

After compilation, run the executable to perform the multi-threaded merge sort:
```
./sorting
```
The program will output the original unsorted array followed by the sorted array.

## License

This project is licensed under the MIT License—see the LICENSE file for details.

## Acknowledgments

This project was developed by Brandon Lavello as an exploration of multi-threaded algorithms in C.
