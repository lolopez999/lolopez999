/*
About this program:
- This program counts words.
- The specific words that will be counted are passed in as command-line
  arguments.
- The program reads words (one word per line) from standard input until EOF or
  an input line starting with a dot '.'
- The program prints out a summary of the number of times each word has
  appeared.
- Various command-line options alter the behavior of the program.

E.g., count the number of times 'cat', 'nap' or 'dog' appears.
> ./main cat nap dog
Given input:
 cat
 .
Expected output:
 Looking for 3 words
 Result:
 cat:1
 nap:0
 dog:0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smp0_tests.h"

#define LENGTH(s) (sizeof(s) / sizeof(*s))

/* Structures */
typedef struct {
  char *word;
  int counter;
} WordCountEntry;


int process_stream(WordCountEntry entries[], int entry_count)
{
  short line_count = 0;
  char buffer[30];

  while (fgets(buffer,sizeof(buffer), stdin)) {
    if (*buffer == '.')
      break;
    /* Compare against each entry */
    
	size_t len = strlen(buffer);
	if(buffer[len -1] == '\n')
		buffer[--len] = 0;
	
	 
      if (!strcmp(entries[line_count].word, buffer))
        entries[line_count].counter++;
      if (++line_count == entry_count)
		  break;
    
  }
  return line_count;
}


void print_result(WordCountEntry entries[], int entry_count)
{
	fprintf (stdout, "\nResult:\n");
	
	for (int i = 0; i < entry_count; i++)
	{
  printf(stdout, "Result:\n");
  
  for (int i = 0; i < entry_count; i++){
  
    printf("%s:%d\n", entries[i].word, entries[i].counter);
	
  }
}


void printHelp(const char *name)
{
  fprintf(stderr, "usage: %s [-h] [-f FILENAME] <word1> ... <wordN>\n", name);
}


int main(int argc, char **argv)
{
  const char *prog_name = *argv;

  WordCountEntry entries[argc];
  int entryCount = 0;

  /* Entry point for the testrunner program */
for (int i =1; i <argc; i++){
  if (*argv[i] == '-') {
      switch ((*argv)[1]) {
        case 'h':
          printHelp(prog_name);
		  break;
        case 'f':
		freopen((*argv)[2], "w", stdout);
		break;
		default:
          fprintf(stderr, "%s: Invalid option %s. Use -h for help.\n", prog_name, *argv);
      }
    } else {
        entries[entryCount].word = *argv;
        entries[entryCount++].counter = 0;
      }
    }

  if (!entryCount) {
    fprintf("%s: Please supply at least one word. Use -h for help.\n",
           prog_name);
    return EXIT_FAILURE;
  }
  if (entryCount == 1) {
    fprintf("Looking for a single word\n");
  } else {
    printf("Looking for %d words\n", entryCount);
  }

  process_stream(entries, entryCount);
  print_result(entries, entryCount);

  return EXIT_SUCCESS;
  fflush(stdout);
}
