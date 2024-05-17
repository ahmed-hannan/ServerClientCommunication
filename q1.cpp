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
#include<time.h>
#include <cstdlib>


//22i-0943 Cs A Anmed Hannan
using namespace std;

void display(int ** grid, int size, int x, int y)
{

    for(int i =0; i< size; i++)
    {
        bool playerx = 0;
        if(i == x)
            playerx =1;
        
        for(int j =0; j< size; j++)
        {
            if(playerx)
            {
                if(y == j)//Player is here
                {
                    cout << "P ";
                    continue; 
                }
            }
            if(grid[i][j] == -1)
            {
                cout << "x "; 
                continue;
            }
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

}


int main()
{
    srand(0);
    int boxsize = 10 + (rand() % 89);
    boxsize *= 3; //0943
    boxsize %= 25;
    if(boxsize < 10)
    {
        boxsize += 15;
    }

    int ** grid = new int*[boxsize];
    for(int i =0; i< boxsize;i++)
    {
        grid[i] = new int[boxsize];
    }

    for(int i =0; i< boxsize; i++)
    {
        for(int j =0; j < boxsize; j++)
        {
            grid[i][j] = 0; //emptying the entire thing
        }
    }

    int num;
    cout << "Enter number of players" << endl;
    cin >> num;
    while(num < 1)
    {
        cout << "Enter valid num of players"<< endl;
        cin >> num;
    }

    int pipes[num][2];

    pid_t pid;

    for(int i =0; i< num; i++)
    {
        if(pipe(pipes[i]) < 1)
        {
            cout << "Err!" << endl;
            return 0;
        }
        cout << "Pipe made for player " << i + 1 << endl; 


    }    

    for(int i =0; i< 5; i++)
    {
        for(int j =0; j< 2; j++)
        {
            int xval = rand() % boxsize;
            int yval = rand() % boxsize;
            grid[xval][yval] = -1;
        }
    }

    for(int i =0; i< num; i++)
    {
        if(!fork()) //child
        {
            
        }
    }







    

    

}