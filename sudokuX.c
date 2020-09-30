#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    FILE * fp = fopen("formula.txt", "w") ;

    int i, j, r, s, n, m;
    int in[9][9];
    int out[9][9];
    char p='?';
    char a[100];
    int num=0;

    for (i = 1 ; i <= 9 ; i++){
        for (j = 1 ; j <= 9 ; j++){
            for(n=1; n<=9; n++){
                fprintf(fp,"(declare-const p%d%d%d Bool)\n", i, j,n) ;
            }
        }
    }
    
    printf("Enter the value of Sudoku-X. If the value is empty, enter ?.\n");
    printf("Enter 'enter' when entering the next line.\n");
    fprintf(fp,"(assert (and ");
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            scanf("%c",&in[i][j]);
            num=in[i][j]-'0'
            if(num<10)
            fprintf(fp,"p%d%d%d ",i+1,j+1,in[i][j]);
            getchar();
            }
    }
    fprintf(fp,"))\n");
    
     
    fprintf(fp,"(assert (and ");
    for(i=1; i<=9; i++){
        fprintf(fp,"(and ");
        for(j=1; j<=9; j++){
            fprintf(fp,"(and ");
            for(n=1; n<=8; n++){
                fprintf(fp,"(and ");
                for(m=n+1; m<=9; m++){
                    fprintf(fp,"(not (and p%d%d%d p%d%d%d))", i, j, n, i, j,m) ;
                }
                fprintf(fp,")");
            }
            fprintf(fp,")");
        }
        fprintf(fp,")");
    }
    fprintf(fp,"))\n");
    
    fprintf(fp,"(assert (and ");
    for(i=1; i<=9; i++){
        fprintf(fp,"(and ");
        for(j=1; j<=9; j++){
            fprintf(fp,"(or ");
            for(n=1; n<=9; n++){
                fprintf(fp,"p%d%d%d ", i, j, n);
            }
            fprintf(fp,")");
        }
        fprintf(fp,")");
    }
    fprintf(fp,"))\n");
    
    fprintf(fp,"(assert (and ");
    for (i=1 ; i<=9 ; i++){
        fprintf(fp,"(and ");
        for (n=1 ; n<=9 ; n++){
            fprintf(fp,"(or ");
            for(j=1; j<=9; j++){
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
            for(i=1; i<=9; i++){
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
                for(i=1; i<=3; i++){
                    fprintf(fp,"(or ");
                    for(j=1; j<=3; j++){
                        fprintf(fp,"p%d%d%d ",3*r+i,3*s+j,n);
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
        for(i=1;i<=9;i++){
                fprintf(fp,"p%d%d%d ",i,i,n);
        }
        fprintf(fp,")");
    }
    fprintf(fp, "))\n");
    
    fprintf(fp,"(assert ");
    fprintf(fp,"(and ");
    for(n=1; n<=9; n++){
        fprintf(fp,"(or ");
        for(i=1;i<=9;i++){
                fprintf(fp,"p%d%d%d ",i,10-i,n);
        }
        fprintf(fp,")");
    }
    fprintf(fp,"))\n");
    
    fprintf(fp,"(check-sat)\n(get-model)\n") ;

    fclose(fp) ;

    FILE * fin = popen("z3 formula.txt", "r") ;
    char buf[128] ;
    char output[128];
    char str[5]= "true)";
    fscanf(fin, "%s %s", buf, buf) ;
    while (!feof(fin)) {
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
                strncpy(output, buf,4);
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
        printf("%s", buf);
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
        fscanf(fin, "%s", buf) ; printf("%s\n", buf) ;
                if(strcmp(buf,str)==0){
                    i=output[1]-'0';
                    j=output[2]-'0';
                    n=output[3]-'0';
                    out[i-1][j-1]=n;
                }
    }
    pclose(fin);
    
    //show output
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            printf("%d ", out[i][j]);
        }
        printf("\n");
    }
}
