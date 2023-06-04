#include "vizinhoProximo.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

node **globalLocation = NULL;

int compare_restaurant(const void* coordinate, const void *candidate, int depth){
  restaurant* a = (restaurant*)coordinate;
  restaurant* b = (restaurant*)candidate;

  if (b->latitude == a->latitude && b->longitude == a->longitude){
    return 0;
  }

  if (depth%2 ==0){
    if ((b)->latitude < (a)->latitude){
    return -1;
  }
  return 1;
  }
  else{
    if ((b)->longitude < (a)->longitude){
      return -1;
    }
    return 1;
  }
}
int compare_cidade(const void* coordinate, const void *candidate, int depth){
  cidade* a = (cidade*)coordinate;
  cidade* b = (cidade*)candidate;

   if (b->latitude == a->latitude && b->longitude == a->longitude){
    return 0;
  }

  if (depth%2 ==0){
    if ((b)->latitude < (a)->latitude){
    return -1;
  }
  return 1;
  }
  else{
    if ((b)->longitude < (a)->longitude){
      return -1;
    }
    return 1;
  }
}

void kd_build(tree *ptree, int (*compara)(const void *a, const void *b, int depth), void (*printNode)(void *node), int (*compareListaMelhores)(const void* A, const void *B), node* (*new_node)(const void *data)){
  
  ptree->root = NULL;
  ptree->compara = compara;
  ptree->printNode = printNode;
  ptree->compareListaMelhores = compareListaMelhores;
  ptree->new_node = new_node;
}

node* new_restaurant(const void *data){
  node *output = malloc(sizeof(node));
  output->pdata = (restaurant*)data;
  return output;
}

node* new_cidade(const void *data){
  node *output = malloc(sizeof(node));
  output->pdata = (cidade*)data;
  return output;
}

node* new_node(const void* data);

void kd_insert(tree *ptree, void *new_node_data){
  node **ppNode;
  node *pNode;
  node *parentTemp;
  ppNode = &(ptree->root);
  parentTemp = *ppNode;
  pNode = *ppNode;
  int depth = 0;

  while (pNode != NULL){
    
    if (ptree->compara(pNode->pdata, new_node_data, depth) == -1){
        parentTemp = *ppNode;
        ppNode = (node**)&(pNode->left);
        pNode = *ppNode;
      }
    else if (ptree->compara(pNode->pdata, new_node_data, depth) == 1){
        parentTemp = *ppNode;
        ppNode = (node**)&(pNode->right);
        pNode = *ppNode;
      }
    else{
      return; //só vai retornar e não irá inserir na árvore caso exista um nó igual a esse presente
    }

    depth++;
  }
  if ((*ppNode == NULL)){
    (*ppNode) = (node*)ptree->new_node(new_node_data);
    (*ppNode)->parent = (node*)parentTemp;
    (*ppNode)->left = NULL;
    (*ppNode)->right = NULL;
  }
}

node* sucessores(node *pnodeAtual, int* duplicate){
  
  if ((pnodeAtual->left == NULL && pnodeAtual->right == NULL) || (*duplicate) == 2){
    *duplicate = 1;
    return pnodeAtual->parent;
  }

  if (pnodeAtual->left ==  NULL){
    if (*duplicate == 1){
      *duplicate = 2;
      pnodeAtual = (node*)pnodeAtual->left;
      while (pnodeAtual->right!=NULL){
        pnodeAtual = (node*)pnodeAtual->right;
      } 
      return pnodeAtual;
    }
    pnodeAtual = (node*)pnodeAtual->right;
    while (pnodeAtual->left!=NULL){
      pnodeAtual = (node*)pnodeAtual->left;
    }
    return pnodeAtual; //será o sucessor no caso de ser um node no início ou meio da árvore
  }
  else{
    if (*duplicate == 1){
      *duplicate = 2;
      pnodeAtual = (node*)pnodeAtual->right;
      while (pnodeAtual->left!=NULL){
        pnodeAtual = (node*)pnodeAtual->left;
      }
      return pnodeAtual; 
    }
    pnodeAtual = (node*)pnodeAtual->left;
    while (pnodeAtual->right!=NULL){
      pnodeAtual = (node*)pnodeAtual->right;
    }
    return pnodeAtual; //será o sucessor no caso de ser um node no início ou meio da árvore

  }
}

