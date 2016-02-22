#include <stdio.h>
#include <stdlib.h>

int main(){
    long long unsigned int val = -1;
    long long unsigned int aux = -1;
    aux >>= 12;
    aux <<= 12;
    val -= aux;
    printf("val = 0x%llX\n", val);
    return 0;
}
