#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>

char *replace(char *s,char *s1,char *s2){
    size_t slen=strlen(s),s1len=strlen(s1),s2len=strlen(s2);
    size_t resultlen=slen+1;//空字符
    char *result=(char *)malloc(resultlen*sizeof(char));
    if(!result)
        return NULL;
    char *src=s,*dst=result;//src short for sRecord,dst short for destination
    int replaced=0;
    //printf("这里没问题");
    while(*src){
        if(strlen(src) >= s1len && strncmp(src,s1,s1len)==0){
            if(!replaced){
                replaced=1;
                size_t newlen=slen+(s2len-s1len)*(src-s);//src-s代表从s（开头）到src的字符数（距离）
                if(newlen>=100)
                    newlen=100;
                else
                    result=(char *)realloc(result,newlen+1);
                if(!result)
                    return NULL;
            }
            strncpy(dst,s2,s2len);
            dst+=s2len;
            src+=s1len;
        }else{
            *dst++=*src++;//没替换的部分照常赋给result，赋值完自增进行从下一个字符开始的比较
        }
    }
    *dst='\0';
    if(replaced&&strlen(result)>100){
        result[100]='\0';
    }
    return result;
}

int main(){
    char s[101],s1[51],s2[51];
    scanf("%100s%50s%50s",s,s1,s2);
    char *result=replace(s,s1,s2);
    printf("%s",result);
    free(result);
    return 0;
}