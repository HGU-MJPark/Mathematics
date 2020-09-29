#include <stdio.h>

int main(void){
    FILE * fp = fopen("abc_formula", "w") ;
    
    int i,j,n,m;
    char s[6]={' ','A','B','C','D','E'};
    
    for (i = 1 ; i <= 6 ; i++){
        for (j = 1 ; j <= 6 ; j++){
            for(n=0; n<6; n++){
                fprintf(fp,"(declare-const p%d%d%d Bool)\n", i, j, s[n]) ;
            }
        }
    }
    
    fprintf(fp, "(assert (and (or p11s[1] p21s[1])(or p14s[5] p24s[5])(or p31s[1] p32s[1])(or p41s[4] p42s[4])(or p62s[2] p52s[2])(or p63s[3] p53s[3])(or p66s[1] p56s[1])(or p16s[5] p15s[5])(or p36s[2] p35s[2])(or p46s[5] p45s[5])))");
    
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
