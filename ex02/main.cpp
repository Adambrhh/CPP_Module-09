/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:45:54 by abarahho          #+#    #+#             */
/*   Updated: 2025/09/02 12:39:17 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char** av)
{
    if (ac < 2)
    {
        std::cerr << "Error: not enough arguments." << std::endl;
        return (1);
    }
    try
    {
        PmergeMe pmergeMe;
        pmergeMe.run(ac, av);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return (1);
    }
    return (0);
}
