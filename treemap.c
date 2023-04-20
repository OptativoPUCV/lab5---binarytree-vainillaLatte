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

  TreeMap* t= (TreeMap*)malloc(sizeof(TreeMap));
  t->root=NULL;
  t->lower_than = lower_than;
    return t;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {

  TreeNode *new=createTreeNode(key,value);
  if(tree->root == NULL)
  {
    tree->root = new;
    return;
  }
  TreeNode *currentNod= tree->root;
  while(1)
    {
      int cmp= is_equal(tree, currentNod->pair->key,key);
      if(cmp==0)
      {
        currentNod->pair->value=value;
        free(new);
        return;
      }
      else if(cmp<0){
        if(currentNod->right == NULL)
        {
          currentNod->right=new;
          new->parent=currentNod;
          break;
        }
        else{
          currentNod=currentNod->right;
        }

      }
      else{
        if(currentNod->left==NULL)
        {
          currentNod->left=new;
          new->parent=currentNod;
          break;
        }
        else{
          currentNod=currentNod->left;
        }
      }
    }
  tree->root=new;
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    tree->current=tree->root;
  if(tree->root == NULL)
  {
    return NULL;
  }
  while(tree->current !=NULL)
    {
      if(is_equal(tree, tree->current->pair->key,key))
      {
        return (tree->current->pair);
      }
      if(tree->lower_than(tree->current->pair->key,key))
      {
        tree->current=tree->current->right;
      }
      else{
        tree->current=tree->current->left;
      }
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
