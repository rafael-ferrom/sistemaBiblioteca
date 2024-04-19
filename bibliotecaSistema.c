#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct		info_livro{
	char	sigla;			// [L]ivre, [E]mprestado, [R]eservado
	int		reg;			
};

typedef struct aluno{
    char	 			RA[7];
    char	 			nome[80];
    int		 			emprestado;		// qtde de livros emprestados - Max=3
	int		 			reservado;		// qtde de livros reservados - Max =1
	struct info_livro	tabela[4];		
}aluno;

struct		info_aluno{
	char		sigla;
	char		RA[7];
	int			dia_ret;			
	int			mes_ret;			
	int			dia_dev;			
	int			mes_dev;			
};

typedef	struct    livro{
	int					reg_livro;				
	char				titulo[80];
	char				autor[80];
	struct info_aluno	status[2];			
} livro;


void aloca_aluno(aluno **palu,int qalu);
void aloca_livro(livro **pliv,int qliv);
int verifica_aluno();
int verifica_livro();
void cadastro_aluno(aluno *palu);
void cadastro_livro(livro *pliv);
void grava_aluno(aluno *palu);
void grava_livro(livro *pliv);
void atualiza_aluno(aluno *palu,int pos);
void atualiza_livro(livro *pliv,int pos);
void troca_reserva(aluno *palu,int reg_livro);
int busca_RA(aluno *palu,char *aux);
int busca_livro(livro *pliv,char *aux);
int busca_livro_reserva(livro *pliv,char *aux);
int busca_livro_deleta(livro *pliv,int reg);
int busca_livro_vago(livro *pliv,char *aux);
int devolve_livro(livro *pliv,char *aux);
void mostra_aluno_total(aluno *palu);
void mostra_aluno_parcial(aluno *palu);
void mostra_livro_total(livro *pliv);
void mostra_livro_status(livro *pliv);
void mostra_livro_titulo(livro *pliv);
void emprestimo(aluno *palu,livro *pliv);
void devolucao(aluno *palu,livro *pliv);
void deleta_livro(aluno *palu,livro *pliv);
void maiuscula(char *aux,int tam);

main()
{
aluno *alu=NULL;
livro *liv=NULL;
int op;

aloca_aluno(&alu,1);
aloca_livro(&liv,1);

do{
   system("cls");                   
   printf("[1]Cadastro Aluno\n[2]Mostra Aluno - Total\n[3]Mostra Aluno - Parcial\n");
   printf("[4]Cadastro Livro\n[5]Mostra Livro - Total\n[6]Mostra Livro - Status\n[7]Mostra Livro - Titulo\n");
   printf("[8]Emprestimo/Reserva\n[9]Devolucao\n[10]Deleta Livro\n[11]Fim\n\nOpcao: ");
   scanf("%i",&op);
   fflush(stdin);
   switch(op)
      {
      case 1: cadastro_aluno(alu);
	  		  break;
	  case 2: mostra_aluno_total(alu);
              break;    
      case 3: mostra_aluno_parcial(alu);
              break;
      case 4: cadastro_livro(liv);
	  		  break;
	  case 5: mostra_livro_total(liv);
              break;    
      case 6: mostra_livro_status(liv);
              break;
	  case 7: mostra_livro_titulo(liv);
              break; 
	  case 8: emprestimo(alu,liv);
              break;   
	  case 9: devolucao(alu,liv);
              break;
	  case 10:deleta_livro(alu,liv);
              break;		  		     
      }//switch
   }while(op!=11);
}//main   

void aloca_aluno(aluno **palu,int qalu)
{
	if((*palu=(aluno*)realloc(*palu,qalu*sizeof(aluno)))==NULL)
	  exit(1);
}//aloca_aluno   

void aloca_livro(livro **pliv,int qliv)
{
	if((*pliv=(livro*)realloc(*pliv,qliv*sizeof(livro)))==NULL)
  	exit(1);
}//aloca_livro

