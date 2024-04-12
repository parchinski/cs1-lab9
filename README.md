# Hash Table with Chaining

This C program implements a hash table using separate chaining to handle collisions. It reads records from an input file, each containing an ID, a character, and an order value, and inserts them into a hash table.

## Changes from Original File

1. **Command Line Arguments:** The program now takes the input file name as a command-line argument. This allows the user to specify the input file directly when running the program.
2. **Structural Changes:**
   - Added a `next` pointer in the `RecordType` struct for chaining in the hash table.
   - Created a new `HashType` struct that represents the hash table, containing an array of pointers (`buckets`) to `RecordType` and the size of the table.
3. **Memory Management:**
   - Added checks for memory allocation failure. If memory allocation fails, the program will output an error message and exit.
4. **Hash Function:** Implemented a simple hash function to compute the index based on the record ID.
5. **Error Handling:** Added error handling for file operations and command-line arguments.

## Building the Program

You can compile the program using gcc or any standard C compiler. Here is an example command to compile the program:

```bash
gcc -o hash_program hash_program.c

./hash_program input.txt
```

make sure to replace `input.txt` with `input_lab_9.txt` or any other valid format input file you want to use. There is no check for valid input type as this was not a requirement for the lab.
