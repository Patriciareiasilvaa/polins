
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polinomio.h" 
int divisor; //global
int mdc (int m, int n ){
	int aux;
	if(n > m){
		aux=n;
		n=m;
		m=aux;
	}
	do {
		aux = m % n;
		m=n;
		n=aux;
	}while(aux!=0);
	return m;
}
polin *normaliza(polin *listp){
	int c=listp->coef;
	char v= listp->var;
	int expo=listp->expo;
	listp=listp->next;
	for(;listp!=NULL; listp=listp->next)
		if(v==listp->var && expo==listp->expo)
			c+=listp->coef;

	return newPolin(c,v,expo);
}
polin *setUpNormaliza(polin *listp){
	polin *new,*final=NULL;
	while(listp!=NULL){

		new=normaliza(listp);
		if(new->coef!=0) final=add(final,new);
		listp=removePolin(listp,listp->var,listp->expo);

	}
	return final;
}
void derivar(polin *listp){
	polin *head;
	head=removePolin(listp,'C',0);
	
	for(;listp!=NULL;listp=listp->next){
		listp->coef*=listp->expo;
		listp->expo--;
	}
        
	printPolin(head);

}

void integral(polin *listp,char ordem){
	fracpolin *fraclist=NULL ,*next;
	for(;listp!=NULL;listp=listp->next){
	
		if(listp->var==ordem){

				listp->expo++;
				divisor = mdc(listp->coef , listp->expo);
				if( listp->expo /  divisor == 1){

					next=newFracPolin(listp->coef / divisor, 1, listp->var,listp->expo);
					fraclist=addFrac(fraclist,next);
				}else{

					next=newFracPolin(listp->coef / divisor, listp->expo /divisor, listp->var,listp->expo);
					fraclist=addFrac(fraclist,next);
				}
		}
		else if(listp->var=='C'){
			next=newFracPolin(listp->coef,1,ordem,1);
			fraclist=addFrac(fraclist,next);
		}
		else{
			next=newFracPolin(listp->coef,1,listp->var,listp->expo);
			fraclist=addFrac(fraclist,next);
		}


	}	
	printFracPolin(fraclist,ordem);
}


int main(){
	int n,c,e, adi;
	char v,ordem;
	polin *prox,*final;
	polin *point2;
	scanf("%d",&adi);
	if(adi==2){
		scanf("%d",&n);
		scanf("%d",&c);
    	getchar(); //ignora caracteres brancos
    	scanf("%c%d",&v,&e);
    	point2=newPolin(c,v,e);
    	for(int i = 0;i<n-1;i++) {
    		scanf("%d",&c);
    		getchar();
    		scanf("%c%d",&v,&e);
    		prox=newPolin(c,v,e);
    		point2=add(point2,prox);
    	}
	}
	scanf("%d",&n);
	scanf("%d",&c);
    getchar(); //ignora caracteres brancos
    scanf("%c%d",&v,&e);
    polin *point=newPolin(c,v,e);
    for(int i = 0;i<n-1;i++) {
    	scanf("%d",&c);
    	getchar();
    	scanf("%c%d",&v,&e);
    	prox=newPolin(c,v,e);
    	point=add(point,prox);
    }
    getchar();
    scanf("%c",&ordem);
    puts("Polinomio:");
    printPolin(point);
    if(adi==2){puts("Polinomio 2:"); printPolin(point2); printf("Soma: \n"); final=setUpNormaliza(append(point2,point)); }
    else{
    puts("------------------------\nNormalizado:");
    final=setUpNormaliza(point);   
	}
	polin *final2=setUpNormaliza(final);
 	printPolin(final);
    puts("------------------------\nDerivada:");;
    derivar(final);
    printf("------------------------\nIntegral em ordem a %c:\n",ordem);
    integral(final2,ordem);  
    
    return 0;
}
