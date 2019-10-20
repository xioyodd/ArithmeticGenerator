#ifndef CALCULATOR_H
#define CALCULATOR_H

//括号不匹配抛出具体异常



#pragma once
#include<string>
#include<stack>
#include<cctype>
#include<sstream>
#include<cstddef>
#include<stdexcept>

namespace calculator
{

    class error : public std::runtime_error
    {
    public:
        error(const std::string& expr, const std::string& message)
            :std::runtime_error(message),
            expr_(expr)
        {}

        std::string expression() const
        {
            return expr_;
        }
    private:
        std::string expr_;
    };


    template<typename T>
    class ExpressionParser
    {
    public:
        T eval(const std::string& expr)
        {
            T result = 0;
            index_ = 0;
            expr_ = expr;
            try
            {
                result = parseExpr();
                if (!isEnd())
                    unexpected();
            }
            catch (const calculator::error&)
            {
                while (!stack_.empty())
                    stack_.pop();
                throw;
            }
            return result;
        }

    private:
        enum
        {
            OPERATOR_NULL,
            OPERATOR_ADD,
            OPERATOR_SUB,
            OPERATOR_MUL,
            OPERATOR_DIV,
            OPERATOR_MOD
        };

        struct Operator
        {
            int op;
            int precedence;
            int associativity;
            //左结合 用 'L'
            Operator(int opr, int prec, int assoc) :
                op(opr),
                precedence(prec),
                associativity(assoc)
            {}
        };

        struct OperatorValue
        {
            Operator op;
            T value;
            OperatorValue(const Operator& opr, T val) :
                op(opr),
                value(val)
            {}
            int getPrecedence() const
            {
                return op.precedence;
            }
            bool isNull() const
            {
                return op.op == OPERATOR_NULL;
            }
        };

        int index_;
        std::string expr_;
        std::stack<OperatorValue> stack_;

        void unexpected() const
        {
            std::ostringstream msg;
            msg << "Syntax error: unexpected token \""
                << expr_.substr(index_, expr_.size() - index_)
                << "\" at index "
                << index_;
            throw calculator::error(expr_, msg.str());
        }

        bool isEnd() const
        {
            return index_ >= (int)expr_.size();
        }
        char getCharacter() const
        {
            if (!isEnd())
                return expr_[index_];
            return 0;
        }

        void eatSpaces()
        {
            while (std::isspace(getCharacter()))// from ctype.h
                index_++;
        }

        Operator parseOp()
        {
            eatSpaces();
            switch(getCharacter())
            {
            case '+':
                index_++;
                return Operator(OPERATOR_ADD, 10, 'L');//+ 的优先级为10 左结合
            case '-':
                index_++;
                return Operator(OPERATOR_SUB, 10, 'L');
            case '*':
                index_++;
                return Operator(OPERATOR_MUL, 20, 'L');
            case '/':
                index_++;
                return Operator(OPERATOR_DIV, 20, 'L');
            case '%':
                index_++;
                return Operator(OPERATOR_MOD, 20, 'L');
            default:
                return Operator(OPERATOR_NULL, 0, 'L');
            }
        }

        T getDigit()
        {
            char c = getCharacter();
            if(c>='0' && c <= '9')
                return  c - '0';
            return 10;
        }

        T parseT()
        {
            T value = 0;
            for (T i; (i = getDigit()) <= 9; index_++)
                value = value * 10 + i;
            return value;
        }

        T parseValue()
        {
            T val = 0;
            eatSpaces();
            switch (getCharacter())
            {
            case '0':case '1':case '2':case '3':case '4':
            case '5':case '6':case '7':case '8':case '9':
                val = parseT();break;
            case '(' :
                index_++;
                //递归
                eatSpaces();
                val = parseExpr();
                eatSpaces();
                if (getCharacter() != ')')
                {
                    if (!isEnd())
                        unexpected();
                    throw calculator::error(expr_, "Syntax error: ')' expected at end of expression");
                }
                index_++; break;
            case '-':
                index_++;
                val = parseValue() * (-1);break;
            /*case '+':
                index_++;
                val = parseValue();break;*/
            default:
                if (!isEnd())
                    unexpected();
                throw calculator::error(expr_, "Syntax error: value expected at end of expression");
            }
            return val;
        }

        T parseExpr()
        {
            stack_.push(OperatorValue(Operator(OPERATOR_NULL, 0, 'L'), 0));
            //取一个数
            T value = parseValue();

            while (!stack_.empty())
            {
                //取一个符号
                Operator op(parseOp());
                //当前符号优先级比较低
                while (op.precedence < stack_.top().getPrecedence() ||
                    (op.precedence == stack_.top().getPrecedence() && op.associativity == 'L'))
                {
                    //全部计算完
                    if (stack_.top().isNull())
                    {
                        stack_.pop();
                        return value;
                    }

                    //计算优先级高的
                    value = calculate(stack_.top().value, value, stack_.top().op);
                    stack_.pop();
                }

                stack_.push(OperatorValue(op, value));

                value = parseValue();
            }
            return 0;
        }

        T checkZero(T value) const
        {
            if (value == 0)
            {
                std::string divOperators("/%");
                std::size_t division = expr_.find_last_of(divOperators, index_ - 2);
                std::ostringstream msg;
                msg << "Parser error: division by 0";
                if (division != std::string::npos)
                    msg << " (error token is \""
                        << expr_.substr(division, expr_.size() - division)
                        << "\")";
                throw calculator::error(expr_, msg.str());
            }
            return value;
        }

        T calculate(T v1, T v2, const Operator& op) const
        {
            switch (op.op)
            {
            case OPERATOR_ADD: return v1 + v2;
            case OPERATOR_SUB: return v1 - v2;
            case OPERATOR_MUL: return v1 * v2;
            case OPERATOR_DIV: return v1 / checkZero(v2);
            case OPERATOR_MOD: return v1 % checkZero(v2);
            default:	return 0;
            }
        }
    };

    template<typename T>
    inline T eval(const std::string& expression)
    {
        ExpressionParser<T> parser;
        return parser.eval(expression);
    }
}

#endif // CALCULATOR_H
