#pragma once
#include "Stack.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <QMessageBox>

#define MAX_RESULT_MEMORY 20
#define MAX_EXP_MEMORY 20

using namespace std;

class Calculator {

private:

    Stack<double> m_num; // 数字栈
    Stack<char> m_opr; // 运算符栈
    bool warning_flag = 0;

    // 知识, 得到运算符优先级
    int precedence(const char &s) const;

    // 读取操作数
    double readNum(string::const_iterator & it);
    string readLet(string::const_iterator & it);
    string readExp(string::const_iterator & it);

    // 动作, 使用运算符栈和操作数栈顶的元素进行计算并修改两个栈
    void calculate();

    bool isNum(string::const_iterator &c) const {
    return *c >= '0'&& *c <= '9' || *c == '.';
    }

    bool isLet(string::const_iterator &c) const {
        return *c >= 65 && *c <= 90 || *c >= 97 && *c <= 122;
    }

    bool isBra(string::const_iterator &c) const {
        return *c == 40 || *c == 41 || *c == 91 || *c == 93 || *c == 123 || *c == 125;
    }

    bool isBra_left(string::const_iterator &c) const {
        return *c == 40 || *c == 91 || *c == 123;
    }

    bool isBra_right(string::const_iterator &c) const {
        return *c == 41 || *c == 93 || *c == 125;
    }

public:

    bool isWarning() const {
        return warning_flag;
    }

    bool handleWarning() {
        warning_flag = 0;
        return 1;
    }

    struct MEMORY {
        double RMemory[MAX_RESULT_MEMORY];
        string EMemory[MAX_EXP_MEMORY];
        int DMemory = 0;
    }MEM;

// 无参构造函数
Calculator() { m_opr.push('#'); }

double doIt(const string &exp);
};




























/*
static double pi = std::atan(1.0) * 4;
using namespace std;
class Calculator {
private:
    Stack<double> m_num; // 数字栈
    Stack<string> m_opr; // 运算符栈
    //  得到运算符优先级
    int precedence(const string& s) const;
    // 读取操作数
    double readNum(string::const_iterator& it);
    //  使用运算符栈和操作数栈顶的元素进行计算并修改两个栈
    void calculate();
    bool isNum(string::const_iterator& c) const {
        return *c >= '0' && *c <= '9' || *c == '.';
    }
    bool isWord(string::const_iterator& c) const {
        return *c >= 'a' && *c <= 'z';
    }
    string readword(string::const_iterator& c);
public:
    // 无参构造函数
    Calculator() { m_opr.push("#"); }
    double doIt(const string& eqt);
};
int Calculator::precedence(const string& s) const {
    if (s == "=") 	return 0;
    else if (s == "#")return 1;
    else if (s == "(" ) return 2;
    else if (s == "+" || s == "-") return 3;
    else if (s == "*" || s == "/" || s == "%") return 4;
    else if (s == "sqrt"  || s == "^")return 5;
    else if (s == "sin" || s == "cos" || s == "tan") return 6;
    else if (s == ")")  return 7;
    else if (s == "pi")  return 9;

}
double Calculator::readNum(string::const_iterator& it) {
    string t;
    while (isNum(it))
        t += *it++;//继续扫描
    return stod(t);//返回读取的数据
}
string Calculator::readword(string::const_iterator& it) {
    string t, a;
    t += *it;
    if (t == "+" || t == "-" || t == "*" || t == "/" || t == "(" || t == ")" || t == "=" || t == "#"  || t == "%" || t == "^") {
        ++it;
        return t;
    }
    if (isWord(it)) {
        while (isWord(it))a += *it++;
        if (a == "pi") { m_num.push(pi); }//pi的优先级最高可直接入栈，由于pi的性质和其他字符串的性质不同，所有要单独处理
        return a;
    }
}
void Calculator::calculate() {
    if (m_opr.top() == "+" || m_opr.top() == "-" || m_opr.top() == "*" || m_opr.top() == "/"  || m_opr.top() == "%" || m_opr.top() == "^") {//只有这几个符号对应两个操作数
        double b = m_num.top();
        m_num.pop();
        double a = m_num.top();
        m_num.pop();
        if (m_opr.top() == "+") {
            m_num.push(a + b);
            m_opr.pop();
        }
        else if (m_opr.top() == "-") {
            m_num.push(a - b);
            m_opr.pop();
        }
        else if (m_opr.top() == "*") {
            m_num.push(a * b);
            m_opr.pop();
        }
        else if (m_opr.top() == "/") {
            m_num.push(a / b);//结果压栈
            m_opr.pop();//运算符出栈
        }
        else if (m_opr.top() == "%") {
            int n = a, m = b;
            m_num.push(n % m);
            m_opr.pop();
        }
        else if (m_opr.top() == "^") {
            m_num.push(pow(a, b));
            m_opr.pop();
        }
    }
    else if (m_opr.top() == "sin" || m_opr.top() == "cos" || m_opr.top() == "tan" || m_opr.top() == "sqrt"|| m_opr.top() == "arccos" || m_opr.top() == "arcsin" || m_opr.top() == "arctan") {
        double c = m_num.top();
        m_num.pop();
        if (m_opr.top() == "sin") {
            m_num.push(sin(c));
            m_opr.pop();
        }
        else if (m_opr.top() == "cos") {
            m_num.push(cos(c));
            m_opr.pop();
        }
        else if (m_opr.top() == "tan") {
            m_num.push(tan(c));
            m_opr.pop();
        }
        else if (m_opr.top() == "sqrt") {
            m_num.push(sqrt(c));
            m_opr.pop();
        }
        else if (m_opr.top() == "arcsin") {
            m_num.push(asin(c));
            m_opr.pop();
        }
        else if (m_opr.top() == "arccos") {
            m_num.push(acos(c));
            m_opr.pop();
        }
        else if (m_opr.top() == "arctan") {
            m_num.push(atan(c));
            m_opr.pop();
        }
    }
    else if (m_opr.top() == ")") {
        m_opr.pop();
        while (m_opr.top() != "(")calculate();
        m_opr.pop();
    }
}
double Calculator::doIt(const string& exp) {
    m_num.clear();
    string s;
    for (auto it = exp.begin(); it != exp.end();) {
        if (isNum(it))
            m_num.push(readNum(it));//操作数入栈
        else {
            s = readword(it);//将读到的运算符给对象s
            //s += *it++;
            while (precedence(s) <= precedence(m_opr.top())) {
                if (m_opr.top() == "#")//如果栈顶是#，则执行下一行的break,即计算完毕,跳出当前while循环，如果不是就跳到下一个if
                    break;
                if (s == "(") break;//如果是(,则执行break跳出while循环执行108行的if ,即“(”入栈
                calculate();//如果目前扫描到的运算符的优先级小于栈顶的运算符的优先级，则执行栈顶运算符的计算
            }
            if (s != "=" && s != "pi")//pi在前面已经入栈了所有这里要加一个判断
                m_opr.push(s);//运算符
            //++it;
        }
    }
    return m_num.top();//返回最后结果
}

*/