int verifica_aluno()
{
	FILE *falu=NULL;
	long int qalu;
	
	if((falu=fopen("aluno.bin","rb"))==NULL)
	  qalu=0;
	else
	  {
	    fseek(falu,0,2);
	    qalu = ftell(falu)/sizeof(aluno);
	    fclose(falu);
	  }
	return qalu;
}//verifica_aluno

int verifica_livro()
{
	FILE *fliv=NULL;
	long int qliv;
	
	if((fliv=fopen("livro.bin","rb"))==NULL)
	  qliv=0;
	else
	  {
	    fseek(fliv,0,2);
	    qliv = ftell(fliv)/sizeof(livro);
	    fclose(fliv);
	  }
	return qliv;
}//verifica_livro

void cadastro_aluno(aluno *palu)
{ 
	int i,tam;
	printf("\n\nNome: ");
	gets(palu->nome);
	fflush(stdin);
	tam=strlen(palu->nome);
	maiuscula(palu->nome,tam);
	printf("\nRA: ");
	gets(palu->RA);
	fflush(stdin);
	palu->emprestado=0;
	palu->reservado=0;
	for(i=0;i<4;i++)	
	   (palu->tabela+i)->sigla='L';
	grava_aluno(palu);
}//cadastro_aluno

void cadastro_livro(livro *pliv)
{ 
	int qliv,tam,ind=-1;
	
	qliv = verifica_livro();
	ind=busca_livro_vago(pliv,"@");
	if(ind!=-1)  
	  qliv=ind;
	pliv->reg_livro = qliv + 1;
	fflush(stdin);
	printf("\n\nRegistro do livro: %i",pliv->reg_livro);
	printf("\n\nDigite o titulo do livro: ");
	gets(pliv->titulo);
	fflush(stdin);
	tam=strlen(pliv->titulo);
	maiuscula(pliv->titulo,tam);
	printf("\n\nDigite o autor do livro: ");
	gets(pliv->autor);
	fflush(stdin);
	tam=strlen(pliv->autor);
	maiuscula(pliv->autor,tam);
	(pliv->status+0)->sigla='L';   	
	(pliv->status+1)->sigla='L';	
	if(ind==-1)  
	  grava_livro(pliv);   
	else
	  atualiza_livro(pliv,qliv);   
}//cadastro_livro

void grava_aluno(aluno *palu)
{
	FILE *falu=NULL;
	
	if((falu=fopen("aluno.bin","ab"))==NULL)    
	    printf("\nErro ao abrir o arquivo\n");
	else
	    fwrite(palu,sizeof(aluno),1,falu); 
	fclose(falu);
}//grava_aluno

void grava_livro(livro *pliv)
{
	FILE *fliv=NULL;
	
	if((fliv=fopen("livro.bin","ab"))==NULL) 
	    printf("\nErro ao abrir o arquivo\n");
	else
	    fwrite(pliv,sizeof(livro),1,fliv); 
	fclose(fliv);
}//grava_livro*/

void atualiza_aluno(aluno *palu,int pos)
{
	FILE *falu=NULL;
	
	if((falu=fopen("aluno.bin","rb+"))==NULL) 
	    printf("\nErro ao abrir o arquivo\n");
	else
	  {
	  	fseek(falu,pos*sizeof(aluno),0);
	  	fwrite(palu,sizeof(aluno),1,falu); 
	  }//else
	fclose(falu);	
}//atualiza_aluno

void atualiza_livro(livro *pliv,int pos)
{
	FILE *fliv=NULL;
	
	if((fliv=fopen("livro.bin","rb+"))==NULL) 
	    printf("\nErro ao abrir o arquivo\n");
	else
	  {
	  	fseek(fliv,pos*sizeof(livro),0);
	  	fwrite(pliv,sizeof(livro),1,fliv); 
	  }//else
	fclose(fliv);	
}//atualiza_livro

