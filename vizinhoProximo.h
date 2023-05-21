#include <stdio.h>

typedef struct Kd_Node{
  void* data;
  float coordinate[2];
  struct Kd_node* parent;
  struct Kd_node* left;
  struct Kd_node* right;
}node;

typedef struct KD_Tree{
  node* root;
  int (*compara)(const void *a, const void *b);
}tree;



int compare(const void *coordinate, const void*candidate);
void kd_build(tree *ptree, int (*compara)(const void *a, const void *b));
void kd_insert(tree *ptree, node *pdata);
node* new_node(void* data, int x, int y);
void printNode(node *nodeObj);
void printKDTree(tree *raiz);
// float distance(const void *coordinate; const void *neighbor);
void searchNextNeighbor(node* current_node, float* location, int numberOfNeighbors, int depth, node** listaMelhores, int* tamAtualLista);
void deleteNodes(node *root);
void deleteTree(tree *raiz);