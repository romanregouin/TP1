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

  printf ("->");

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

//ne prend pas en compte le cas ou on éléve à la puisssance 0 un polynôme.
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
  p = (p_polyf_creux_t) malloc(sizeof(struct polyf_creux_t));
  if(p==NULL){
    fprintf(stderr, "Erreur mémoire\n");
    exit(-1);
  }
  p->degre = 0;
  p->coeff = 0.0;
  p->suivant = NULL;
  return p;
}

p_polyf_creux_t ajouter_monome_creux(p_polyf_creux_t p, int degre, float coef){
  //on ne peut pas ajouter de coeff 0
  if(coef==0.0){
    return p;
  }
  //p ne contient encore aucun monome
  if((p->coeff==0.0)&&(p->degre==0)){
    p->coeff = coef;
    p->degre = degre;
  //sinon
  }else{
    p_polyf_creux_t courant = p;
    p_polyf_creux_t avant;
    p_polyf_creux_t new = malloc(sizeof(struct polyf_creux_t));
    new->coeff = coef;
    new->degre = degre;
    if(p->degre>degre){
      new->suivant=p;
      return new;
    }
    while((courant!=NULL) && (courant->degre<degre)){
      avant=courant;
      courant=courant->suivant;
    }
    if((courant!=NULL)&&(courant->degre==degre)){
      courant->coeff += coef;
    }else{
      new->suivant = courant;
      avant->suivant = new;
    }
  }
  return p;
}



p_polyf_creux_t lire_polynome_creux_float(char* file_name){
  FILE *f;
  int degre; //sert a rien
  int degre_monome = 0;
  float coef;
  int res;
  int total_coef_nuls = 0;
  p_polyf_creux_t p;

  f = fopen(file_name,"r");
  if(f==NULL){
    fprintf(stderr, "Erreur d'ouverture de %s\n",file_name);
    exit(-1);
  }
  res = fscanf(f,"%d",&degre);
    if(res!=1){
      fprintf(stderr, "Erreur lors de la lecture du degre\n");
      exit(-1);
    }
  p = creer_polynome_creux();
  while(degre_monome<=degre){
    res = fscanf(f,"%f",&coef);
    if(res!=1){
      fprintf(stderr, "Erreur lors de la lecture des coefficients\n");
      exit(-1);
    }
    //Mettre la précision des floats?
    if(coef==0.0){
      total_coef_nuls++;
    }else{
      p=ajouter_monome_creux(p,degre_monome,coef);
    }
    degre_monome++;
  }
  fclose(f);
  return p;
}

void detruire_polynome_creux(p_polyf_creux_t p){
  if(p==NULL)return;
  p_polyf_creux_t tmp1,tmp2=p->suivant;
  free(p);
  while(tmp2!=NULL){
    tmp1=tmp2;
    tmp2=tmp2->suivant;
    free(tmp1);
  }
}

void ecrire_polynome_float_creux (p_polyf_creux_t p)
{
  p_polyf_creux_t courant=p;
  printf ("->");
  if(courant->suivant!=NULL){
    if(courant->degre==0){
        printf ("%f +", p->coeff);
        courant=courant->suivant;
    }else{  
        printf ("%f X^%d + ", courant->coeff ,courant->degre);
        courant=courant->suivant;
    }
  }
  while(courant->suivant!=NULL){ 
    printf (" %f X^%d + ", courant->coeff ,courant->degre);
    courant=courant->suivant;
  }
  if(courant->degre==0){
    printf ("%f\n", p->coeff);
    courant=courant->suivant;
  }else{
    printf ("%f X^%d\n", courant->coeff ,courant->degre);
    courant=courant->suivant;
  }
  return ;
}

int egalite_polynome_creux (p_polyf_creux_t p1, p_polyf_creux_t p2){
  p_polyf_creux_t courant_p1 = p1;
  p_polyf_creux_t courant_p2 = p2;
  if((courant_p1->degre!=courant_p2->degre)||(courant_p1->coeff!=courant_p2->coeff)){
    return 0;
  }
  if((courant_p1->suivant==NULL)&&(courant_p2->suivant==NULL)){
    return 1;
  }
  if(!(courant_p1->suivant!=NULL)&&(courant_p2->suivant!=NULL)){
    return 0;
  }
  while(1){
    courant_p1 = courant_p1->suivant;
    courant_p2 = courant_p2->suivant;
    if((courant_p1->degre!=courant_p2->degre)||(courant_p1->coeff!=courant_p2->coeff)){
      return 0;
    }
    if((courant_p1->suivant==NULL)&&(courant_p2->suivant==NULL)){
      return 1;
    }
    if(!(courant_p1->suivant!=NULL)&&(courant_p2->suivant!=NULL)){
      return 0;
    }
  }
  return -1;
}


