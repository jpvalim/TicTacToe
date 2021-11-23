/* JOGO DA VELHA - ANALISE DE ALGORITIMOS - CEUNSP
 IMPLEMENTAÇÃO DO CÓDIGO DE: JEFFERSON PRADO VALIM 
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<ctype.h>
#include<string.h>

int velha[3][3];
char jog[10];
int a,b=-1;
FILE *arq;

int espera();
void maniparquivo(int parametro);
void pcxpc();
void jogxpc();
void jogada(int linha, int coluna, int jogador);
void jogajog(char *jog);
int jogapc();
int fecha(int linha, int flag);
int ataca();
int defende();
int verifica();

void imprime()
{
  int i,j;
  system("cls");
printf("  0    1    2 \n\n");

  for(i=0;i<3;i++)
  {
    for (j=0;j<3;j++)
    {
      if(velha[i][j]==-1) printf("  %c  ",' ');
      if(velha[i][j]==0) printf("  %c  ",'O');
      if(velha[i][j]==1) printf("  %c  ",'X');
      
      if(j==2){
        printf(" %d",i);
        printf("\n\n\n");
      }
    }
  }
}

void inicializa()
{
  int i,j;
  for(i=0;i<3;i++)
  {
    for (j=0;j<3;j++)
    {
      velha[i][j]=-1;
    }
  }
}

int escolha()
{
    int escolha;
    system("cls");
    printf("\n\nEntre com a opcao: \n");
    printf("\n1- Jogador X PC\n");
    printf("\n2- PC X PC\n");
    printf("\n3- Sair\n");
    scanf("%d",&escolha);
    return escolha;
}

void inicio()
{
    
    printf("**************BEM VINDO AO JOGO DA VELHA***************");
    getch();
    printf("\n\n\n\n\n\n\n                  JPVALIM\n\n            All rights reserved.\n");
    getch();
}

int main()
{
 int opcao;
 
 inicio();
 opcao=escolha();
 
  do{  
    switch (opcao)
    {
        case 1:
            jogxpc();
            break;
        case 2:
            pcxpc();
            break;
        case 3:
            break;   
        default:
            printf("Opcao Errada!\n");
            opcao=escolha();
            break;
    }
  }while(opcao!=1 && opcao!=2 && opcao!=3);
 
}
        
void jogxpc()
{
   char m;
    system("cls");
    printf("Entre com seu nome: ");
    scanf("%s",&jog);
  
    system("cls"); 
    
    printf("%s",jog);
    //sleep(1000);
    printf("  Versus  ");
    //sleep(1000);
    printf("PC\n\n");
    printf("Devo comecar? s/n\n");
    scanf(" %c",&m);
    if(m=='s'){

      inicializa();
      //system("cls");
      imprime();
      printf("\n\n");
      printf("Eu serei o 'X' \n\n");
      system("pause");
      do{      
        b=verifica();
        printf("pc vai jogar\n");
        system("pause");
        if (!jogapc())b=2;
        b=verifica();
        if(b!=-1) break;
        jogajog(jog);
        if(a==-1) jogajog(jog);
        b=verifica();
     }while(b==-1);
  }
  else{

      inicializa();
      //system("cls");
      imprime();
      printf("\n\n");
      printf("Eu serei o 'X' \n\n");
      system("pause");
      do{      
        b=verifica();
        jogajog(jog);
        if(a==-1) jogajog(jog);
        b=verifica();
        if(b!=-1) break;
        printf("pc vai jogar\n");
        system("pause");
        if (!jogapc())b=2;
        b=verifica();
     }while(b==-1);  
  }

    if(b==1){
       printf("\n\n\n\nEU GANHEI!!!!!");
       system("pause");
  }
  else{
      if(b==2){
        printf("\n\n\n\n\nEMPATE!!!!!");
        system("pause");
      } 
      else{
          if(b==0){ 
            printf("\n\n\n\n\n%s GANHOU!!!!!",jog);
            system("pause");
          }
      }
  }
}

void pcxpc(){
  
    char m;
    system("cls");
    printf("PC X PC\n\n");

    printf("Devo comecar? s/n\n");
    scanf(" %c",&m);
   printf("Eu serei o 'X' \n\n");
    system("pause"); 

    if(m=='s') {

      inicializa();
    
      imprime();
      maniparquivo(1);//escreve no arquivo
        
      do{      
        b=verifica();
        if(b!=-1) break;
        printf("pc vai jogar\n");
        system("pause");
      
        if (!jogapc()) b=2;
          b=verifica();   
        if(b!=-1) break;   
          maniparquivo(1);//escreve no arquivo

        while(espera()){
          printf("Esperando jogada do outro pc\n");  
          system("pause");
        }
        maniparquivo(0);//lê o arquivo
        imprime();
    }while(b==-1);
  }
  else
  {
    inicializa();
    imprime();        
    while(espera()){
      printf("Esperando jogada do outro pc\n");  
      system("pause");
    }
    do{      
      maniparquivo(0);
      imprime();
      b=verifica();
      if(b!=-1) break;
        printf("pc vai jogar\n");
        system("pause");
      
      if (!jogapc()) b=2;
        b=verifica();   
      if(b!=-1) break;   
        maniparquivo(1);//escreve no arquivo

      while(espera()){
        printf("Esperando jogada do outro pc\n");  
        system("pause");
      }
      
   }while(b==-1);
    
  }
   if(b==1){
       printf("\n\n\n\nEU GANHEI!!!!!");
       system("pause");
   }
   else{
       if(b==2){
       printf("\n\n\n\n\nEMPATE!!!!!");
       system("pause");
      } 
      else{
          if(b==0){ 
            printf("\n\n\n\n\nPERDI!!!!!");
            system("pause");
          }
      }
  }  
}

int espera()
{
  arq = fopen("velha.txt","r");
  int i,j,h;
  char c;

  for(i=0;i<3;i++)
  {
    c=getc(arq);
    for(j=0;j<3;j++)
    {
      if(velha[i][j]==1 && c=='X')
          h=1;
       else
          if(velha[i][j]==0 && c=='O')
            h=1;
          else
              if(velha[i][j]==-1 && c=='_')
                h=1;
              else
                h=0;
      c=getc(arq);
      if(h==0) return h;

      }
  }

  fclose(arq);

  return h;//se h== 0 quer dizer que o arquivo foi alterado
}

void maniparquivo(int parametro)//parametro 1 para mover o velha para o arquivo 0 para copiar do arquivo para o velha
{
  int i,j;
  char c;

  if(parametro==1){
    arq = fopen("velha.txt","w");
    for(i=0;i<3;i++)
    {
      for(j=0;j<3;j++)
      {
        if(velha[i][j]==0)
        {
          fprintf(arq,"%c",'O');
        }
        else
        {
          if(velha[i][j]==1)
          {
            fprintf(arq,"%c",'X');
          }
          else
          {
            fprintf(arq,"%c",'_');
          }
        }
        if(j==2) fprintf(arq,"\n");
      }
    }
  } 
  else{
      arq = fopen("velha.txt","r");
      c=getc(arq);
      
        for(i=0;i<3;i++)
        {
          for(j=0;j<3;j++)
          {
            
            if(c==10) c=getc(arq);
            if(c=='X')
            {
              velha[i][j]=1;
            }
            else
              if(c=='O'){
                velha[i][j]=0;
              }
              else{
                velha[i][j]=-1;
              }
              c=getc(arq);
          }
        }
      } 

fclose(arq);

}

int verifica()
{
 int i,j,cont=0, conth1=0,conth2=0,contv1=0,contv2=0,contdd1=0,contdd2=0,contde1=0,contde2=0;

//HORIZONTAL
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(velha[i][j]==0)conth1++;
      if(velha[i][j]==1) conth2++;

      
    }
    if(conth1>2 || conth2>2) break;
    conth1=0;
    conth2=0;
  }

//VERTICAL

  for(j=0;j<3;j++)
  {
    for(i=0;i<3;i++)
    {
      if(velha[i][j]==0)contv1++;
      if(velha[i][j]==1)contv2++;
    }
    if(contv1>2 || contv2>2) break;
    contv1=0;
    contv2=0;
  }

//DIAGONAL DIREITA

  for(i=0;i<3;i++)
  {

      if(velha[i][i]==0)contdd1++;
      if(velha[i][i]==1)contdd2++;
      if(contdd1>2 || contdd2>2) break;
  }

//DIAGONAL ESQUERDA
j=2;

  for(i=0;i<3;i++)
  {
    
    if(velha[i][j]==0)contde1++;
    if(velha[i][j]==1)contde2++;

    j--;
    if(contde1>2 || contde2>2) break;
  }

    if ( conth1>2 || contv1>2|| contdd1>2 || contde1>2) return 0;
    if (conth2>2 || contv2>2 ||  contdd2>2 || contde2>2) return 1;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(velha[i][j]==0 || velha[i][j]==1)cont++;

    }
  }

  if(cont==9) return 2;

  return -1;
}



int defende()
{
 int i,j,cont;
 //HORIZONTAL
cont=0;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(j>2){
        cont=0;
       }
      if(velha[i][j]==0) cont++;
      
      if(cont==2){ 
        if(fecha(i,0)) 

        return 1;
      }
    }
    
    cont=0;
  }

//VERTICAL
cont=0;
  for(j=0;j<3;j++)
  {
    for(i=0;i<3;i++)
    {
      if(i>2){
        cont=0;
      }
      if(velha[i][j]==0) cont++;
      if(cont==2){ 
        if(fecha(j,1)) 

          return 1;
      }
    }

    cont=0;
  }

//DIAGONAL DIREITA
cont=0;
  for(i=0;i<3;i++)
  {
      if(i>2){
        cont=0;
      }
      if(velha[i][i]==0) cont++;
      if(cont==2){
        if(fecha(i,2))
          return 1; 
      }
  }

//DIAGONAL ESQUERDA
j=2;
cont=0;
  for(i=0;i<3;i++)
  {
    
    if(velha[i][j]==0) cont++;
    if(cont==2){
      if(fecha(j,3)) 
        return 1;
      }
    j--;

  }
  return 0;
}

int ataca()
{
 int i,j,cont;
 //HORIZONTAL
cont=0;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(j>2){
        cont=0;
       }
      if(velha[i][j]==1) cont++;

    }
    if(cont==2){ 
      if(fecha(i,0)) 
        return 1;
    }
    cont=0;
  }

//VERTICAL
cont=0;
  for(j=0;j<3;j++)
  {
    for(i=0;i<3;i++)
    {
      if(i>2){
        cont=0;
      }
      if(velha[i][j]==1) cont++;
    }
    if(cont==2){ 
      if(fecha(j,1)) 
        return 1;
    }
    cont=0;
  }

//DIAGONAL DIREITA
cont=0;
  for(i=0;i<3;i++)
  {
      if(i>2){
        cont=0;
      }
      if(velha[i][i]==1) cont++;
      if(cont==2){
        if(fecha(i,2))
          return 1; 
      }
  }

//DIAGONAL ESQUERDA
j=2;
cont=0;
  for(i=0;i<3;i++)
  {
    
    if(velha[i][j]==1) cont++;
    if(cont==2){
      if(fecha(j,3)) 
        return 1;
      }
    j--;

  }
  return 0;
}

int jogapc()
{
  int i=0,j=0;


  if(!ataca())
  {
    if(!defende())
    {
        if(velha[0][0]!=1 && velha[0][0]!=0 )
          jogada(0,0,1);
        else
          if(velha[0][2]!=1 && velha[0][2]!=0 )
            jogada(0,2,1);
          else
            if(velha[2][0]!=1 && velha[2][0]!=0 )
              jogada(2,0,1);
            else
              if(velha[2][2]!=1 && velha[2][2]!=0 )
                jogada(2,2,1);  
              else return 0;
    }
  }
//  printf("%d",i);system("pause");
  //printf("%d",j);system("pause");
  return 1;
}

int fecha(int linha, int flag)
{

  int j=0;
  if(flag==0)//horizontal
  {
    while(velha[linha][j]!=-1)
    {
      if(j==2)return 0;
      j++;
    }
    jogada(linha,j,1);
  }
  else 
  {

    if(flag==1){  //vertical
      while(velha[j][linha]!=-1)
      {
        if(j==2)return 0;
        j++;
      }
      jogada(j,linha,1);
    }
    else
    {
      if(flag==2)//fecha diagonal direita
      {
        while(velha[j][j]!=-1)
        {
          if(j==2)return 0;
          j++;
        }
        jogada(j,j,1);
      }
      else
      {//fecha diagonal esquerda
        int i=0;j=2;
        while(velha[i][j]!=-1)
          {
            if(i==2)return 0;          
            j--;
            i++;
          }
          jogada(i,j,1);
      }
    }
  }
 return 1;
}


void jogajog(char *jog)
{
    int linha;
    int coluna;
    printf("%s entre com a linha: ",jog);
    scanf("%d",&linha);
    printf("\n");
    printf("%s entre com a coluna: ",jog);
    scanf("%d",&coluna);
    jogada(linha,coluna,0);
}

void jogada(int linha, int coluna, int jogador)
{
  if(jogador==0){//pessoa
    if((velha[linha][coluna]!= 0 && velha[linha][coluna] != 1 )|| (linha>2 && coluna>2)){
      velha[linha][coluna]=0;
      jogador=1;
      a=1;
      imprime();
      
    }
    else{
      printf("Coordenada ja utilizada ou inexistente\n");
      a=-1;
    }
  }
  else{
    velha[linha][coluna]=1;
    jogador=0;
    a=1;
    imprime();
  }
  
}



