#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include "base64.h"

using namespace std;

void decode(string& c,int a[]){ 

    for(int i = 0, j = 0; c[j];j++, i = (i + 1) % 7){
        
        c[j]-=a[i];
        
        if(c[j] < 32) c[j] += 90;
    }
}

int main()
{
    int a[] = {4, 9, 6, 2, 8, 7, 3};
    string str;

    cout << "Please Enter info to decode : " << endl;
    cin >> str;

    decode(str, a);
    //cout << "str is : " << str <<endl;

    char ctr[100] = "";
    strcpy(ctr,str.c_str());
    int len = strlen(ctr);   
    char *dec = base64_decode(ctr, len);

    cout << "The result is : " << dec << endl;

    return 0;
}