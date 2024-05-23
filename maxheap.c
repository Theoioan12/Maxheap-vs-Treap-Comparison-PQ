#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
long long H[50000];
int size = -1;

#define ERR -1

// swap function
void swap(long long *a, long long *b)
{
	long long tmp = *a;
	*a = *b;
	*b = tmp;
}

// function to get the parent
long long parent(long long i)
{
 
    return (i - 1) / 2;
}
 
// function to get the left child
long long leftChild(long long i)
{
 
    return ((2 * i) + 1);
}
 
// function to get the right child
long long rightChild(long long i)
{
 
    return ((2 * i) + 2);
}
 
// function to shift up
void shiftUp(long long i)
{
    while (i > 0 && H[parent(i)] < H[i]) {
 
        
        swap(&(H[parent(i)]), &(H[i]));
 
        
        i = parent(i);
    }
}
 
// function to shift down
void shiftDown(long long i)
{
    long long maxIndex = i;
 
    
    long long l = leftChild(i);
 
    if (l <= size && H[l] > H[maxIndex]) {
        maxIndex = l;
    }
 
    long long r = rightChild(i);
 
    if (r <= size && H[r] > H[maxIndex]) {
        maxIndex = r;
    }
 
    if (i != maxIndex) {
        swap(&(H[i]), &(H[maxIndex]));
        shiftDown(maxIndex);
    }
}

// inserting function
void insert(long long p)
{
    size = size + 1;
    H[size] = p;
 
    shiftUp(size);
}

// function to extract and delete the maximum
long long extractMax()
{
    long long result = H[0];
 
    H[0] = H[size];
    size = size - 1;
 
    shiftDown(0);
    return result;
}
 
// function to get the maximum value
long long getMax()
{
 
    return H[0];
}

// function to remove an element 
void remove1(long long i)
{
    H[i] = getMax() + 1;
 
    shiftUp(i);
 
    extractMax();
}
 
// Driver Code
int main (int argc, char *argv[]) {
    double time_spent = 0.0;
 
    clock_t begin = clock();

    // getting the name of the input file
    char *in = argv[1];

    // getting the name of the output file
    char *out = argv[2];

    // opening the input file with the check
    FILE *infile = fopen(in, "rt");
    if (!infile) {
        fprintf(stderr, "Error: Could not open the file\n");
        return ERR;
    }

    // opening the output file with the check
    FILE *outfile = fopen(out, "wt");
    if (!outfile) {
        fprintf(stderr, "Error: Could not open the file\n");
        return ERR;
    }

    // getting the number of elements
    long long elementscount = 0, linescount;
    fscanf(infile, "%lld", &linescount);

    // operation type
    int opt;

    // adding the elements at first
    for (long long i = 0; i < linescount; i++) {

        // getting the operation type
        fscanf(infile, "%d", &opt);

        // inserting an element
        if (opt == 0) {
            long long elem;
            fscanf(infile, "%lld", &elem);
            insert(elem);
            elementscount ++;

        // removing an element
        } else if (opt == 1) {
            remove1(0);

        // getting the maximum
        } else if (opt == 2) {
            fprintf(outfile, "%lld\n", getMax());
        }
    }
   
   clock_t end = clock();
   time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   fprintf(outfile, "%lf", time_spent);

    fclose(outfile);
   fclose(infile);

    return 0;
}

