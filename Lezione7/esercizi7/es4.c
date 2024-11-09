#include <stdio.h>

int main(){
    int n = 0;
    int i = 0;
    for(int c = getchar(); c != EOF; c = getchar()){
        if(c ==' '){
            if(i==0){
                i++;
            }
        }
        else{
            if(i==1){
                n++;
                i=0;
            }
        }
    }
    if(i==1){
        n++;
    }
    printf("\n%d\n", n);
    return 0;
}