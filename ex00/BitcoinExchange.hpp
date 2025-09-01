/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:46:46 by abarahho          #+#    #+#             */
/*   Updated: 2025/09/01 09:46:53 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>

class BitcoinExchange
{
private:
    std::map<std::string, double> _db;
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange&);
	BitcoinExchange &operator=(const BitcoinExchange &);
    ~BitcoinExchange();

    void    loadDatabase();
    void    processInputFile(const std::string& filename);
    bool    isValidDate(const std::string& date) const;
    void    printResult(const std::string& date, double value);
};

#endif