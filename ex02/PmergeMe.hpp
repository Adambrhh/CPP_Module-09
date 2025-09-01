/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:46:01 by abarahho          #+#    #+#             */
/*   Updated: 2025/09/01 15:38:43 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <iomanip>

class PmergeMe
{
private:
    std::vector<int> _vec;
    std::list<int> _lst;

    // functions for the Ford-Johnson algorithm
    void insertionSort(std::vector<int>& vec, int left, int right);
    void mergeInsertSort(std::vector<int>& vec, int left, int right);
    void merge(std::vector<int>& vec, int left, int mid, int right);

    void insertionSort(std::list<int>& lst);
    void mergeInsertSort(std::list<int>& lst);
    
    // helper for list
    std::list<int> merge(std::list<int>& left, std::list<int>& right);

    void parseInput(char** av, int ac);
    void printResults();
public:
    PmergeMe();
    PmergeMe(const PmergeMe&);
    PmergeMe& operator=(const PmergeMe&);
    ~PmergeMe();

    void sort(char** av, int ac);
};

#endif