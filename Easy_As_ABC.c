#include <stdio.h>
#include <string.h>

int main(void){
    FILE * fp = fopen("abc_formula", "w") ;
    
    int i,j,n,m;
    int N;
    char s[]={'A','B','C','D','E'};
    char in;
    char k;
    char p;

    
    printf("Enter the size(n) of the grid. The size should be between 5 and 10.\n");
    scanf("%d",&N);
    
    while(N<5 || N>10){
        printf("Enter the size(n) of the grid. The size should be between 5 and 10.\n");
        scanf("%d",&N);
    }
    
    getchar();
    char out[N][N];
    
    if(N>5){
        s[5]='_';
        for(k=6; k<N; k++){
            s[k]=p;
            p++;
        }
    }
    
    for (i = 1 ; i <= N ; i++){
        for (j = 1 ; j <= N ; j++){
            for(n=0; n<N; n++){
                fprintf(fp,"(declare-const p%d%d%c Bool)\n", i, j, s[n]) ;
            }
        }
    }
        
    fprintf(fp,"(assert (and ");
    if(N>5){
        for(i=0; i<N; i++){
            scanf("%c", &in);
            if(strcmp(&in,&s[5])!=0){
                fprintf(fp,"(or (and p1%d%c p2%d%c) p1%d%c)",i+1,s[5],i+1,in,i+1,in);
            }
        }
    }
    else{
        for(i=0; i<N; i++){
            scanf("%c", &in);
            fprintf(fp,"p1%d%c)",i+1,in);
        }
    }
    getchar();
    if(N>5){
        for(i=0; i<N; i++){
            scanf("%c", &in);
            if(strcmp(&in,&s[5])!=0){
                fprintf(fp,"(or (and p%d%d%c p%d%d%c) p%d%d%c)",N,i+1,s[5],N-1,i+1,in,N,i+1,in);
            }
        }
    }
    else{
        for(i=0; i<N; i++){
            scanf("%c", &in);
            fprintf(fp,"p%d%d%c)",N,i+1,in);
        }
    }
    getchar();
    if(N>5){
        for(i=0; i<N; i++){
            scanf("%c", &in);
            if(strcmp(&in,&s[5])!=0){
                fprintf(fp,"(or (and p%d1%c p%d2%c) p%d1%c)",i+1,s[5],i+1,in,i+1,in);
            }
        }
    }
    else{
        for(i=0; i<N; i++){
            scanf("%c", &in);
            fprintf(fp,"p%d1%c)",i+1,in);
        }
    }
    getchar();
    if(N>5){
        for(i=0; i<N; i++){
            scanf("%c", &in);
           if(strcmp(&in,&s[5])!=0){
                fprintf(fp,"(or (and p%d%d%c p%d%d%c) p%d%d%c)",i+1,N,s[5],i+1,N-1,in,i+1,N,in);
            }
        }
    }
    else{
        for(i=0; i<N; i++){
            scanf("%c", &in);
            fprintf(fp,"p%d1%c)",i+1,N,in);
        }
    }
    fprintf(fp,"))\n");
    
    fprintf(fp,"(assert (and ");
    for(i=1; i<=N; i++){
        fprintf(fp,"(and ");
        for(j=1; j<=N; j++){
            fprintf(fp,"(and ");
            for(n=0; n<N-1; n++){
                fprintf(fp,"(and ");
                for(m=n+1; m<N; m++){
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
    for(i=1; i<=N; i++){
        fprintf(fp,"(and ");
        for(j=1; j<=N; j++){
            fprintf(fp,"(or ");
            for(n=0; n<N; n++){
                fprintf(fp,"p%d%d%c ", i, j, s[n]);
            }
            fprintf(fp,")");
        }
        fprintf(fp,")");
    }
    fprintf(fp,"))\n");

    fprintf(fp, "(assert (and ");
    for(i=1; i<=N; i++){
        fprintf(fp,"(and ");
        for(n=0; n<N; n++){
            fprintf(fp,"(or ");
            for(j=1; j<=N; j++){
                fprintf(fp,"p%d%d%c ", i, j, s[n]);
            }
            fprintf(fp,")");
        }
        fprintf(fp,")");
    }
    fprintf(fp,"))\n");
    
    fprintf(fp, "(assert (and ");
    for(j=1; j<=N; j++){
        fprintf(fp,"(and ");
        for(n=0; n<N; n++){
            fprintf(fp,"(or ");
            for(i=1; i<=N; i++){
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
    char output[128];
    char str[5]= "true)";
    fscanf(fin, "%s %s", buf, buf) ;
    while (!feof(fin)) {
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
                strncpy(output, buf,4);
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
        fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
        fscanf(fin, "%s", buf) ; printf("%s\n", buf) ;
                if(strcmp(buf,str)==0){
                    i=output[1]-'0';
                    j=output[2]-'0';
                    out[i-1][j-1]=output[3];
                }
    }
    pclose(fin);
    
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(out[i][j]>69)
                printf("_ ");
            
            else
                printf("%c ", out[i][j]);
        }
        printf("\n");
    }
        return 0;
}
