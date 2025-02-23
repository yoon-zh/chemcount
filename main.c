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
        cElement* myElements = chemcount(chemCompound);
        if(myElements != NULL) {
            printElements(myElements);
            free(myElements);
        }
        else puts("Error, invalid syntax...");
        pressEnterToContinue();
        if(argc > 1) return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}
