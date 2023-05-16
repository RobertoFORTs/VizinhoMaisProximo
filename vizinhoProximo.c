#include "vizinhoProximo.h"
#include <stdlib.h>


int compare(float *coordinate, float *candidate){
  if (candidate < coordinate){
    return -1;
  }
  return 0;
}

void kd_build(tree *ptree, int (*compara)(const void *a, const void *b)){
  ptree -> root = NULL;
  ptree -> compara = compara;
}
void kd_insert(tree *ptree, void *pdata){
  node **ppNode;
  node *pNode;
  ppNode = &(ptree->root);
  pNode = *ppNode;
  int depth = 0;
  struct Kd_Node* pDataResultant = (struct Kd_Node*)pdata;

  while (pNode != NULL){
    
    if (depth%2==0){
      if (ptree->compara(&(pNode->coordinate[0]), &(pDataResultant->coordinate[0])) < 0){
        ppNode = &(pNode->left);
        pNode = *ppNode;
      }
      else{
        ppNode = &(pNode->right);
        pNode = *ppNode;
      }
    }
    else{
      if (ptree->compara(&(pNode->coordinate[1]), &(pDataResultant->coordinate[1])) < 0){
        ppNode = &(pNode->left);
        pNode = *ppNode;
      }
      else{
        ppNode = &(pNode->right);
        pNode = *ppNode;
      }
    }

    depth++;
  }
  if ((*ppNode == NULL)){
    (*ppNode) = malloc(sizeof(node));
    (*ppNode)->data = pDataResultant->data;
    (*ppNode)->left = NULL;
    (*ppNode)->right = NULL;
  }
}