void troca_reserva(aluno *palu,int reg_livro)
{
	FILE *falu=NULL;
	int i,j,qalu,pos;
	
	qalu=verifica_aluno();
	if((falu=fopen("aluno.bin","rb+"))==NULL) 
	    printf("\nErro ao abrir o arquivo\n");
	else
	  {
	  	for(i=0;i<qalu;i++)
	  	  {
	  	    fseek(falu,i*sizeof(aluno),0);
	  	    fread(palu,sizeof(aluno),1,falu);
	  	    for (j=0;j<4;j++)     //varre as tabelas
	  	    	if((palu->tabela+j)->reg==reg_livro)
	  	      	  {
	  	      		(palu->tabela+j)->sigla='E';     
	  	      		(palu->reservado)--;			
	  	      		(palu->emprestado)++;			
	  	      		j=4;			
	  	      		pos=i;			
	  	      	    i=qalu;			
	  	          }//if
	      }//for
	  	fseek(falu,pos*sizeof(aluno),0);
	  	fwrite(palu,sizeof(aluno),1,falu); 
	  }//else
	fclose(falu);	
}//troca_reserva

int busca_RA(aluno *palu,char *aux)
{
	FILE *falu=NULL;
	int i,qalu,achou=-1;
	
	qalu=verifica_aluno();
	if((falu=fopen("aluno.bin","rb"))==NULL)
	  printf("\nArquivo Inexistente");
	else
	  {
	  	for(i=0;i<qalu;i++)
	  	  {
	  	    fseek(falu,i*sizeof(aluno),0);
	  	    fread(palu,sizeof(aluno),1,falu);
	  	    if(strcmp(palu->RA,aux)==0)
	  	      {
	  	      	achou=i;
	  	      	i=qalu;			
	  	      }//if
	      }//for
	    fclose(falu);
	  }//else
	return achou;
}//busca_RA

int busca_livro(livro *pliv,char *aux) 
{
	FILE *fliv=NULL;
	int i,qliv,achou=-1;
	
	qliv=verifica_livro();
	if((fliv=fopen("livro.bin","rb"))==NULL) 
	    printf("\nErro ao abrir o arquivo\n");
	else
	  {
	  	for(i=0;i<qliv;i++)
	  	  {
	  	  	fseek(fliv,i*sizeof(livro),0);
	    	fread(pliv,sizeof(livro),1,fliv);
	  	    if(strcmp(pliv->titulo,aux)==0 && (pliv->status+0)->sigla=='L')    
	    	 {
	       		achou=i;
	       		i=qliv;
	    	 }//if
	      }//for
	    fclose(fliv);    
	  }//else
	return achou;
}//busca_livro

int busca_livro_reserva(livro *pliv,char *aux) 
{
	FILE *fliv=NULL;
	int i,qliv,achou=-1;
	
	qliv=verifica_livro();
	if((fliv=fopen("livro.bin","rb"))==NULL) 
	    printf("\nErro ao abrir o arquivo\n");
	else
	  {
	  	for(i=0;i<qliv;i++)
	  	  {
	  	  	fseek(fliv,i*sizeof(livro),0);
	    	fread(pliv,sizeof(livro),1,fliv);
	  	    if(strcmp(pliv->titulo,aux)==0 && (pliv->status+1)->sigla=='L')			
	  	     {
	       		achou=i;
	       		i=qliv;
	    	 }//if
	      }//for
	    fclose(fliv);    
	  }//else
	return achou;
}//busca_livro_reserva

int busca_livro_deleta(livro *pliv,int reg)
{
	FILE *fliv=NULL;
	int i,qliv,achou;
	
	qliv=verifica_livro();
	if((fliv=fopen("livro.bin","rb"))==NULL) 
	    achou=-1;
	else
	  {
	  	for(i=0;i<qliv;i++)
	  	  {
	  	  	fseek(fliv,i*sizeof(livro),0);
	    	fread(pliv,sizeof(livro),1,fliv);
	  	    if(pliv->reg_livro==reg)			
	  	     {
	       		achou=i;
	       		i=qliv;
	    	 }//if
	      }//for
	    fclose(fliv);    
	  }//else
	return achou;
}//busca_livro_deleta

