#include <iostream>
#include<windows.h>
#include<ctime>
#include<stdlib.h>
#include <cstdlib>
#define limite 150

using namespace std;

int main()
{
    int i = 0;
    int j = 0;

    while(i<limite){
        system("cls");
        j=0;
        while(j<i){
            cout << " ";
            j++;
        }
        cout << "*";
        Sleep(50);
        i++;
    }
}
