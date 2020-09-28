#include <stdio.h>

int main(void){
    FILE * fp = fopen("formula", "w") ;
    
    int i,j,n,m;
    char s[6]={' ','A','B','C','D','E'};
    
    fprintf(fp, "(assert (and (or p11A p21A)(or p14E p24E)(or p31A p32A)(or p41D p42D)(or p62B p52B)(or p63C p53C)(or p66A p56A)(or p16E p15E)(or p36B p35B)(or p46E p45E)))");
    
    fprintf(fp,"(assert (and ");
    for(i=1; i<=6; i++){
        fprintf(fp,"(and ");
        for(j=1; j<=6; j++){
            fprintf(fp,"(and ");
            for(n=0; n<=4; n++){
                fprintf(fp,"(and ");
                for(m=n+1; m<=5; m++){
                    fprintf(fp,"(not (and p%d%d%c p%d%d%c))", i, j, s[n], i, j,s[m]) ;
                }
                fprintf(fp,")");
            }
            fprintf(fp,")");
        }
        fprintf(fp,")");
    }
    fprintf(fp,"))\n");
    
    for(i=1; i<=6; i++){
        for(j=1; j<=6; j++){
            for(n=0; n<6; n++){
                fprintf(fp, "(declare-const p%d%d%c Bool)\n", i, j, s[n]);
            }
        }
    }
    
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
    pclose(fin);
}


