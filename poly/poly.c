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
    for(int i=0;i<=p1->degre;i++){
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
  for(int i=0;i<=p->degre;i++){
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
  for(int i=0;i<=p->degre;i++){
    result += tmp*(p->coeff[i]);
    tmp*=x;
  }
  return result;
}

p_polyf_t multiplication_polynomes (p_polyf_t p1, p_polyf_t p2)
{
  p_polyf_t resultat=creer_polynome(p1->degre+p2->degre);
  init_polynome(resultat,0);
  for(int i=0;i<=p1->degre;i++){
    for(int j=0;j<=p2->degre;j++){
      resultat->coeff[i+j]+=p1->coeff[i]*p2->coeff[j];
    }
  }

  return resultat ;
}

p_polyf_t puissance_polynome (p_polyf_t p, int n)
{
  if(n<=1)return p;
  p_polyf_t res;
  if(n%2==0)res=puissance_polynome(multiplication_polynomes(p,p),n/2);
  else res=multiplication_polynomes(p,puissance_polynome(multiplication_polynomes(p,p),(n-1)/2));

  return res ;
}

p_polyf_t composition_polynome (p_polyf_t p, p_polyf_t q)
{
  p_polyf_t tmp;
  tmp = creer_polynome(0);
  init_polynome(tmp,1);
  p_polyf_t res=creer_polynome(q->degre*p->degre);

  init_polynome(res,0);
  for(int i=0;i<=p->degre;i++){
    for(int j=0;j<=tmp->degre;j++){
      res->coeff[j]+=p->coeff[i]*(tmp->coeff[j]);
    }
    tmp=multiplication_polynomes(tmp,q);

  }
  return res;
}




//============================Polynome Creux ==================================



p_polyf_creux_t creer_polynome_creux(){
  p_polyf_creux_t p;
  p = (p_polyf_creux_t) malloc(sizeof(polyf_creux_t));
  if(p==NULL){
    fprintf(stderr, "Erreur mémoire\n");
    exit(-1);
  }
  p->degre = 0;
  p->coeff = 0.0;
  p->suivant = NULL;
  return p;
}

p_polyf_creux_t lire_polynome_creux_float(char* file_name){
  FILE *f;
  int degre;
  float coef;
  int res;
  int total_coef_nuls = 0;
  p_polyf_creux_t p;

  f = fopen(file_name,"r");
  if(f==NULL){
    fprintf(stderr, "Erreur d'ouverture de %s\n",file_name);
    exit(-1);
  }
  p = creer_polynome_creux();
  while(res==1){
    res = fscanf(f,"%d",&degre);
    if(res!=1){
      fprintf(stderr, "Erreur lors de la lecture du degre\n");
      exit(-1);
    }
    res = fscanf(f,"%f",&coef);
    if(res!=1){
      fprintf(stderr, "Erreur lors de la lecture des coefficients\n");
      exit(-1);
    }
    //Mettre la précision des floats?
    if(coef==0.0){
      total_coef_nuls++;
    }else{
<<<<<<< Updated upstream
      p=ajouter_monome(p,degre,coef);
=======
      polyf_creux_t* added = (polyf_creux_t*)malloc(sizeof(polyf_creux_t));
      added->coeff = coef;
      added->degre = degre;
      last->suivant = added;
      last = last->suivant;
>>>>>>> Stashed changes
    }
  }
  fclose(f);
  return p;
}





void detruire_polynome(p_polyf_creux_t p){
  if(p==NULL)return;
  p_polyf_creux_t tmp1,tmp2=p->suivant;
  free(p);
  while(tmp2!=NULL){
    tmp1=tmp2;
    tmp2=tmp2->suivant;
    free(tmp1);
  }
}




p_polyf_creux_t ajouter_monome(p_polyf_creux_t p, int degre, float coef){
  //p ne contient encore aucun monome
  if(p->coeff==0.0){
    p->coeff = coef;
    p->degre = degre;
  //sinon
  }else{
    polyf_creux_t* courant = p;
    polyf_creux_t* avant;
    polyf_creux_t* new = (polyf_creux_t*)malloc(sizeof(polyf_creux_t));
    new->coeff = coef;
    new->degre = degre;
    if(p->degre>degre){
      new->suivant=p;
      return new;
    }
    while(courant!=NULL && courant->degre<degre){
      avant=courant;
      courant=courant->suivant;
    }
    new->suivant = courant;
    avant->suivant = new;
  }
  return p;
}


void ecrire_polynome_float (p_polyf_creux_t p)
{
  p_polyf_creux_t courant=p;
  if(p->degre==0){
    printf ("%f +", p->coeff) ;
    courant=courant->suivant;
  }
  while(courant->suivant!=NULL)
    {  
      printf (" %f X^%d ", courant->coeff ,courant->degre) ;
      courant=courant->suivant;
    }
  printf ("\n") ;
  return ;
}




p_polyf_creux_t addition_polynome (p_polyf_creux_t p1, p_polyf_creux_t p2)
{
  p_polyf_creux_t p3 ;
  register unsigned int i ;
  
  p3 = creer_polynome (max (p1->degre, p2->degre));
  p_polyf_creux_t courant1,courant2;

  while(courant1!= NULL && courant2!=NULL)
    {
      if(courant1->degre==courant2->degre){
        p3=ajouter_monome(p3,courant1->degre,courant1->coeff+courant2->coeff);
        courant1=courant1->suivant;
        courant2=courant2->suivant;
      }if(courant1->degre<courant2->degre){
        p3=ajouter_monome(p3,courant1->degre,courant1->coeff);
        courant1=courant1->suivant;
      }else{
        p3=ajouter_monome(p3,courant1->degre,courant2->coeff);
        courant2=courant2->suivant;
      }
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