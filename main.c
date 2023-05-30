#include "vizinhoProximo.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
  tree *kd_arvore;
  kd_arvore = malloc(sizeof(tree));
  restaurant *restauranti = new_restaurant(2,3);
  kd_build(kd_arvore, compare_restaurant, printNode_restaurant);
  kd_insert(kd_arvore, restauranti);
  kd_insert(kd_arvore, new_restaurant(8,2));
  kd_insert(kd_arvore, new_restaurant(10,11));
  kd_insert(kd_arvore, new_restaurant(20,15));
  kd_insert(kd_arvore, new_restaurant(6,7));
  kd_insert(kd_arvore, new_restaurant(9,12));
  kd_insert(kd_arvore, new_restaurant(19,4));
  kd_insert(kd_arvore, new_restaurant(1,6));
  kd_insert(kd_arvore, new_restaurant(13,14));
  printKDTree(kd_arvore, kd_arvore->printNode);
  deleteTree(kd_arvore);
  return 0;
}