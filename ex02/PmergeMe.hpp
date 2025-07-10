/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:02:24 by ilevy             #+#    #+#             */
/*   Updated: 2025/07/11 00:37:57 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# pragma once

# include <iostream>
# include <list>
# include <deque>
# include <algorithm>
# include <ctime>
# include <cstdlib>

class PmergeMe
{
	private:
		PmergeMe( const PmergeMe& copy );
		PmergeMe operator=( const PmergeMe& src );
		std::deque<int>	_inputDeque;
		std::list<int>	_inputList;
	public:
		PmergeMe( int argc, char **argv );
		~PmergeMe( void );
		template <typename T>
		void	display( const T& container );
		void	mergeInsertSortDeque( std::deque<int>& arr );
		void	mergeInsertSortList( std::list<int>& arr );
};

#endif
