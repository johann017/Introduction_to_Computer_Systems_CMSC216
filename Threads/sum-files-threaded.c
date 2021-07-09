/*Johann Antisseril, johann, 0207, 116533928
 *
 *I pledge on my honor that I have not given or received any unauthorized
 *assistance on this assignment.*
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static void* read_and_sum(void *argv);


static void *read_and_sum(void *argv) {
  long one_file_sum = 0, *ret = NULL;
  FILE *fp = NULL;
  char *arg = NULL;
  int n = 0;
  ret = malloc(sizeof(long *));
  if (argv != NULL && ret != NULL) {
    arg = (char *)argv;
    fp = fopen(arg, "r");
    if (fp != NULL) {
      one_file_sum= 0;
      fscanf(fp, "%d", &n);
      while (!feof(fp)) {
	one_file_sum += n;
	fscanf(fp, "%d", &n);
      }
      fclose(fp);
      *ret = one_file_sum;
      return ret;
    }
  }
  return NULL;
}


int main(int argc, char *argv[]) {
  pthread_t *tids = NULL;
  long all_files_total = 0;
  void *retval = NULL;
  int i = 0;

  if (argc > 1) {
    tids = malloc(sizeof(pthread_t) * argc);
    if (tids != NULL) {
      tids[0] = 0;
      for (i= 1; i < argc; i++) {
	pthread_create(&tids[i], NULL, read_and_sum, argv[i]);
      }
    }
    for (i = 1; i < argc; i++) {
      pthread_join(tids[i], &retval);
      if (retval != NULL) {
	all_files_total += *(long *)retval;
	free(retval);
      }
    }
    free(tids);
  }
  printf("%ld\n", all_files_total);
  return 0;
}
