#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HT 50

struct MinHNode {
  char item;
  unsigned freq;
  struct MinHNode *left, *right;
};

struct MinHeap {
  unsigned size;
  unsigned capacity;
  struct MinHNode **array;
};


// Print the array
void printArray(int arr[], int n) {
  int i;
  for (i = 0; i < n; ++i)
    printf("%d", arr[i]);

  printf("\n");
}

struct MinHNode *newNode(char item, unsigned freq) {
  struct MinHNode *temp = (struct MinHNode *)malloc(sizeof(struct MinHNode));

  temp->left = temp->right = NULL;
  temp->item = item;
  temp->freq = freq;

  return temp;
}

// Create min heap
struct MinHeap *createMinH(unsigned capacity) { //Priority Queue
  struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));

  minHeap->size = 0;

  minHeap->capacity = capacity;

  minHeap->array = (struct MinHNode **)malloc(minHeap->capacity * sizeof(struct MinHNode *));
  //Allocates array where we store pointers to minHNode srtuctures
 
  return minHeap;
}

// Function to swap
void swapMinHNode(struct MinHNode **a, struct MinHNode **b) {
  struct MinHNode *t = *a;
  *a = *b;
  *b = t;
}

// Heapify
void minHeapify(struct MinHeap *minHeap, int idx) {//reconstructs heap from smallest to largest
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
    smallest = left;

  if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
    smallest = right;

  if (smallest != idx) {
    swapMinHNode(&minHeap->array[smallest], &minHeap->array[idx]);
    minHeapify(minHeap, smallest);
  }
}

// Check if size if 1
int checkSizeOne(struct MinHeap *minHeap) {
  return (minHeap->size == 1);
}

// Extract min
struct MinHNode *extractMin(struct MinHeap *minHeap) {
  struct MinHNode *temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];
 
  --minHeap->size;
  minHeapify(minHeap, 0); // sorts heap again from smallest to largest

  return temp;
}

// Insertion function
void insertMinHeap(struct MinHeap *minHeap, struct MinHNode *minHeapNode) {
  ++minHeap->size;
  int i = minHeap->size - 1;

  while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
    minHeap->array[i] = minHeap->array[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap *minHeap) {
  int n = minHeap->size - 1;
  int i;

  for (i = (n - 1) / 2; i >= 0; --i)
    minHeapify(minHeap, i);
}

int isLeaf(struct MinHNode *root) {
  return !(root->left) && !(root->right);
}

struct MinHeap *createAndBuildMinHeap(char item[], int freq[], int size) {
  struct MinHeap *minHeap = createMinH(size);// Creates Priority queue

  for (int i = 0; i < size; ++i)
// Stores pointers to each minHNode structure in array.
       minHeap->array[i] = newNode(item[i], freq[i]);

  minHeap->size = size;
  buildMinHeap(minHeap);

  return minHeap;
}

struct MinHNode *buildHuffmanTree(char item[], int freq[], int size) {
  struct MinHNode *left, *right, *top;
  struct MinHeap *minHeap = createAndBuildMinHeap(item, freq, size); // creates the tree

  while (!checkSizeOne(minHeap)) { //Takes 2 smallest nodes and extracts from tree
    left = extractMin(minHeap);
    right = extractMin(minHeap);
 // creates new node with the sum of frequencies of left and right
    top = newNode('$', left->freq + right->freq);

    top->left = left;
    top->right = right;

    insertMinHeap(minHeap, top);// adds new node to the tree
  }
  return extractMin(minHeap); // only one element in remains  priority queue so it will return the root
of the tree
}

void printHCodes(struct MinHNode *root, int arr[], int top) {
  if (root->left) {// checks if it has  left node
    arr[top] = 0;
    printHCodes(root->left, arr, top + 1);
  }
  if (root->right) { // checks if it has right node
    arr[top] = 1;
    printHCodes(root->right, arr, top + 1);
  }
  if (isLeaf(root)) {// checks if it is a leaf node so we can print the letter and it's code
    printf("  %c   | ", root->item);
    printArray(arr, top);//prints the code
  }
}

// Wrapper function
void HuffmanCodes(char item[], int freq[], int size) {
  struct MinHNode *root = buildHuffmanTree(item, freq, size);

  int arr[MAX_TREE_HT], top = 0;

  printHCodes(root, arr, top);
}


int compact(char arr[], int freq[], int size)
{
int j = 0;
for (int i = 0; i < size; i++)
{
if (freq[i] == 0)
continue;

freq[j] = freq[i];
arr[j] = arr[i];
      j++;

}
return j;
}


int main() 
{
 char str[1001] = "Hello my friend";
   
  char arr[256] = {'\0'};
  int freq[256] = {0};

    printf("Enter a string (max 1000): \n");
    //fgets(str, sizeof(str), stdin);
    

    for(int i = 0; str[i] != '\0'; i++)
    {
		char ch = str[i];
        arr[ch] = ch;
        freq[ch]++;
    }
  int size = sizeof(arr) / sizeof(arr[0]);
  size = compact(arr, freq, size);

  HuffmanCodes(arr, freq, size);
}
