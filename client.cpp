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
#include <sys/wait.h>



using namespace std;


int chartoInt(char a)
{
    return (int)(a-'0');
}


int* managePMS(int total, int num)
{
    int * ids = new int[total];
    int keyval;
    for(int i =0 ;i < total; i++)//number of PMs possible for this guy
    {
        keyval = num * 10 + (i+1);
        if(num > i)
            keyval = (i+1) * 10 + num;
        
        ids[i] = shmget((key_t)keyval, 1024, 0666 | IPC_CREAT );
       
    }
    return ids;

}
void checkPMs(int * ids, int total, char arr1[], int curr, string s)
{
    
    int keyval;
    int shmid;
    void * mem;
    char arr[20];
    for(int i =0; i< total; i++)
    {
        keyval= (i+1)* 10 + curr;
        if(i == curr)
        {
            continue;
        }   
        if(i > curr)
            keyval = curr* 10 + (i + 1);
        shmid = shmget((key_t)keyval, 1024, 0666 | IPC_CREAT);
        mem = shmat(shmid, NULL, 0);
        strcpy(arr, (char*)mem);
        
        if(!arr[0])
            continue;
        else
        {
            if(chartoInt(arr[0])== curr)//sent by self
                continue;
            
            char * cptr = &arr[1];
            cout << "Found PM from client number -> " << arr[0] << ": " << cptr << endl;
            ofstream File1(s, ios::app);
            File1 << cptr << "\n";
            File1.close();
            char empty[] = "\0";
            strcpy((char*)mem, empty);
            break;
        }


    }

}


void sendPM(int val, int * ids, char buff[], int curr, string s)
{
    int res = chartoInt(buff[1]);
    

    int keyval = val * 10 + res;
    if(val > res)
        keyval = res * 10 + val;
    
    char msg[100];
    bool end =0;
    string message;
    message += (char)('0'+ curr);
    for(int i =2; i<100; i++)
    {
        if(!buff[i])
        {
            break;
        }
        message += buff[i];

    }
    
    

    void * mem;
    int shmid = shmget((key_t)keyval, 1024, 0666 | IPC_CREAT);
    mem = shmat(shmid, NULL, 0);
    if(!mem)
    {
        cout << "Error!";
        cin.ignore();
        return;
    }
    ofstream File1(s, ios::app);
    File1 << message << "\n";
    File1.close();
    strcpy((char*)mem, message.c_str());
    return;



}


int main(int argc, char * argv[])
{
    void * sharedmemory;
    char buff[100];
    char PrivM[100];
    int total;
    int *ids;
    void * priv;
    string s;
    s+= argv[1][0];
    s += ".txt";

    ofstream fileCurr(s); //making file
    fileCurr.close();

    int shmid = shmget((key_t)1234, 1024, 0666 | IPC_CREAT);
    sharedmemory = shmat(shmid, NULL, 0);
    cout << "This is client number -> " << argv[1] << endl;
    cout << "Total clients -> " << argv[2] << endl;
    total = chartoInt(argv[2][0]);
    int curr = chartoInt(argv[1][0]);

    ids = managePMS(total, curr);


    printf("Enter your message below\nStart it with 1 followed by client number to send it to client\n2 to request making a group\n3 to view chat history\nAny other gets sent to server\n\n");
    while(1)
    {   
        
        char msg[100]= "Not user input";
        if(((char*)sharedmemory)[0] != '\0')
        {
            sleep(1); //message not processed yet
            continue;
        }

        checkPMs(ids, total, PrivM, curr, s);
        string input;
        getline(cin,input);
        strcpy(buff, input.c_str());
        
        
        if(buff[0]== '1')//Private message
        {
            sendPM(curr, ids, buff, curr, s);
            sleep(1);
            continue;
        }   
        
        if(buff[0] == '3')
        {
            ifstream File2(s);
            string line;
            while (getline(File2, line)) {
                cout << line << '\n';
            }
            sleep(1);
            continue;
        }
        ofstream File2(s,ios::app);
        File2 << buff << "\n";
        File2.close();
        strcpy((char*)sharedmemory, buff);
        sleep(1);

        
        
    }
        

    


    return 0;
}