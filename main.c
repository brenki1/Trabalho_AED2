#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

int main(){

    short esc = 0;

    do{

        printf("1) \n2) \n3) \n");
        scanf("%i", &esc);

    }while((esc < 1) || (esc > 3));

    switch(esc){
        case 1: printf("a");
    }

    return 0;
}