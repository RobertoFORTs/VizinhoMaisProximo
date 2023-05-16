#include "vizinhoProximo.h"
#include <stdlib.h>


float compare(float *coordinate, float *candidate){
  if (candidate < coordinate){
    return -1;
  }
  return 0;
}

void kd_build(tree *ptree, float (*compara)(const void *a, const void *b)){
  ptree -> root = NULL;
  ptree -> compara = compara;
}
void kd_insert(tree *ptree, void *pdata, int depth){
  tree **ppNode;
  tree *pNode;
  ppNode = &(ptree->root);
  pNode = *ppNode;
  depth = 0;
  ptree->compara = compare;
  struct Kd_Node* pDataResultant = (struct Kd_Node*)pdata;

  while (pNode != NULL){
    
    if (depth%2==0){
      if (compare(pNode->root->coordinate[0] < pDataResultant->coordinate[0]) < 0){
        //mover para esquerda
      }
      else{
        //mover para direita
      }
    }
    else{
      if (compare(pNode->root->coordinate[1] < pDataResultant->coordinate[1]) < 0){
        //mover para esquerda
      }
      else{
        //mover para direita
      }
    }

    depth++;
  }
}