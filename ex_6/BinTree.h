#ifndef BIN_TREE
#define BINTREE

typedef struct BinTree {
    int id;
    char *name;
    int age;
    char gender;

    void (*task)(void *val);

    void *action;
    struct BinTree *left;
    struct BinTree *right;
} BinTree;
typedef enum {SUCEESS, FAILURE, MEM_ERROR} Result;


BinTree* createBinTree(BinTree *child);
Result addToBinTree(BinTree* root, BinTree *child);
int sizeOfBinTree(BinTree* root);
BinTree* findInBinTree(BinTree* root, BinTree *child);
void destroyBinTree(BinTree* root);


void generic_function(BinTree* root, void(*task)(void*));

int generic_int_function(BinTree* root, int(*task)(void*));

void child_task(void* val);
void moshe_task(void* val);

void inorder(BinTree *child);
void preorder(BinTree *child);
void postorder(BinTree *child);

void printChildDetails(BinTree *child);

#endif //BIN_TREE
