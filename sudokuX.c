#include <stdio.h>

int main(void){

  FILE * fp = fopen("formula", "w");

  int i,j,n,r,s,k,l;

  int p[9][9]={
    {0,3,0,8,4,0,0,0,0},
    {0,0,0,9,0,0,0,0,0},
    {0,0,5,0,0,0,0,0,0},
    {2,5,0,0,0,7,4,8,0},
    {0,0,1,0,0,0,0,3,0},
    {0,7,3,0,0,0,0,0,1},
    {0,4,0,0,0,0,0,0,0},
    {0,0,8,6,0,0,9,0,0},
    {9,0,0,0,0,0,0,0,0}
  };

  for (i=1; i<=9; i++){
      for (j=1; j<=9; j++){
          for (n=1; n<=9; n++){
          if(p[i-1][j-1]==n){
              fprintf(fp,"(declare-const p%d%d%d Bool)\n", i,j,n);
              break;
          }
          else
              fprintf(fp,"(declare-const p%d%d%d Bool)\n", i,j,n);
      }
      }
  }


  fprintf(fp,"(assert (and ");
  for (i=1 ; i<=9 ; i++){
      fprintf(fp,"(and ");
      for (n=1 ; n<=9 ; n++){
          fprintf(fp,"(or ");
          for(k=1; k<=9; k++){
              if(p[i-1][k-1]==n){
                  fprintf(fp,"p%d%d%d ",i,k,n);
                  break;
              }
          }
          if(k==10){
              for(j=1; j<=9; j++)
                  fprintf(fp,"p%d%d%d ", i,j,n);
                  }
          fprintf(fp,")");
      }
      fprintf(fp,")");
  }
  fprintf(fp,"))\n");

  fprintf(fp,"(assert (and ");
  for (j=1 ; j<=9 ; j++){
      fprintf(fp,"(and ");
      for (n=1 ; n<=9 ; n++){
          fprintf(fp,"(or ");
          for(k=1; k<=9; k++){
              if(p[k-1][j-1]==n){
                  fprintf(fp,"p%d%d%d ",k,j,n);
                  break;
              }
          }
          if(k==10){
              for(i=1; i<=9; i++)
                  fprintf(fp,"p%d%d%d ", i,j,n);
                  }
              fprintf(fp,")");
      }
      fprintf(fp,")");
  }
  fprintf(fp,"))\n");

  fprintf(fp,"(assert ");
  fprintf(fp,"(and ");
  for (r=0 ; r<=2 ; r++){
      fprintf(fp,"(and ");
      for (s=0 ; s<=2 ; s++){
          fprintf(fp,"(and ");
          for (n=1 ; n<=9 ; n++){
              fprintf(fp,"(or ");
              for(l=1; l<=3; l++){
                  for(k=1; k<=3; k++){
                      if(p[3*r+l-1][3*s+k-1]==n){
                          fprintf(fp,"p%d%d%d) ",3*r+l,3*s+k,n);
                          l=5;
                          break;
                      }
                  }printf("%d%d%d%d%d%d%d%d%d",l,l,l,l,l,l,l,l,l);
              }
              if(l!=5){
                  for(i=1; i<=3; i++){
                      fprintf(fp,"(or ");
                      for(j=1; j<=3; j++)
                          fprintf(fp,"p%d%d%d ", 3*r+i, 3*s+j, n);
                      fprintf(fp,")");
                  }
              }
              fprintf(fp,")");
          }
          fprintf(fp,")");
      }
      fprintf(fp,")");
  }
  fprintf(fp,"))\n");


  fprintf(fp,"(assert ");
  fprintf(fp,"(and ");
  for(n=1; n<=9; n++){
      fprintf(fp,"(or ");
    for(k=1; k<=9; k++){
        if(p[k-1][k-1]==n){
            fprintf(fp,"p%d%d%d ",k,k,n);
            break;
        }
    }
      if(k==10)
          for(i=1;i<=9;i++)
              fprintf(fp,"p%d%d%d ",i,i,n);
      fprintf(fp,")");
  }
    fprintf(fp, "))\n");
  


  fprintf(fp,"(assert ");
  fprintf(fp,"(and ");
  for(n=1; n<=9; n++){
      fprintf(fp,"(or ");
      for(k=1; k<=9; k++){
        if(p[k-1][9-k]==n){
            fprintf(fp,"p%d%d%d ",k,10-k,n);
            break;
        }
    }
      if(k==10)
          for(i=1;i<=9;i++)
              fprintf(fp,"p%d%d%d ",i,10-i,n);
          fprintf(fp,")");
      }
    fprintf(fp,"))\n");
  
  


  fprintf(fp,"(check-sat)\n(get-model)\n") ;

  fclose(fp);

  FILE * fin = popen("z3 formula", "r") ;
    char buf[128] ;
    fscanf(fin, "%s %s", buf, buf) ;
    while (!feof(fin)) {
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
        fscanf(fin, "%s", buf) ; printf("%s\n", buf) ;
    }
    pclose(fin) ;


}
