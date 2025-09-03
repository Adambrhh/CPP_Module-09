/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:13:13 by abarahho          #+#    #+#             */
/*   Updated: 2025/09/02 15:42:48 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& copy)
{
    (void)copy;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& src)
{
    if (this != &src)
    {
        // no members to copy for now, but good practice.
    }
    return (*this);
}

PmergeMe::~PmergeMe() {}

void PmergeMe::run(int ac, char** av)
{
    int i;
    int num;
    size_t j;
    std::vector<int> numbers_vec;
    std::list<int> numbers_list;
    
    i = 1;
    while (i < ac)
    {
        j = 0;
        std::string arg = av[i];
        if (arg.length() > 0 && arg[0] == '-')
            throw std::invalid_argument("Error: Negative number.");
        while (j < arg.length())
        {
            if (!isdigit(arg[j]))
                throw std::invalid_argument("Error: Non-numeric argument.");
            j++;
        }
        num = std::atoi(av[i]);
        numbers_vec.push_back(num);
        numbers_list.push_back(num);
        i++;
    }
    std::cout << "Before: ";
    printSequence(numbers_vec);
    std::cout << std::endl;
    sortAndMeasure(numbers_vec, "std::vector");
    sortAndMeasure(numbers_list, "std::list");
}

template <typename T>
void PmergeMe::sortAndMeasure(T& numbers, const std::string& containerName)
{
    clock_t start = clock();
    mergeInsertSort(numbers);
    clock_t end = clock();
    std::cout << "After: ";
    printSequence(numbers);
    std::cout << std::endl;
    double elapsed = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1e6;
    std::cout.precision(10);
    std::cout << "Time to process a range of " << numbers.size() << " elements with " << containerName << " : " << elapsed << " us" << std::endl;
}

template <typename T>
void PmergeMe::mergeInsertSort(T& sequence)
{
    if (sequence.size() <= 1)
        return;
    T mainChain;
    T pendElements;
    bool has_odd = (sequence.size() % 2 != 0);
    int odd_value = 0;
    _divideAndConquer(sequence, mainChain, pendElements, odd_value, has_odd);
    _mergePending(mainChain, pendElements, odd_value, has_odd);
    sequence = mainChain;
}

template <typename T>
void PmergeMe::_divideAndConquer(T& sequence, T& mainChain, T& pendElements, int& odd_value, bool& has_odd)
{
    if (has_odd)
    {
        odd_value = sequence.back();
        sequence.pop_back();
    }
    typename T::iterator it = sequence.begin();
    while (it != sequence.end())
    {
        typename T::iterator nextIt = it;
        nextIt++;
        if (*it > *nextIt)
            std::swap(*it, *nextIt);
        mainChain.push_back(*nextIt);
        pendElements.push_back(*it);
        it++;
        it++;
    }
    mergeInsertSort(mainChain);
}

template <typename T>
void PmergeMe::_mergePending(T& mainChain, T& pendElements, int odd_value, bool has_odd)
{
    std::vector<int> jacobsthal = _getJacobsthalSequence();
    typename T::iterator firstPend = pendElements.begin();
    typename T::iterator insertPos = this->template binarySearch<T>(mainChain.begin(), mainChain.end(), *firstPend);
    mainChain.insert(insertPos, *firstPend);
    size_t prev_jac = 1;
    size_t i = 1;
    while (i < jacobsthal.size())
    {
        size_t current_jac = jacobsthal[i];
        if (current_jac > pendElements.size())
            current_jac = pendElements.size();
        typename T::iterator end_it = pendElements.begin();
        std::advance(end_it, current_jac);
        typename T::iterator start_it = pendElements.begin();
        std::advance(start_it, prev_jac);
        while (end_it != start_it)
        {
            end_it--;
            insertPos = this->template binarySearch<T>(mainChain.begin(), mainChain.end(), *end_it);
            mainChain.insert(insertPos, *end_it);
        }
        prev_jac = current_jac;
        if (current_jac == pendElements.size())
            break;
        i++;
    }
    if (has_odd)
    {
        insertPos = this->template binarySearch<T>(mainChain.begin(), mainChain.end(), odd_value);
        mainChain.insert(insertPos, odd_value);
    }
}

std::vector<int> PmergeMe::_getJacobsthalSequence()
{
    std::vector<int> jacobsthal;
    jacobsthal.push_back(1);
    jacobsthal.push_back(3);
    jacobsthal.push_back(5);
    jacobsthal.push_back(11);
    jacobsthal.push_back(21);
    jacobsthal.push_back(43);
    jacobsthal.push_back(85);
    jacobsthal.push_back(171);
    jacobsthal.push_back(341);
    jacobsthal.push_back(683);
    jacobsthal.push_back(1365);
    jacobsthal.push_back(2731);
    jacobsthal.push_back(5461);
    jacobsthal.push_back(10923);
    jacobsthal.push_back(21845);
    jacobsthal.push_back(43691);
    jacobsthal.push_back(87381);
    jacobsthal.push_back(174763);
    return (jacobsthal);
}

template <typename T>
typename T::iterator PmergeMe::binarySearch(typename T::iterator first, typename T::iterator last, int value)
{
    typename T::iterator low = first;
    typename T::iterator high = last;
    while (std::distance(low, high) > 0)
    {
        typename T::iterator mid = low;
        std::advance(mid, std::distance(low, high) / 2);
        if (*mid < value)
        {
            low = mid;
            low++;
        }
        else
            high = mid;
    }
    return (low);
}

template <typename T>
void PmergeMe::printSequence(const T& sequence)
{
    typename T::const_iterator it = sequence.begin();
    
    while (it != sequence.end())
    {
        std::cout << *it << " ";
        it++;
    }
}
