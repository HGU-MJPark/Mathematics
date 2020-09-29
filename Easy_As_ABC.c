#include <stdio.h>

int main(void){
    FILE * fp = fopen("abc_formula", "w") ;
    
    int i,j,n,m;
    char s[6]={' ','A','B','C','D','E'};
    
    for (i = 1 ; i <= 6 ; i++){
        for (j = 1 ; j <= 6 ; j++){
            for(n=0; n<6; n++){
                fprintf(fp,"(declare-const p%d%d%c Bool)\n", i, j, s[n]) ;
            }
        }
    }
    
    fprintf(fp, "(assert (and");
    fprintf(fp, "(or p11%c p21%c)", s[1],s[1]);
    fprintf(fp, "(or p14%c p24%c)", s[5],s[5]);
    fprintf(fp, "(or p31%c p32%c)", s[1],s[1]);
    fprintf(fp, "(or p41%c p42%c)", s[4],s[4]);
    fprintf(fp, "(or p62%c p52%c)", s[2],s[2]);
    fprintf(fp, "(or p63%c p53%c)", s[3],s[3]);
    fprintf(fp, "(or p66%c p56%c)", s[1],s[1]);
    fprintf(fp, "(or p16%c p15%c)", s[5],s[5]);
    fprintf(fp, "(or p36%c p35%c)", s[2],s[2]);
    fprintf(fp, "(or p46%c p45%c)));\n", s[5],s[5]);
    

    
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
            for(n=1; n<=5; n++){
                fprintf(fp,"p%d%d%d ", i, j, s[n]);
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
