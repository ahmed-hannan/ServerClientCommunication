#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <sys/shm.h>
#include <string.h>
#include <pthread.h>
#include <fstream>




using namespace std;
//22i-0943 CS A Ahmed Hannan

struct Group
{
    int num;
    char * ids;
    Group()
    {
        num =0;
        ids = nullptr;
    }
};

//This is going to be the server 

int main()
{
    int i;
    void * sharedmemory;
    char buff[100];
    int shmid;
    Group * G_Pool = new Group[10];
    int groups=0;
    int clients;    
    shmid = shmget((key_t)1234, 1024, 0666 | IPC_CREAT);  //making shared memory
    char wipe[] = "\0";
    sharedmemory = shmat(shmid, NULL, 0);
    strcpy((char*)sharedmemory, wipe);


    printf("This is the server booting up, it will have to manage everything you do\n\n");
    printf("Enter number of clients to manage\n-> ");
    scanf("%d", &clients);
    
    
    //Emptying old memory
    
    

    for (int i = 0; i < clients; ++i) {
        pid_t pid = fork();

        if (pid == 0) { // Child process
            
            std::string arg = std::to_string(i + 1) + " " + (char)('0'+clients);
            
            string s2 = "./client " + arg;
            execlp("gnome-terminal", "gnome-terminal", "--", "bash", "-c", s2.c_str(), "; exec bash", NULL);
            
            std::cerr << "Failed to execute gnome-terminal\n";
            exit(1);
        } else if (pid < 0) {
            std::cerr << "Failed to fork process\n";
            return 1;
        }
    }
    
    while(1)
    {
        if(((char*)sharedmemory)[0] != '\0')
        {
            cout << "Message found by server -> " << (char*)sharedmemory << endl;
            strcpy((char*)sharedmemory, wipe);
            continue;
        }
        continue;
        
    }



    cout << "This should occur just once"<< endl; //Works!
    int val;
    cout << "enter val here" << endl;
    cin >> val;


    return 0;
}