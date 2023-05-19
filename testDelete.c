#include "vizinhoProximo.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(){

  tree *kd_tree;
  kd_tree = malloc(sizeof(tree));
  kd_tree->root = NULL;
  kd_tree->compara = compare;

  node *node1 = new_node(NULL, 2, 3);
  node *node2 = new_node(NULL, 4, 1);
  node *node3 = new_node(NULL, 1, 5);
  node *node4 = new_node(NULL, 6, 7);
  node *node5 = new_node(NULL, 0, 12);
  
  kd_insert(kd_tree, node1);
  kd_insert(kd_tree, node2);
  kd_insert(kd_tree, node3);
  kd_insert(kd_tree, node4);
  kd_insert(kd_tree, node5);

  deleteTree(kd_tree);

  assert(kd_tree == NULL);

  printf("Deletion test was succesfull!!");

  return 0;
}