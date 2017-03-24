#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polinomio.h"

polin *newPolin(int c, char v, int e)
{
	polin *newp;
	newp = (polin*) malloc(sizeof(polin));
	newp->coef=c;
	newp-> var = v;
	newp->expo=e;
	newp->next = NULL;
	return newp;

}
fracpolin *newFracPolin(int num, int denom, char v, int e)
{
	fracpolin *newp;
	newp = (fracpolin*) malloc(sizeof(fracpolin));
	newp->numerador=num;
	newp->denominador=denom;
	newp-> var = v;
	newp->expo=e;
	newp->next = NULL;
	return newp;

}
polin *add(polin *listp, polin *newp) {
	newp->next=listp;
	return newp;
}
fracpolin *addFrac(fracpolin *listp, fracpolin *newp) {
	newp->next=listp;
	return newp;
}
polin *append (polin *list1, polin *list2) {
	polin *temp;	
	temp=list1;
	while(temp->next!=NULL) temp=temp->next;
	temp->next=list2;
	
	return list1;
}
polin *removePolin(polin *listp, char v, int e){
	polin *temp;
	if(listp==NULL) return NULL;
	if( v==listp->var  && e==listp->expo) {  temp=listp->next; return removePolin(temp,v,e); }
	listp->next=removePolin(listp->next,v,e);
	return listp;
}
void printPolin(polin *listp){
	for(;listp!=NULL;listp=listp->next){
			if(listp->expo==1) printf("%d%c", listp->coef,listp->var);
			else if(listp->expo ==0 && listp->coef==0 && listp->var=='c') printf("%c" , listp->var);
			else if(listp->expo ==0)printf("%d", listp->coef);
			else printf("%d%c^%d", listp->coef, listp->var,listp->expo);
		if(listp->next!=NULL) printf(" + ");
		else printf("\n");
	}
	
}
void printFracPolin(fracpolin *listp,char ordem){
	for(;listp!=NULL;listp=listp->next){
		if(listp->var!=ordem)
		{
				if(listp->expo==1) printf("%d%c%c",listp->numerador,listp->var,ordem );
				else { printf("%d%c^%d%c",listp->numerador,listp->var, listp->expo,ordem );}
		}else{
				if(listp->denominador==0) printf("%c^%d",listp->var, listp->expo);
				else if(listp->denominador==1 && listp->expo==1) printf("%d%c",listp->numerador,listp->var); 
				else if(listp->denominador==1 && listp->expo!=1) printf("%d%c^%d",listp->numerador,listp->var,listp->expo); 
				else {printf("(%d/%d)%c^%d",listp->numerador,listp->denominador,listp->var, listp->expo );}
		}
		if(listp->next!=NULL) printf(" + ");
		else printf("\n");
	}	
}
