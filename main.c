#include "vizinhoProximo.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
  tree *Kd_arvore;

  kd_build(Kd_arvore, compare);
  kd_insert(Kd_arvore, new_node(NULL, 2,3));
  printKDTree(Kd_arvore);
  return 0;
}