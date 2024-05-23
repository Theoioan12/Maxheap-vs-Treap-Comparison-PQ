#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
    char *out = argv[1];
    FILE *outfile = fopen(out, "wt");
    if (!outfile) {
        fprintf(stderr, "Error: Could not open the file\n");
        return -1;
    }
    int n = atoi(argv[2]);
    
    fprintf(outfile, "%d\n", n + 24);

    for (int i = 1; i <= 50; i++) {
        int a = (rand() % n);
        fprintf(outfile, "0 %d\n", a);
        
    }
    for (int i = 1; i <= 24; i++) {
        fprintf(outfile, "1\n");
    }

    //for (int i = 1; i <= 50; i++) {
        //int a = (rand() % n);
        //fprintf(outfile, "1 \n");
    //}
    //for (int i = 1; i <= 1999; i++) {
       // fprintf(outfile, "1\n");
       // fprintf(outfile, "2\n");
    //}


    return 0;
}