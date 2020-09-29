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
    
    fprintf(fp, "(assert (and (or p11'A' p21'A')(or p14'E' p24s'E')(or p31'A' p32'A')(or p41'D' p42'D')(or p62'B' p52'B')(or p63'C' p53'C')(or p66'A' p56'A')(or p16'E' p15'E')(or p36'B' p35'B')(or p46'E' p45'E')))");
    
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
