/*****************************************************************//**
 * \file   main.cpp
 * \brief  �����õĺ���
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
    cout << "������ʽ" << endl;
    s_gets(Infix, MAX_EXP_LEN);
    double sum;

    cal.InfixToPostfix(Infix, Postfix);
    sum = cal.Calculation(Postfix);
    cout << "���ռ�����Ϊ" << sum << endl;
    return 0;
}