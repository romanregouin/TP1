#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

int main(int argc,char** argv){
    if(argc != 3){
        printf("Syntaxe : %s poly1 n\n",argv[0]);
        exit(-1);
    }
    p_polyf_t p1,p2;
    p1 = lire_polynome_float(argv[1]);
    ecrire_polynome_float(p1);
    int n = atoi(argv[2]);
    p2 = puissance_polynome(p1,n);
    printf("Polynôme à la puissance %d : ",n);
    ecrire_polynome_float(p2);
    printf("\n");
    detruire_polynome(p1);
    detruire_polynome(p2);
    p_polyf_creux_t p_creux1,p_creux2;
    p_creux1 = lire_polynome_creux_float(argv[1]);
    ecrire_polynome_float_creux(p_creux1);
    p_creux2 = puissance_polynome_creux(p_creux1,n);
    printf("Polynôme creux à la puissance %d : ",n);
    ecrire_polynome_float_creux(p_creux2);
    printf("\n");
    detruire_polynome_creux(p_creux1);
    detruire_polynome_creux(p_creux2);
    return 0;
}