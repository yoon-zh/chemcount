#include "chemcount.h"

// ClC5H2(OH)2
// 1. int chemClength = strlen(chemCompound);
// 2. if (!chemClength) return NULL;
// 3. Define struct for myElements, malloc for 2 space
// 4. Initialize strcpy(myElements[0].name, "TT"), myElements[0].num = 0
// 5. if (chemCompound[i] == '('), char* inParenthesis = malloc(sizeof(char)), realloc for following chars
// 6. if upper case, get position i, get element and check if is in struct
//      If not in struct, realloc struct, elements.num ++
//      If in struct, continue
//      a. Read next element:
//          if isadigit, get number and add to elements[i]
//          if closing parenthesis: repeat a, free inParenthesis when done
// 7. Return pointer of struct

cElement* chemcount(char* chemCompound) {
    // 1. Validate the syntax of the chemCompound
    if(isWrongSyntax(chemCompound)) { 
        printf("Invalid Syntax: %s\n", chemCompound);
        return NULL;
    }
    
    // 2. Define struct for myElements, malloc for 1 space (will use reallocation for every found element)
    cElement* myElements = malloc(sizeof(cElement));

    // 3. Initialize myElements[0] with string "TT" meaning total, and amount of chemical
    strcpy(myElements[0].name, "TTT");
    myElements[0].amount = 0;

    // 4. For every character in chemCompound, find elements and fill myElements list
    findElements(chemCompound, &myElements);

    // 5. Return pointer of struct
    return myElements;   
}

void findElements(char* chemCompound, cElement** myElements) {
    size_t i, j;                   // Counter
    int elemPos;                // Position of search finding in string chemCompound
    float amount;               // Amount of elements denoted by a digit in chemCompound
    float multiplier = 1;       // Multiplier for elements inside a parenthesis
    char elemSearch[4];        // String for element search results
    size_t chemClength = strlen(chemCompound); // Length of input string
    for (i = 0; i < chemClength; i++) {
        switch (chemCompound[i]) {
        // 1. If a parenthesis is found, look for the beginning/end and get the multiplier number
        case '(': 
            // 1. Look for numbers before the parenthesis
            j = i-1; // j will look for the number length
            while(isdigit(chemCompound[j--]) && j>0); // Move to the beginning of the number
            // Store multiplier for future elements
            multiplier = readDigits(chemCompound, j);
            
            // 2. Look for numbers after the parenthesis
            j = i+1;  // j will store the position
            while(chemCompound[j++] != ')'); // Move to the end of the parenthesis
            // Store multiplier for future elements
            multiplier *= readDigits(chemCompound, j);
            break;
        // 2. If a closing parenthesis is found, reset multiplier to 1.
        case ')':
            multiplier = 1;
            break;
        // 3. If element found, get element elemSearch and get position i
        default:
            if (elementFound(chemCompound, elemSearch, i, chemClength)) {
            elemPos = isIn_cElement(elemSearch, (*myElements));
            // a. If elemSearch is NOT in myElements, add to struct
            if (!elemPos) {
                addToMyElements(elemSearch, myElements);
                elemPos = (*myElements)[0].amount; // Set elemPos to final element
            }
            // b. Look for digits after elemSearch result
            amount = readDigits(chemCompound, i+strlen(elemSearch));
            // c. Sum digits to element
            (*myElements)[elemPos].amount += (amount*multiplier);
            break;
            }
        }
    }
}

// Looks for chemical elements in a given position i of chemCompound. Assigns string to elementStr and returns 1 if found.
int elementFound(char* chemCompound, char* elementStr, int i, int strLength) {
    strcpy(elementStr, "");
    if(isupper(chemCompound[i])) { // If an upper-case letter is found
        addCharToString(elementStr, chemCompound[i]);
        // Check if there is a double or triple-letter element (example: He instead of H, Cl instead of C)
        for (int j = 1; j < 3; j++) {
            if(i+j < strLength && islower(chemCompound[i+j])) { // If so, the second letter must be lowercase
                addCharToString(elementStr, chemCompound[i+j]); // If lowercase found, assign it to the comparison element
            }
        }
        return 1; // Element found, return true
    }
    return 0; // Element not found, return false
}

