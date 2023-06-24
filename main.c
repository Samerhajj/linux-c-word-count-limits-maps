/*

  Word Count using dedicated lists,
  modified for Kinneret College on the Sea of Galile

*/

/*
Copyright © 2019 University of California, Berkeley

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include <assert.h>
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "word_count.h"

/* Global data structure tracking the words encountered */
WordCount *word_counts = NULL;

/* The maximum length of each word in a file */
#define MAX_WORD_LEN 64

/*
 * Total Word Count
 *
 * Returns the total amount of words found in infile.
 * Useful functions: fgetc(), isalpha().
 */
int num_words(FILE* infile) {
  int num_words = 0;
  char c;
  bool prev_space =false;
 do{
  c=tolower(fgetc(infile));//takes every char inside the file to a char parameter c
    if(!isspace(c) ||isalpha(c) ||isdigit(c)) // checks if digit or alphabet or not space
    {
      
        if(!prev_space &&c==EOF)//make sure no continuious spaces
        {
      num_words++;
    }prev_space=false;
  }
  else if(!prev_space)
  {
    num_words++;
    prev_space=true;
  }
}while(c!=EOF);//while we haven't reached EOF the do loop continues.

  return num_words;//return our num words
}

/*
 * Word Frequency Count
 *
 * Given infile, extracts and adds each word in the FILE to `wclist`.
 * Useful functions: fgetc(), isalpha(), tolower(), add_word().
 */
void count_words(WordCount **wclist, FILE *infile) {
char word[MAX_WORD_LEN+1];//our variable to store word
size_t index=0;//our index for the char
char c;
while((c=fgetc(infile))!=EOF)//we get every char in from file to our c parameter;
{
  if(isalpha(c) || isdigit(c)){
    word[index++]=tolower(c);//if our character is digit or alphabet. we store it in our word variable index++;
  }
  else{
    word[index]='\0';//if we finished reached end of word. we reset the word itself
    if(strlen(word)){
      add_word(wclist,word);//add word to the list
    }
    index=0;//we reset our index 
  }
}
word[index]='\0';
  if(strlen(word)){//make sure we dont have null in our word
    add_word(wclist,word);
  }
}

/*
 * Comparator to sort list by frequency.
 * Useful function: strcmp().
 */
static bool wordcount_less(const WordCount *wc1, const WordCount *wc2) {
  if(wc1->count !=wc2->count){
    return wc1->count <wc2->count;//sort our word count accordingly to frequency
  }
  return strcmp(wc1->word ,wc2->word )<0;// <0 because we want digits to appear first
}

/*
 * Comparator to reverse sort list by frequency.
 * Useful function: strcmp().
 */
static bool wordcount_more(const WordCount *wc1, const WordCount *wc2) {
    if(wc1->count !=wc2->count){
    return wc1->count >wc2->count;
  }
  return strcmp(wc1->word ,wc2->word )>0; //>0 because we want alphabets first
}


// In trying times, displays a helpful message.
static int display_help(void) {
	printf("Flags:\n"
	    "-c: Count the total amount of words in the file, or STDIN if a file is not specified.\n"
	    "-f: Count the frequency of each word in the file, or STDIN if a file is not specified.  Display words sorted by count (ascending), then alphabetically (A->Z)\n"
		"-r: Count the frequency of each word in the file, or STDIN if a file is not specified.  Display words sorted by count (descending), then reverse alphabetically (Z->A)\n"
	    "-h: Displays this help message.\n");
	return 0;
}

/*
 * Handle command line flags and arguments.
 */
int main (int argc, char *argv[]) {

  // Count Mode (default): outputs the total amount of words counted
  bool count_mode = false;
  int total_words = 0;

  // Freq Mode: outputs the frequency of each word
  bool freq_mode = false;
  bool reverse_mode = false;


  FILE *infile = NULL;

  // Variables for command line argument parsing
  int i;
  static struct option long_options[] =
  {
      {"count", no_argument, 0, 'c'},
      {"frequency", no_argument, 0, 'f'},
	  {"reverse", no_argument, 0, 'r'},
      {"help", no_argument, 0, 'h'},
      {0, 0, 0, 0}
  };

  // Sets flags
  while ((i = getopt_long(argc, argv, "cfrh", long_options, NULL)) != -1) {
      switch (i) {
          case 'c':
              count_mode = true;
              freq_mode = false;
     		  reverse_mode = false;
              break;
          case 'f':
              	count_mode = false;
              	freq_mode = true;
		reverse_mode = false;
              	break;
	  case 'r':
		count_mode = false;
		freq_mode = false;
		reverse_mode = true;
		break;
          case 'h':
              	return display_help();
		break;
      }
  }

  if (!count_mode && !freq_mode && !reverse_mode) {
    printf("Please specify a mode.\n");
    return display_help();
  }

  /* Create the empty data structure */
  init_words(&word_counts);

  if ((argc - optind) < 1) {
    // No input file specified, instead, read from STDIN instead.
    infile = stdin;
    if (count_mode)
    {
    total_words =total_words + num_words(infile);
}
   

  else if(freq_mode|| reverse_mode)
  {
    
    count_words(&word_counts,infile);
  
  }
}

    else {
    // At least one file specified. Useful functions: fopen(), fclose().
    // The first file can be found at argv[optind]. The last file can be
    // found at argv[argc-1].
    for (int i=optind;i<argc;i++)
    {
      FILE *file;
      file=fopen(argv[i],"r");
      total_words +=num_words(file);
      fclose(file);
    }
  }

  if (count_mode) {
    	printf("The total number of words is: %i\n", total_words);
  }  else if (freq_mode) {
    for (int i=optind;i<argc;i++)
    {
      infile=fopen(argv[i],"r");
      count_words(&word_counts,infile);
      fclose(infile);
    }
    	wordcount_sort(&word_counts, wordcount_less);
    	printf("The frequencies of each word are: \n");
    	fprint_words(word_counts, stdout);
   } else if (reverse_mode) {
    {
      for (int i=optind;i<argc;i++)
      {
        infile=fopen(argv[i],"r");
        count_words(&word_counts,infile);
        fclose(infile);
      }
    }
	 wordcount_sort(&word_counts, wordcount_more);
	 printf("The reverse frequencies of each word are: \n");
	 fprint_words(word_counts, stdout);
	}
  return 0;
}
