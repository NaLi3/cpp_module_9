/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:21:21 by ilevy             #+#    #+#             */
/*   Updated: 2025/04/21 17:10:07 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <algorithm>
# include <stack>
# include <exception>
# include <sstream>

class ExpressionCalculator
{
	private:
		std::string prompt;
		ExpressionCalculator( void );
	public:
		ExpressionCalculator( const std::string& prompt );
		ExpressionCalculator( const ExpressionCalculator& copy );
		ExpressionCalculator& operator=( const ExpressionCalculator& src );
		~ExpressionCalculator( void );

		void	checkMultiDigit( void );
		const std::string getExpression( void );
		int	evaluate( const std::string& expression);
		bool isOperator( char c );
		int	precedence( char op );
		int applyOperator( int a, int b, char op);

		class InvalidDivideByZero: public std::exception
		{
			public:
				char const *what() const throw();
		};
};

#endif
