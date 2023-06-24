# Word Count and Limits

This repository contains a word count program written in C for Linux, along with a limits program that displays system limits and a map program that demonstrates memory allocation and variable addresses.

## Map Program

The `map.c` file in the repository contains a sample program that showcases different types of variable allocations and their respective addresses. The program demonstrates the following:

- Statically allocated variables (`foo`, `bar`, `stuff`)
- Stack allocated variables (`localInt`, `localFloat`, `i`)
- Dynamically allocated memory (`buf1`, `buf2`)

The program also includes recursive function calls and prints the addresses of various variables.

To run the map program, execute the following command:

```shell
gcc -o map map.c
./map
```

## Word Count Program
The word count program in this repository (`word_count.c`) counts the number of words in a given input file. It utilizes the word_count function defined in `word_count.c` to perform the counting. The program takes a file path as input and displays the word count on the console.

To compile and run the word count program, use the following commands:
```shell
gcc -o word_count word_count.c
./word_count <file_path>
```

## Limits Program
The limits program (`limits.c`) displays various system limits such as maximum file size, maximum number of open files, and more. The program retrieves these limits using the appropriate system functions and displays them on the console.

To compile and run the limits program, use the following commands:
```shell
gcc -o limits limits.c
./limits
```