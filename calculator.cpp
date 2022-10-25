/*****************************************************************//**
 * \file   calculator.cpp
 * \brief  计算器类的实现
 *
 * \author praist
 * \date   October 2022
 *********************************************************************/

#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include "Tools.h"

template<typename E>
Calculator<E>::Calculator()
{
    s.base = new E[STACK_INIT_SIZE];// 栈底指向申请空间的首地址
    if (s.base == NULL) {// 空间分配失败，退出
        exit(0);
    }
    s.top = s.base;// top指向栈顶的下一个空间
    s.stackSize = STACK_INIT_SIZE;
}

// 销毁栈，将内存空间释放
template<typename E>
Calculator<E>::~Calculator()
{
    delete[] s.base;
}

// 元素压入栈
template<typename E>
void Calculator<E>::Push(E e)
{
    if (s.top - s.base >= s.stackSize) { // 空间不足时，申请一个新的空间，并拷贝旧的内容到新的空间 
        s.base = (E*)realloc(s.base, (s.stackSize + STACKINCREMENT) * sizeof(E));
        if (s.base == NULL) { // 空间分配失败，退出
            exit(0);
        }
        s.top = s.base + s.stackSize; // 重新设置栈顶
        s.stackSize = s.stackSize + STACKINCREMENT; // 更改当前栈的最大容量
    }
    *(s.top) = e;
    s.top++;
}

// 元素出栈
template<typename E>
bool Calculator<E>::Pop(E& e)
{
    if (s.top == s.base) { // 若为空栈，则出栈失败
        return false;
    }
    e = *(--(s.top));
    return true;
}

// 清空栈，不改变已经赋值的空间
template<typename E>
void Calculator<E>::clearStack()
{
    s.top = s.base;
}

// 计算栈的当前容量（存储的数据量或者元素个数）
template<typename E>
int Calculator<E>::StackLen()
{
    return s.top - s.base;
}

// 由后缀表达式计算表达式的值
template<typename E>
double Calculator<E>::Calculation(char Postfix[])
{
    int i = 0, j;
    char c;
    char num[MAXBUFFER];
    double a = 0, b = 0;

    for (j = 0; Postfix[j] != '\0'; j++)
    {
        while ((Postfix[j] >= 48) && (Postfix[j] <= 57) || Postfix[j] == '.') 
        { // 得到数字
            num[i] = Postfix[j];
            i++;
            num[i] = '\0';
            if (i >= 10)
            {
                printf("出错，输入的数据长度过大!\n");
                return -1;
            }
            j++;
            if ((Postfix[j] == ' '))
            { // 遍历到第一个空格，说明已得到第一个数字
                a = atof(num);
                Push(a);
                i = 0;
            }

        }

        switch (Postfix[j])
        {
        case '+':
            Pop(a);
            if (!Pop(b)) // 处理单目运算符
            {
                Push(a);
                break;
            }
            Pop(b);
            Push(b + a);
            break;
        case '-':
            Pop(a);
            if (!Pop(b))
            {
                Push(-a);
                break;
            }
            Push(b - a);
            break;
        case '*':
            Pop(a);
            Pop(b);
            Push(b * a);
            break;
        case '/':
            Pop(a);
            if (a == 0)
            {
                printf("除数不能为零 ！\n");
                return -1;
            }
            Pop(b);
            Push(b / a);

            break;
        default:
            break;
        }
    }
    Pop(a);
    return a;

}

// 中缀表达式到后缀表达式的转换
template<typename E>
bool Calculator<E>::InfixToPostfix(char Infix[], char Postfix[])
{
    stringIgnoreSpace(Infix);
    Calculator<char> s;
    int i = 0, j = 0;
    char e;

    printf("后缀表达式为：");
    while (Infix[j] != '\0')
    {
        while ((Infix[j] >= '0' && Infix[j] <= '9') || Infix[j] == '.')
        { // 处理数字
            printf("%c", Infix[j]);
            Postfix[i++] = Infix[j];
            j++;
            if ((Infix[j] < '0' || Infix[j] > '9') && Infix[j] != '.')
            {
                Postfix[i++] = ' ';
                printf(" ");
            }
        }

        switch (Infix[j])
        { // 处理运算符

        case ')':
            s.Pop(e); // 找到右括号，直接弹出
            while ('(' != e)
            { // 遍历运算符栈至左括号
                printf("%c ", e);
                // 加入后缀运算数组
                Postfix[i++] = e;
                Postfix[i++] = ' ';
                s.Pop(e);
            }
            break;

        case '+':
        case '-':
            if (0 == s.StackLen()) {
                // 运算符栈为空，直接压入
                s.Push(Infix[j]);
            }
            else
            { // 运算符栈不为空时，判断与栈顶元素优先级
                do
                {
                    s.Pop(e);
                    if ('(' == e)
                    { // 遇到左括号则压入
                        s.Push(e);
                    }
                    else
                    { // 遇到其他符号则弹出并打印
                        printf("%c ", e);
                        Postfix[i++] = e;
                        Postfix[i++] = ' ';
                    }
                } while (s.StackLen() && '(' != e); // 循环终止条件，遇到左括号或全部弹出
                s.Push(Infix[j]);
            }
            break;

        // 以下运算符直接压入
        case '*':
        case '/':
        case '(':
            s.Push(Infix[j]);
            break;

        // 字符串结束，直接跳出循环
        case '\0':
            break;

        // 出现非法字符，返回错误信息
        default:
            printf("\n输入格式错误！\n");
            return -1;
        }

        if ('\0' == Infix[j])
            break;
        j++;
    }

    // 将剩余的栈内运算符加入后缀表达式中
    while (s.StackLen())
    {
        s.Pop(e);
        printf("%c ", e);
        Postfix[i++] = e;
        Postfix[i++] = ' ';
    }
    Postfix[i] = '\0';
    printf("\n");
    return true;
}