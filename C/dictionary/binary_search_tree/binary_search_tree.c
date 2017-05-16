#include <stdlib.h>
#include <stdio.h>
#include "binary_search_tree.h"

/*
 * Creates and allocates a new node
 * key: the key of the node
 * cargo: cargo (the element)
 * return: the pointer of the new element
 */
Tree new_node(void* key,void* cargo,Tree parent){
  Tree elem = (Tree)malloc(sizeof(BinaryTreeNode));
  elem->key = key;
  elem->cargo = cargo;
  elem->parent = parent;
  elem->left = elem->right = NULL;
  return elem;
}

/*
 * Inserts an element in the tree
 * tree: pointer to the pointer of the root node of the tree
 * key: the key of the node
 * cargo: cargo (the element)
 * compare: the function for comparison
 * return: the pointer of the searched element or NULL
 */
Tree tree_insert_element(Tree* tree,void* key,void* cargo,CompFunction compare){
  Tree parent = NULL;
  Tree temp_tree =  *tree;
  int comp;
  while(temp_tree != NULL){
    parent = temp_tree;
    comp = compare(key,temp_tree->key);
    if(comp == 0){
      temp_tree->cargo = cargo;
      return temp_tree;
    }else{
      if(comp < 0){
        temp_tree = temp_tree->left;
      }else{
        temp_tree = temp_tree->right;
      }
    }
  }
  Tree elem = new_node(key,cargo,parent);
  if(parent == NULL){
    *tree = elem;
  }else{
    if(compare(key,parent->key) < 0){
      parent->left = elem;
    }else{
      parent->right = elem;
    }
  }
  return elem;
}

/*
 * Searches a node from the tree by key
 * tree: pointer to the root node of the tree
 * key_search: key to be deleted
 * compare: the function for comparison
 * return: the pointer of the searched element or NULL
 */
Tree tree_search_element(Tree tree,void* key_search,CompFunction compare){
  if(tree == NULL){
    return NULL;
  }else{
    if(compare(tree->key,key_search) == 0){
      return tree;
    }else{
      if(compare(key_search,tree->key) < 0){
        return tree_search_element(tree->left,key_search,compare);
      }else{
        return tree_search_element(tree->right,key_search,compare);
      }
    }
  }
}

/*
 * This function changes the tree jumping the to_jump node
 * to_jump: the node to jump
 * target: the target node
 */
void jump_node(Tree to_jump,Tree target){
  if(to_jump->parent->left == to_jump){
      to_jump->parent->left = target;
  }else{
      to_jump->parent->right = target;
  }
  target->parent = to_jump->parent;
}

/*
 * Deletes a node with only a child from the tree
 * tree: pointer to the root node of the tree
 * node: node to be deleted
 * return: pointer to the deleted node
 */
Tree one_delete(Tree* tree , Tree node){
    if (node->parent == NULL) {
        if(node->left != NULL){
            node->left->parent = NULL;
            *tree = node->left;
        }else{
            node->right->parent = NULL;
            *tree = node->right;
        }
    }else{
        if(node->left != NULL){
            jump_node(node,node->left);
        }else{
            jump_node(node,node->right);
        }
    }
    return node;
}

/*
 * This function returns true if the node is a leaf, false otherwise
 */
int tree_is_leaf(Tree node){
  return node->left == NULL && node->right == NULL;
}

/*
 * This function returns true if the node has only one child, false otherwise
 */
int tree_has_one_children(Tree node){
  return node->left == NULL || node->right == NULL;
}

/*
 * This function swaps the content of two nodes
 */
void swap_node_contents(Tree first_node,Tree second_node){
  void* key_temp = first_node->key;
  void* key_cargo = first_node->cargo;

  first_node->key = second_node->key;
  first_node->cargo = second_node->cargo;

  second_node->key = key_temp;
  second_node->cargo = key_cargo;
}

/*
 * Deletes a node from the tree
 * tree: pointer to pointer of the root node of the tree
 * node: pointer to the node to be deleted
 * return: pointer to the deleted node
 */
Tree delete_node(Tree* tree, Tree node){
  Tree deleted_tree_node = NULL;
  if (tree_is_leaf(node)) {
    if(node->parent == NULL){
      deleted_tree_node = *tree;
      *tree = NULL;
    }else{
      if (node->parent->left == node) {
        deleted_tree_node = node->parent->left;
        node->parent->left = NULL;
      }else{
        deleted_tree_node = node->parent->right;
        node->parent->right = NULL;
      }
    }
  }else{
    if (tree_has_one_children(node)) {
      deleted_tree_node = one_delete(tree,node);
    }else{
      Tree succ = tree_find_min(node->right);
      swap_node_contents(node,succ);
      deleted_tree_node = delete_node(tree,succ);
    }
  }
  return deleted_tree_node;
}

/*
 * Deletes a node from the tree by key
 * tree: pointer to pointer of the root node of the tree
 * key_search: key to be deleted
 * compare: the function for comparison
 * return: the tree in case of succes, NULL if the element there isn't in the tree
 */
Tree tree_delete_element(Tree* tree ,void* key_search,CompFunction compare){
  Tree temp;
  temp = tree_search_element(*tree,key_search,compare);
  if(temp!=NULL){
    return delete_node(tree,temp);
  }else{
    return NULL;
  }
}

/*
 * Searches the node with the min cargo in the tree
 * return: pointer to the min node
 */
Tree tree_find_min(Tree tree){
  while(tree->left != NULL){
    tree = tree->left;
  }
  return tree;
}

/*
 * Searches the successor of the node "node" in the tree
 * return: pointer to the successor node
 */
Tree tree_successor(Tree node){
  Tree temp_node = NULL;
  if (node != NULL){
    if(node->right != NULL){
      return tree_find_min(node->right);
    }else{
      temp_node = node->parent;
      while (temp_node != NULL && node == temp_node->right){
        node = temp_node;
        temp_node = node->parent;
      }
    }
  }
  return temp_node;
}

/*
 * Searches the node with the max cargo in the tree
 * return: pointer to the max node
 */
Tree tree_find_max(Tree tree){
  while(tree->right != NULL){
    tree = tree->right;
  }
  return tree;
}

/*
 * Prints the tree in order
 * tree: the tree to be printed
 * print: function to print the tree
 */
void tree_print_in_order(Tree tree,PrintFunction print){
  if(tree == NULL) return;
  tree_print_in_order(tree->left,print);
  print(tree->cargo);
  tree_print_in_order(tree->right,print);
}

/*
 * Deallocates the tree
 * tree: the tree to be dealloced
 * deallocNode: function to dealloc the node
 */
void tree_dealloc(Tree tree,DeallocFunction dealloc_node){
  if(tree == NULL) return;
  tree_dealloc(tree->left,dealloc_node);
  tree_dealloc(tree->right,dealloc_node);
  dealloc_node(tree);
}

/*
 * Prints the tree in preorder
 * tree: the tree to be printed
 * print: function to print the tree
 */
void tree_print_pre_order(Tree tree,PrintFunction print){
  if(tree == NULL) return;
  print(tree->cargo);
  tree_print_pre_order(tree->left,print);
  tree_print_pre_order(tree->right,print);
}
