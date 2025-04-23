#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "search_queue.h"
#include "types.h"
#include "file_utils.h"

#define MAX_STRING 1024

int main(int argc, char argv[])
{
  SearchQueue *sq = NULL;
  FILE *fin = NULL, *fout = NULL;
  char *filename_in = NULL, *filename_out = NULL, *string = NULL, line[MAX_STRING];

  if (argc != 2)
  {
    fprintf(stdout, "The input format should be ./p4_e2 <input file> <output file>\n");
    return -1;
  }

  filename_in = argv[1];
  filename_out = argv[2];

  fin = fopen(filename_in, "r");

  if (!fin)
  {
    return -1;
  }

  sq = search_queue_new(string_print, string_cmp);

  if (!sq)
  {
    fclose(fin);
    search_queue_free(sq);
    return -1;
  }

  while ((string = fgets(line, MAX_STRING, fin)) != NULL)
  {
    search_queue_push(sq, string);
  }

  fclose(fin);

  fout = fopen(filename_out, "w");

  if (!fout)
  {
    search_queue_free(sq);
    return -1;
  }

  if (search_queue_print(fout, sq) < 0)
  {
    search_queue_free(sq);
    return -1;
  }

  fclose(fout);
  search_queue_free(sq);

  return 0;
}