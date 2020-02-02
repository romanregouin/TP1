#include <stdio.h>
#include <stdlib.h>

#include "poly.h"
inline int test_polynomes(int argc, char **argv);
inline int test_polynomes_creux(int argc, char **argv);

int main (int argc, char **argv)
{  
  if (argc != 6)
    {
      fprintf (stderr, "5 paramètres (polynomes1(fichier),polynomes2(fichier),scalaire,x,puissance) sont à passer \n") ;
      exit (-1) ;
    }
  test_polynomes(argc,argv);
  fprintf(stdout, "---------------------------------------------------------------------------------\n");
  test_polynomes_creux(argc,argv);

}

int test_polynomes(int argc, char **argv){
  
  p_polyf_t p1, p2, p3, p5, p6, p7;
  
  fprintf(stdout, "Début des tests sur les polynômes\n\n");
  p1 = lire_polynome_float (argv [1]) ;
  p2 = lire_polynome_float (argv [2]) ;

  ecrire_polynome_float (p1) ;
  ecrire_polynome_float (p2) ;

  if(egalite_polynome(p1,p2)){
    fprintf (stdout, "Les poplynômes sont égaux.\n\n");
  }else
  {
    fprintf (stdout, "Les polynômes sont différents.\n\n");
  }

  float a = atof(argv [3]);

  fprintf(stdout, "Résultat de p1 * %f :\n\n",a);
  p3 = multiplication_polynome_scalaire(p1,a);
  ecrire_polynome_float(p3);
  fprintf(stdout, "Résultat de p2 * %f :\n\n",a);
  p3 = multiplication_polynome_scalaire(p2,a);
  ecrire_polynome_float(p3);

  float x = atof(argv [4]);
  
  fprintf(stdout, "Résultat de p1(%f) :\n\n",x);
  fprintf(stdout, "-> %f\n",eval_polynome(p1,x));
  fprintf(stdout, "Résultat de p2(%f) :\n\n",x);
  fprintf(stdout, "-> %f\n",eval_polynome(p2,x));

  fprintf(stdout, "Multiplication des 2 polynômes entre eux :\n\n");
  p5 = multiplication_polynomes(p1,p2);
  ecrire_polynome_float(p5);

  int n = atoi(argv [5]);

  fprintf(stdout, "Resultat de la puissance du polynôme p1 par %d :\n\n",n);
  p6 = puissance_polynome (p1,n);
  ecrire_polynome_float(p6);
  fprintf(stdout, "Resultat de la puissance du polynôme p2 par %d :\n\n",n);
  p6 = puissance_polynome (p2,n);
  ecrire_polynome_float(p6);

  fprintf(stdout, "Resultat de la composition de p1 avec p2 :\n\n");
  p7 = composition_polynome (p1,p2);
  ecrire_polynome_float(p7);

  fprintf(stdout, "Fin des tests sur les polynômes.\n\n");
  return 0;
}

int test_polynomes_creux(int argc, char **argv){
  
  p_polyf_creux_t p1, p2, p3, p4;
  
  fprintf(stdout, "Début des tests sur les polynômes creux.\n\n");
  
  p1 = lire_polynome_creux_float (argv [1]) ;
  p2 = lire_polynome_creux_float (argv [2]) ;

  ecrire_polynome_float_creux (p1) ;
  ecrire_polynome_float_creux (p2) ;

  if(egalite_polynome_creux(p1,p2)){
    fprintf (stdout, "Les poplynômes sont égaux.\n\n");
  }else{
    fprintf (stdout, "Les polynômes sont différents.\n\n");
  }

  float a = atof(argv [3]);
  fprintf(stdout, "Résultat de p1 * %f :\n\n",a);
  p3 = multiplication_polynome_scalaire_creux(p1,a);
  ecrire_polynome_float_creux(p3);
  fprintf(stdout, "Résultat de p2 * %f :\n\n",a);
  p4 = multiplication_polynome_scalaire_creux(p2,a);
  ecrire_polynome_float_creux(p4);

  float x = atof(argv [4]);
  
  fprintf(stdout, "Résultat de p1(%f) :\n\n",x);
  fprintf(stdout, "-> %f\n",eval_polynome_creux(p1,x));
  fprintf(stdout, "Résultat de p2(%f) :\n\n",x);
  fprintf(stdout, "-> %f\n",eval_polynome_creux(p2,x));

  fprintf(stdout, "Multiplication des 2 polynômes entre eux :\n\n");
  p3 = multiplication_polynomes_creux(p1,p2);
  ecrire_polynome_float_creux(p3);

  int n = atoi(argv [5]);

  fprintf(stdout, "Resultat de la puissance du polynôme p1 par %d :\n\n",n);
  p3 = puissance_polynome_creux (p1,n);
  ecrire_polynome_float_creux(p3);
  fprintf(stdout, "Resultat de la puissance du polynôme p2 par %d :\n\n",n);
  p4 = puissance_polynome_creux (p2,n);
  ecrire_polynome_float_creux(p4);

  fprintf(stdout, "Resultat de la composition de p1 avec p2 :\n\n");
  p3 = composition_polynome_creux (p1,p2);
  ecrire_polynome_float_creux(p3);

  fprintf(stdout, "Fin des tests sur les polynômes.\n");
  return 0;
}