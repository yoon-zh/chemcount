# Chemical Compound Parser - chemCount()

## What is it?

A simple library in C for a chemical formula parser that converts strings like `C2H5OH` into structured element counts, including total element types.

## Features

- Parses chemical formulas (e.g., `CoCl3 (NH3)6`) into element counts
- Handles parentheses for grouped compounds (e.g., `(NH3)6 → N:6, H:18`)
- Returns a `cElement` struct with total element count `"TTT"` and individual element quantities

## Installation

Clone the repository and compile the code:

```bash
git clone https://github.com/yoonzh/chemcount
```

## Usage

Import the chemcount library in your code:
```c
#include "chemcount.h"
```
 
 Then build into .o file and link into your function.

```bash
cd chemcount  
gcc -o chemcount chemcount.c
gcc yourprogram.c chemcount.o -o yourprogram
```

## Output Format
The `cElement` struct is an array of arrays sorted by appearance.

```c
cElement[0].name = "TTT";
cElement[0].amount = N;
```

The first element in the struct has the title `"TTT"` and `N` is the total unique elements in the formula.

```c
for (int i = 0; i < cElement[0].amount+1; i++) {
    printf("%s\t%f\n", cElement[i].name, cElement[i].amount);
}
```

The other objects in the `cElement` struct contain the string of the element and its amount in the compound.

## Example

```c
chemcount("C2H5OH");
/* Returns:
 * ["TTT", 3]
 * ["C", 2]
 * ["H", 6]
 * ["O", 1]
 */

chemcount("CoCl3 (NH3)6");
/* Returns:
 * ["TTT", 4]
 * ["Co", 1]
 * ["Cl", 3]
 * ["N", 6]
 * ["H", 18]
 */
```

## main.c example

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

To use this example, run the following commands in your terminal:

```bash
git clone https://github.com/yoonzh/chemcount
cd chemcount
gcc -o chemcount chemcount.c
gcc main.c chemcount.o -o main
./main
```

## Assumptions
- Case-sensitive: `Co` (cobalt) ≠ `CO` (carbon monoxide).
- Parentheses: Coefficients outside parentheses apply to all nested elements (e.g., `(H2O)2 → H:4, O:2`).
- Implicit "1": Missing counts are treated as 1 (e.g., `OH → O:1, H:1`).