// Check if elem is in myElements
int isIn_cElement(char* elem, cElement* myElements) {
    int i; // Counter
    int myElementsNum = (int)(myElements[0].amount); // Total number of elements
    // Compare elem with all elements in myElements
    for(i = 0; i < myElementsNum; i++) {
        if(strcmp(elem, myElements[i+1].name) == 0) {
            return i+1; // If found, return position (i+1 because pos 0 holds total values)
        }
    }
    return 0; // If not found, return 0 (false)
}

// Reallocate memory of myElements and add elem to myElements
void addToMyElements(char* elem, cElement** myElements) {
    // 1. Sum total number of elements +1
    int myElementsNum = (int)(++ (*myElements)[0].amount);
    // 2. Create temporary element 
    cElement* temp = realloc(*myElements, sizeof(cElement)*(myElementsNum+1));
    verifyMallocSuccess(temp);
    // 3. If successful, copy data to myElements
    *myElements = temp;
    // 4. Initialize myElements[myElementsNum]
    strcpy((*myElements)[myElementsNum].name, elem);
    (*myElements)[myElementsNum].amount = 0;
}

float readDigits(char* chemCompound, int elemPos) {
    char digitInString[MAX_CHEMSTRLEN];
    memset(digitInString, 0, MAX_CHEMSTRLEN);
    while(isdigit(chemCompound[elemPos])) {
        // Copy each digit character into digitInString
        addCharToString(digitInString, chemCompound[elemPos++]);   
    }
    // If number has decimals, add dot and continue
    if(chemCompound[elemPos] == '.') {
        addCharToString(digitInString, chemCompound[elemPos++]);
        while(isdigit(chemCompound[elemPos])) {
        // Copy each digit character into digitInString
        addCharToString(digitInString, chemCompound[elemPos++]);
        }
    }
    if(!digitInString[0]) return 1; // If no numbers are found, return amount 1
    return atof(digitInString); // Cast string digit into int
}

void printElements(cElement* myElements) {
    int elemNum = myElements[0].amount + 1;
    printf("Element\tAmount\n");
    for (int i = 1; i < elemNum; i++) {
        printf("%s\t", myElements[i].name);
        if (fabs(myElements[i].amount - (int)(myElements[i].amount)) < 1e-6) {
            printf("%d\n", (int)(myElements[i].amount));
        }
        else {
            printf("%.2f\n", myElements[i].amount);
        }
    }
}


// Checks if compound has valid syntax
int isWrongSyntax(char* chemCompound) {
    size_t i, ph;  // Counter
    int isInParenthesis = 0;    // Bool for chars in parenthesis
    char ch;    // Character holder for chemCompound chars
    for (i = 0; i < strlen(chemCompound); i++) {
        ch = chemCompound[i];
        // 1. If an opening parenthesis is found
        if(ch == '(') {
            // Ensure there is at least one letter after the parenthesis
            if(!isalpha(chemCompound[i + 1])) return 1; // If not, has wrong syntax
            // Verify there are no double opening parenthesis
            if(isInParenthesis) return 1;   // If so, has wrong syntax
            isInParenthesis = 1;    // If not, set opening parenthesis true
        }

        // 2. If a closing parenthesis is found
        else if(ch == ')') {
            // If closing parenthesis without previous opening, has wrong syntax
            if(!isInParenthesis) return 1;
            isInParenthesis = 0;    // Open-closing parentheses are met, set to false
        }

        // 3. If a dot for decimals is found
        else if(ch == '.') {
            ph = i; // Get the position of the dot
            // Check if there is a letter or number before the dot
            if(!isalnum(chemCompound[ph - 1])) return 1; // If not, has wrong syntax
            // Ensure there is at least one number after the dot
            if(!isdigit(chemCompound[++ph])) return 1; // If not, has wrong syntax
            
            // Continue checking after the dot until no digits are found
            while(ph < strlen(chemCompound) && isdigit(chemCompound[ph++]));
            ch = chemCompound[ph]; // Get the character after all decimal digits
            // After the decimal digits, ch must be a letter, parenthesis or end of string
            if (!isalpha(ch) && ch != '(' && ch != ')' && !isStrEnd(ch) && ph != strlen(chemCompound)) {
                return 1; // If not, has wrong syntax, return 1 (true)
            }
        }
        
        // 4. If a lowercase is found
        else if(islower(ch)) {
            if(i == 0) return 1;    // If the lowercase is the first letter, wrong syntax
            
            // Verify the previous character is a letter
            if(!isalpha(chemCompound[i-1])) return 1;

            // Check for strings with 1 or 2 lowercases
            if(!isupper(chemCompound[i-1]) && islower(chemCompound[i-1]) && !isupper(chemCompound[i-2])) return 1;
        }

        else if (!isalnum(ch) && ch != '(' && ch != ')' && ch != '.' && !isStrEnd(ch) && !isspace(ch)) {
            return 1; // Has wrong syntax, return 1 (true)
        }
    }
    // If an open parenthesis is left hanging, has wrong syntax
    if(isInParenthesis) return 1;
    return 0;   // If as valid syntax, return 0 (false)
}


