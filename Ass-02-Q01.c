/*
 * TO DO
 * - Currently issues passing by reference to functions.
 * - Need to handle backspaces in the parser.
 *
 */

#include "Ass-02.h"
#ifdef STM32F407xx
#include "usart.h"
#endif

#define MAX_STR_LEN 100		// Maximum characters in the input string
#define CR 13				// Carriage return character

/* void serial_string_parser(char**,int*); */
void serial_string_parser(void);
int string_parser(char *inp, char **array_of_words_p[]);

int main()
{
	CommandLineParserInit();
	while(1)
		CommandLineParserProcess();
}

void CommandLineParserInit (void){

  printf ("\n");
  printf ("%s\n", ASS_STRING);
  printf ("%s\n", VER_STRING);
  printf ("Command Line Parser Example\n");
}

// Check for input and echo back
void CommandLineParserProcess (void){

#ifdef STM32F407xx
	char** arrayOfWords = NULL;			//This will hold the parsed inputs, broken into words.
	int* count;
	count = 0;
	serial_string_parser(arrayOfWords, count);			//This will echo the input and populate the arrayOfWords.



	//Do a check that things went correctly by doing a loop through ArrayOfWords and printing.

	//printf("\n\n The number of words is: %d", *count);


	//Do the string command handling here.
		//Build some function to handle things.
		//
	//If macro is incorrect.
	#else


	  /* int c; */
	  /* char* word; */
          /*  */
	  /* word = "string"; */
	  /* word += c; */
	  /* printf("word = '%s'\n", word); */
          /*  */
	  /* c = getchar(); */
	  /* if (c<0) */
	  /* { */
		/* printf("INFO: Exiting program.\n"); */
		/* exit(0); */
	  /* } */
	  /* printf("SERIAL: Got "); */
	  /* if ((c<32) | (c>126)) */
	  /* { */
		/* printf("ASCII %d\n", c); */
	  /* } */
	  /* else */
	  /* { */
		/* printf("character '%c'\n", c); */
	  /* } */
	/* serial_string_parser(arrayOfWords, count); */
	char** arrayOfWords = NULL;			//This will hold the parsed inputs, broken into words.
	int* count;
	count = 0;
	/* serial_string_parser(arrayOfWords, count);			//This will echo the input and populate the arrayOfWords. */
	serial_string_parser();
	printf("The array of words is:");
	for (int i = 0; i < sizeof(arrayOfWords); i++)
	{
		printf("%s", arrayOfWords[i]);
	}
	printf("worddddddddd");

#endif
}
void serial_string_parser(void) {
  char c;
  int i, j;
  char command_line[MAX_STR_LEN + 1];
  char **array_of_words;
  int count;

  // Get one line of input
  printf("--> Enter text:\n");
  i = 0;
  c = getchar();
  while (c != '\n' && i < MAX_STR_LEN) {
    printf("%c", c);
    if (c < ' ')
      printf("[0x%02x]", c);
    command_line[i] = c;
    i++;
    c = getchar();
  }
  command_line[i] = 0;

  // Parse the input and print result
  count = string_parser(command_line, &array_of_words);
  printf("\n--> count = %d\n", count);
  for (j = 0; j < count; j++) {
    printf("---> %2d: '%s'\n", j + 1, (array_of_words)[j]);
// ~~~ operations
    if (j == 2)
    {
	    float one = strtof(array_of_words[1], NULL);
	    float two = strtof(array_of_words[2], NULL);

	    float result = -1;
	    if (strcmp(array_of_words[0], "add") == 0)
		    result = one + two;

	    if (strcmp(array_of_words[0], "div") == 0)
		    result = one / two;

	    if (strcmp(array_of_words[0], "mul") == 0)
		    result = one * two;
	    printf("\n Result of operation is: %f\n", result);
	    // ~~~ operations ^
    }
  }
  if (count != 0) {
    free(array_of_words[0]);
    free(array_of_words);
  }

}


/* These functiond are from Q4 of A1 */

/*
 * Gets the size of the contents of a char pointer.
 * The function will only be used in this file and so is static.
 *
 * @Params:
 *
 *  char* s - input pointer whose contents are the subject of the function.
 *
 *
 * @Returns:
 *
 *  int - this is the size of the pointer's subject in bytes.
 *
 *
 */