int busca_livro_vago(livro *pliv,char *aux) 
{
	FILE *fliv=NULL;
	int i,qliv,achou=-1;
	
	qliv=verifica_livro();
	if((fliv=fopen("livro.bin","rb"))==NULL) 
	    printf("\nErro ao abrir o arquivo\n");
	else
	  {
	  	for(i=0;i<qliv;i++)
	  	  {
	  	  	fseek(fliv,i*sizeof(livro),0);
	    	fread(pliv,sizeof(livro),1,fliv);
	  	    if(strcmp(pliv->titulo,aux)==0)    
	    	 {
	       		achou=i;
	       		i=qliv;
	    	 }//if
	      }//for
	    fclose(fliv);    
	  }//else
	return achou;
}//busca_livro_vago

int devolve_livro(livro *pliv,char *aux) 
{
	FILE *fliv=NULL;
	int i,qliv,achou=-1;
	
	qliv=verifica_livro();
	if((fliv=fopen("livro.bin","rb"))==NULL) 
	    printf("\nErro ao abrir o arquivo\n");
	else
	  {
	  	for(i=0;i<qliv;i++)
	  	  {
	  	  	fseek(fliv,i*sizeof(livro),0);
	    	fread(pliv,sizeof(livro),1,fliv);
	  	    if(strcmp(pliv->titulo,aux)==0 && (pliv->status+0)->sigla=='E')    
	    	 {
	       		achou=i;
	       		i=qliv;
	    	 }//if
	      }//for
	    fclose(fliv);    
	  }//else
	return achou;
}//devolve_livro

void mostra_aluno_total(aluno *palu)
{
	FILE *falu=NULL;
	int i,qalu,j;
	
	qalu=verifica_aluno();
	if((falu=fopen("aluno.bin","rb"))==NULL) 
	    printf("\nErro ao abrir o arquivo\n");
	else
	  {
	  	for(i=0;i<qalu;i++)
	  	  {
	  	  	fseek(falu,i*sizeof(aluno),0);
	    	fread(palu,sizeof(aluno),1,falu);
	    	printf("\n\nRA: %s\nNome: %s\nQtde livros emprestados: %i\nQtde de livros reservados: %i\n",palu->RA,palu->nome,palu->emprestado,palu->reservado);
	    	if(palu->emprestado!=0 || palu->reservado!=0)
	    	  for(j=0;j<(palu->emprestado + palu->reservado);j++)
	    	    printf("\nLivro %i:\t%c - %i",j+1,(palu->tabela+j)->sigla,(palu->tabela+j)->reg);
	      }//for
	  	fclose(falu);
	  }//else
	fclose(falu);
	system("pause");
}//mostra_aluno	

void mostra_aluno_parcial(aluno *palu)
{
	char aux[7];
	int j,achou;
	
	printf("\nDigite o RA: ");
	gets(aux);
	fflush(stdin);
	achou = busca_RA(palu,aux);
	if(achou==-1)
	  printf("\nRA invalido\n\n"); 
	else 
	   {
	    printf("\n\nRA: %s\nNome: %s\nQtde livros emprestados: %i\nQtde de livros reservados: %i\n",palu->RA,palu->nome,palu->emprestado,palu->reservado);
		if(palu->emprestado!=0 || palu->reservado!=0)
	      for(j=0;j<(palu->emprestado + palu->reservado);j++)
	        printf("\nLivro %i:\t%c - %i",j+1,(palu->tabela+j)->sigla,(palu->tabela+j)->reg);
	   }//else
	system("pause");
}//mostra_aluno_parcial

