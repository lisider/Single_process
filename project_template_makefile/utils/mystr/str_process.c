#include <stdio.h>

#if 0
char * Reverse(char *s)
{
    char temp;
    char *p = s; 
    char *q = s;
 
    while (*p != '\0')
    {
        p ++;
    }
    q --;
    while (p > q)
    {
        temp = *p;
        *q ++ = *p;
        *q -- = temp;
    }
 
    return s;
}
 
#endif
char* my_itoa(int nval)
{
    static char cBuff[100] = {0};
    int i = 0;
    int nTempVal = nval;
 
    if (nval < 0)
    {
        nval = -1 * nval;
    }
 
    do
    {
        cBuff[i ++] = (nval % 10)  + '0';
        nval = nval / 10;
 
    }while (nval > 0);
 
    if (nTempVal < 0)
    {
        cBuff[i ++] = '-';
    }
    cBuff[i] = '\0';
 
    return cBuff;
}
