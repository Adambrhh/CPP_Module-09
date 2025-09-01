/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* PmergeMe.cpp                                       :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/09/01 10:20:03 by abarahho          #+#    #+#             */
/* Updated: 2025/09/01 10:20:04 by abarahho         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& copy)
{
    *this = copy;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        this->_vec = other._vec;
        this->_lst = other._lst;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::insertionSort(std::vector<int>& vec, int left, int right)
{
    int i;

    i = left + 1;
    while (i <= right)
    {
        int key = vec[i];
        int j = i - 1;
        while (j >= left && vec[j] > key)
        {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
        i++;
    }
}

void PmergeMe::merge(std::vector<int>& vec, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);

    int i = 0;
    while (i < n1) {
        L[i] = vec[left + i];
        i++;
    }
    int j = 0;
    while (j < n2) {
        R[j] = vec[mid + 1 + j];
        j++;
    }

    i = 0;
    j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            vec[k++] = L[i++];
        else
            vec[k++] = R[j++];
    }
    while (i < n1)
        vec[k++] = L[i++];
    while (j < n2)
        vec[k++] = R[j++];
}

void PmergeMe::mergeInsertSort(std::vector<int>& vec, int left, int right)
{
    if (right - left + 1 <= 10) // Small sequences are sorted with insertion sort
    {
        insertionSort(vec, left, right);
    }
    else
    {
        int mid = left + (right - left) / 2;
        mergeInsertSort(vec, left, mid);
        mergeInsertSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

// Private member functions for std::list
void PmergeMe::insertionSort(std::list<int>& lst)
{
    std::list<int>::iterator it = lst.begin();
    while (it != lst.end()) {
        int key = *it;
        std::list<int>::iterator j = it;
        while (j != lst.begin()) {
            std::list<int>::iterator prev = j;
            --prev;
            if (*prev > key) {
                *j = *prev;
                j = prev;
            } else {
                break;
            }
        }
        *j = key;
        it++;
    }
}

std::list<int> PmergeMe::merge(std::list<int>& left, std::list<int>& right)
{
    std::list<int> result;
    while (!left.empty() && !right.empty()) {
        if (left.front() <= right.front()) {
            result.push_back(left.front());
            left.pop_front();
        } else {
            result.push_back(right.front());
            right.pop_front();
        }
    }
    result.splice(result.end(), left);
    result.splice(result.end(), right);
    return result;
}

void PmergeMe::mergeInsertSort(std::list<int>& lst)
{
    if (lst.size() <= 1)
        return;
    std::list<int> left, right;
    std::list<int>::iterator it = lst.begin();
    
    int i = 0;
    while (i < (int)lst.size() / 2) {
        left.push_back(*it);
        ++it;
        i++;
    }
    right.splice(right.begin(), lst, it, lst.end());

    mergeInsertSort(left);
    mergeInsertSort(right);

    lst = merge(left, right);
}

void PmergeMe::parseInput(char** av, int ac)
{
    int i;
    
    i = 1;
    std::cout << "Before: ";
    while (i < ac)
    {
        std::string arg = av[i];
        if (arg.find_first_not_of("0123456789") != std::string::npos) {
            throw std::runtime_error("Error: non-numeric or negative number.");
        }
        int num = std::atoi(arg.c_str());
        _vec.push_back(num);
        _lst.push_back(num);
        std::cout << num << " ";
        i++;
    }
    std::cout << std::endl;
}

void PmergeMe::printResults()
{
    // Print sorted sequence
    std::cout << "After: ";
    std::vector<int>::iterator it = _vec.begin();
    while (it != _vec.end())
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout << std::endl;
    
    // Sort with std::vector and measure time
    clock_t start_vec = clock();
    mergeInsertSort(_vec, 0, _vec.size() - 1);
    clock_t end_vec = clock();
    
    // Sort with std::list and measure time
    clock_t start_lst = clock();
    mergeInsertSort(_lst);
    clock_t end_lst = clock();
    
    // Print timings
    double time_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC * 1000000.0;
    double time_lst = static_cast<double>(end_lst - start_lst) / CLOCKS_PER_SEC * 1000000.0;

    std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector : " << time_vec << " us" << std::endl;
    std::cout << "Time to process a range of " << _lst.size() << " elements with std::list : " << time_lst << " us" << std::endl;
}

void PmergeMe::sort(char** av, int ac)
{
    parseInput(av, ac);
    printResults();
}