p_polyf_creux_t addition_polynome_creux (p_polyf_creux_t p1, p_polyf_creux_t p2)
{
  p_polyf_creux_t p3 ;
  
  p3 = creer_polynome_creux (max (p1->degre, p2->degre));
  p_polyf_creux_t courant1,courant2;

  while(courant1!= NULL || courant2!=NULL)
    {
      if(courant1!= NULL && courant2!=NULL && courant1->degre==courant2->degre){
        p3=ajouter_monome_creux(p3,courant1->degre,courant1->coeff+courant2->coeff);
        courant1=courant1->suivant;
        courant2=courant2->suivant;
      }if(courant1!= NULL && courant1->degre<courant2->degre){
        p3=ajouter_monome_creux(p3,courant1->degre,courant1->coeff);
        courant1=courant1->suivant;
      }else if(courant2!= NULL && courant1->degre>courant2->degre){
        p3=ajouter_monome_creux(p3,courant1->degre,courant2->coeff);
        courant2=courant2->suivant;
      }
    }
  return p3 ;
}

p_polyf_creux_t multiplication_polynome_scalaire_creux (p_polyf_creux_t p, float alpha){
  p_polyf_creux_t res = creer_polynome_creux();
  if(p==NULL){
    return NULL;
  }
  p_polyf_creux_t courant = p;
  while(courant->suivant!=NULL){
    res = ajouter_monome_creux(res,courant->degre,(courant->coeff)*alpha);
    courant = courant->suivant;
  }
  res = ajouter_monome_creux(res,courant->degre,(courant->coeff)*alpha);
  return res;
}

float eval_polynome_creux (p_polyf_creux_t p, float x){
  float res = 0.0;
  if(p==NULL){
    return 0;
  }
  p_polyf_creux_t courant = p;
  float tmp = 1;
  int deg_tmp = 0;
  while(courant->suivant!=NULL){
    while(deg_tmp<courant->degre){
      tmp *= x;
      deg_tmp++;
    }
    res += courant->coeff*tmp;
    courant = courant->suivant;
  }
  while(deg_tmp<courant->degre){
    tmp *= x;
    deg_tmp++;
  }
  res += courant->coeff*tmp;
  return res;
}

p_polyf_creux_t multiplication_polynomes_creux (p_polyf_creux_t p1, p_polyf_creux_t p2){
  if((p1==NULL)||(p2==NULL)){
    return NULL;
  }
  p_polyf_creux_t p = creer_polynome_creux();
  p_polyf_creux_t courant_p1 = p1;
  p_polyf_creux_t courant_p2 = p2;
  while(courant_p1->suivant!=NULL){
    while(courant_p2->suivant!=NULL){
      p = ajouter_monome_creux(p,(courant_p1->degre)+(courant_p2->degre),(courant_p1->coeff)*(courant_p2->coeff));
      courant_p2 = courant_p2->suivant;
    }
    p = ajouter_monome_creux(p,(courant_p1->degre)+(courant_p2->degre),(courant_p1->coeff)*(courant_p2->coeff));
    courant_p1 = courant_p1->suivant;
    courant_p2 = p2;
  }
  while(courant_p2->suivant!=NULL){
    p = ajouter_monome_creux(p,(courant_p1->degre)+(courant_p2->degre),(courant_p1->coeff)*(courant_p2->coeff));
    courant_p2 = courant_p2->suivant;
  }
  p = ajouter_monome_creux(p,(courant_p1->degre)+(courant_p2->degre),(courant_p1->coeff)*(courant_p2->coeff));
  return p;
}

p_polyf_creux_t puissance_polynome_creux (p_polyf_creux_t p, int n){
  if(n<=1){
    return p;
  }
  if(n%2==0){
    return puissance_polynome_creux(multiplication_polynomes_creux(p,p),n/2);
  }else{
    return multiplication_polynomes_creux(p,puissance_polynome_creux(multiplication_polynomes_creux(p,p),(n-1)/2));
  }
}

p_polyf_creux_t composition_polynome_creux (p_polyf_creux_t p, p_polyf_creux_t q){
  return NULL;
}