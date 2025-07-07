/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:18:05 by ilevy             #+#    #+#             */
/*   Updated: 2025/07/07 10:10:16 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


// Constructors and destructor
BitcoinExchange::BitcoinExchange( void )
{
	std::cout << "Non instantiable without parameters" << std::endl;
}

BitcoinExchange::BitcoinExchange( const std::string& inputName ): _inputName(inputName)
{
	std::cout << "Parameterized constructor called with input file path: " << this->getInputName() << std::endl;
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange& copy ): _inputName(copy.getInputName()), _exchangeRates(copy.getExchangeRates())
{
	std::cout << "Copy constructor called with copy input file path: " << copy.getInputName() << std::endl;
}

BitcoinExchange& BitcoinExchange::operator=( const BitcoinExchange& src )
{
	if (this != &src )
	{
		this->_exchangeRates = src.getExchangeRates();
		this->_inputName = src.getInputName();
	}
	
	return (*this);
}

BitcoinExchange::~BitcoinExchange( void )
{
	std::cout << RED << "Default destructor called" << RESET << std::endl;
}

// Getter functions
const std::map<std::string, double>&	BitcoinExchange::getExchangeRates( void ) const
{
	return (this->_exchangeRates);
}

const std::string&						BitcoinExchange::getInputName( void ) const
{
	return (this->_inputName);
}

//Loads database in ifstream variable, checks its opening and then sends to parsing inner function
int	BitcoinExchange::loadDatabase( const std::string& databaseName )
{
	std::ifstream file;

	file.open(databaseName);
	if (!file.is_open())
	{
		std::cerr << RED << "Error: Could not open database file with path: " << RESET << databaseName << std::endl;
		return (ERROR);
	}
	this->parseDatabase(file);
	return (SUCCESS);
}

// Checks through every line in the file for the key value pairs, and populates the exchange rate hashmap with them.
void	BitcoinExchange::parseDatabase( std::ifstream& databaseFile )
{
	std::string	line;
	std::string	date;
	double		rateValue;

	while (std::getline(databaseFile, line))
	{
		if (line != "date,exchange_rate")
		{
			std::istringstream ss(line);
			if (std::getline(ss, date, ',') && (ss >> rateValue))
				this->_exchangeRates[date] = rateValue;	
		}
	}
}

// Loads input variables
int		BitcoinExchange::loadInput( void )
{
	std::ifstream file;

	file.open(this->getInputName());
	if (!file.is_open())
	{
		std::cerr << RED << "Error: Could not open input file with path: " << RESET << this->getInputName() << std::endl;
		return (ERROR);
	}
	this->parseInput(file);
	return (SUCCESS)
}

static bool isNotSpace(char c)
{
	return (!std::isspace(static_cast<unsigned char>(c)));
}

static std::string& rtrim(std::string& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), isNotSpace).base(), s.end());
	return (s);
}

static std::string& ltrim(std::string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), isNotSpace));
	return (s)
}

static std::string& trim( std::string& s )
{
	return (ltrim(rtrim(s)));
}

void	BitcoinExchange::parseInput( std::ifstream& file )
{
	std::string	line;
	std::string	date;
	double		rateValue;

	while (std::getline(file, line))
	{
		trim(line);
		if 
	}
}