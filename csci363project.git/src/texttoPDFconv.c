#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

//runs a little execvp to convert a pdf into a txt file called pdfconv.txt
//from there we could run a parser on the .txt file to get the words.
//any other way of parsing through PDFs could be quite hairy
     
int main(int argc, char* argv[]){    
     if (argc < 2) {
        printf("Not enough args!\n");
        exit(1);
     }
     
     char *args[] = {"pdftotext", argv[1],"pdfconv.txt",NULL};
     if (execvp("pdftotext", args) < 0) {     /* execute the command  */
           printf("*** ERROR: exec failed\n");
           exit(1);
     }
     return 0;
}
