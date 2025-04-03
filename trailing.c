#include<stdio.h>
#include<string.h>
#include<stdbool.h>

bool isbracket(char c){
    if(c=='(' || c==')') return 1;
    return 0;
}

typedef struct 
{
    char left;
    char right[50];
}prod;

bool is_bracket(char c) {
    return (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']');
}

int main(){

    prod p[50];
    int n;
    printf("Enter number of production:");
    scanf("%d",&n);
    int count=0;

    for (int i = 0; i < n; i++) {
        char input[500];
        scanf("%s", input);
        char left = input[0];
        char *arrowpos = strstr(input, "->");
        char *rhs = arrowpos + 2;
        char temp[50];
        int pos = 0;

        int len = strlen(rhs);
        for (int j = 0; j <= len; j++) {
            if (rhs[j] == '|' || rhs[j] == '\0') {
                temp[pos] = '\0';
                p[count].left = left;
                strcpy(p[count].right, temp);
                pos = 0;
                count++;
            } else {
                temp[pos++] = rhs[j];
            }
        }
    }

    bool null[50]={false};

    bool change=true;
    do{
        change=false;
        for(int i=0;i<count;i++){
            int l=p[i].left-'A';
            if(null[l]) continue;

            if(strcmp(p[i].right,"e")==0){
                null[l]=true;
                change=true;
                continue;
            }

            bool isallnull=true;
            for(int j=0;j<strlen(p[i].right);j++){
                int c=p[i].right[j];
                if(c>='A' && c<='Z'){
                    if(!null[c-'A']){
                        isallnull=false;
                        break;
                    }
                }else{
                    isallnull=false;
                    break;
                }
            }
            if(isallnull){
                null[l]=true;
                change=true;
            }
        }

    }while(change);

    char trail[26][50]={{0}};

    do{
        change=false;
        for(int i=0;i<count;i++){
            int l=p[i].left-'A';

            if(strcmp(p[i].right,"e")==0){
                continue;
            }
            

            for(int j=strlen(p[i].right)-1;j>=0;j--){
                char c=p[i].right[j];

                if (is_bracket(c) && (j == strlen(p[i].right) - 1)) {
                    if (!strchr(trail[l], c)) {
                        int len = strlen(trail[l]);
                        trail[l][len] = c;
                        trail[l][len + 1] = '\0';
                        change = true;
                    }
                    break; 
                }

                if(!(c>='A' && c<='Z')){
                    if(!strchr(trail[l],c)){
                        int len=strlen(trail[l]);
                        trail[l][len]=c;
                        trail[l][len+1]='\0';
                        change=true;
                    }
                }else{

                    int idx=c-'A';
                    for(int k=0;k<strlen(trail[idx]);k++){
                        if(!strchr(trail[l],trail[idx][k])){
                            int len=strlen(trail[l]);
                            trail[l][len]=trail[idx][k];
                            trail[l][len+1]='\0';
                            change=true;
                        }
                    }
                    if(!null[idx]) break;
                }
            }
        }

    }while(change);

    char printed[26]={false};

    for(int i=0;i<count;i++){
        printed[p[i].left-'A']=true;
    }

    for(int i=0;i<26;i++){
        if(printed[i]){
            printf("TRAI(%c)={",i+'A');
            for (int j = 0; j < strlen(trail[i]); j++) {
                printf("%c ", trail[i][j]);
            }
            printf("}\n");
        }
    }
}
