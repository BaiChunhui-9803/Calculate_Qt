#include "Calculator.h"
#include <math.h>

using namespace std;

#define pi 3.1415926
#define e 2.7182818

int Calculator::precedence(const char & s) const {

    switch (s) {

        case '=': 	return 0;

        case '#': 	return 1;

        case '+': case '-':	return 3;

        case '*': case '/': case '%':	return 4;

        case '^': 	return 5;

        case '(': case '[':	case '{': return 10;

        case ')': case ']':	case '}': return 2;

        default: return 0;
    }

}

double Calculator::readNum(string::const_iterator &it) {

    string t;

    while (isNum(it))

        t += *it++;

    return stod(t);

}

string Calculator::readLet(string::const_iterator &it) {

    string str;

    while (isLet(it))

        str += *it++;

    return str;

}

string Calculator::readExp(string::const_iterator &it) {

    string str_att;

    int p = 0;

    int q = 0;

    while (p != q || p == 0) {

        if (isBra_left(it)) {

            p++;

        }

        if (isBra_right(it)) {

            q++;

        }

        str_att += *it++;

    }

    if (&str_att != nullptr)
        return str_att;
    else
        return "error";

}


void Calculator::calculate() {
    double b = m_num.top();
    m_num.pop();
    double a = 0;
    if (&m_num.top() != nullptr) {
        a = m_num.top();
        m_num.pop();
    }

    switch (m_opr.top()) {

        case '+': {
            m_num.push(a + b);
            m_opr.pop();
            break;
        }

        case '-': {
            m_num.push(a - b);
            m_opr.pop();
            break;
        }

        case '*': {
            m_num.push(a * b);
            m_opr.pop();
            break;
        }

        case '/': {
            m_num.push(a / b);
            m_opr.pop();
            break;
        }

        case '%': {
            m_num.push(fmod(a, b));
            m_opr.pop();
            break;
        }

        case '^': {
            m_num.push(pow(a,b));
            m_opr.pop();
            break;
        }

    }

}

double Calculator::doIt(const string & exp) {

    Calculator cclt_att;

    m_num.clear();

    for (auto it = exp.begin(); it != exp.end();) {

        if (isNum(it))

            m_num.push(readNum(it));

        else if (isLet(it)) {

            string math_function = readLet(it);

            if (math_function == "sin") {
                if (isBra(it)) {
                    string exp_att = readExp(it);
                    m_num.push(sin(cclt_att.doIt(exp_att)));

                }
            }

            else if (math_function == "cos") {
                if (isBra(it)) {
                    string exp_att = readExp(it);
                    m_num.push(cos(cclt_att.doIt(exp_att)));

                }
            }

            else if (math_function == "tan") {
                if (isBra(it)) {
                    string exp_att = readExp(it);
                    m_num.push(tan(cclt_att.doIt(exp_att)));

                }
            }

            else if (math_function == "arcsin") {
                if (isBra(it)) {
                    string exp_att = readExp(it);
                    m_num.push(asin(cclt_att.doIt(exp_att)));

                }
            }

            else if (math_function == "arccos") {
                if (isBra(it)) {
                    string exp_att = readExp(it);
                    m_num.push(acos(cclt_att.doIt(exp_att)));

                }
            }

            else if (math_function == "arctan") {
                if (isBra(it)) {
                    string exp_att = readExp(it);
                    m_num.push(atan(cclt_att.doIt(exp_att)));

                }
            }

            else if (math_function == "sqrt") {
                if (isBra(it)) {
                    string exp_att = readExp(it);
                    m_num.push(sqrt(cclt_att.doIt(exp_att)));

                }
            }

            else if (math_function == "abs") {
                if (isBra(it)) {
                    string exp_att = readExp(it);
                    m_num.push(fabs(cclt_att.doIt(exp_att)));

                }
            }

            else if (math_function == "ln") {
                if (isBra(it)) {
                    string exp_att = readExp(it);
                    m_num.push(log(cclt_att.doIt(exp_att)));

                }
            }

            else if (math_function == "lg") {
                if (isBra(it)) {
                    string exp_att = readExp(it);
                    m_num.push(log10(cclt_att.doIt(exp_att)));

                }
            }

            else if (math_function == "mem") {
                if (isBra(it)) {
                    int i = 0;
                    string exp_att = readExp(it);
                    i = (int)cclt_att.doIt(exp_att);
                    m_num.push(MEM.RMemory[i - 1]);
                }
            }

            else if (math_function == "del") {
                if (isBra(it)) {
                    int i = 0;
                    string exp_att = readExp(it);
                    i = (int)cclt_att.doIt(exp_att);
                    for (int j = 0; MEM.EMemory[j]!=""; j++) {
                        MEM.EMemory[i - 1] = MEM.EMemory[i];
                        MEM.RMemory[i - 1] = MEM.RMemory[i++];
                    }
                    MEM.DMemory = 1;
                    m_num.push(0);
                }
            }

            else if (math_function == "clc") {
                if (isBra(it)) {
                    string exp_att = readExp(it);
                    for (int j = 0; j < MAX_EXP_MEMORY; j++) {
                        MEM.EMemory[j] = "";
                        MEM.RMemory[j] = 0;
                    }
                    MEM.DMemory = 2;
                    m_num.push(0);
                }
            }

            else if (math_function == "sum") {
                if (isBra(it)) {
                    double sum = 0;
                    string exp_att = readExp(it);
                    for (int i = 0; MEM.EMemory[i] != ""; i++) {
                        sum += MEM.RMemory[i];
                    }

                    m_num.push(sum);
                }
            }

            else if (math_function == "pi") {
                m_num.push(pi);
            }

            else if (math_function == "e") {
                m_num.push(e);
            }

            else {
                QMessageBox::warning(0 ,
                "警告" , "输入了错误的指令",
                QMessageBox::Ok | QMessageBox::Default ,
                QMessageBox::Cancel | QMessageBox::Escape ,  0 );
                m_num.clear();
                m_opr.clear();
                m_opr.push('#');
                warning_flag = 1;
                return 0;
            }
        }

        else {

            while (precedence(*it) <= precedence(m_opr.top()) && precedence(m_opr.top()) != 10) {

                if (m_opr.top() == '#')

                    break;

                calculate();

            }

            if (*it == ')' && m_opr.top() == '(' || *it == ']' && m_opr.top() == '[' || *it == '}' && m_opr.top() == '{') {

                m_opr.pop();

            }

            if (*it != '=' && *it != ')' && *it != ']' && *it != '}') {

                m_opr.push(*it);

            }

            ++it;

        }

    }

    return m_num.top();

}