// ================================================================================================================================

// Obtain user input printing a prompt and assigning input to buffer
void usr_input(char *buffer, size_t sizeof_buffer, const char *prompt) {
	if(prompt != NULL)  {
        printf("%s", prompt); // Print prompt
    }
    while(1) {
		if (fgets(buffer, sizeof_buffer, stdin) == NULL) {
            // Display error message if it does not read input
			printf("Error reading input.\n");
			continue;
		}
		// Remove newline character if present
		buffer[strcspn(buffer, "\n")] = '\0';

		// Refuse empty inputs
		if (strcmp(buffer, "") == 0) {
			printf("Input cannot be empty.\n");
		}
		else {
			return;
		}
	}
}

void usr_input_diy(char *usrStr, size_t sizeof_usrStr, const char *prompt) {
    if(prompt != NULL) {
        printf("%s", prompt);
    }
    int ch;
    size_t counter = 0;

    // Skip any leading whitespace
    while ((ch = getchar()) != EOF && isspace(ch));

    // Set usrStr empty
    usrStr[0] = '\0';    

    // Read string
    while (ch != '\n' && ch != EOF && counter < sizeof_usrStr) {
        addCharToString(usrStr, ch);
        counter++;
        ch = getchar();
    }
}

// Adds a char to a string assuming it is long enough to hold it without overflowing
void addCharToString(char* myString, char myChar) {
    while(*myString ++);        // Moving pointer to the end
    *(myString - 1) = myChar;   // Replaces end-1 with myChar, previous to null
    *myString = '\0';           // Null terminates the string
}


// Scanf but safe, returns 1 if input is a number, 0 if not
// Example syntax: 
// while(usr_input_num(&myNumber, "") != 1) printf("Not a number\n"); printf("%f", myNumber);
int usr_input_num(double *num, const char *prompt) {
    if(prompt != NULL) {
        printf("%s", prompt);
    }
    *num = 0;
    int ch;         // Holder for getchar return values
    int sign = 1;   // Positive/negative sign for input (default positive)

    // Skip any leading whitespace
    while ((ch = getchar()) != EOF && isspace(ch));

    // Check for optional sign
    if (ch == '-') {
        sign = -1;
        ch = getchar();
    }
    else if (ch == '+') {
        // Default sign is positive, skip to next char
        ch = getchar();
    }

    // Read digits
    while (ch != EOF && isdigit(ch)) {
        *num = *num * 10 + (ch - '0');
        ch = getchar();
    }

    // Check for decimal point
    if (ch == '.') {
        double fraction = 0.0, divisor = 10.0;
        ch = getchar();  // Move past the dot
        while (ch != EOF && isdigit(ch)) {
            fraction += (ch - '0') / divisor;
            divisor *= 10;
            ch = getchar();
        }
        *num += fraction;
    }

    // Check for exponent part (e or E)
    if (ch == 'e' || ch == 'E') {
        ch = getchar();  // move past 'e' or 'E'
        int exponent = 0, exp_sign = 1;
        // Check for exponent sign (+ or -), default (+)
        if (ch == '-') {
            exp_sign = -1;
            ch = getchar();
        } 
        else if (ch == '+') {
            ch = getchar();
        }

        // read exponent digits
        while (ch != EOF && isdigit(ch)) {
            exponent = exponent * 10 + (ch - '0');
            ch = getchar();
        }

        // apply exponent to the number
        *num *= power_int(10, exp_sign * exponent);
    }

    // handle trailing junk or no input
    *num *= sign;
    if (ch != '\n' && ch != EOF) {
        return 0; // Not a number, return 0 (false)
    }
    return 1;     // Is a number, return 1 (true)
}

