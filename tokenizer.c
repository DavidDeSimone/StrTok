/*
 * tokenizer.c
 */
#include <stdio.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

const int MAX_SIZE = 1000000;

struct TokenizerT_ {

  char* seps;
  char* tokens;
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

TokenizerT *TKCreate(char *separators, char *ts) {

  TokenizerT *strtok = malloc(sizeof(TokenizerT));
  //Question to ask, are the strings in the struct malloc'd right now?
  
  //If tokens are NULL, fail to form the struct and return NULL
  if(!tks) {
    return NULL;
  }


  strtok->seps = separators;
  strtok->tokens = ts;
  strtok->curr_pos = 0;
  strtok->len = strlen(ts);

  return strtok;
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

  if(argc != 2) {
    printf("Error, invalid number of arguments!");
  }
 
  //TODO: Check argv1 and 2 for validity, take off quote marks. 

  char* seps = argv[1];
  char* toks = argv[2];

  TokenizerT* strtok = TKCreate(seps, toks);

  while(hasNext(strtok)) {
    char* next = next(strtok);
    printf("%s\n", next);
  }


  return 0;
}


/* Function used to determine if the tokenized string has another token not 
 *  yet read
 */

int hasNext(TokenizerT *strtok) {

  char *buffer[MAX_SIZE]; //CHANGE SIZE TO BE VARIABLE
  int mark = 0;
  int i;

  for(i = 0; i < strtok->len; i++) {
    if(!isSep(strtok->seps, strtok->toks)) {
      buffer[mark] = strtok->toks[i];
      mark++;
    } else {
      break;
    }
  }
      if(mark == 0) {
	strtok->has_next = 0;
	return 0;
      }
      
      buffer[mark] = '\0';

      //Use strncpy to prevent against buffer overflow
      strncpy(strtok->next, buffer, mark);
      free(buffer);

      //Set the current position the number of steps we have progressed so far
      strtok->curr_pos = mark - 1;


  return 1;
}

/* Function used to return the next token of the String to be tokenized
 * Returns NULL if no tokens are left. String is placed on the heap. 
 * All escape characters will be placed by bracketed ASCII equivalents
 * i.e. \n will be replaced with [0x0a]
 */

