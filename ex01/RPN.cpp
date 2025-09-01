/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* RPN.cpp                                            :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/09/01 10:20:03 by abarahho          #+#    #+#             */
/* Updated: 2025/09/01 10:20:04 by abarahho         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& src)
{
    *this = src;
}

RPN &RPN::operator=(const RPN &src)
{
    if (this != &src)
    {
        std::stack<int> temp = src._operands;
        while (!this->_operands.empty())
            this->_operands.pop();
        while (!temp.empty())
        {
            this->_operands.push(temp.top());
            temp.pop();
        }
    }
    return (*this);
}

RPN::~RPN() {}

void RPN::apply_operator(char op)
{
    if (_operands.size() < 2)
        throw std::runtime_error("Error: not enough operands for operator.");
    int b = _operands.top();
    _operands.pop();
    int a = _operands.top();
    _operands.pop();
    switch (op)
    {
        case '+':
            _operands.push(a + b);
            break;
        case '-':
            _operands.push(a - b);
            break;
        case '*':
            _operands.push(a * b);
            break;
        case '/':
            if (b == 0)
                throw std::runtime_error("Error: division by zero.");
            _operands.push(a / b);
            break;
        default:
            throw std::runtime_error("Error: unknown operator.");
    }
}

void RPN::evaluate(const std::string& expression)
{
    std::string token;
    std::stringstream ss(expression);

    while (ss >> token)
    {
        if (token.length() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/'))
        {
            try {
                apply_operator(token[0]);
            } catch (const std::exception& e) {
                throw;
            }
        }
        else
        {
            int number;
            std::stringstream conv(token);
            if (!(conv >> number) || !conv.eof() || number >= 10 || number < 0)
                throw std::runtime_error("Error: invalid token.");
            _operands.push(number);
        }
    }
    if (_operands.size() != 1)
        throw std::runtime_error("Error: invalid expression.");
    std::cout << _operands.top() << std::endl;
}