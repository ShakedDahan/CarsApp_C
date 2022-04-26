#include <stdio.h>
#include <string.h>
#include <ctype.h>


int checkNumString(char* string)
{
    if(string!= NULL)
    {
        int i;
        for(i=0;i<strlen(string);i++)
        {
            if(isdigit(string[i]) == 0) return 0;
        }
        return 1;
    }
    return 0;
}


int checkIdString(char* string)
{
    if(checkNumString(string))
    {
        if(strlen(string) == 9) return 1;
    }
    return 0;
}


int checkYear(char* string)
{
    if(checkNumString(string))
    {
        if(strlen(string) == 4)
        {
            if(strcmp(string,"1886") >= 0)
            {
                return 1;
            }
        }
    }
    return 0;
}


int hasNumDigits(long num,int k)
{
    if(k >= 0)
    {
        char counter;
        counter = 0;
        while(num != 0)
        {
            num = num/10;
            counter++;
        }
        if(k == counter) return 1;
        else return 0;
    }
    return 0;
}

int getNumDigits(long num)
{
    char counter;
    counter = 0;
    while(num != 0)
    {
        num = num/10;
        counter++;
    }
    return counter;
}

int hasNumDigitsString(char* string,int k)
{
    if(k >=0)
    {
        if(checkNumString(string))
        {
            if(strlen(string) == k) return 1;
        }
    }
    return 0;
}


int checkPhoneNumber(char* string)
{
    if(hasNumDigitsString(string,9) || hasNumDigitsString(string,10))
    {
        if(string[0] == '0')
        {
            if(strlen(string) == 9)
            {
                char second;
                second = string[1];
                if((second == '2') || (second == '3') || (second == '4') || (second == '8') || (second == '9')) return 1;
            }
            else
            {
                if(string[1] == '5') return 1;
            }
        }
    }
    return 0;
}


int isSingleWord(char* string)
{
    if(string != NULL)
    {
        int i;
        i=0;
        while(i<strlen(string))
        {
            if(isspace(string[i])) return 0;
            i++;
        }
        return 1;
    }
    return 0;
}