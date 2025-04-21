/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:21:17 by ilevy             #+#    #+#             */
/*   Updated: 2025/04/21 17:09:22 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main( int argc, char **argv )
{
	if (argc != 2)
	{
		std::cout << "Usage ./RNP [Mathematical expression]" << std::endl;
		return (-1);
	}
	try
	{
		ExpressionCalculator calc( argv[1] );
		std::cout << "Result: " << calc.evaluate(calc.getExpression()) << std::endl;  // Output: 13
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}


