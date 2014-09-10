/*
 * tokenizer.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

const int MAX_SIZE = 1000000;

struct TokenizerT_ {

  char* seps;
  char* toks;
  int curr_pos;
  int len;
  int has_next;
  char* next;

};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

int isSep(char* seps, char chr);

TokenizerT *TKCreate(char *separators, char *ts) {

  TokenizerT *strtok = malloc(sizeof(TokenizerT));
  //Question to ask, are the strings in the struct malloc'd right now?
  
  //If tokens are NULL, fail to form the struct and return NULL
  if(!ts) {
    return NULL;
  }

  strtok->seps = malloc(strlen(separators) * sizeof(char));
  strtok->toks = malloc(strlen(ts) * sizeof(char));

  int tok_len = strlen(ts);
  int sep_len = strlen(separators);
  
  strncpy(strtok->seps, separators, sep_len);
  strncpy(strtok->toks, ts, tok_len);
  strtok->curr_pos = 0;
  strtok->len = tok_len;

  return strtok;
}


/* Frees the memory reserved for the next token in the String.
 */

void destroyNext(TokenizerT *strtok) {
  free(strtok->next);
}


/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
  free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {
  return tk->next;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {

  if(argc != 3) {
    printf("Error, invalid number of arguments!\n");
  }
 
  //TODO: Check argv1 and 2 for validity, take off quote marks. 

  char* seps = argv[1];
  char* toks = argv[2];

  TokenizerT* strtok = TKCreate(seps, toks);

  while(hasNext(strtok)) {
    char* next = TKGetNextToken(strtok);
    printf("%s\n", next);
    destroyNext(strtok);
  }

  TKDestroy(strtok);
  return 0;
}


/* Function used to determine if the tokenized string has another token not 
 *  yet read
 */

int hasNext(TokenizerT *strtok) {

  if(strtok->curr_pos >= strlen(strtok->toks)) {
    return 0;
  }


  char buffer[MAX_SIZE]; //CHANGE SIZE TO BE VARIABLE
  int mark = strtok->curr_pos;
  int i;
  int total = 0;
  

  for(i = mark; i < strtok->len; i++) {
    char* tmp = strtok->toks;
    char inspect = tmp[i];
    if(!isSep(strtok->seps, inspect)) {
      buffer[total] = strtok->toks[i];
      mark++;
      total++;
    } else {
      break;
    }
  }
      if(mark == 0) {
	strtok->has_next = 0;
	mark++;
	strtok->curr_pos = mark;
	return 0;
      }
      /* Add terminating character to buffer */
      buffer[total] = '\0';

      /*Malloc space for the next token in the struct */
      strtok->next = malloc(total);
      memset(strtok->next, 0, total);

      char *buff_ptr = &buffer[0];
      //Use strncpy to prevent against buffer overflow
      strncpy(strtok->next, buff_ptr, total);
      

      //Set the current position the number of steps we have progressed so far
      strtok->curr_pos = mark + 1;


  return 1;
}

/* Function used to determine if a given character is a seperator character
 * Works in O(n) time. 
 */
int isSep(char *seps, char chr) {
  int length = strlen(seps);
  int i;

  if(length == 0) {
    return 0;
  }

  for(i = 0; i < length; i++) {
    if(seps[i] == chr) {
      return 1;
    }
  }

  return 0;
}



/* Function used to return the next token of the String to be tokenized
 * Returns NULL if no tokens are left. String is placed on the heap. 
 * All escape characters will be placed by bracketed ASCII equivalents
 * i.e. \n will be replaced with [0x0a]
 */

