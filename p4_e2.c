#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "search_queue.h"
#include "types.h"
#include "file_utils.h"

#define MAX_STRING 1024

int main(int argc, char *argv[])
{
  SearchQueue *sq = NULL;
  FILE *fin = NULL, *fout = NULL;
  char *filename_in = NULL, /*filename_out = NULL,*/ line[MAX_STRING];
  void *string = NULL/*, *n_string[MAX_STRING]*/;
  /*int i, total;*/

  if (argc != 3)
  {
    fprintf(stdout, "The input format should be ./p4_e2 <input file> <output file>\n");
    return -1;
  }

  filename_in = argv[1];
  /*filename_out = argv[2];*/
  fout = stdout;

  fin = fopen(filename_in, "r");

  if (!fin)
  {
    fprintf(stderr, "The input file could not be opened\n");
    return -1;
  }

  sq = search_queue_new(string_print, string_cmp);

  if (!sq)
  {
    fprintf(stderr, "The search queue could not be created\n");
    fclose(fin);
    search_queue_free(sq);
    return -1;
  }

  /*i = 0;*/

  while (fgets(line, MAX_STRING, fin) != NULL)
  {
    string = string_copy(line);
    /*n_string[i] = string;
    i++;*/
    search_queue_push(sq, string);
  }

  fclose(fin);

  /*fout = fopen(filename_out, "w");*/

  /*if (!fout)
  {
    fprintf(stderr, "The output file could not be opened\n");
    for (total = 0; total <= i; total++)
    {
      free(n_string[i]);
    }
    search_queue_free(sq);
    return -1;
  }*/

  if (search_queue_print(fout, sq) < 0)
  {
    fprintf(stderr, "The result could not be written on the output file\n");
    /*for (total = 0; total <= i; total++)
    {
      free(n_string[i]);
    }*/
    search_queue_free(sq);
    return -1;
  }

  fclose(fout);
  /*for (total = 0; total <= i; total++)
  {
    free(n_string[i]);
  }
  free(*n_string);*/
  search_queue_free(sq);

  return 0;
}