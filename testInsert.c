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
    tree *tempLeft;
    tree *tempRight;
    tempLeft = malloc(sizeof(tree));
    tempRight = malloc(sizeof(tree));

    tempLeft->root = (node*) kd_tree->root->left;
    tempRight->root =(node*) kd_tree->root->right;

    assert(kd_tree->root != NULL);
    assert(kd_tree->root->left != NULL);
    assert(kd_tree->root->right != NULL);
    assert(tempLeft->root->right != NULL);
    assert(tempRight->root->right != NULL);
    assert(kd_tree->root == node1);
    assert((node*) kd_tree->root->left == node3);
    assert((node*) kd_tree->root->right == node2);
    assert((node*) tempLeft->root->right == node5);
    assert((node*) tempRight->root->right == node4);
    free(tempLeft);
    free(tempRight);

    printf("Insertion test was successfull\n");

    return 0;
}