void mostra_livro_total(livro *pliv)
{
	FILE *fliv=NULL;
	int i,qliv;
	
	qliv=verifica_livro();
	if((fliv=fopen("livro.bin","rb"))==NULL) 
	    printf("\nErro ao abrir o arquivo\n");
	else
	  {
	  	for(i=0;i<qliv;i++)
	  	  {
	  	  	fseek(fliv,i*sizeof(livro),0);
	    	fread(pliv,sizeof(livro),1,fliv);
	  	    printf("\n\nRegistro: %i\nTitulo: %s\nAutor: %s",pliv->reg_livro,pliv->titulo,pliv->autor);
	  	    printf("\nStatus Emprestimo: %c",(pliv->status+0)->sigla);
	  	    if((pliv->status+0)->sigla=='E')
	  	      printf("\nRA aluno: %s\nRetirada: %i/%i\nDevolucao: %i/%i",(pliv->status+0)->RA,(pliv->status+0)->dia_ret,(pliv->status+0)->mes_ret,(pliv->status+0)->dia_dev,(pliv->status+0)->mes_dev);
	  	    printf("\nStatus Reserva: %c",(pliv->status+1)->sigla);
	  	    if((pliv->status+1)->sigla=='R')
	  	      printf("\nRA aluno: %s\nRetirada: %i/%i\nDevolucao: %i/%i",(pliv->status+1)->RA,(pliv->status+1)->dia_ret,(pliv->status+1)->mes_ret,(pliv->status+1)->dia_dev,(pliv->status+1)->mes_dev);  
	      }//for
	   fclose(fliv);   
	  }//else
	printf("\n\n");
	system("pause");
}//mostra_livro_total

void mostra_livro_status(livro *pliv)
{
	FILE *fliv=NULL;
	char letra;
	int i,qliv,achou=-1;
	
	printf("\nDigite o status: ");
	scanf("%c",&letra);
	fflush(stdin);
	maiuscula(&letra,1);
	qliv=verifica_livro();
	if((fliv=fopen("livro.bin","rb"))==NULL) 
	    printf("\nErro ao abrir o arquivo\n");
	else
	  {
	  	for(i=0;i<qliv;i++)
	  	  {
	  	  	fseek(fliv,i*sizeof(livro),0);
	    	fread(pliv,sizeof(livro),1,fliv);
	    	if((pliv->status+0)->sigla==letra || (pliv->status+1)->sigla==letra)   
	    	  {
	    	   achou=i;
			   printf("\n\nRegistro: %i\nTitulo: %s\nAutor: %s",pliv->reg_livro,pliv->titulo,pliv->autor);
	  	       printf("\nStatus Emprestimo: %c",(pliv->status+0)->sigla);
	  	       if((pliv->status+0)->sigla=='E')
	  	         printf("\nRA aluno: %s\nRetirada: %i/%i\nDevolucao: %i/%i",(pliv->status+0)->RA,(pliv->status+0)->dia_ret,(pliv->status+0)->mes_ret,(pliv->status+0)->dia_dev,(pliv->status+0)->mes_dev);
	  	       printf("\nStatus Reserva: %c",(pliv->status+1)->sigla);
	  	       if((pliv->status+1)->sigla=='R')
	  	         printf("\nRA aluno: %s\nRetirada: %i/%i\nDevolucao: %i/%i",(pliv->status+1)->RA,(pliv->status+1)->dia_ret,(pliv->status+1)->mes_ret,(pliv->status+1)->dia_dev,(pliv->status+1)->mes_dev);  
	  	      }//if
	      }//for
	   fclose(fliv);   
	  }//else
	if(achou==-1)
	  printf("\nNao ha livros com esse status\n\n");
	system("pause");
}//mostra_livro_status

