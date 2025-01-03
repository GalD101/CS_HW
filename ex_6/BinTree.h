#ifndef BIN_TREE
#define BIN_TREE

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

BinTree *createNode(int id, const char *name, int age, char gender);
void freeNode(BinTree *node);
void deleteNodes(BinTree *root);
void freeIsrael(BinTree *root);
BinTree *addChild(BinTree *root, int id,
                  const char *name, int age, char gender);

void inorderTask(BinTree *child);
void preorderTask(BinTree *child);
void postorderTask(BinTree *child);

int sizeOfJews(BinTree *root);
int sizeOfFemale(BinTree *root);
int sizeOfMale(BinTree *root);

void child_task(void *val);
void moshe_task(void *val);

BinTree *deleteId(BinTree *root, int id);
BinTree *findMoshe(BinTree *root);
int findMen(BinTree *root);
int findDead(BinTree *root);
void incrementAge(BinTree *root);
void lookForMoshe(BinTree *root);
void fuckMoshe(BinTree **root);
int doTask(BinTree *root);
void printAllChildren(BinTree *root);
int getOrder();

BinTree **deleteDead(BinTree **root);
BinTree **deleteMen(BinTree **root);


void generic_function(BinTree* root, void(*task)(void*));

int generic_int_function(BinTree* root, int(*task)(void*));

void child_task(void* val);
void moshe_task(void* val);

void inorderPrintDetails(BinTree *child);
void preorderPrintDetails(BinTree *child);
void postorderPrintDetails(BinTree *child);


void printChildDetails(BinTree *child);

#endif //BIN_TREE
