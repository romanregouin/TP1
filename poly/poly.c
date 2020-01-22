#include <stdio.h>
#include <stdlib.h>

#include "poly.h"

#include <x86intrin.h>

p_polyf_t creer_polynome (int degre)
{
  p_polyf_t p ;
  
  p = (p_polyf_t) malloc (sizeof (polyf_t)) ;
  p->degre = degre ;

  p->coeff = (float *) malloc ((degre+1) * sizeof (float))  ;

  return p ;
}

void detruire_polynome (p_polyf_t p)
{
  free (p->coeff) ;
  free (p) ;

  return ;
}

void init_polynome (p_polyf_t p, float x)
{
  register unsigned int i ;

  for (i = 0 ; i <= p->degre; ++i)
    p->coeff [i] = x ;

  return ;
}



p_polyf_t lire_polynome_float (char *nom_fichier)
{
  FILE *f ;
  p_polyf_t p ;
  int degre ;
  int i  ;
  int cr ;
  
  f = fopen (nom_fichier, "r") ;
  if (f == NULL)
    {
      fprintf (stderr, "erreur ouverture %s \n", nom_fichier) ;
      exit (-1) ;
    }
  
  cr = fscanf (f, "%d", &degre) ;
  if (cr != 1)
    {
      fprintf (stderr, "erreur lecture du degre\n") ;
      exit (-1) ;
    }
  p = creer_polynome (degre) ;
  
  for (i = 0 ; i <= degre; i++)
    { 
      cr = fscanf (f, "%f", &p->coeff[i]) ;
       if (cr != 1)
    {
      fprintf (stderr, "erreur lecture coefficient %d\n", i) ;
      exit (-1) ;
    }
       
    }

  fclose (f) ;

  return p ;
}

void ecrire_polynome_float (p_polyf_t p)
{
  int i ;

  printf ("%f + %f x ", p->coeff [0], p->coeff [1]) ;
  
  for (i = 2 ; i <= p->degre; i++)
    {  
      printf ("+ %f X^%d ", p->coeff [i], i) ;
    }
  
  printf ("\n") ;

  return ;
}

int egalite_polynome (p_polyf_t p1, p_polyf_t p2)
{
  if(p1==NULL||p2==NULL){
    return 0;
  }
  if(p1->degre==p2->degre){
    for(int i=0;i<p1->degre;i++){
      if(p1->coeff[i]!=p2->coeff[i]){
        return 0;
      }
    }
    return 1;
  }
  return 0;
}

p_polyf_t addition_polynome (p_polyf_t p1, p_polyf_t p2)
{
  p_polyf_t p3 ;
  register unsigned int i ;
  
  p3 = creer_polynome (max (p1->degre, p2->degre));

  for (i = 0 ; i <= min (p1->degre, p2->degre); ++i)
    {
      p3->coeff [i] = p1->coeff [i] + p2->coeff [i] ;
    }

  if (p1->degre > p2->degre)
    {
      for (i = (p2->degre + 1) ; i <= p1->degre; ++i)
	p3->coeff [i] = p1->coeff [i] ;
    }
  else if (p2->degre > p1->degre)
    {
      for (i = (p1->degre + 1) ; i <= p2->degre; ++i)
	p3->coeff [i] = p2->coeff [i] ;
    }
    
  return p3 ;
}

p_polyf_t multiplication_polynome_scalaire (p_polyf_t p, float alpha)
{
  p_polyf_t resultat=creer_polynome(p->degre);
  for(int i=0;i<p->degre;i++){
    resultat->coeff[i]=p->coeff[i]*alpha;
  }

  return resultat;
}

float eval_polynome (p_polyf_t p, float x)
{
  if(p==NULL){
    exit(-1);
  }
  float tmp = 1;
  float result = 0.0;
  for(int i=0;i<p->degre;i++){
    result += tmp*(p->coeff[i]);
    tmp*=x;
  }
  return result;
}

p_polyf_t multiplication_polynomes (p_polyf_t p1, p_polyf_t p2)
{
  p_polyf_t resultat=creer_polynome(p1->degre+p2->degre);
  for(int i=0;i<p1->degre;i++){
    for(int j=0;j<p2->degre;j++){
      resultat->coeff[i*j]+=p1->degre+p2->degre;
    }
  }

  return resultat ;
}

p_polyf_t puissance_polynome (p_polyf_t p, int n)
{
  if(n<=1)return p;
  p_polyf_t res;
  if(n%2==0)res=puissance_polynome(multiplication_polynomes(p,p),n/2);
  else res=multiplication_polynomes(p,(multiplication_polynomes(p,p),n-1/2));

  return res ;
}

p_polyf_t composition_polynome (p_polyf_t p, p_polyf_t q)
{
  p_polyf_t res=creer_polynome(q->degre*p->degre);
  for(int i=0;i<p->degre;i++){
    
  }

  return NULL ;
}



