#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libsocket/libinetsocket.h>
#include <ctype.h>
FILE * connect_to_server();
void menu();
char get_choice();
void list_files(FILE *s);
void download(FILE *s);
void quit(FILE *s);

int main()
{
    // Connect
    FILE * s = connect_to_server();
    
    while(1){
        // Menu
        menu();
    
        // Get choice
        char choice = get_choice();
    
        // Handle choice
        switch(choice)
        {
            case 'l':
            case 'L':
                list_files(s);
                break;
        
            case 'd':
            case 'D':
                download(s);
                break;
            
            case 'q':
            case 'Q':
                quit(s);
                exit(0);
                break;
            
            default:
                printf("Choice must be d, l, or q\n");
        }
    }
}

/*
 * Connect to server. Returns a FILE pointer that the
 * rest of the program will use to send/receive data.
 */
FILE * connect_to_server()
{
    int sockfd = create_inet_stream_socket("runwire.com", "1234", LIBSOCKET_IPv4, 0);
    if (!sockfd)
    {
        printf("Can't connect to server\n");
    }

    FILE *s = fdopen(sockfd, "r+");
    return s;
}

/*
 * Display menu of choices.
 */
void menu()
{
    printf("List files\n");
    printf("Download a file\n");
    printf("Quit\n");
    printf("\n");
}

/*
 * Get the menu choice from the user. Allows the user to
 * enter up to 100 characters, but only the first character
 * is returned.
 */
char get_choice()
{
    printf("Your choice: ");
    char buf[100];
    fgets(buf, 100, stdin);
    return buf[0];
}

 // Display a file list to the user.

void list_files(FILE *s)
{
    
   char list[500];
   
   fprintf(s, "LIST\n");
   
   while(fgets(list, 500, s) !=NULL)
   {
       
       if(strcmp(&list[0], ".\n") == 0) break;
       printf("%s", list);
   } 
   
   printf("\n");
   
}

/*
 * Download a file.
 * Prompt the user to enter a filename.
 * Download it from the server and save it to a file with the
 * same name.
 */
void download(FILE *s)
{
    char filename[50];
    char size[100];
    char data[1000];
    
    printf("Enter the filename\n");
    scanf("%s", filename);
    
    
    fprintf(s, "SIZE %s", filename);
    while(fgets(size, 100, s)!=NULL)
    {
        printf("%s", size);
    }
    
    
    
    
    //fprintf(s, "GET %s", filename);
    
    
    
}

/* 
 * Close the connection to the server.
 */
void quit(FILE *s)
{
    fclose(s);
}