static int getSize(char *s){

  char* t;                        //This pointer will move through the input input pointer's contents.
  for(t = s; *t !='\0'; t++){}    //Moves the t through contents of s until it NULL terminator
  return t - s;                   //The difference in address between two pointers is the size of s. s points to beggining and t points to the end.
}
/*
 * Find the number of "words" in an series of characters based on a delimiter.
 *
 * @Params:
 *
 *  char* s - input pointer whose contents are the subject of the function.
 *  char delim - a delimiter that determines what is a word and what isn't.
 *               This parameter can be passed by value as it is not modified
 *               by the function.
 *
 * @Returns:
 *
 *  int - the number of words in the series of characters.
 *
 *
 */
static int getNumWords(char *s, char delim){

  char* t;                                  //This pointer will move through the input input pointer's contents.
  char tPrev;
  int wordCount = 0;
  int flag1 = 0;
  int flag2 = 0;                      //Flags for determining if word is present.



for(t = s+1; *t !='\0'; t++){             //Loop begins at second character.

    tPrev = *(t-1);                         //Hold previous character.

    if((*t != delim && tPrev == delim) || (t == (s+1) && tPrev != delim)){     //Check if the beginning of word has been found.
      flag1 = 1;
    }
    if((tPrev != delim && *t == delim) || ((t-s) == (getSize(s)-1) && *t != delim)){//Check if the end of word has been found.
      flag2 = 1;
    }


    if(flag1 && flag2){                     //If both flags set a whole word has been found!
      wordCount++;
      flag1 = 0;                            //Reset the flags.
      flag2 = 0;
    }

  }
  return wordCount;


}
/*
 * Given a delimiter terminated word determines the number of characters in the word.
 *
 * @Params
 *  char* word - target of the character count.
 *  char delim - the character indicating the end of the word.
 *
 * @Returns
 *  int - the number of characters in the word.
 */
static int getWordCharCount(char* word, char delim){
  int numChar = 0;
  int i = 0;

  while(*(word+i) != delim){
    numChar++;
    i++;
  }


  return numChar;
}
/*
 * Break ups a string by a delimiter (currently a space " "). Will be modified later to include a delimiter parameter (dynamic for later assignments).
 *
 * @Params:
 *
 *  char* inp - the input data to be parsed.
 *  char** array_of_words_p[] - pointer to a pointer to an array of char. (Which is also an array of pointers?) Will be updated to hold the words in
 *                              in the char* input as determined by the delimiter.
 *
 * @Returns:
 *
 *  int - the number of words in the input char* as determined by the delimiter.
 */
int string_parser(char *inp, char **array_of_words_p[]) {

  int sizeOfInput = getSize(inp);
  int wordsInInput = getNumWords(inp, ' ');

  if(wordsInInput == 0 || sizeOfInput == 0) return 0;

  *array_of_words_p = (char**)malloc(sizeof(char*) * wordsInInput);
  wordsInInput = 0;
  char* carrier;      //Points to characters in the input.
  int numChar = 0;

  for(int i = 0; i < sizeOfInput; i++){
    carrier = inp + i;
    if(*(carrier) != ' '){
       numChar = getWordCharCount((carrier), ' ');
       (*array_of_words_p)[wordsInInput] = (char*)malloc(sizeof(char)*(numChar+1));
       i+= numChar;
       wordsInInput++;
       numChar = 0;
    }
  }

    wordsInInput = 0;
    numChar = 0;


  for(int i = 0; i < sizeOfInput; i++){
    carrier = inp + i;
    if(*(carrier) != ' '){                                          //If delimiter reached stop writing word to array.
       (*array_of_words_p)[wordsInInput][numChar] = *(carrier);
       numChar++;
    }

    if(*(carrier) == ' ' && i!=0){                                  //If end of word reached and it's no beginning of input.
      if(*(carrier - 1) != ' '){                                    //If previous character was not delim, then a new word has been logged.
        (*array_of_words_p)[wordsInInput][numChar] = '\0';          //Append NULL to end of string to terminate word.
        wordsInInput++;                                             //Count the word.
      }

      numChar = 0;                                                  //Reset numbe rof characters.
    }

    if(i == (sizeOfInput - 1) && *(carrier) != ' '){                //If end of input reached and last character is not delim then append the NULL.
      (*array_of_words_p)[wordsInInput][numChar] = '\0';            //Append NULL to end of string to terminate word.
    }
  }


  return getNumWords(inp,' ');

}