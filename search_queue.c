#include "search_queue.h"
#include "bstree.h"

#include <stdio.h>
#include <stdlib.h>

struct _SearchQueue
{
  BSTree *data;
};

SearchQueue *search_queue_new(P_ele_print print_ele, P_ele_cmp cmp_ele)
{
  SearchQueue *sq = NULL;

  sq = (SearchQueue *)calloc(1, sizeof(SearchQueue));

  if (!sq)
  {
    return NULL;
  }
  
  sq->data = tree_init(print_ele, cmp_ele);

  if (!sq->data)
  {
    search_queue_free(sq);
    return NULL;
  }

  return sq;
}

void search_queue_free(SearchQueue *q)
{
  if (q)
  {
    if (q->data)
    {
      tree_destroy(q->data);
    }
    
    free(q);
  }
  
}

Bool search_queue_isEmpty(const SearchQueue *q)
{
  if (!q || q->data)
  {
    return TRUE;
  }
  
  return tree_isEmpty(q->data);
}

Status search_queue_push(SearchQueue *q, void *ele)
{
  if (!q || !ele || !q->data)
  {
    return ERROR;
  }

  return tree_insert(q->data, ele);
}

void *search_queue_pop(SearchQueue *q)
{
  void *e;

  if (!q || !q->data)
  {
    return NULL;
  }
  
  e = tree_find_min(q->data);
  tree_remove(q->data, e);

  return e;
}

void *search_queue_getFront(const SearchQueue *q)
{
  void *e;

  if (!q || !q->data)
  {
    return NULL;
  }
  
  e = tree_find_min(q->data);

  return e;
}

void *search_queue_getBack(const SearchQueue *q)
{
  void *e = NULL;

  if (!q)
  {
    return NULL;
  }

  e = tree_find_max(q->data);

  return e;
}

void *search_queue_popBack(SearchQueue *q){
  void *e = NULL;

  if (!q)
  {
    return NULL;
  }

  e = tree_find_max(q->data);
  tree_remove(q->data, e);

  return e;
}

size_t search_queue_size(const SearchQueue *q)
{
  if (!q || !q->data)
  {
    return 0;
  }

  return tree_size(q->data);
}

int search_queue_print(FILE *fp, const SearchQueue *q)
{
  int count=0;

  if (!fp || !q || !q->data)
  {
    return -1;
  }

  count += tree_inOrder(fp, q->data);
  
  return count;
}
