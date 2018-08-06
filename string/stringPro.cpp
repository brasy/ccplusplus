#include <string.h>
#include <stdio.h>

char *strcat(char *str1, const char *str2)
{
    char *p = str1;
    assert((str1 != NULL) && (str2 != NULL));
    while(*str1!='\0')str1++;
    while(*str1++=*str2++);
    return p;
}

int strcmp(const char *str1, const char *str2)
{
    assert((str1 != NULL) && (str2 != NULL));
    while(*str1 && *str2 && (*str1==*str2)){
        str1++; str2++;
    }
    return *str1 -*str2;
}

char *strcpy(char *str1, const char *str2)
{
    char *p=str1;
    assert((str1 != NULL) && (str2 != NULL));
    while(*str1++=*str2++);
    return p;
}

char *StrStr(const char *string, const char *substring)
{
    int i, j ,temp;
    assert((string != NULL) && (substring != NULL));
    for (i = 0; string[i] != '\0'; i++){
        temp =i; j=0;
        while(string[i++] == substring[j++]){
            if(substring[j] == '\0')return (char*)&string[temp];
        }
        i=temp;
    }
    return NULL;
}

int atoi(char *str)
{
    int sum=0, sign=1;
    char *p = str;
    assert(str != NULL);
    if(*p == " " || *p == '\t')p++;
    if(*p == "-") sign = -1;
    if (*p == "-" || *p == "+")p++;
    while(*p>='0' && *p <='9'){
        sum = sum*10 + *p-'0';
        p++;
    }
    return sign*sum;
}

void itoa(int num, char str[])
{
    int i=0, j=0;
    char temp[10];
    if(num<0)num=-num;
    do{
        temp[i++] = num%10 + '0';
        num/=10;
    }while(num>0);
    if(sign<0) temp[i++]='-';
    temp[i]='\0';
    i--;
    while(i>=0){
        str[j] = temp[i];
        j++; i--;
    }
    str[j]='\0';
}
