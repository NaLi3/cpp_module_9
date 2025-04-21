/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:21:19 by ilevy             #+#    #+#             */
/*   Updated: 2025/04/21 17:19:59 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

ExpressionCalculator::ExpressionCalculator( void )
{
	this->prompt = "1 + 1 - 1 * 2 + 1 / 1";
	std::cout << "Default constructor called with expression: " << this->prompt << std::endl;
}

ExpressionCalculator::ExpressionCalculator( const std::string& prompt )
{
	this->prompt = prompt;
	std::cout << "Parameterized constructor called with expression: " << this->prompt << std::endl;
}

ExpressionCalculator::ExpressionCalculator( const ExpressionCalculator& copy )
{
	this->prompt = copy.prompt;
	std::cout << "Copy constructor called with expression: " << this->prompt << std::endl;
}

ExpressionCalculator& ExpressionCalculator::operator=( const ExpressionCalculator& src )
{
	if (this != &src)
		this->prompt = src.prompt;
	std::cout << "Copy assignment operator called with expression: " << this->prompt << std::endl;
	return (*this);
}

ExpressionCalculator::~ExpressionCalculator( void )
{
	std::cout << "Destructor called" << std::endl;
}

const std::string ExpressionCalculator::getExpression( void )
{
	return (this->prompt);
}

void	ExpressionCalculator::checkMultiDigit( void )
{
	bool	lastDigit = false;
	bool	lastOperator = false;

	for (unsigned int i = 0; i < this->prompt.length(); i++)
	{
		if (isdigit(this->prompt[i]))
		{
			if (lastDigit == true )
				throw std::invalid_argument("Multi-digit numbers are forbidden");
			lastDigit = true;
			lastOperator = false;
		}
		else if (isspace(this->prompt[i]) || this->isOperator(this->prompt[i]))
		{
			if (this->isOperator(this->prompt[i]) == true)
			{
				if (lastOperator == true)
					throw (std::invalid_argument("Multiple operator detected"));
				lastOperator = true;
			}
			lastDigit = false;
		}
	}
	unsigned int i = 0;
	while (isspace(this->prompt[i]))
		i++;
	if (this->isOperator(this->prompt[i]) || lastOperator == true)
		throw (std::invalid_argument("Invalid Operator at the start / end of the expression"));
}

int	ExpressionCalculator::evaluate( const std::string& prompt )
{
	std::stack<int> numbers;
	std::stack<char> operators;
	std::istringstream iss(prompt);
	char token;

	this->checkMultiDigit();
	while (iss >> token)
	{
		if (isdigit(token))
		{
			int new_num = token - '0';

			numbers.push(new_num);
		}
		else if (this->isOperator(token))
		{
			while (!operators.empty() && this->precedence(operators.top()) >= this->precedence(token))
			{
				int b = numbers.top();
				numbers.pop();
				int a = numbers.top();
				numbers.pop();
				char op = operators.top();
				operators.pop();
				numbers.push(this->applyOperator(a, b, op));
			}
			operators.push(token);
		}
	}
	while (!operators.empty())
	{
		int b = numbers.top();
		numbers.pop();
		int a = numbers.top();
		numbers.pop();
		char op = operators.top();
		operators.pop();
		numbers.push(this->applyOperator(a, b, op));
	}
	if (numbers.empty())
		throw std::runtime_error("Invalid Expression found");
	return (numbers.top());
}

bool	ExpressionCalculator::isOperator( char c )
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return (true);
	return (false);
}

int		ExpressionCalculator::precedence( char op )
{
	if ( op == '+' || op == '-')
		return (1);
	if (op == '*' || op == '/')
		return (2);
	return (-1);
}

int		ExpressionCalculator::applyOperator( int a, int b, char op )
{
	int	result;
	switch(op)
	{
		case '-':
			result = a - b;
			break;
		case '+':
			result = a + b;
			break;
		case '/':
			if (b == 0)
				throw (ExpressionCalculator::InvalidDivideByZero());
			result = a / b;
			break;
		case '*':
			result = a * b;
			break ;
		default:
			throw (std::invalid_argument("Unknown Operator"));
	}
	return (result);
}

char const* ExpressionCalculator::InvalidDivideByZero::what() const throw()
{
	return ("Invalid operation, can't divide by zero.");
}
