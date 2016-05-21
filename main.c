#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SIZE 1024

char** read_lines(FILE* txt, int* count) {
    char** array = NULL;        /* Array of lines */
    int    i;                   /* Loop counter */
    char   line[100];           /* Buffer to read each line */
    int    line_count;          /* Total number of lines */
    int    line_length;         /* Length of a single line */

    /* Clear output parameter. */
    *count = 0;

    /* Get the count of lines in the file */
    line_count = 0;
    while (fgets(line, sizeof(line), txt) != NULL) {                                      
       line_count++;
    }

    /* Move to the beginning of file. */
    rewind(txt);

    /* Allocate an array of pointers to strings 
     * (one item per line). */
    array = malloc(line_count * sizeof(char *));
    if (array == NULL) {
        return NULL; /* Error */
    }

    /* Read each line from file and deep-copy in the array. */
    for (i = 0; i < line_count; i++) {    
        /* Read the current line. */
        fgets(line, sizeof(line), txt);

        /* Remove the ending '\n' from the read line. */
        line_length = strlen(line);        
        line[line_length - 1] = '\0';
        line_length--; /* update line length */

        /* Allocate space to store a copy of the line. +1 for NUL terminator */
        array[i] = malloc(line_length + 1);

        /* Copy the line into the newly allocated space. */
        strcpy(array[i], line);
    }

    /* Write output param */
    *count = line_count;

    /* Return the array of lines */
    return array;
}

int main(int argc, char* argv[]) {

	char**      array    = NULL;    /* Array of read lines */
    FILE*       file     = NULL;    /* File to read lines from */
    const char* filename = NULL;    /* Name of the input file */
    int         i, j;                  /* Loop index */
    int         line_count;         /* Total number of read lines */

    /* Get filename from the command line. */
    if (argc != 2) {
        printf("Specify the input file from the command line.\n");
        return 1;
    }    
    filename = argv[1];

    /* Try opening the file. */
    file = fopen(filename, "rt");
    if (file == NULL) {
        printf("Can't open file %s.\n", filename);
        return 1;
    }

    /* Read lines from file. */
    array = read_lines(file, &line_count);

    int ** graph = malloc(sizeof(int*) * atoi(array[0]));

    for(i = 0; i < atoi(array[0]); i++) {
    	graph[i] = malloc(sizeof(int*) * atoi(array[0]));
    }

    /* Just for test, print out the read lines. */
    for (i = 1; i < line_count; i++) {
        //printf("[%d]: %s\n", (i+1), array[i]);
    	int p = atoi(strtok(array[i], " "));
    	int k = p;
    	p = atoi(strtok(NULL, " "));

    	graph[k][p] = 1;
    }

    for(i = 0; i < sizeof(graph); i++) {
    	printf("%d\n", i);
    	for(j = 0; j < sizeof(graph[i]); j++) {
    		printf("%d %d = %d\n", i, j, graph[i][j]);
    	}
    }

    /* Cleanup. */
    fclose(file);
    for (i = 0; i < line_count; i++) {
        free(array[i]);
    }
    free(array);
    array = NULL;

    /* All right */
    return 0;
}