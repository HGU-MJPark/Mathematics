#include <stdio.h>

int main(void){

  FILE * fp = fopen("formula", "w");

  int i,j,n,r,s,;

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

  for (i=1; i<=9; i++)
      for (j=1; j<=9; j++)
          for (n=1; n<=9; n++)
		fprintf(fp,"(declare-const p%d%d%d Bool)\n", i,j,n);
	

  fprintf(fp,"(assert (and ");
  for (i=1 ; i<=9 ; i++){
      fprintf(fp,"(and ");
      for (n=1 ; n<=9 ; n++){
          fprintf(fp,"(or "); 
	        for(int k=1; k<=9; k++){
		          if(p[i-1][k-1]==n){
			             fprintf(fp,"p%d%d%d ",i,k,n);
			             break;
		           }              
	        }
	        if(k==10){
		          for (j=1 ; j<=9 ; j++){
			             if (p[i-1][j-1]==0)
                  		fprintf(fp,"p%d%d%d ",i,j,n);
             		   else{
                 		  fprintf(fp,"p%d%d%d ",i,j,p[i-1][j-1]);
		     		          if(p[i-1][j-1]==n)
					                 break;
			             }
		          } 
		   
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
          for(int k=1; k<=9; k++){
		          if(p[k-1][j-1]==n){
			             fprintf(fp,"p%d%d%d ",k,j,n);
			             break;
		           }              
	        }
	        if(k==10){
		          for (i=1 ; i<=9 ; i++){
			             if (p[i-1][j-1]==0)
                  		fprintf(fp,"p%d%d%d ",i,j,n);
             		   else{
                 		  fprintf(fp,"p%d%d%d ",i,j,p[i-1][j-1]);
		     		          if(p[i-1][j-1]==n)
					                 break;
			             }
		          } 
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
              for (i=1 ; i<=3 ; i++){
                  fprintf(fp,"(or ");
                  for (j=1 ; j<=3 ; j++){
                    if (p[3*r+i-1][3*s+j-1]==0)
                       fprintf(fp,"p%d%d%d ",3*r+i,3*s+j,n);
                  else{
                        fprintf(fp,"p%d%d%d ",3*r+i,3*s+j,p[3*r+i-1][3*s+j-1]);
			if(p[3*r+i-1][3*s+j-1]==n)
				break;
		  }
                  }
                  fprintf(fp,")");
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
  	for (i=1 ; i<=9 ; i++){
  		j=i;
		if(p[i-1][j-1]==0)
			fprintf(fp,"p%d%d%d ",i,j,n);
		else{
			fprintf(fp,"p%d%d%d ",i,j,p[i-1][j-1]);
			if(p[i-1][j-1]==n)
				break;
		}
		
  	}
	fprintf(fp,")");
  }
  fprintf(fp,"))\n");
      
  
  fprintf(fp,"(assert ");
  fprintf(fp,"(and ");
  for(n=1; n<=9; n++){
  	fprintf(fp,"(or ");
  	for (i=1 ; i<=9 ; i++){
  		j=10-i;
		if(p[i-1][j-1]==0)
			fprintf(fp,"p%d%d%d ",i,j,n);
		else{
			fprintf(fp,"p%d%d%d ",i,j,p[i-1][j-1]);
			if(p[i-1][j-1]==n)
				break;
		}
  	}
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
