/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:47:03 by abarahho          #+#    #+#             */
/*   Updated: 2025/09/02 09:23:08 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
    *this = src;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
    if (this != &src)
        this->_db = src._db;
    return( *this);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase()
{
    std::ifstream file("data.csv");
    if (!file.is_open())
        throw std::runtime_error("Error: could not open data.csv file.");
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        size_t comma = line.find(',');
        if (comma != std::string::npos)
        {
            try {
                std::string date = line.substr(0, comma);
                double rate;
                std::stringstream ss(line.substr(comma + 1));
                ss >> rate;
                _db[date] = rate;
            } 
            catch (const std::exception& e) {
                // ignore invalid lines in the database file
            }
        }
    }
    file.close();
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
    int i;

    i = 0;
    if ((date.length() != 10) || (date[4] != '-' || date[7] != '-'))
        return (false);
    while (i < 10)
    {
        if (i == 4 || i == 7) 
          i++;
        if (!isdigit(date[i])) 
          return (false);
        i++;
    }
    try {
        int year;
        int month;
        int day;
        std::stringstream ss_year(date.substr(0, 4));
        ss_year >> year;
        std::stringstream ss_month(date.substr(5, 2));
        ss_month >> month;
        std::stringstream ss_day(date.substr(8, 2));
        ss_day >> day;
        if (month < 1 || month > 12 || day < 1 || day > 31)
            return (false);
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
            return (false);
        if (month == 2)
        {
            bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if ((isLeap && day > 29) || (!isLeap && day > 28))
                return (false);
        }
    } catch (const std::exception& e) {
        return (false);
    }
    return (true);
}

void BitcoinExchange::printResult(const std::string& date, double value)
{
    std::map<std::string, double>::const_iterator it = _db.lower_bound(date); // find the closest lower date using lower_bound
    if (it != _db.end() && it->first == date)     // if the exact date is found
        std::cout << date << " => " << value << " = " << value * it->second << std::endl;
    else
    {
        if (it == _db.begin())
        {
            std::cout << "Error: date " << date << " is before the first date in the database." << std::endl;
            return;
        }
        --it; // if the date is not found, use the previous one (closest lower date)
        std::cout << date << " => " << value << " = " << value * it->second << std::endl;
    }
}

void BitcoinExchange::processInputFile(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file.");
    std::string line;
    std::getline(file, line); // skip header
    while (std::getline(file, line))
    {
        std::string trimmed_line = line;
        size_t pipe = trimmed_line.find('|');
        if (pipe == std::string::npos)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string date_str = trimmed_line.substr(0, pipe);
        std::string value_str = trimmed_line.substr(pipe + 1);
        // trim whitespace from date and value strings
        date_str.erase(0, date_str.find_first_not_of(" \t\n\r\f\v"));
        date_str.erase(date_str.find_last_not_of(" \t\n\r\f\v") + 1);
        value_str.erase(0, value_str.find_first_not_of(" \t\n\r\f\v"));
        value_str.erase(value_str.find_last_not_of(" \t\n\r\f\v") + 1);
        if (!isValidDate(date_str))
        {
            std::cout << "Error: bad input => " << date_str << std::endl;
            continue;
        }
        try
        {
            double value;
            std::stringstream ss(value_str);
            ss >> value;
            if (ss.fail() || !ss.eof()) // check if conversion failed or if there are extra characters
            {
                std::cout << "Error: bad input => " << line << std::endl;
                continue;
            }
            if (value < 0)
                std::cout << "Error: not a positive number." << std::endl;
            else if (value > 1000)
                std::cout << "Error: too large a number." << std::endl;
            else
                printResult(date_str, value);
        }
        catch (const std::exception& e) {
            std::cout << "Error: bad input => " << line << std::endl;
        }
    }
    file.close();
}