/*****************************************************************//**
 * \file   main.cpp
 * \brief  测试用的函数
 * 
 * \author praist
 * \date   October 2022
 *********************************************************************/

#include <iostream>
#include "calculator.cpp"
#include "Tools.h"
using namespace std;

int main()
{
    Calculator<double> cal;
    char Infix[MAX_EXP_LEN], Postfix[MAX_EXP_LEN];
    cout << "输入表达式" << endl;
    s_gets(Infix, MAX_EXP_LEN);
    double sum;

    cal.InfixToPostfix(Infix, Postfix);
    sum = cal.Calculation(Postfix);
    cout << "最终计算结果为" << sum << endl;
    return 0;
}