/*****************************************************************//**
 * \file   Tools.cpp
 * \brief  工具函数的实现
 *
 * \author praist
 * \date   October 2022
 *********************************************************************/

#include "Tools.h"

// 去除字符串中的空格
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

// 读取字符串的函数
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
