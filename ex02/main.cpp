/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:33:40 by ilevy             #+#    #+#             */
/*   Updated: 2025/07/11 00:35:38 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		std::cerr << "Error: No input sequence provided." << std::endl;
		return 1;
	}
	PmergeMe pmergeMe(argc, argv);
	(void)pmergeMe;
	return 0;
}
