#include "vizinhoProximo.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
  tree *Kd_arvore;
  node *pdata;
  pdata ->coordinate[0] = 2;
  pdata ->coordinate[0] = 3;
  printf("oi\n");
  printf("%f %f \n \n", pdata->coordinate[0], pdata->coordinate[1]);

  kd_build(Kd_arvore, compare);
  kd_insert(Kd_arvore, pdata);
  printKDTree(Kd_arvore);
  return 0;
}