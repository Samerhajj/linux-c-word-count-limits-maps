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
make words
./words [options] [file1] [file2]
```
Replace [file1], [file2], etc. with the path(s) to the input file(s) you want to process. If no file is specified, the program will read from standard input.
### Options

The program supports the following options:

- `-c`: Count Mode  
  Counts the total number of words in the file(s) and displays the count.

- `-f`: Frequency Mode  
  Counts the frequency of each word in the file(s) and displays the words sorted by count (ascending), then alphabetically.

- `-r`: Reverse Mode  
  Counts the frequency of each word in the file(s) and displays the words sorted by count (descending), then reverse alphabetically.

- `-h`: Help  
  Displays the help message with usage instructions.

### Examples
1. Count the total number of words in a file:
```shell
./words -c myfile.txt
```

2. Count the frequency of each word in multiple files and display the results sorted by count, then alphabetically:
```shell
./words -f file1.txt file2.txt file3.txt
```

3. Count the frequency of each word in a file and display the results sorted by count in descending order, then reverse alphabetically:
```shell
./words -r myfile.txt
```

4. Display the help message:
```shell
./words -h
```

Note: If no file is specified, the program will read from STDIN.



## Limits Program
The limits program (`limits.c`) displays various system limits such as maximum file size, maximum number of open files, and more. The program retrieves these limits using the appropriate system functions and displays them on the console.

To compile and run the limits program, use the following commands:
```shell
gcc -o limits limits.c
./limits
```