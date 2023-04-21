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

  if(!tree->root)
  {
    tree->root=createTreeNode(key,value);
  }
  else{
    tree->current=tree->root;
     while(tree->current)
    {
    if(is_equal(tree, tree->current->pair->key,key))
    {
      return;
    }
    if(tree->lower_than(tree->current->pair->key, key))
    {
      if(!tree->current->right)
      {
        tree->current->right = createTreeNode(key, value);
        tree->current->right->parent = tree->current;
        tree->current = tree->current->right;
        return;
      }
      tree->current = tree->current->right;
    }
    else
    {
      if(tree->current->left == NULL)
      {
        tree->current->left = createTreeNode(key, value);
        tree->current->left->parent = tree->current;
        tree->current = tree->current->left;
        return;
      }
      tree->current = tree->current->left;
    }
  }
  }
  
}

TreeNode * minimum(TreeNode * x){
   while (x->left != NULL) {
        x = x->left;
    }
    return x;

}


void removeNode(TreeMap * tree, TreeNode* node) {
  if (node == NULL) {
        return;
    }

    if (node->left == NULL && node->right == NULL) {
        if (node == tree->root) {
            tree->root = NULL;
        } else if (node == node->parent->left) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }
        free(node);
    } else if (node->left == NULL || node->right == NULL) {
       
        TreeNode * child = node->left ? node->left : node->right;
        if (node == tree->root) {
            tree->root = child;
            child->parent = NULL;
        } else if (node == node->parent->left) {
            node->parent->left = child;
            child->parent = node->parent;
        } else {
            node->parent->right = child;
            child->parent = node->parent;
        }
        free(node);
    } else {
        
        TreeNode * successor = minimum(node->right);
        node->pair = successor->pair;
        removeNode(tree, successor);
    }

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
    TreeNode* current = tree->root;
    TreeNode* ub_node = NULL;

    while (current != NULL) {
        if (tree->lower_than(key, current->pair->key)) {
            ub_node = current;
            current = current->left;
        } else if (tree->lower_than(current->pair->key, key)) {
            current = current->right;
        } else {
            return current->pair;
        }
    }

    
    if (ub_node != NULL) {
        return ub_node->pair;
    } else {
        return NULL; 
    }
}

Pair * firstTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }

    TreeNode* node = tree->root;
    while (node->left != NULL) {
        node = node->left;
    }

    tree->current = node;
    return node->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->current == NULL) {
        return NULL;
    }

    TreeNode* node = tree->current;
    if (node->right != NULL) {
        node = node->right;
        while (node->left != NULL) {
            node = node->left;
        }
        tree->current = node;
    } else {
        TreeNode* parent = node->parent;
        while (parent != NULL && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        tree->current = parent;
    }

    return tree->current == NULL ? NULL : tree->current->pair;
}
