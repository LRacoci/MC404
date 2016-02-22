#include <stdio.h>
int phibonacci(int r0){
    int r1 = 0, r2 = 1;
    r0--;
    loop:
        r1 += r2;
        r0--;
        if(r0 < 0)
        goto end;
        r2 += r1;
        r0--;
        if(r0 < 0)
        goto r2f;
    goto loop;


    r2f:
        r1 = r2;
    goto end;

    end:
    return r1;
}
int main(){
    int i, nn;
    scanf("%d", &nn);
    for(i = 0; i < nn; i++){
        printf("%d\n", phibonacci(i));
    }

}