void mostra_livro_titulo(livro *pliv)
{
	FILE *fliv=NULL;
	char aux[80];
	int i,qliv,achou=-1,tam;
	
	printf("\nDigite o Titulo: ");
	gets(aux);
	fflush(stdin);
	tam=strlen(aux);
	maiuscula(aux,tam);
	qliv=verifica_livro();
	if((fliv=fopen("livro.bin","rb"))==NULL) 
	    printf("\nErro ao abrir o arquivo\n");
	else
	  {
	  	for(i=0;i<qliv;i++)
	  	  {
	  	  	fseek(fliv,i*sizeof(livro),0);
	    	fread(pliv,sizeof(livro),1,fliv);
	  	    if(strcmp(pliv->titulo,aux)==0)			
	    	 {
	       	   achou=i;
			   printf("\n\nRegistro: %i\nTitulo: %s\nAutor: %s",pliv->reg_livro,pliv->titulo,pliv->autor);
	  	       printf("\nStatus Emprestimo: %c",(pliv->status+0)->sigla);
	  	       if((pliv->status+0)->sigla=='E')
	  	         printf("\nRA aluno: %s\nRetirada: %i/%i\nDevolucao: %i/%i",(pliv->status+0)->RA,(pliv->status+0)->dia_ret,(pliv->status+0)->mes_ret,(pliv->status+0)->dia_dev,(pliv->status+0)->mes_dev);
	  	       printf("\nStatus Reserva: %c",(pliv->status+1)->sigla);
	  	       if((pliv->status+1)->sigla=='R')
	  	         printf("\nRA aluno: %s\nRetirada: %i/%i\nDevolucao: %i/%i",(pliv->status+1)->RA,(pliv->status+1)->dia_ret,(pliv->status+1)->mes_ret,(pliv->status+1)->dia_dev,(pliv->status+1)->mes_dev);  
	    	 }//if
	      }//for
	    fclose(fliv);    
	  }//else
	if(achou==-1)
	  printf("\nTitulo invalido\n\n");
	system("pause");
}//mostra_livro_parcial

void emprestimo(aluno *palu,livro *pliv)
{
	char aux_RA[7],aux_tit[80];
	int ind,ind1,achou=-1,pos,tab,tam;
	
	printf("\nRA: ");
	gets(aux_RA);
	fflush(stdin);
	achou=busca_RA(palu,aux_RA);
	if(achou==-1)
	  printf("\nRA invalido\n\n");
	else 
	   {
	    printf("\n\nRA: %s\nNome: %s\nQtde livros emprestados: %i\nQtde de livros reservados: %i\n\n",palu->RA,palu->nome,palu->emprestado,palu->reservado);
		if(palu->emprestado>3 && palu->reservado>1)
		  {
	        printf("\nRA não permitido - atingiu o numero de emprestimos/reserva\n\n");
	        system("pause");
	      }//if
	    else    //RA valido
	      {
	      	printf("\nTitulo: ");
			gets(aux_tit);
			fflush(stdin);
			tam=strlen(aux_tit);
			maiuscula(aux_tit,tam);
			ind=busca_livro(pliv,aux_tit);  
			if(ind==-1)
			  {
			  	ind1=busca_livro_reserva(pliv,aux_tit);  
			  	if(ind1==-1)
			  	  printf("\nNao ha livro disponivel");
			  	else
			  	  ind=ind1;
			  }//else
	  		if(ind!=-1)
	  		  {
	  			tab=(palu->emprestado + palu->reservado);    
				printf("\nRA: %s",palu->RA);
	    		printf("\nNome: %s",palu->nome);
	    		if((pliv->status+0)->sigla=='L')  
	  			  {
	  			  	printf("\nLivro sera emprestado - registro %i\n",pliv->reg_livro);
	  			  	pos=0;   //emprestimo
	  			  	(pliv->status+pos)->sigla= 'E';
	  			  	(palu->tabela+tab)->sigla= 'E';
	  			  	(palu->tabela+tab)->reg=pliv->reg_livro;
	  			  	(palu->emprestado)++;  
	  			  	printf("\nDia Retirada: ");
	  				scanf("%i",&(pliv->status+pos)->dia_ret);				
	  				fflush(stdin);
	  				printf("\nMes Retirada: ");
	  				scanf("%i",&(pliv->status+pos)->mes_ret);				
	  				fflush(stdin);
	  			  }//if
	  			else
	  			  {
	  			  	printf("\nLivro sera reservado - registro %i\n",pliv->reg_livro);
					pos=1;   //reserva
	  			  	(pliv->status+pos)->sigla= 'R';	
	  			  	(palu->tabela+tab)->sigla= 'R';
	  			  	(palu->tabela+tab)->reg= pliv->reg_livro;
	  			  	(palu->reservado)++;  
	  			  	(pliv->status+pos)->dia_ret=((pliv->status+0)->dia_dev)+1;  
	  			  	(pliv->status+pos)->mes_ret=(pliv->status+0)->mes_dev;
					printf("\nDia Retirada: %i", (pliv->status+pos)->dia_ret);				
	  				printf("\nMes Retirada: %i", (pliv->status+pos)->mes_ret);				
	  			  }//else
				strcpy((pliv->status+pos)->RA,aux_RA);	
				printf("\nDia Devolucao: ");
	  			scanf("%i",&(pliv->status+pos)->dia_dev);				
	  			fflush(stdin);
	  			printf("\nMes Devolucao: ");
	  			scanf("%i",&(pliv->status+pos)->mes_dev);				
	  			fflush(stdin);
	  			atualiza_livro(pliv,ind);
				atualiza_aluno(palu,achou);
	  	      }//if
	      }//else
	  }//else
	printf("\n\n");
	system("pause");
}//emprestimo

