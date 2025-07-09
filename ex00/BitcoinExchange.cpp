/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:18:05 by ilevy             #+#    #+#             */
/*   Updated: 2025/07/09 17:54:57 by ilevy            ###   ########.fr       */
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

	file.open(databaseName.c_str());
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

	file.open(this->getInputName().c_str());
	if (!file.is_open())
	{
		std::cerr << RED << "Error: Could not open input file with path: " << RESET << this->getInputName() << std::endl;
		return (ERROR);
	}
	this->parseInput(file);
	return (SUCCESS);
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
	return (s);
}

static std::string& trim( std::string& s )
{
	return (ltrim(rtrim(s)));
}

void	BitcoinExchange::parseInput( std::ifstream& file )
{
	std::string	inputLine;
	std::string	datePart;
	std::string	valuePart;

	double		value;

	bool		firstLine = true;

	while (std::getline(file, inputLine))
	{
		trim (inputLine);
		if (firstLine)
		{
			if (inputLine == "date | value")
			{
				firstLine = false;
				continue;
			}
		}
		firstLine = false;
		std::stringstream ss(inputLine);

		if (inputLine[11] != '|' || inputLine[10] != ' ' || inputLine[12] != ' ')
		{
			inputLine = inputLine.empty() ? "empty" : inputLine;
			std::cout << "Error: bad input: " << inputLine << std::endl;
			continue;
		}
		if (std::getline(ss, datePart, '|'))
		{
			if (!std::getline(ss, valuePart))
			{
				std::cout << "Error: Bad Input: " << inputLine << std::endl;
				continue;
			}
			datePart.erase(datePart.find_last_not_of(" \n\r\t") + 1);
			valuePart.erase(0, valuePart.find_first_not_of(" \n\r\t"));
			if (!isValidDate(datePart))
			{
				std::cout << "Error: Bad Input: " << datePart << std::endl;
				continue;
			}
			if (!isValidValue(valuePart))
				continue;
			value = atof(valuePart.c_str());
			if (value > 1000)
			{
				std::cout << "Error: Too large a number" << std::endl;
				continue ;
			}
			std::cout << datePart << "=>" << value << " = " << value * this->getSpecificExchangeRate(datePart) << std::endl;
		}
		else
		{
			inputLine = inputLine.empty() ? "empty" : inputLine;
			std::cout << "Error: bad input: " << inputLine << std::endl;
		}
	}
}

double	BitcoinExchange::getSpecificExchangeRate( const std::string& date ) const
{
	std::map<std::string, double>::const_iterator it = _exchangeRates.lower_bound(date);

	if (it == this->_exchangeRates.end() || it->first != date)
	{
		if (it == this->_exchangeRates.begin())
			return (0);
		--it;
	}
	return (it->second);
}

bool	BitcoinExchange::isValidDate( const std::string& date ) const
{
	/* Check if the date is of the form YYYY-MM-DD */
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
	{
		std::cout << "Error: bad input: " << date << std::endl;
		return (false);
	}
	/* Check if the year contains only nums.*/
	for (int i = 0; i < 4; i++)
	{
		if (!isdigit(date[i]))
		{
			std::cout << "Error: bad input: " << date << std::endl;
			return (false);
		}
	}
	/* Check if the month contains only nums.*/
	for (int i = 5; i < 7; i++)
	{
		if (!isdigit(date[i]))
		{
			std::cout << "Error: bad input: " << date << std::endl;
			return (false);
		}
	}
	/* Check if the days contain only nums.*/
	for (int i = 8; i < 10; i++)
	{
		if (!isdigit(date[i]))
		{
			std::cout << "Error: bad input: " << date << std::endl;
			return (false);
		}
	}
	int year, month, day;
	year = atoi(date.substr(0, 4).c_str());
	month = atoi(date.substr(5, 2).c_str());
	day = atoi(date.substr(8, 2).c_str());
	/*Check month validity*/
	if (month < 0 || month > 12)
	{
		if (month < 0)
			std::cout << "Error: Not a positive number";
		else
			std::cout << "Error: bad input: " << date << std::endl;
		return (false);
	}
	/*Check month validity*/
	if (day < 0 || day > 31)
	{
		if (day < 0)
			std::cout << "Error: Not a positive number";
		else
			std::cout << "Error: bad input: " << date << std::endl;
		return (false);
	}
	/*Check february validity*/
	if (month == 2)
	{
		bool leap_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > 29 || (day == 29 && !leap_year))
		{
			std::cout << "Error: bad input: " << date << std::endl;
			return (false);
		}
	}
	/*Check months with only 30 days*/
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
		{
			std::cout << "Error: bad input: " << date << std::endl;
			return (false);
		}
	}
	return (true);
}


bool	BitcoinExchange::isValidValue(const std::string& value) const
{
	char*	end;
	double	val = strtod(value.c_str(), &end);
	if (val < 0)
	{
		std::cout << "Error: not a positive number" << std::endl;
		return (false);
	}
	if (val > 1000)
	{
		std::cout << "Error: too large a number" << std::endl;
		return (false);
	}
	return (end != value.c_str() && *end == '\0' && val >= 0);
}
