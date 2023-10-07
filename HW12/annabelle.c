#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define TEXT 51
#define Character 30

int check_anagram(char word1[],char word2[])
{
    int arr1[Character] = {0};  
    int arr2[Character] = {0};  
    int n = 0;  
    if (strlen(word1) != strlen(word2))  
        return 0;
    for ( n = 0; word1[n] && word2[n]; n++){
        arr1[word1[n]-97]++;  
        arr2[word2[n]-97]++;  
    }
    for (n = 0; n < Character; n++)  
    {  
        if (arr1[n] != arr2[n])  
            return 0;  
    }  
    return 1;      
}

int main(){
    int m,n,i,j;
    scanf("%d %d", &m, &n);
    char **arr = calloc(m,sizeof(char*));
    char *word = NULL;
    for (i = 0 ; i < m ; ++i){
        arr[i] = malloc(TEXT*sizeof(char));
        scanf("%50s", arr[i]);
    }
    for (i = 0 ; i < n ; i++){
        word = malloc(TEXT*sizeof(char));
        scanf("%50s", word);
        for (j = 0 ; j < m ; j++){
            if (check_anagram(word,arr[j]) == 1){
                printf("%s ",arr[j]);
            }
        }
        printf("\n");
    }
    for(int i = 0; i < m; i++){
        free(arr[i]);
    }
    free(arr);
    free(word);
    return 0;
}