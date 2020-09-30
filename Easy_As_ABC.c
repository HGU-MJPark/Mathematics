#include <stdio.h>
#include <string.h>

int main(void){
    FILE * fp = fopen("abc_formula", "w") ;
    
    int i,j,n,m;
    int N;
    char s[6]={'_','A','B','C','D','E'};
    char in;
    
    
    for (i = 1 ; i <= 6 ; i++){
        for (j = 1 ; j <= 6 ; j++){
            for(n=0; n<6; n++){
                fprintf(fp,"(declare-const p%d%d%c Bool)\n", i, j, s[n]) ;
            }
        }
    }
    printf("%c",s[0]);
    
    /*printf("Enter the size(n) of the grid. The size should be between 5 and 10.\n");
    scanf("%d",&N);
    getchar();
    fprintf(fp,"(assert (and ");
    for(i=0; i<N; i++){
        scanf("%c", &in);
        if(strcmp(&in,&s[0])!=0){
            fprintf(fp,"(or (and p1%d%c p2%d%c) p1%d%c)",i+1,s[0],i+1,in,i+1,in);
        }
        
    }
    getchar();
    for(i=0; i<N; i++){
        scanf("%c", &in);
        if(strcmp(&in,&s[0])!=0){
            fprintf(fp,"(or (and p6%d%c p5%d%c) p6%d%c)",i+1,s[0],i+1,in,i+1,in);
        }
      
    }
    getchar();
    for(i=0; i<N; i++){
        scanf("%c", &in);
        if(strcmp(&in,&s[0])!=0){
            fprintf(fp,"(or (and p%d1%c p%d2%c) p%d1%c)",i+1,s[0],i+1,in,i+1,in);
        }
      
    }
    getchar();
    for(i=0; i<N; i++){
        scanf("%c", &in);
        if(strcmp(&in,&s[0])!=0){
            fprintf(fp,"(or (and p%d6%c p%d5%c) p%d6%c)",i+1,s[0],i+1,in,i+1,in);
        }
        
    }
    fprintf(fp,"))\n");
     */
    
    
    /*
    fprintf(fp, "(assert (and");
    fprintf(fp, "(or (and p11%c p21%c) p11%c)", s[0],s[1],s[1]);
    fprintf(fp, "(or (and p14%c p24%c) p14%c)", s[0],s[5],s[5]);
    fprintf(fp, "(or (and p31%c p32%c) p31%c)", s[0],s[1],s[1]);
    fprintf(fp, "(or (and p41%c p42%c) p41%c)", s[0],s[4],s[4]);
    fprintf(fp, "(or (and p62%c p52%c) p62%c)", s[0],s[2],s[2]);
    fprintf(fp, "(or (and p63%c p53%c) p63%c)", s[0],s[3],s[3]);
    fprintf(fp, "(or (and p66%c p56%c) p66%c)", s[0],s[1],s[1]);
    fprintf(fp, "(or (and p16%c p15%c) p16%c)", s[0],s[5],s[5]);;;;;;;
    fprintf(fp, "(or (and p36%c p35%c) p36%c)", s[0],s[2],s[2]);
    fprintf(fp, "(or (and p46%c p45%c) p46%c)));\n", s[0],s[5],s[5]);
    */

    
    fprintf(fp,"(assert (and ");
    for(i=1; i<=6; i++){
        fprintf(fp,"(and ");
        for(j=1; j<=6; j++){
            fprintf(fp,"(and ");
            for(n=0; n<5; n++){
                fprintf(fp,"(and ");
                for(m=n+1; m<6; m++){
                    fprintf(fp,"(not (and p%d%d%c p%d%d%c))", i, j, s[n], i, j,s[m]) ;
                }
                fprintf(fp,")");
            }
            fprintf(fp,")");
        }
        fprintf(fp,")");
    }
    fprintf(fp,"))\n");
    
    fprintf(fp,"(assert (and ");
    for(i=1; i<=6; i++){
        fprintf(fp,"(and ");
        for(j=1; j<=6; j++){
            fprintf(fp,"(or ");
            for(n=0; n<6; n++){
                fprintf(fp,"p%d%d%c ", i, j, s[n]);
            }
            fprintf(fp,")");
        }
        fprintf(fp,")");
    }
    fprintf(fp,"))\n");

    fprintf(fp, "(assert (and ");
    for(i=1; i<=6; i++){
        fprintf(fp,"(and ");
        for(n=0; n<6; n++){
            fprintf(fp,"(or ");
            for(j=1; j<=6; j++){
                fprintf(fp,"p%d%d%c ", i, j, s[n]);
            }
            fprintf(fp,")");
        }
        fprintf(fp,")");
    }
    fprintf(fp,"))\n");
    
    fprintf(fp, "(assert (and ");
    for(j=1; j<=6; j++){
        fprintf(fp,"(and ");
        for(n=0; n<6; n++){
            fprintf(fp,"(or ");
            for(i=1; i<=6; i++){
                fprintf(fp,"p%d%d%c ", i, j, s[n]);
            }
            fprintf(fp,")");
        }
        fprintf(fp,")");
    }
    fprintf(fp,"))\n");
    
    fprintf(fp,"(check-sat)\n(get-model)\n") ;

    fclose(fp) ;

    FILE * fin = popen("z3 abc_formula", "r") ;
    char buf[128] ;
    fscanf(fin, "%s %s", buf, buf) ;
    while (!feof(fin)) {
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
        fscanf(fin, "%s", buf) ; printf("%s\n", buf) ;
    }
    pclose(fin);
}