node *predecessor(node *pnodeAtual){

    node* parent = pnodeAtual->parent;

    while (parent != NULL && pnodeAtual == parent->left){
      pnodeAtual = parent;
      parent = parent->parent;
    }

    return parent;
  

    
}

void printKDTree(const void *treeObj, void (*printNode)(void *nodeObj)){
  tree *arv = (tree*)treeObj;
  node* root = arv->root;
  if (root == NULL){
    return;
  }
  else printNode(root); 
}

void printNode_restaurant(void *nodeObj){
  node *nodeAux = (node*)nodeObj;
  restaurant *aux = (restaurant*)nodeAux->pdata;
  if(nodeAux->left) {
    printNode_restaurant((node*)nodeAux->left);
  }

  printf("[%f, %f] \n", aux->latitude, aux->longitude);
  
  if(nodeAux->right) {
    printNode_restaurant((node*)nodeAux->right);
  }

}

void printNode_cidade(void *nodeObj){
  node *nodeAux = (node*)nodeObj;
  cidade *aux = (cidade*)(nodeAux->pdata);
  if(nodeAux->left) {
    printNode_cidade((node*)nodeAux->left);
  }

  printf("[%f, %f] \n", aux->latitude, aux->longitude);
  
  if(nodeAux->right) {
    printNode_cidade((node*)nodeAux->right);
  }

}

void deleteNodes(node *actual){

  if (actual == NULL){
    return;
  }

  deleteNodes((node*)actual->left);
  deleteNodes((node*)actual->right);

  free(actual);
}

void deleteTree(tree *kd_tree){

  deleteNodes((node*)kd_tree->root);
  kd_tree->compara = NULL;
  kd_tree->root=NULL;
  
}

float distanceCidade(const void* coordinate, const void* neighbor){
  cidade *a;
  a = (cidade*)coordinate;
  node *cidadeAuxiliar = (node*) neighbor;
  cidade *b = (cidade*)cidadeAuxiliar->pdata;
  return sqrt( pow(b->latitude - a->latitude, 2) + pow(b->longitude - a->longitude, 2) );
}

 float distanceRestaurante(const void* coordinate, const void* neighbor){
   restaurant *a, *b;
   a = (restaurant*) coordinate;
   b = (restaurant*) neighbor;
   return sqrt( pow(b->latitude - a->latitude, 2) + pow(b->longitude - a->longitude, 2) );}

int compareListaMelhores(const void* A, const void *B);
  
int compareListaMelhoresRestaurante(const void* A, const void *B){
  node* a = (node*)A;
  node* b = (node*)B;

  if (distanceRestaurante(b->pdata, (*globalLocation)) < distanceRestaurante(a->pdata, (*globalLocation))){
    return -1;
  }

  if (distanceRestaurante(b->pdata, (*globalLocation)) > distanceRestaurante(a->pdata, (*globalLocation))){
    return 1;
  }

  return 0;
}

int compareListaMelhoresCidade(const void* A, const void *B){
  node* a = (node*)A;
  node* nodeAux = (node*)B;
  cidade *b = (cidade*)nodeAux->pdata;
  if (distanceCidade(b, (*globalLocation)) < distanceCidade(a, (*globalLocation))){
    return -1;
  }

  if (distanceCidade(b, (*globalLocation)) > distanceCidade(a, (*globalLocation))){
    return 1;
  }

  return 0;
}

 void insereListaMelhores(tree *ptree, node** listaMelhores, int K, int* tamAtual, node* candidato){
   listaMelhores[(*tamAtual)++] = candidato;
   if (*tamAtual>1){
    qsort(listaMelhores, *tamAtual, sizeof(node*) * 2, ptree->compareListaMelhores);

   }
   if(*tamAtual == K + 1) {
     (*tamAtual)--;
   }
 }