// DIY power function for exponents of type int
double power_int(double base, int32_t exponent) {
    if(exponent == 0) return 1; // Does not include case 0^0
    double result = 1.0;
    int32_t abs_exponent = (exponent > 0) ? exponent : -exponent;  // Handle negative exponent

    while (abs_exponent > 0) {
        if (abs_exponent % 2 == 1) {
            result *= base;  // Multiply by base when exponent is odd
        }
        base *= base;  // Square the base for each step
        abs_exponent /= 2;  // Halve the exponent
    }

    if(exponent < 0) { 
        // If exponent is negative, move result to divisor
        result = 1.0/result;
    }
    return result;
}

// Wait for user input to continue
void pressEnterToContinue() {
    printf("\nPress enter to continue...\n");
    char ph[2]; // place holder
    fgets(ph, sizeof(ph), stdin);
	// system("cls"); // Optional cleanup WINDOWS ONLY
}

// Check if a test string exists within a sample string. Requires #include <stdint.h>
// If test exists in sample, returns 1 + (position in sample). Otherwise returns 0
int existsInString(char* test, char* sample) {
    size_t sampleLength = strlen(sample);
    size_t testLength = strlen(test);
    if(testLength > sampleLength) return 0;                         // If the test string is longer than the sample, cancel
    if(testLength == 0 && sampleLength != 0) return 0;              // If the test string is empty but sample is not, cancel

    size_t loopRange = sampleLength - testLength + 1;               // Loop range up to sample length
    char* testStr = malloc(sizeof(char) * testLength);              // Create string placeholder for test
    verifyMallocSuccess(testStr);

    int j; // Counter
    for(size_t i = 0; i < loopRange; i++) {
        memset(testStr, 0, testLength);                             // Set testStr to blank string
        j = 0;
        while (test[j] == sample[i+j] && (i+j < sampleLength)) {    // As equal characters are found...
            addCharToString(testStr, sample[i+j]);                  // Appends characters to testStr
            j++;
        }                                                           // If the length of the final testStr is the same of the test string and both strings are equal
        
        // First compare sizes since it requires less resources compared  using strcmp for all testStr
        if(strlen(testStr) == testLength && strcmp(test, testStr) == 0) {
            free(testStr);
            return 1 + i; // Returns 1 + (position of finding in sample) if exists
        }
    }
    free(testStr);
    return 0;   // Returns 0 if test is not in sample
}


// Append two strings assuming string1 has enough space
void strAppend(char* string1, char* string2) {
    size_t len1 = strlen(string1), len2 = strlen(string2), i;
    char* finalString = malloc(sizeof(char)*(len1 + len2 + 1));
    verifyMallocSuccess(finalString);
    memset(finalString, 0, len1 + len2 + 1);
    for (i = 0; i < len1; i++) {
        addCharToString(finalString, string1[i]);
    }
    for (i = len1; i < len1 + len2; i++) {
        addCharToString(finalString, string2[i-len1]);
    }
    strcpy(string1, finalString);
    free(finalString);
}

// Exit program if malloc returns null
void verifyMallocSuccess(void* data) {
    if (data == NULL) {
        printf("Memory allocation failed :( ");
        exit(EXIT_FAILURE);
    }
}