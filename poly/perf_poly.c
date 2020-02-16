#include <stdio.h>
#include <stdlib.h>

#include "poly.h"

#include <x86intrin.h>

int deg_max(p_polyf_creux_t p){
  p_polyf_creux_t courant = p;
  if(courant==NULL){
    return -1;
  }
  if(courant->suivant==NULL){
    return courant->degre;
  }
  while(courant->suivant!=NULL){
    courant = courant->suivant;
  }
  return courant->degre;
}

static const float duree_cycle = (float) 1 / (float) 2.6 ; // duree du cycle en nano seconde 10^-9

void calcul_flop (char *message, int nb_operations_flottantes, unsigned long long int cycles)
{
  printf ("%s %d operations %f GFLOP/s\n", message, nb_operations_flottantes, ((float) nb_operations_flottantes) / (((float) cycles) * duree_cycle)) ;
  return ;
}

int main (int argc, char **argv)
{
  p_polyf_t p1, p2, p3;
  p_polyf_creux_t p_creux1, p_creux2, p_creux3;
  unsigned long long start, end ;
  
  if (argc != 5)
    {
      fprintf (stderr, "Syntaxe : %s poly1 poly2 alpha for multiplication scalaire\
       beta for eval polynôme\n",argv[0]) ;
      exit (-1) ;
    }
  
  float alpha = atof(argv[3]);
  float beta = atof(argv[4]);
  p1 = lire_polynome_float (argv [1]) ;
  p2 = lire_polynome_float (argv [2]) ;

  printf ("p1 = ") ;
  ecrire_polynome_float (p1) ;

  printf ("p2 = ") ;
  ecrire_polynome_float (p2) ;

  start = _rdtsc () ;
  
        p3 = addition_polynome (p1, p2) ;

  end = _rdtsc () ;

  printf ("p3 = ") ;
  ecrire_polynome_float (p3) ;
  
  printf ("addition %Ld cycles\n", end-start) ;
  calcul_flop ("p1+p2", min(p1->degre, p2->degre)+1, end-start) ;
  detruire_polynome (p3) ;

  p_creux1 = lire_polynome_creux_float(argv[1]);
  p_creux2 = lire_polynome_creux_float(argv[2]);
  printf("p1 creux =");
  ecrire_polynome_float_creux(p_creux1);
  printf("p2 creux = ");
  ecrire_polynome_float_creux(p_creux2);
  start = _rdtsc();
  p_creux3 = addition_polynome_creux(p_creux1,p_creux2);
  end = _rdtsc();
  int degre = min(deg_max(p_creux1),deg_max(p_creux2))+1;
  printf("addition %Ld cycles\n",end-start);
  calcul_flop("p1 creux + p2 creux",degre,end-start);
  detruire_polynome_creux(p_creux3);

  start = _rdtsc();
  p3 = multiplication_polynome_scalaire(p1,alpha);
  end = _rdtsc();
  printf ("p3 = ") ;
  ecrire_polynome_float (p3) ;
  printf ("addition %Ld cycles\n", end-start) ;
  calcul_flop ("p1+p2", min(p1->degre, p2->degre)+1, end-start) ;
  detruire_polynome (p3);

  start = _rdtsc();
  p_creux3 = multiplication_polynome_scalaire_creux(p_creux1,alpha);
  end = _rdtsc();
  printf("addition %Ld cycles\n",end-start);
  calcul_flop("p1 creux + p2 creux",degre,end-start);
  detruire_polynome_creux(p_creux3);

  start = _rdtsc();
  float res = eval_polynome(p1,beta);
  end = _rdtsc();
  printf ("res = %f\n",res) ;
  printf ("addition %Ld cycles\n", end-start) ;
  calcul_flop ("p1+p2", min(p1->degre, p2->degre)+1, end-start) ;

  start = _rdtsc();
  p_creux3 = eval_polynome_creux(p_creux1,beta);
  end = _rdtsc();
  printf("addition %Ld cycles\n",end-start);
  calcul_flop("p1 creux + p2 creux",degre,end-start);
  detruire_polynome_creux(p_creux3);


  /*
  p4 = creer_polynome (1024) ;
  p5 = creer_polynome (1024) ;

  init_polynome (p4, 1.0) ;
  init_polynome (p5, 2.0) ;

    start = _rdtsc () ;
  
        p6 = addition_polynome (p4, p5) ;

  end = _rdtsc () ;

  printf ("addition %Ld cycles\n", end-start) ;
  calcul_flop ("p4+p5", min(p4->degre, p5->degre)+1, end-start) ;
  detruire_polynome (p6) ;
  */
  
}
