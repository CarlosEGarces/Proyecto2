#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]){
    srand(time(0));
    for(int i = 0; i < 10; ++i){
        printf("%i\n", (rand() % 10) + 1);
    }
    return 0;
}
