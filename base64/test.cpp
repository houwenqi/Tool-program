
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "base64.h"

int main(int argc, char* argv[])   
{   
    char *t = "cyhd";     
    int j = strlen(t);   
    char *enc = base64_encode(t, j);   
    int len = strlen(enc);   
    char *dec = base64_decode(enc, len);   
    printf("\noriginal: %s\n", t);   
    printf("\nencoded : %s\n", enc);   
    printf("\ndecoded : %s\n", dec);   
    free(enc);   
    free(dec);   
    return 0;   
} 