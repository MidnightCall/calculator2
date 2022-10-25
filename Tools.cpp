/*****************************************************************//**
 * \file   Tools.cpp
 * \brief  ���ߺ�����ʵ��
 *
 * \author praist
 * \date   October 2022
 *********************************************************************/

#include "Tools.h"

// ȥ���ַ����еĿո�
void stringIgnoreSpace(char* str)
{
    char* str_c = str;
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ')
            str_c[j++] = str[i];
    }
    str_c[j] = '\0';
    str = str_c;
}

// ��ȡ�ַ����ĺ���
char* s_gets(char* st, int n)
{
    char* ret_val;
    char* find;
    ret_val = fgets(st, n, stdin);
    if (ret_val) {
        find = strchr(st, '\n');
        if (find) {
            *find = '\0';
        }
        else {
            while (getchar() != '\n');
        }
    }
    return ret_val;
}
