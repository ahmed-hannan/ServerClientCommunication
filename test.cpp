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

int main()
{

    void * sharedmemory;
    int shmid;
    char buff[100] ="waste";
    shmid = shmget((key_t)1234, 1024, 0666 | IPC_CREAT);

    sharedmemory = shmat(shmid, NULL, 0);
    char str1[] = "\0";
    strcpy((char*)sharedmemory, str1); //resetting

    if(!fork()) //child
    {
       
        
        
        write(shmid, buff, sizeof(buff)-1);
        //strcpy((char*)sharedmemory, buff);
        
        return 0; 
    }

    printf("Parent-> %s\n\n\n", (char*)sharedmemory);

    read(shmid, buff, sizeof(buff) -1);
    cout << buff << endl;



    return 0;
}












































































































/*
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Child with args -> " << argc << endl;
    for(int i =0; i< argc; i++)
    {
        cout << argv[i] << endl;
    }

    cout<< "Child ends here" << endl;

    int val;
    cin >> val;

    

    return 0;
}
*/

// Basic child logic above
// Basic exec command below


/*

using namespace std;
int main() {
    int n;
    std::cout << "Enter the number of processes to create: ";
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        pid_t pid = fork();

        if (pid == 0) { // Child process
            
            std::string arg = std::to_string(i + 1);
            string s2 = "./test " + arg;
            execlp("gnome-terminal", "gnome-terminal", "--", "bash", "-c", s2.c_str(), "; exec bash", NULL);
            
            std::cerr << "Failed to execute gnome-terminal\n";
            exit(1);
        } else if (pid < 0) {
            std::cerr << "Failed to fork process\n";
            return 1;
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < n; ++i) {
        wait(NULL);
    }
    std::cout << "How mnay times does this print" <<std::endl;
    return 0;
}
*/