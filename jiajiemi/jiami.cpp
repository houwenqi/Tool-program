#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include "base64.h"

using namespace std;

void encryption(string& c, int a[]){ 

    for(int i = 0, j = 0; c[j];j++, i = (i + 1) % 7){
        
        c[j]+=a[i];
        
        if(c[j] > 122) c[j] -= 90;
    }
}

int main()
{
    int a[] = {4, 9, 6, 2, 8, 7, 3};
    string str;
    cout << "Please Enter info to encryption : " << endl;
    cin >> str;
       
    char ctr[100] = "";
    strcpy(ctr,str.c_str());
    int len = strlen(ctr);   
    char *enc = base64_encode(ctr, len);
    //cout << "enc is : " << enc << endl;

    string ret = enc;
    encryption(ret, a);
    
    cout << "The result is : " << ret <<endl; 

    return 0;
}