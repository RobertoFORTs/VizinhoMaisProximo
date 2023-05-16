#include <stdio.h>

typedef struct Kd_Node{
  void* data;
  float coordinate[2];
  struct Kd_node* left;
  struct Kd_node* right;
}node;

typedef struct KD_Tree{
  node* root;
  float (*compara)(const void *a, const void *b);
}tree;



float compare(float *coordinate, float *candidate);
void kd_build(tree *ptree, float (*compara)(const void *a, const void *b));
void kd_insert(tree *ptree, void *pdata);