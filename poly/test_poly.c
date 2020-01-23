#include <stdio.h>
#include <stdlib.h>

#include "poly.h"


int main (int argc, char **argv)
{
  p_polyf_t p1, p2, p3, p5, p6, p7;
  
  if (argc != 6)
    {
      fprintf (stderr, "5 paramètres (polynomes1(fichier),polynomes2(fichier),scalaire,x,puissance) sont à passer \n") ;
      exit (-1) ;
    }
      
  p1 = lire_polynome_float (argv [1]) ;
  p2 = lire_polynome_float (argv [2]) ;

  ecrire_polynome_float (p1) ;
  ecrire_polynome_float (p2) ;

  if(egalite_polynome(p1,p2)){
    fprintf (stdout, "Les poplynômes sont égaux.\n");
  }else
  {
    fprintf (stdout, "Les polynômes sont différents.\n");
  }

  float a = atof(argv [3]);

  fprintf(stdout, "Résultat de p1 * %f :\n",a);
  p3 = multiplication_polynome_scalaire(p1,a);
  ecrire_polynome_float(p3);
  fprintf(stdout, "Résultat de p2 * %f :\n",a);
  p3 = multiplication_polynome_scalaire(p2,a);
  ecrire_polynome_float(p3);

  float x = atof(argv [4]);
  
  fprintf(stdout, "Résultat de p1(%f)\n",x);
  fprintf(stdout, "Result : %f\n",eval_polynome(p1,x));
  fprintf(stdout, "Résultat de p2(%f)\n",x);
  fprintf(stdout, "Result : %f\n",eval_polynome(p2,x));

  fprintf(stdout, "Multiplication des 2 polynômes entre eux :\n");
  p5 = multiplication_polynomes(p1,p2);
  ecrire_polynome_float(p5);

  int n = atoi(argv [5]);

  fprintf(stdout, "Resultat de la puissance du polynôme p1 par %d\n",n);
  p6 = puissance_polynome (p1,n);
  ecrire_polynome_float(p6);
  fprintf(stdout, "Resultat de la puissance du polynôme p2 par %d\n",n);
  p6 = puissance_polynome (p2,n);
  ecrire_polynome_float(p6);

  fprintf(stdout, "Resultat de la composition de p1 avec p2\n");
  p7 = composition_polynome (p1,p2);
  ecrire_polynome_float(p7);
}