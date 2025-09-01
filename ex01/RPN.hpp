/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:48:29 by abarahho          #+#    #+#             */
/*   Updated: 2025/09/01 15:24:47 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack> 
# include <sstream>
# include <stdexcept>

class RPN
{
private:
    std::stack<int> _operands;
public:
    RPN();
    RPN(const RPN&);
    RPN &operator=(const RPN &);
    ~RPN();

    void evaluate(const std::string& expression);
    void apply_operator(char op);
};

#endif