void devolucao(aluno *palu,livro *pliv)
{
	char aux_RA[7],aux_tit[80];
	int i,ind,dia, mes,achou=-1,multa=0,pos,tam,tab;
	
	printf("\nRA: ");
	gets(aux_RA);
	fflush(stdin);
	achou=busca_RA(palu,aux_RA);
	if(achou==-1)
	  printf("\nRA invalido\n\n");
	else 
	   {
	    printf("\nTitulo: ");
		gets(aux_tit);
		fflush(stdin);
		tam=strlen(aux_tit);
		maiuscula(aux_tit,tam);
		printf("\nDia atual: ");
		scanf("%i",&dia);
		fflush(stdin);
		printf("\nMes atual: ");
		scanf("%i",&mes);
		fflush(stdin);
		ind=devolve_livro(pliv,aux_tit);  
		if(ind==-1)
		  printf("\nTitulo invalido ou nao esta emprestado");
		else
		  {
		  	if(strcmp((pliv->status+0)->RA,aux_RA)==0)    
		  	  {
		  	  	for(i=0;i<4;i++)   
				  if((palu->tabela+i)->reg==pliv->reg_livro)
				    {
				     (palu->tabela+i)->sigla='L';
				     (palu->tabela+i)->reg=0;
				     (palu->emprestado)--;
				     tab=i+1;     
				     if((palu->tabela+tab)->sigla=='E' || (palu->tabela+tab)->sigla=='R')  
				       {
				       	(palu->tabela+i)->sigla=(palu->tabela+tab)->sigla;  
				        (palu->tabela+i)->reg=(palu->tabela+tab)->reg;
				        (palu->tabela+tab)->sigla='L';						
				        (palu->tabela+tab)->reg=0;
				       }//if
				     atualiza_aluno(palu,achou);	
				  	}//if
				
		  	  	if(mes<=(pliv->status+0)->mes_dev)      
		  	      if(dia>((pliv->status+0)->dia_dev))		
		  	        {
		  	          multa=(dia-((pliv->status+0)->dia_dev))*3;
		  	          printf("\nMulta de: %i reais\n\n",multa);
		  	        }//if
		  	    
		  		if((pliv->status+1)->sigla=='R')    
				  {
				  	strcpy((pliv->status+0)->RA,(pliv->status+1)->RA);   
				  	(pliv->status+0)->dia_ret=dia;
				  	(pliv->status+0)->mes_ret=mes;
				  	printf("\nO aluno RA: %s - trocou este livro de Reserva para Emprestimo\n", (pliv->status+0)->RA);
				  	printf("\nNOVO Dia Devolucao: ");
	  				scanf("%i",&(pliv->status+0)->dia_dev);				
	  			    fflush(stdin);
	  			    printf("\nNOVO Mes Devolucao: ");
	  			    scanf("%i",&(pliv->status+0)->mes_dev);
	  			    fflush(stdin);
				  	pos=1;
				  	troca_reserva(palu,pliv->reg_livro);
				  }//if
				else		
				  {
				  	pos=0;
				  }//else
				(pliv->status+pos)->sigla='L';	
				strcpy((pliv->status+pos)->RA,"      ");   
				(pliv->status+pos)->dia_ret=0;
				(pliv->status+pos)->mes_ret=0;
				(pliv->status+pos)->dia_dev=0;
				(pliv->status+pos)->mes_dev=0;  
				atualiza_livro(pliv,ind);
	
	  	      }//if
	      }//else
	  }//else
	printf("\n\n");
	system("pause");
}//devolucao

