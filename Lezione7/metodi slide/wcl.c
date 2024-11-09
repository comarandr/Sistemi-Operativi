//implementazione di wc -l 
#include <stdio.h>

int main()
{
    long nc = 0;
    for(int c = getchar(); c != EOF; c = getchar())
    {
        if(c == '\n')
            ++nc;
    }
    printf("%ld\n", nc);
    return 0;
}