//Para funcionar, devemos INSERIR por ÚLTIMO o nó q desejamos procurar
void searchNeighbors(tree *ptree, node **listaMelhores, int k, int* tamAtual, node* location, node *pnodeAtual, int *duplicate){
  int depth = 0;
  globalLocation = &location;
  if (*tamAtual == k){ //condição de parada
    return;
  }

  if (*tamAtual > 1){
    //procurar por sucessores do "paiAtual" e adicionar na listaMelhores
    pnodeAtual = sucessores(pnodeAtual, duplicate);
    insereListaMelhores(ptree, listaMelhores, k, tamAtual, pnodeAtual);
    return searchNeighbors(ptree, listaMelhores, k, tamAtual, location, pnodeAtual, duplicate);
  }

  if (ptree->compara(pnodeAtual->pdata, location->pdata, depth) == 0){
    node *pred = predecessor(pnodeAtual);
    node *suc = sucessores(pnodeAtual,duplicate);
    if (pred == suc){
      insereListaMelhores(ptree, listaMelhores, k, tamAtual, pred);  
    }
    else{
      insereListaMelhores(ptree, listaMelhores, k, tamAtual, pred);   
      insereListaMelhores(ptree, listaMelhores, k, tamAtual, suc);
    }
    
    *duplicate = 1;
    return searchNeighbors(ptree, listaMelhores, k, tamAtual, location, pnodeAtual->parent, duplicate); //recursivamente searchNeighborss com o nó pai e o duplicate atualizado  
  }

  while (pnodeAtual != NULL){
    //percorrer árvore até achar o nó que se procura
    if (ptree->compara(pnodeAtual->pdata, location->pdata, depth) == -1){
        pnodeAtual = pnodeAtual->left;
      }
    else if (ptree->compara(pnodeAtual->pdata, location->pdata, depth) == 1){
        pnodeAtual = pnodeAtual->right;
      }
    else{
      //achou igual
      return searchNeighbors(ptree, listaMelhores, k, tamAtual, location, pnodeAtual, duplicate);
    }
    depth++;
  }
}