void deleta_livro(aluno *palu,livro *pliv)
{
	char aux_RA[7];
	int i,num_deleta,achou,achou1,tab;
	
	mostra_livro_titulo(pliv);
	printf("\nRegistro do livro a ser deltado: ");
	scanf("%i",&num_deleta);
	fflush(stdin);
	achou=busca_livro_deleta(pliv,num_deleta);
	if(achou==-1)
	  printf("\nRegistro invalido\n\n");
	else
	  {
	  	if((pliv->status+0)->sigla=='E')       
	  	  {
	  	  	strcpy(aux_RA,(pliv->status+0)->RA);     
	  	  	achou1=busca_RA(palu,aux_RA);		  
	  	  	for(i=0;i<4;i++)   
			  if((palu->tabela+i)->reg==pliv->reg_livro)
			    {
			     (palu->tabela+i)->sigla='L';
			     (palu->tabela+i)->reg=0;
			     (palu->emprestado)--;
			     tab=i+1;     
			     if((palu->tabela+tab)->sigla=='E' || (palu->tabela+tab)->sigla=='R')   
			       {
			       	(palu->tabela+i)->sigla=(palu->tabela+tab)->sigla;  
			        (palu->tabela+i)->reg=(palu->tabela+tab)->reg;
			        (palu->tabela+tab)->sigla='L';						
			        (palu->tabela+tab)->reg=0;
			       }//if
				 atualiza_aluno(palu,achou1);
	  	  		}//if
	  	    printf("\nMulta de 150,00 reais\n\n");
	      }//if
	  	if((pliv->status+1)->sigla=='R')       
	  	  {
	  	  	strcpy(aux_RA,(pliv->status+1)->RA);     
	  	  	achou1=busca_RA(palu,aux_RA);		  
	  	  	for(i=0;i<4;i++)    
			  if((palu->tabela+i)->reg==pliv->reg_livro)
			    {
			     (palu->tabela+i)->sigla='L';
			     (palu->tabela+i)->reg=0;
			     (palu->reservado)--;
			     tab=i+1;     
			     if((palu->tabela+tab)->sigla=='E')  
			       {
			       	(palu->tabela+i)->sigla=(palu->tabela+tab)->sigla;  
			        (palu->tabela+i)->reg=(palu->tabela+tab)->reg;
			        (palu->tabela+tab)->sigla='L';						
			        (palu->tabela+tab)->reg=0;
			       }//if
				 atualiza_aluno(palu,achou1);
	  	  		}//if    
	  	  }//if
	  	strcpy(pliv->titulo,"@");        
	  	atualiza_livro(pliv,achou);
	  }//else
	printf("\n\n");
	system("pause");
}//deleta_livro

void maiuscula(char *aux,int tam)
{
	int i;
	for(i=0;i<tam;i++)
	  if(*(aux+i)>='a'&&*(aux+i)<='z')
	    *(aux+i)-=32;
}//maiuscula