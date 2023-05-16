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
  node **ppNode;
  node *pNode;
  ppNode = &(ptree->root);
  pNode = *ppNode;
  depth = 0;
  while (pNode != NULL){
    
    if (depth%2==0){
      //realizar comparação a partir da coordenada x
    }
    else{
      //realizar comparação a partir da coordenada y
    }

  }
}