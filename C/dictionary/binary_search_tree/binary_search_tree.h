#ifndef __TREE_H_KEIXJ4PDU3__
#define __TREE_H_KEIXJ4PDU3__

/* -------TREE STRUCT------- */
struct BinaryTreeNodeType{
  void* key;
  void* cargo;
  struct BinaryTreeNodeType *parent,*left,*right;
}BinaryTreeNode;

typedef struct BinaryTreeNodeType* Tree;

/* -------POINTERS TO FUNCTION------- */
typedef int (*CompFunction)(void*, void*);
typedef void (*PrintFunction)(void*);
typedef void (*DeallocFunction)(Tree tree);

/* -------PROTOTYPES------- */
// Inserts an element in the tree
Tree tree_insert_element(Tree* tree,void* key_search,void* cargo,CompFunction compare);
// Searches a node from the tree by key
Tree tree_search_element(Tree tree,void* key_search,CompFunction compare);
// Deletes a node from the tree by key
Tree tree_delete_element(Tree* tree ,void* key_search,CompFunction compare);
// Searches the node with the min cargo in the tree
Tree tree_find_min(Tree tree);
// Searches the node with the max cargo in the tree
Tree tree_find_max(Tree tree);
// Searches the successor of the node "node" in the tree
Tree tree_successor(Tree tree);
// This function returns true if the node is a leaf, false otherwise
int tree_is_leaf(Tree node);
// This function returns true if the node has only one child, false otherwise
int tree_has_one_children(Tree node);
// Prints the tree in order
void tree_print_in_order(Tree tree,PrintFunction print);
// Prints the tree in preorder
void tree_print_pre_order(Tree tree,PrintFunction print);
// Deallocates the tree
void tree_dealloc(Tree tree,DeallocFunction deallocNode);
#endif
