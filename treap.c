#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>

#define ERR -1

// the structure for the node
typedef struct TreapNode
{
    int key, priority;

    // pointers to the children
    struct TreapNode *left, *right;
} TreapNode;

// right rotation
TreapNode *rightRotate(TreapNode *y)
{
    TreapNode *x = y->left,  *T2 = x->right;
  
    // perform rotation
    x->right = y;
    y->left = T2;
  
    // return new root
    return x;
}

// left rotation
TreapNode *leftRotate(TreapNode *x)
{
    TreapNode *y = x->right, *T2 = y->left;
  
    // perform rotation
    y->left = x;
    x->right = T2;
  
    // return new root
    return y;
}

// creating a new node based on the key
TreapNode* newNode(int key)
{
    // allocating the memory
    TreapNode* temp = (TreapNode *)malloc(sizeof(TreapNode));;
    temp->key = key;

    // generating a priority
    temp->priority = rand()%100;
    temp->left = temp->right = NULL;

    // returning the actual node
    return temp;
}

// inserting a new node
TreapNode* insert(TreapNode* root, int key)
{
    // if root is NULL, create a new node and return it
    if (!root)
        return newNode(key);
  
    // if key is smaller than root
    if (key <= root->key)
    {
        // insert in left subtree
        root->left = insert(root->left, key);
  
        // fix Heap property if it is violated
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    }
    else  // ff key is greater
    {
        // insert in right subtree
        root->right = insert(root->right, key);
  
        // fix Heap property if it is violated
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }
    return root;
}



void inorder(TreapNode* root, FILE* outfile) {
  if (root != NULL) {
    inorder(root->left, outfile);
    fprintf(outfile, "%d ", root->key);
    inorder(root->right, outfile);
  }
}

// getting the node with the maximum value
TreapNode* maxValueNode(TreapNode* node) {
  TreapNode* current = node;

  // going to the left subtree
  while (current->right != NULL) {
    current = current->right;
  }
  return current;
}

// delete function
TreapNode* delete(TreapNode* root, int key) {
  if (root == NULL) {
    return root;
  }

  if (key < root->key) {
    root->left = delete(root->left, key);
  } else if (key > root->key) {
    root->right = delete(root->right, key);
  } else {
    if (root->left == NULL) {
      TreapNode* temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      TreapNode* temp = root->left;
      free(root);
      return temp;
    }

    TreapNode* temp = maxValueNode(root->right);
    root->key = temp->key;
    root->right = delete(root->right, temp->key);
}
    return root;
}

int main (int argc, char *argv[]) {
    double time_spent = 0.0;
 
    clock_t begin = clock();

    struct TreapNode *root = NULL;

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
            root = insert(root, elem);
            elementscount ++;

        // removing an element
        } else if (opt == 1) {
            TreapNode *tmp = maxValueNode(root);
            delete(root, tmp->key);

        // getting the maximum
        } else if (opt == 2) {
            TreapNode *tmp = maxValueNode(root);
            fprintf(outfile, "%d\n", tmp->key);
        }
    }

    //inorder(root, outfile);
   
   clock_t end = clock();
   time_spent += (double)(end - begin) / 1000000;
   fprintf(outfile, "%lf", time_spent);
   fclose(outfile);
   fclose(infile);

    return 0;
}