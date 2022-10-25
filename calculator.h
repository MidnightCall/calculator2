/*****************************************************************//**
 * \file   calculator.h
 * \brief  计算器类
 *
 * \author praist
 * \date   October 2022
 *********************************************************************/

#ifndef CALCULATOR_H
#define CALCULATOR_H

// 常量的定义
enum MAXSIZE
{
    STACK_INIT_SIZE = 20, // 栈的初始最大容量
    STACKINCREMENT = 10, // 栈满的时候，动态增加容量，每次增加10个元素空间
    MAXBUFFER = 10, // 最大缓冲区
    MAX_EXP_LEN = 100 // 表达式最长为100
};

template<typename E>
class Calculator
{
public:
    struct sqStack
    {
        E* base; // 指向栈底
        E* top; // 指向栈顶
        int stackSize; // 当前栈的最大容量
    };
    Calculator();
    ~Calculator();
    void Push(E e);
    bool Pop(E& e);
    void clearStack();
    int StackLen();

    double Calculation(char Postfix[]); // 后缀表达式的计算
    bool InfixToPostfix(char Infix[], char Postfix[]); // 中缀表达式变为后缀表达式

private:
    sqStack s;

};

#endif // CALCULATOR_H