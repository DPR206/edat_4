#include "bstree.h"

#include <stdio.h>
#include <stdlib.h>

/* START [_BSTNode] */
typedef struct _BSTNode {
  void *info;
  struct _BSTNode *left;
  struct _BSTNode *right;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _BSTree {
  BSTNode *root;
  P_ele_print print_ele;
  P_ele_cmp cmp_ele;
};
/* END [_BSTree] */

/*** BSTNode TAD private functions ***/
BSTNode *_bst_node_new() {
  BSTNode *pn = NULL;

  pn = malloc(sizeof(BSTNode));
  if (!pn) {
    return NULL;
  }

  pn->left = NULL;
  pn->right = NULL;
  pn->info = NULL;

  return pn;
}

void _bst_node_free(BSTNode *pn) {
  if (!pn) {
    return;
  }

  free(pn);
}

void _bst_node_free_rec(BSTNode *pn) {
  if (!pn) {
    return;
  }

  _bst_node_free_rec(pn->left);
  _bst_node_free_rec(pn->right);
  _bst_node_free(pn);

  return;
}

int _bst_depth_rec(BSTNode *pn) {
  int depth_l, depth_r;

  if (!pn) {
    return 0;
  }

  depth_l = _bst_depth_rec(pn->left);
  depth_r = _bst_depth_rec(pn->right);

  if (depth_r > depth_l) {
    return depth_r + 1;
  } else {
    return depth_l + 1;
  }
}

int _bst_size_rec(BSTNode *pn) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_size_rec(pn->left);
  count += _bst_size_rec(pn->right);

  return count + 1;
}

int _bst_preOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += print_ele(pf, pn->info);
  count += _bst_preOrder_rec(pn->left, pf, print_ele);
  count += _bst_preOrder_rec(pn->right, pf, print_ele);
  count += fprintf(pf, " ");

  return count;
}

int _bst_inOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_inOrder_rec(pn->left, pf, print_ele);
  count += print_ele(pf, pn->info);
  count += fprintf(pf, " ");
  count += _bst_inOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_postOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_postOrder_rec(pn->left, pf, print_ele);
  count += _bst_postOrder_rec(pn->right, pf, print_ele);
  count += print_ele(pf, pn->info);
  count += fprintf(pf, " ");

  return count;
}

/*** BSTree TAD functions ***/
BSTree *tree_init(P_ele_print print_ele, P_ele_cmp cmp_ele) {
  BSTree *tree;

  if (!print_ele || !cmp_ele) {
    return NULL;
  }

  tree = malloc(sizeof(BSTree));
  if (!tree) {
    return NULL;
  }

  tree->root = NULL;
  tree->print_ele = print_ele;
  tree->cmp_ele = cmp_ele;

  return tree;
}

void tree_destroy(BSTree *tree) {
  if (!tree) {
    return;
  }

  _bst_node_free_rec(tree->root);
  free(tree);

  return;
}

Bool tree_isEmpty(const BSTree *tree) {
  if (!tree || !tree->root) {
    return TRUE;
  }
  return FALSE;
}

int tree_depth(const BSTree *tree) {
  if (!tree) {
    return -1;
  }

  return _bst_depth_rec(tree->root);
}

size_t tree_size(const BSTree *tree) {
  if (!tree) {
    return -1;
  }

  return _bst_size_rec(tree->root);
}

int tree_preOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_preOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_inOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_inOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_postOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_postOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

/**** TODO: find_min, find_max, insert, contains, remove ****/
BSTNode *_bst_find_min_rec(BSTNode *pn) {
  if (!pn) return NULL;

  if (pn->left) {
    return _bst_find_min_rec(pn->left);
  }

  return pn;
}

BSTNode *_bst_find_max_rec(BSTNode *pn) {
  if (!pn) return NULL;

  if (!pn->right) {
    return pn;
  }

  return _bst_find_max_rec(pn->right);
}

Bool _bst_contains_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_elem) {
  if(!pn || !elem || !cmp_elem){
    return FALSE;
  }

  if(cmp_elem(elem, pn->info) == 0){
    return TRUE;
  } else if (cmp_elem(elem, pn->info) < 0){
    return _bst_contains_rec(pn->left, elem, cmp_elem);
  } else {
    return _bst_contains_rec(pn->right, elem, cmp_elem);
  }
}

BSTNode *_bst_insert_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_elem) {
int cmp;

  if(!pn){
    pn = _bst_node_new();
    if (!pn) return NULL;
    pn->info = (void*)elem;

    return pn;
  }

  cmp = cmp_elem(elem, pn->info);
  if (cmp < 0){
    pn->left = _bst_insert_rec(pn->left, elem, cmp_elem);
  } else if (cmp > 0){
    pn->right = _bst_insert_rec(pn->right, elem, cmp_elem);
  }
  return pn;
}

BSTNode *_bst_remove_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_elem) {
  BSTNode *ret_node = NULL, *aux_node = NULL;

  if (!pn){
    return NULL;
  }

  if(cmp_elem(elem, pn->info)<0){
    pn->left = _bst_remove_rec(pn->left, elem, cmp_elem);
  } else if (cmp_elem(elem, pn->info)>0) {
    pn->right = _bst_remove_rec(pn->right, elem, cmp_elem);
  } else {
    if(!pn->right && !pn->left){

      _bst_node_free(pn);
      return NULL;
    } else if (!pn->right){

      ret_node = pn->left;
      _bst_node_free(pn);
      return ret_node;
    } else if (!pn->left){

      ret_node = pn->right;
      _bst_node_free(pn);
      return ret_node;
    } else if (pn->right && pn->left) {
      
      aux_node = _bst_find_min_rec(pn->right);
      pn->info = aux_node->info;
      pn->right=_bst_remove_rec(pn->right, aux_node->info, cmp_elem);
    }
  }
  return pn;
}

void *tree_find_min(BSTree *tree) {
  BSTNode *min_node = NULL;

  if (!tree || !tree->root) {
    return NULL;
  }

  min_node = _bst_find_min_rec(tree->root);
  if (!min_node) return NULL;

  return min_node->info;
}

void *tree_find_max(BSTree *tree) {
  BSTNode *max_node = NULL;

  if (!tree || !tree->root) {
    return NULL;
  }

  max_node = _bst_find_max_rec(tree->root);
  if (!max_node) return NULL;

  return max_node->info;
}

Bool tree_contains(BSTree *tree, const void *elem) {
  if(!tree || !elem || !tree->root || !tree->cmp_ele){
    return FALSE;
  }

  return _bst_contains_rec(tree->root, elem, tree->cmp_ele);
}

Status tree_insert(BSTree *tree, const void *elem) {
  if(!tree || !elem || !tree->cmp_ele){
    return ERROR;
  }

  tree->root = _bst_insert_rec(tree->root, elem, tree->cmp_ele);

  if(tree->root == NULL){
    return ERROR;
  }

  return OK;
}

Status tree_remove(BSTree *tree, const void *elem) {

  if(!tree || !elem || !tree->root || !tree->cmp_ele){
    return ERROR;
  }

  tree->root = _bst_remove_rec(tree->root, elem, tree->cmp_ele);
  return OK;
}