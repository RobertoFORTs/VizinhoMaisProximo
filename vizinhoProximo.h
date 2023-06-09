#include <stdio.h>

typedef struct Kd_restaurant{
  int line;
  int cod;
  char address[100];
  char categories[100];
  char city[100];
  char country[100];
  float latitude;
  float longitude;
  char name[100];
  char postalCode[100];
  char province[100];
  char  websites[400];
} restaurant;

typedef struct Kd_municipios{
  int cod_ibge;
  char nome[50];
  float latitude;
  float longitude;
  int capital;
  int cod_uf;
  int cod_siafi;
  int ddd;
  char fuso_hor[50];
} cidade;

typedef struct Kd_Node{
  void* pdata;
  struct Kd_node* parent;
  struct Kd_node* left;
  struct Kd_node* right;
}node;

typedef struct KD_Tree{
  node* root;
  int (*compara)(const void *a, const void *b, int depth);
  void (*printNode)(void* nodeObj);
  int (*compareListaMelhores)(const void* A, const void *B);
  node* (*new_node)(const void *data);
}tree;


node* new_restaurant(const void *data);
node* new_cidade(const void *data);
int compare_restaurant(const void *coordinate, const void*candidate, int depth);
int compare_cidade(const void *coordinate, const void*candidate, int depth);
void kd_build(tree *ptree, int (*compara)(const void *a, const void *b, int depth), void (*printNode)(void* nodeObj), int (*compareListaMelhores)(const void* A, const void *B), node* (*new_node)(const void *data));
void kd_insert(tree *ptree, void *pdata);
node* new_node(const void* data);
void printNode_cidade(void *nodeObj);
void printNode_restaurant(void *nodeObj);
void printKDTree(const void* tree, void (*printNode)(void *nodeObj));
float distanceCidade(const void *coordinate, const void *neighbor);
float distanceRestaurante(const void *coordinate, const void *neighbor);
void searchNeighbors(tree *ptree, node **listaMelhores, int k, int* tamAtual, node* candidato, node *pnodeAtual, int *duplicate);
void searchDeleteNode(tree *ptree);
void deleteNodes(node *root);
void deleteTree(tree *raiz);
node* sucessores(node *pnodeAtual, int *duplicate);
node* predecessor(node* pNodeAtual);
int compareListaMelhoresRestaurante(const void* A, const void *B);
int compareListaMelhoresCidade(const void* A, const void *B);

void menu();