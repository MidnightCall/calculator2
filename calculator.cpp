/*****************************************************************//**
 * \file   calculator.cpp
 * \brief  ���������ʵ��
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
    s.base = new E[STACK_INIT_SIZE];// ջ��ָ������ռ���׵�ַ
    if (s.base == NULL) {// �ռ����ʧ�ܣ��˳�
        exit(0);
    }
    s.top = s.base;// topָ��ջ������һ���ռ�
    s.stackSize = STACK_INIT_SIZE;
}

// ����ջ�����ڴ�ռ��ͷ�
template<typename E>
Calculator<E>::~Calculator()
{
    delete[] s.base;
}

// Ԫ��ѹ��ջ
template<typename E>
void Calculator<E>::Push(E e)
{
    if (s.top - s.base >= s.stackSize) { // �ռ䲻��ʱ������һ���µĿռ䣬�������ɵ����ݵ��µĿռ� 
        s.base = (E*)realloc(s.base, (s.stackSize + STACKINCREMENT) * sizeof(E));
        if (s.base == NULL) { // �ռ����ʧ�ܣ��˳�
            exit(0);
        }
        s.top = s.base + s.stackSize; // ��������ջ��
        s.stackSize = s.stackSize + STACKINCREMENT; // ���ĵ�ǰջ���������
    }
    *(s.top) = e;
    s.top++;
}

// Ԫ�س�ջ
template<typename E>
bool Calculator<E>::Pop(E& e)
{
    if (s.top == s.base) { // ��Ϊ��ջ�����ջʧ��
        return false;
    }
    e = *(--(s.top));
    return true;
}

// ���ջ�����ı��Ѿ���ֵ�Ŀռ�
template<typename E>
void Calculator<E>::clearStack()
{
    s.top = s.base;
}

// ����ջ�ĵ�ǰ�������洢������������Ԫ�ظ�����
template<typename E>
int Calculator<E>::StackLen()
{
    return s.top - s.base;
}

// �ɺ�׺���ʽ������ʽ��ֵ
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
        { // �õ�����
            num[i] = Postfix[j];
            i++;
            num[i] = '\0';
            if (i >= 10)
            {
                printf("������������ݳ��ȹ���!\n");
                return -1;
            }
            j++;
            if ((Postfix[j] == ' '))
            { // ��������һ���ո�˵���ѵõ���һ������
                a = atof(num);
                Push(a);
                i = 0;
            }

        }

        switch (Postfix[j])
        {
        case '+':
            Pop(a);
            if (!Pop(b)) // ����Ŀ�����
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
                printf("��������Ϊ�� ��\n");
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

// ��׺���ʽ����׺���ʽ��ת��
template<typename E>
bool Calculator<E>::InfixToPostfix(char Infix[], char Postfix[])
{
    stringIgnoreSpace(Infix);
    Calculator<char> s;
    int i = 0, j = 0;
    char e;

    printf("��׺���ʽΪ��");
    while (Infix[j] != '\0')
    {
        while ((Infix[j] >= '0' && Infix[j] <= '9') || Infix[j] == '.')
        { // ��������
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
        { // ���������

        case ')':
            s.Pop(e); // �ҵ������ţ�ֱ�ӵ���
            while ('(' != e)
            { // ���������ջ��������
                printf("%c ", e);
                // �����׺��������
                Postfix[i++] = e;
                Postfix[i++] = ' ';
                s.Pop(e);
            }
            break;

        case '+':
        case '-':
            if (0 == s.StackLen()) {
                // �����ջΪ�գ�ֱ��ѹ��
                s.Push(Infix[j]);
            }
            else
            { // �����ջ��Ϊ��ʱ���ж���ջ��Ԫ�����ȼ�
                do
                {
                    s.Pop(e);
                    if ('(' == e)
                    { // ������������ѹ��
                        s.Push(e);
                    }
                    else
                    { // �������������򵯳�����ӡ
                        printf("%c ", e);
                        Postfix[i++] = e;
                        Postfix[i++] = ' ';
                    }
                } while (s.StackLen() && '(' != e); // ѭ����ֹ���������������Ż�ȫ������
                s.Push(Infix[j]);
            }
            break;

        // ���������ֱ��ѹ��
        case '*':
        case '/':
        case '(':
            s.Push(Infix[j]);
            break;

        // �ַ���������ֱ������ѭ��
        case '\0':
            break;

        // ���ַǷ��ַ������ش�����Ϣ
        default:
            printf("\n�����ʽ����\n");
            return -1;
        }

        if ('\0' == Infix[j])
            break;
        j++;
    }

    // ��ʣ���ջ������������׺���ʽ��
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