void menu(){
   int op = -1;
   tree *kd_arvore;
   kd_arvore = malloc(sizeof(tree));
   FILE *arq;
   while (op != 5){
   
    printf("------------- Search Next Neighbor -------------\n");
     printf("1 - build Tree(s)\n");
     printf("2 - Search Neighbor(s)\n");
     printf("3 - Delete tree\n");
     printf("4 - Print tree\n");
     printf("5 - Stop program\n");

     int y = scanf("%d", &op);

     if (op ==1){
      printf("Please inform the name of the file containing the dataset:\n");
      
      char nomeArq[50];
      scanf(" %s", nomeArq);
      arq = fopen(nomeArq, "r");
      if (arq == NULL){
        printf("Erro ao abrir o arquivo!");
        return 1;
      }
      if (strcmp(nomeArq, "Fast_Food_Restaurants_US.txt") == 0){
        
        kd_build(kd_arvore, compare_restaurant, printNode_restaurant, compareListaMelhoresRestaurante, new_restaurant);
        //ler restaurantes / fast-food
        char line[900];
        while (fgets(line, sizeof(line), arq) != NULL)
        {
          restaurant *rest = malloc(sizeof(restaurant));

          sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%f,%f,%[^,],%d,%[^,],%[^\n]",
                  &rest->line, rest->address, rest->categories, rest->city, rest->country, &rest->latitude, &rest->longitude, rest->name, &rest->postalCode, rest->province, rest->websites);
          kd_insert(kd_arvore, rest);
        
        }
        printf("Tree built succesfully!!!!\n");

      }

      else if (strcmp(nomeArq, "municipios.txt") == 0){
       
        kd_build(kd_arvore, compare_cidade, printNode_cidade, compareListaMelhoresCidade, new_cidade);
        //ler municipios
        while (!feof(arq)) {
          cidade *aux = malloc(sizeof(cidade));
      
          // fscanf(arq, "%d,%[^,],%[^,],%[^,],%[^,],%f,%f,%[^,],%[^,],%[^,],%[^,\n]", &i, aux.address, aux.categories, aux.city, aux.country, &aux.latitude, &aux.longitude, aux.name, aux.postalCode, aux.province, aux.websites);
          fscanf(arq, "%d, %[^,], %f, %f, %d, %d, %d, %d, %[^,\n]", &aux->cod_ibge, aux->nome, &aux->latitude, &aux->longitude, &aux->capital, &aux->cod_uf, &aux->cod_siafi, &aux->ddd, aux->fuso_hor);
          kd_insert(kd_arvore, aux);      
        }

        printf("Tree built succesfully!!!!\n");

      }
      else{
        printf("Arquivo não encontrado, verifique se o nome digitado está correto!\n");
      }

     }

     if(op == 2){

        if (kd_arvore->root == NULL){
          printf("Tree is empty!!!\n");
          
        }
        else{
          printf("Inform the latitude and longitude That you want to search for its next neighbors:\n");

        float lat, lon;
        int k;
        scanf(" %f %f", &lat, &lon);
        printf("inform the quantity of next neighbors you want to find:\n");
        scanf("%d", &k);
        int *tamAtual;
        int *duplicate;
        int v1 = 0;
        int v2 = 0;
        tamAtual = &v1;
        duplicate = &v2;
        node **listaMelhores = malloc(sizeof(node*));
        node *candidato = malloc(sizeof(node));
        printf("inform if you Want to look for Restaurants or Cities?\n Please type or restaurant or city\n");
        char name[15];
        scanf(" %s", name);
        
        if (strcmp(name, "restaurant") == 0){
          restaurant *aux = malloc(sizeof(restaurant));
          aux->latitude = lat;
          aux->longitude = lon;
          candidato->pdata = aux;
          
        }
        else if (strcmp(name, "city") == 0){
          cidade *aux = malloc(sizeof(cidade));
          aux->latitude = lat;
          aux->longitude = lon;
          candidato->pdata = aux;
          
        }
        else{
          printf("You may have misswritten the word!");
          continue;
        }
        searchNeighbors(kd_arvore, listaMelhores, k, tamAtual, candidato, kd_arvore->root, duplicate);
        int cont = 0;

        if (strcmp(name, "restaurant") == 0){
          while (cont<k){
            restaurant *restaurantProxima;
            restaurantProxima = (restaurant*)listaMelhores[cont]->pdata;
            printf("\nRestaurante(s) Próximo(s): %s\n", restaurantProxima->name);
            printf("\nRestaurante(s) Próximo(s): %s\n", restaurantProxima->name);
            printf("\nRestaurante(s) Próximo(s): %s\n", restaurantProxima->name);
            printf("\nRestaurante(s) Próximo(s): %s\n", restaurantProxima->name);
            printf("\nRestaurante(s) Próximo(s): %s\n", restaurantProxima->name);
            printf("\nRestaurante(s) Próximo(s): %s\n", restaurantProxima->name);
            printf("\nRestaurante(s) Próximo(s): %s\n", restaurantProxima->name);

            cont++;
          }
        }
        else{
          while (cont<k){
            cidade *cidadeProxima;
            cidadeProxima = (cidade*)listaMelhores[cont]->pdata;
            printf("\nCidade(s) Próxima(s): %s\n", cidadeProxima->nome);
            printf("\n %d", cidadeProxima->cod_ibge);
            printf("\n %d", cidadeProxima->cod_uf);
            printf("\n %d", cidadeProxima->capital);
            printf("\n %f", cidadeProxima->latitude);
            printf("\n %f", cidadeProxima->longitude);
            printf("\n %d", cidadeProxima->cod_siafi);
            printf("\n %d", cidadeProxima->ddd);
            printf("\n %s", cidadeProxima->fuso_hor);

            printf("\n-------------------------\n");

            cont++;
          }
        }
        }
        
        
     }
     if(op == 3){
       deleteTree(kd_arvore);
       printf("Tree deleted\n");
     }

     if (op == 4){
      if (kd_arvore != NULL){
        printKDTree(kd_arvore, kd_arvore->printNode);
      }
      else{
        printf("Tree is not inicialized\n");
      }
     }

     if(op == 5){
      if (arq != NULL){
        fclose(arq);
      }

      printf("Stopped!\n");
      break;
     }
    }
 }

