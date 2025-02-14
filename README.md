# Chemical Element Parser - chemCount()

## What is it?

A simple library in C for a chemical formula parser that converts strings like `C2H5OH` into structured element counts, including total element types.

## Features

- Parses chemical formulas (e.g., CoCl3 6(NH3)) into element counts.
- Handles parentheses and coefficients (e.g., 6(NH3) → N:6, H:18).
- Returns a `cElement` struct with total element count (TTT) and individual element quantities

## Installation

Clone the repository and compile the code:

```bash
git clone https://github.com/yoonzh/chemcount
```

## Usage

Import the chemcount library, build into .o file and link into your function.

```bash
cd chemcount  
gcc -o chemcount chemcount.c
gcc main.c chemcount.o -o main
```

## Example

In the repository you may find a main function containing an example of the usage. Below is the snippet of the implementation:

```c
#include "chemcount.h"

int main (int argc, char *argv[]) {
    char chemCompound[MAX_CHEMSTRLEN];
    while(1) {
        if(argc == 1) {
            usr_input(chemCompound, sizeof(chemCompound), "Compound to count (1 to exit): ");
            if(strcmp(chemCompound, "1") == 0) return EXIT_SUCCESS;
        }
        else {
            strcpy(chemCompound, argv[2]);
        }
        cElement* myElements = chemCount(chemCompound);
        if(myElements != NULL) {
            printElements(myElements);
            free(myElements);
        }
        else printf("Error, invalid syntax...\n");
        pressEnterToContinue();
        if(argc > 1) return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}

```

To write

```bash
cd chemcount  
gcc -o chemcount chemcount.c
gcc main.c chemcount.o -o main
```

## Assumptions

