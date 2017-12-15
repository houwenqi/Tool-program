#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>

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
    
    string s ;
    
    cout << "Please Enter info to encryption : " << endl;
    cin >> s;
    
    encryption(s, a);
    
    cout << "The result is : " << s <<endl; 

    return 0;
}