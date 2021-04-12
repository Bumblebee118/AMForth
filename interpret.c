#include "interpret.h"
#include "executor.h"
#include "global.h"

void startInterpret(FILE *stream) {
    //welcome text on startup
    fprintf(stdout, "Type 'bye' to exit\n");

    //initialize variables for loop exit and holding the next valid token
    int quit = 0;
    int interpret_error = 0;

    //initialize variables for getting a new line from the stream
    char *line = NULL;
    size_t length = 0;
    ssize_t nread;

    //get first line from stream and save in variable 'line'
    if ((nread = getline(&line, &length, stream)) == -1) quit = 1;
    else fwrite(line, nread - 1, 1, stdout);  //print content to stdout

    while (quit == 0) {

        //get the next token from the current line whoch has ben read in
        int len = nextTokenFromLine(line, &token, nread);    //get next token from stream

        //if the current line has no tokens left
        if ((len == 0) || (interpret_error == 1)) {
            //check if an error occurred
            if (interpret_error == 0) PRINT_INPUT_OK(stream);
            else interpret_error = 0;

            //get new line if end has been reached
            if ((nread = getline(&line, &length, stream)) == -1)quit = 1;
            else fwrite(line, nread - 1, 1, stdout);

        } else {

            //check if an error occurred or the the user wants to quit
            if (len == -1) {
                fprintf(stdout, "\nerror occured during parsing\n");
                quit = 1;
            } else if (len >= MAX_WORD_NAME_SIZE) {
                fprintf(stdout, "\nsize of token exceeds MAX_WORD_NAME_SIZE\n");
                quit = 1;
            } else if (strcmp(token, "bye") == 0) {
                fprintf(stdout, "\nsee you later!\n");
                quit = 1;
            } else {
                //call the executor if a valid token has been received -> executor checks dictionary
                //printf("token is: %s - len: %d\n", token, len);
                if (execute(token) == -1) {
                    if (stream != stdin) quit = 1;  //quit the interpreter if the program is run from file
                    else interpret_error = 1;       //if the input is stdin indicate that an error happened
                    // and start over with next line
                    clearStack(parameterStack);
                }

            }
        }
    }

    //free token if quit
    if (token != NULL) free(token);
    if (line != NULL) free(line);
}


/*int nextToken(FILE *stream, char **token_ptr) {
    //if token_ptr is NULL, then acquire memory
    if (*token_ptr == NULL) *token_ptr = malloc(sizeof(char) * MAX_WORD_NAME_SIZE);
    //check pointer again
    if (*token_ptr == NULL) return -1;

    //get next char from stream
    char currentChar = fgetc(stream);

    int len = 0;
    while ((currentChar != ' ') && (currentChar != '\t') && (currentChar != '\r') ){
        if (currentChar == EOF) {
            return -1;  //immediately return if the EOF has been reached
        }

        if(currentChar == '\n'){
            return -2;  //return -2 is the current line has ended
        }

        //only add new chars to string, it MAX_WORD_NAME_SIZE has not been exceeded
        if (len < MAX_WORD_NAME_SIZE - 1) {
            (*token_ptr)[len] = currentChar;
        }

        len++;
        currentChar = fgetc(stream);    //read in next char for next loop iteration,
                                        // even if MAX_WORD_NAME_SIZE has been reached
    }

    //getting rid of whitespaces by recursively calling nextToken
    //until a string with len > 0 is found
    if (len == 0) {
        return nextToken(stream, token_ptr);
    }

    //add zero delimiter at the end of string
    //special handling string with size bigger than MAX_WORD_NAME_SIZE
    if (len < MAX_WORD_NAME_SIZE - 1) {
        (*token_ptr)[len] = '\0';
    } else {
        (*token_ptr)[MAX_WORD_NAME_SIZE - 1] = '\0';
    }

    return len;
}*/

int nextTokenFromLine(char *line, char **token_ptr, ssize_t nread) {
    static int line_index = 0;

    //check if end of line has been reached
    if (line_index == nread) {
        line_index = 0;
        return 0;
    }

    //if token_ptr is NULL, then acquire memory
    if (*token_ptr == NULL) *token_ptr = malloc(sizeof(char) * MAX_WORD_NAME_SIZE);
    //check pointer again
    if (*token_ptr == NULL) return -1;

    //get next char from stream and also increment the index (important for recursive calls)
    char currentChar = line[line_index];
    line_index++;

    int len = 0;
    while ((currentChar != ' ') && (currentChar != '\t') && (currentChar != '\r') && (currentChar != '\n') &&
           (line_index < nread)) {

        //only add new chars to string, it MAX_WORD_NAME_SIZE has not been exceeded
        if (len < MAX_WORD_NAME_SIZE - 1) {
            (*token_ptr)[len] = currentChar;
        }

        len++;
        currentChar = line[line_index];     //read in next char for next loop iteration,
        // even if MAX_WORD_NAME_SIZE has been reached
        line_index++;
    }

    //getting rid of whitespaces by recursively calling nextToken
    //until a string with len > 0 is found
    if (len == 0) {
        return nextTokenFromLine(line, token_ptr, nread);
    }

    //add zero delimiter at the end of string
    //special handling string with size bigger than MAX_WORD_NAME_SIZE
    if (len < MAX_WORD_NAME_SIZE - 1) {
        (*token_ptr)[len] = '\0';
    } else {
        (*token_ptr)[MAX_WORD_NAME_SIZE - 1] = '\0';
    }

    return len;
}

void PRINT_INPUT_OK(FILE *stream) {
    if (stream == stdin) fprintf(stdout, " ok\n");
}