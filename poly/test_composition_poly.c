#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

int main(int argc,char** argv){
    if(argc != 3){
        printf("Syntaxe : %s poly1 poly2\n",argv[0]);
        exit(-1);
    }
    p_polyf_t p1,p2,p3;
    p1 = lire_polynome_float(argv[1]);
    ecrire_polynome_float(p1);
    p2 = lire_polynome_float(argv[2]);
    ecrire_polynome_float(p2);
    p3 = composition_polynome(p1,p2);
    printf("Composition du premier polynôme avec le deuxième");
    ecrire_polynome_float(p3);
    printf("\n");
    detruire_polynome(p1);
    detruire_polynome(p2);
    detruire_polynome(p3);
    p_polyf_creux_t p_creux1,p_creux2,p_creux3;
    p_creux1 = lire_polynome_creux_float(argv[1]);
    ecrire_polynome_float_creux(p_creux1);
    p_creux2 = lire_polynome_creux_float(argv[2]);
    ecrire_polynome_float_creux(p_creux2);
    p_creux3 = composition_polynome_creux(p_creux1,p_creux2);
    printf("Composition du premier polynôme creux avec le deuxième");
    ecrire_polynome_float_creux(p_creux3);
    printf("\n");
    detruire_polynome_creux(p_creux1);
    detruire_polynome_creux(p_creux2);
    detruire_polynome_creux(p_creux3);
    return 0;
}