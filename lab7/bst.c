#include <stdlib.h>
#include <stdio.h>
#include "adrbook.h"

const char *_bst_todo_format = "TODO [bst]: %s\nhalting\n";

bst *bst_singleton(vcard *c)
{
  bst *res = (bst *)malloc(sizeof(bst));
  res->c =  c;
  res->left = NULL;
  res->right = NULL;

  return res;
}


/*

 insertion, by alphabetical order of cnet ID, of a vcard into a bst
 (use strcmp for alphabetical order),

*/
int bst_insert(bst *t, vcard *c)
{
  if(t == NULL) {
    fprintf(stderr, "Error: NULL Tree passed into bst_insert");
    exit(1);
  }
  
  int cmp = strcmp(c->cnet, t->c->cnet);
  bst *node = bst_singleton(c);


  if(cmp == 0) {
    return 0;
  }
  else if (cmp < 0) { // left case
    if(t->left == NULL) { // left is empty
      t->left = bst_singleton(c);
    } else if (strcmp(c->cnet, t->left->c->cnet) > 0) { // left is less than new
      bst *tmp = t->left;
      t->left = node;
      node->left = tmp;
      return 1;
    }
    else { // left greater than new
    bst_insert(t->left, c);
    }
    return 1;
  }
  else { // right case
    if(t->right == NULL) { // right dne
      t->right = bst_singleton(c);
    } else if (strcmp(c->cnet, t->right->c->cnet) < 0) { // right greater than c
      bst *tmp = t->right;
      t->right = node;
      node->right = tmp;
      return 1;
    }
    else { // right less than c
    bst_insert(t->right, c);
    }
    return 1;
  }
}

unsigned int bst_num_entries(bst *t) {
  if(t == NULL) {
    return 0;
  }

  if(t->right == NULL && t->left == NULL) {
    return 1;
  }

  return bst_num_entries(t->left) + bst_num_entries(t->right) + 1;
}

unsigned int bst_height(bst *t)
{
  if(t == NULL) {
    return 0;
  }

  if(t->right == NULL && t->left == NULL) {
    return 1;
  }
  else if (t->right == NULL) {
    return 1 + bst_height(t->left);
  } else {
    return 1 + bst_height(t->right);
  }
}

vcard *bst_search(bst *t, char *cnet, int *n_comparisons)
{
  if(t == NULL) {
    return NULL;
  }

  int cmp = strcmp(cnet, t->c->cnet);
  (*n_comparisons)++;
  
  if(cmp == 0) {
    return t->c;
  }
  else if(cmp < 0) {
    return bst_search(t->left, cnet, n_comparisons);
  } else {
    return bst_search(t->right, cnet, n_comparisons);
  }
}

unsigned int bst_c(FILE *f, bst *t, char c)
{
  if(t == NULL) {
    return 0;
  }

  int cmp = (c == t->c->cnet[0]) ? 1 : 0;
  
  if(cmp) {
    fprintf(f, "%s\n", t->c->cnet);
    return 1 + bst_c(f, t->left, c) + bst_c(f, t->right, c);
  } else {
    return bst_c(f, t->left, c) + bst_c(f, t->right, c);
  }
}

void bst_free(bst *t)
{
  if(t == NULL) {
    return;
  } else {
    bst_free(t->right);
    bst_free(t->left);
    vcard_free(t->c);
    return;
  }
}
