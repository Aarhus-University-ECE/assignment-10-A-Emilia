#include "btree.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_node *Insert(int x, struct tree_node *t) {
  if (t == NULL) {                                                 // If there is no node it makes a new one and insert it.
    struct tree_node *n_node = malloc(sizeof(struct tree_node));
    n_node->item = x;
    n_node->left = NULL;
    n_node->right = NULL;
    return n_node;
  }
  if (x == t->item) {                                              // If the node to be inserted has the same value as another one, it has to be placed to the left of it.
    struct tree_node *n_node = malloc(sizeof(struct tree_node));
    n_node->item = x;
    n_node->left = t->left;
    n_node->right = NULL;
    return t;
  }
  if (x <= t->item) {                                              // Recursion to find right placement for node.
    t->left = Insert(x, t->left);
    return t;
  }
  if (x >= t->item) {                                              // Recursion to find right placement for node.
    t->right = Insert(x, t->right);
    return t;
  }
}

int Empty(struct tree_node *t) {
  if (t == NULL)
    return 1;
  return 0;
}

int Contains(int x, struct tree_node *t) {
  if (Empty(t))                                                    // Returns 0 if element is not found.
    return 0;
  if (x == t->item)                                                // Returns 1 if element is find.
    return 1;
  if (x < t->item)                                                 // Recursion to find element.
    return Contains(x, t->left);
  if (x > t->item)                                                 // Recursion to find element.
    return Contains(x, t->right);
}

struct tree_node *Remove(int x, struct tree_node *t) {
  if (!Contains(x, t))                                             // Checks if element is present in tree.
    return t;
  if (x == t->item) {                                              // Logic for if element has been found.
    if (t->left == NULL && t->right == NULL) {                     // If it has neither left nor right child, free it.
      free(t);
      return NULL;
    } 
    if (t->left != NULL && t->right == NULL) {                     // If it has a left child, but not a right child, the left child needs to be returned.
      struct tree_node *temp = t->left;
      free(t);
      return temp;
    } 
    if (t->left == NULL && t->right != NULL) {                     // If it has a right child, but not a left child, the right child needs to be returned.
      struct tree_node *temp = t->right;
      free(t);
      return temp;
    }
    if (t->left != NULL && t->right != NULL) {                     // If it has both a left child and a right child.
      struct tree_node *temp = t->right;                           // Temp node for the right child to be freed later.
      
      while (temp->left != NULL) { temp = temp->left; }            // Finds value of node that will be larger than all values to the left of the node that will be removed, but smaller than all values to the right of the node that will be remmoved.
      t->item = temp->item;                                        // Readjusts values to uphold logic.

      Remove(x,temp);
      return t;
    }
  }
  if (x < t->item) {                                               // Recursion to find element.
		t->left = Remove(x, t->left);
		return t;
	if (x > t->item) {                                               // Recursion to find element.
		t->right = Remove(x, t->right);
		return t;
	}
}
}

struct tree_node *Initialize(struct tree_node *t) {
  t = NULL;
  return t;
}

int Full(struct tree_node *t) {
  return 0;
}