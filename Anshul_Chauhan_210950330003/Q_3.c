// Q_3: Open the file /usr/share/dictionary.txt in process P1 which is a parent. 
// Create two child process using fork. Child 1 searches for a word from the top of the 
// file and child 2 search from bottom of the file. The word is provided by parent Process. 
// Whichever child finds it prints the message "Found".

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t id1, id2;
    int fd, pi[2];
    char c, d, e;
    fd = open("/home/anshul/Downloads/dictionary.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error: dictionary.txt does not exist.\n");
        exit(0);
    }
    pipe(pi);
    id1 = fork();
    id2 = fork();

    if(id1 == 0)
    {
        close(pi[1]);
        read(pi[0], &d, 1);
        fprintf(stderr, "Word received from pipe: %c", d);
        do{
            read(fd, &e, 1);
            if(e == d)
            {
                printf("found %c = %c", d ,e);
                break;
            }
        }while(e != EOF);
    }
    else if(id2 == 0)
    {
        close(pi[1]);
        read(pi[0], &d, 1);
        do{
            read(fd, &e, 1);
            if(e == d)
            {
                printf("found %c = %c", d ,e);
            }
        }while(e != EOF);
    }
    else
    {
        close(pi[0]);
        fprintf(stderr, "Enter the word: ");
        fscanf(stdin, "%c", &c);
        write(pi[1], &c, 1);
    }
return 0;
}