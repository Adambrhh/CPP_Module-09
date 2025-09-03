/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:46:01 by abarahho          #+#    #+#             */
/*   Updated: 2025/09/02 14:39:42 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <ctime>

class PmergeMe
{
private:
    template <typename T>
    void mergeInsertSort(T& sequence);
    template <typename T>
    typename T::iterator binarySearch(typename T::iterator first, typename T::iterator last, int value);
    template <typename T>
    void sortAndMeasure(T& numbers, const std::string& containerName);
    template <typename T>
    void printSequence(const T& sequence);
    template <typename T>
    void _divideAndConquer(T& sequence, T& mainChain, T& pendElements, int& odd_value, bool& has_odd);
    template <typename T>
    void _mergePending(T& mainChain, T& pendElements, int odd_value, bool has_odd);
    std::vector<int> _getJacobsthalSequence();
public:
    PmergeMe();
    PmergeMe(const PmergeMe&);
    PmergeMe& operator=(const PmergeMe&);
    ~PmergeMe();

    void run(int ac, char** av);
};

#endif