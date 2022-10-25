/*****************************************************************//**
 * \file   Tools.h
 * \brief  工具类，提供工具函数
 * 
 * \author praist
 * \date   October 2022
 *********************************************************************/
#ifndef TOOLS_H
#define TOOLS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 去除字符串中的空格
void stringIgnoreSpace(char* str);

// 读取字符串的函数
char* s_gets(char* st, int n);

#endif // !__TOOLS_H__
