#include <stdio.h>

typedef struct Kd_restaurant{
  int x;
  int y;
} restaurant;

typedef struct Kd_brasil{
  int x;
  int y;
} cidade;

typedef struct Kd_Node{
  void* pdata;
  struct Kd_node* parent;
  struct Kd_node* left;
  struct Kd_node* right;
}node;

typedef struct KD_Tree{
  node* root;
  int (*compara)(const void *a, const void *b, int depth);
  void (*printNode)(void* nodeObj);
}tree;


restaurant* new_restaurant(int x, int y);
cidade* new_cidade(int x, int y);
int compare_restaurant(const void *coordinate, const void*candidate, int depth);
int compare_cidade(const void *coordinate, const void*candidate, int depth);
void kd_build(tree *ptree, int (*compara)(const void *a, const void *b, int depth), void (*printNode)(void* nodeObj));
void kd_insert(tree *ptree, void *pdata);
node* new_node(void* data);
void printNode_cidade(void *nodeObj);
void printNode_restaurant(void *nodeObj);
void printKDTree(const void* tree, void (*printNode)(void *nodeObj));
float distance(const void *coordinate, const void *neighbor);
int searchNextNeighbor(tree *ptree, node **listaMelhores, int k, int* tamAtual, node* candidato, node *pnodeAtual, int *duplicate);
void searchDeleteNode(tree *ptree);
void deleteNodes(node *root);
void deleteTree(tree *raiz);
node* sucessores(node *pnodeAtual, int *duplicate);
node* predecessor(node* pNodeAtual, int depth);