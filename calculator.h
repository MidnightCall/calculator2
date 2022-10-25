/*****************************************************************//**
 * \file   calculator.h
 * \brief  ��������
 *
 * \author praist
 * \date   October 2022
 *********************************************************************/

#ifndef CALCULATOR_H
#define CALCULATOR_H

// �����Ķ���
enum MAXSIZE
{
    STACK_INIT_SIZE = 20, // ջ�ĳ�ʼ�������
    STACKINCREMENT = 10, // ջ����ʱ�򣬶�̬����������ÿ������10��Ԫ�ؿռ�
    MAXBUFFER = 10, // ��󻺳���
    MAX_EXP_LEN = 100 // ���ʽ�Ϊ100
};

template<typename E>
class Calculator
{
public:
    struct sqStack
    {
        E* base; // ָ��ջ��
        E* top; // ָ��ջ��
        int stackSize; // ��ǰջ���������
    };
    Calculator();
    ~Calculator();
    void Push(E e);
    bool Pop(E& e);
    void clearStack();
    int StackLen();

    double Calculation(char Postfix[]); // ��׺���ʽ�ļ���
    bool InfixToPostfix(char Infix[], char Postfix[]); // ��׺���ʽ��Ϊ��׺���ʽ

private:
    sqStack s;

};

#endif // CALCULATOR_H