#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

int main(int argc, char**argv){
    if(argc != 3){
        printf("Syntaxe : ./%s poly1 poly2",argv[0]);
        exit(-1);
    }
    p_polyf_t p1,p2;
    p1 = lire_polynome_float(argv[1]);
    p2 = lire_polynome_float(argv[2]);
    ecrire_polynome_float(p1);
    ecrire_polynome_float(p2);
    if(egalite_polynome(p1,p2)){
        printf("Les polynômes sont égaux\n");
    }else{
        printf("les polynômes sont différents\n");
    }
    detruire_polynome(p1);
    detruire_polynome(p2);
    p_polyf_creux_t p_creux1,p_creux2;
    p_creux1 = lire_polynome_creux_float(argv[1]);
    p_creux2 = lire_polynome_creux_float(argv[2]);
    ecrire_polynome_float_creux(p_creux1);
    ecrire_polynome_float_creux(p_creux2);
    if(egalite_polynome_creux(p_creux1,p_creux2)){
        printf("Les polynômes creux sont égaux\n");
    }else{
        printf("Les polynômes creux sont différents\n");
    }
    detruire_polynome_creux(p_creux1);
    detruire_polynome_creux(p_creux2);
    return 0;
}