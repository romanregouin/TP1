#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

int main(int argc,char** argv){
    if(argc != 3){
        printf("Syntaxe : ./%s poly1 scalaire\n",argv[0]);
        exit(-1);
    }
    p_polyf_t p1;
    float result;
    float alpha = atof(argv[2]);
    p1 = lire_polynome_float(argv[1]);
    ecrire_polynome_float(p1);
    result = eval_polynome(p1,alpha);
    printf("Evaluation du polynôme par %f : %f",alpha,result);
    printf("\n\n");
    detruire_polynome(p1);
    p_polyf_creux_t p_creux1;
    p_creux1 = lire_polynome_creux_float(argv[1]);
    ecrire_polynome_float_creux(p_creux1);
    result = eval_polynome_creux(p_creux1,alpha);
    printf("Evaluation du polynôme creux par %f : %f",alpha,result);
    printf("\n\n");
    detruire_polynome_creux(p_creux1);
    return 0;
}