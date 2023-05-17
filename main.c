#include "vizinhoProximo.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
  tree *kd_arvore;
  kd_arvore = malloc(sizeof(tree));
  kd_build(kd_arvore, compare);
  kd_insert(kd_arvore, new_node(NULL, 2,3));
  printKDTree(kd_arvore);
  
  return 0;
}