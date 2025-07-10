/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:05:47 by ilevy             #+#    #+#             */
/*   Updated: 2025/07/11 00:42:01 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::~PmergeMe( void )
{
	std::cout << "default destructor called" << std::endl;
}

PmergeMe::PmergeMe( int argc, char **argv )
{
	srand(time(NULL));
	for (int i = 1; i < argc; i++)
	{
		int value = atoi(argv[i]);
		if (value <= 0)
		{
			std::cerr << "Error: Invalid input value, no negative number: " << argv[i] << std::endl;
			exit(1);
		}
		this->_inputDeque.push_back(value);
		this->_inputList.push_back(value);
	}
	std::cout << "Before: ";
	display(this->_inputDeque);

	clock_t	start1 = clock();
	mergeInsertSortDeque(this->_inputDeque);
	clock_t end1 = clock();
	double	time1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1000;

	clock_t	start2 = clock();
	mergeInsertSortList(this->_inputList);
	clock_t end2 = clock();
	double	time2 = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC * 1000;

	std::cout << "After: ";
	display(this->_inputDeque);
	std::cout << "Time to process a range of " << this->_inputDeque.size() << " elements with std::deque container: " << time1 << " us" << std::endl;
	std::cout << "Time to process a range of " << this->_inputList.size() << " elements with std::list container: " << time2 << " us" << std::endl;
	if (this->_inputDeque == std::deque<int>(this->_inputList.begin(), this->_inputList.end()))
		std::cout << "The sorted sequences are equal." << std::endl;
	else
		std::cout << "The sorted sequences are not equal." << std::endl;
}

template <typename T>
void PmergeMe::display(const T& container)
{
	typename T::const_iterator it;

	for (it = container.begin(); it != container.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void PmergeMe::mergeInsertSortDeque(std::deque<int>& arr)
{
	std::deque<int>::iterator it1, it2;
	for (it1 = arr.begin() + 1; it1 != arr.end(); ++it1)
	{
		int temp = *it1;
		it2 = it1;
		while (it2 != arr.begin())
		{
			std::deque<int>::iterator it_prev = it2;
			--it_prev;
			if (*it_prev <= temp)
				break;
			*it2 = *it_prev;
			--it2;
		}
		*it2 = temp;
	}
}

void PmergeMe::mergeInsertSortList(std::list<int>& arr)
{
	std::list<int>::iterator it1, it2;
	for (it1 = ++arr.begin(); it1 != arr.end(); ++it1)
	{
		int temp = *it1;
		it2 = it1;
		while (it2 != arr.begin())
		{
			std::list<int>::iterator it_prev = it2;
			--it_prev;
			if (*it_prev <= temp)
				break;
			*it2 = *it_prev;
			--it2;
		}
		*it2 = temp;
	}
}
