#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * map = (TreeMap *)malloc(sizeof(TreeMap));
    if (!map) {
        return NULL;
    }
    map->root = NULL;
    map->current = NULL;
    map->lower_than = lower_than;

    return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
 /*/   if (tree == NULL || key == NULL || value == NULL) return;

    if(tree->root == NULL){
        TreeNode * newNode = createTreeNode(key, value);
        tree->root = newNode;
        tree->current = newNode;
        return;
    }

    TreeNode *current = tree->root;
    TreeNode *parent = NULL;
    int izquierda = 0;

    while(current != NULL){
        if(is_equal(tree, key, current->pair->key)){
            return;
        }

    parent = current;
    current = tree->lower_than(key, current->pair->key) ? (izquierda = 1, current->left) : (izquierda = 0, current->right); //se pueden colocar ambos resultados para el if y el else con el formato condicion ? (si se cumple(accion 1, accion 2 que ademas se aplicara a la igualdad)) : (si no se cumple(accion1, accion2 que adenas...)))

    }

    TreeNode * newNode = createTreeNode(key, value);
    newNode->parent = parent;

    if(izquierda){
        parent->left = newNode;
    }
    else{
        parent->right = newNode;
    }

    tree->current = newNode;*/
}


TreeNode * minimum(TreeNode * x){
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}

void removeNode(TreeMap * tree, TreeNode* node) {
    if (tree == NULL || node == NULL) return;

    if(node->left == NULL && node->right == NULL){

        if(node->parent->left == node) node->parent->left = NULL;
        else node->parent->right = NULL;
    }

    else if(node->left != NULL && node->right == NULL){
        if (node->parent->left == node)
        {
            node->parent->left = node->left;
            node->left->parent = node->parent;
        }
        if (node->parent->right == node)
        {
            node->parent->right = node->left;
            node->left->parent = node->parent;
        }
    }
    else if(node->left == NULL && node->right != NULL){
        if (node->parent->left == node)
        {
            node->parent->left = node->right;
            node->right->parent = node->parent;
        }
        if (node->parent->right == node)
        {
            node->parent->right = node->right;
            node->right->parent = node->parent;
        }
    }

    else{
        TreeNode *aux = minimum(node->right);
        node->pair->key = aux->pair->key;
        node->pair->value = aux->pair->value;
        removeNode(tree, aux);
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
/*    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);
*/
}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    if(tree == NULL || tree->root == NULL || key == NULL) return NULL;
    TreeNode *current = tree->root;
    while(current != NULL){
        if(is_equal(tree, key, current->pair->key)){
            tree->current = current;
            return current->pair;
        }
        //if(tree->lower_than(key, current->pair->key) == 1)
        current = tree->lower_than(key, current->pair->key) ? current->left : current->right;//el operador ternario es una forma de escribir if else en una sola linea, funciona colocando la condicion ? opcion1 : opcion2. en este caso se usa para darle un valor al current, pero no necesariamente tiene que ser la igualdad de algo.
    }
return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
