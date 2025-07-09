/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:18:00 by ilevy             #+#    #+#             */
/*   Updated: 2025/07/09 16:04:54 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# pragma once

# include <iostream>
# include <map>
# include <fstream>
# include <sstream>
# include <cstdlib>
# include <algorithm>

# define SUCCESS 0
# define ERROR 1
# define CRITICAL_ERROR -1


# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RED "\033[31m"
# define CYAN "\033[36m"
# define MAGENTA "\033[35m"
# define BLUE "\033[34m"
# define RESET "\033[0m"


// This exercise, I've made the choice to use a hashmap in order to make full use of the key/value pair that it provides.
// Indeed, we need to find the value of the bitcoin at a specific date, hence date as a string and value as a double.

class BitcoinExchange
{
	private:

		std::string							_inputName;
		std::map<std::string, double>		_exchangeRates;

		BitcoinExchange( void );

		//Will parse the Database and put the exchange rate in the map.
		void		parseDatabase( std::ifstream& databaseFile );
		void		parseInput( std::ifstream& inputFile );
		bool		isValidDate( const std::string& date ) const;
		bool		isValidValue( const std::string& value ) const;
		double		getSpecificExchangeRate( const std::string& date ) const;

	public:

		// Constructor and destructors
		BitcoinExchange( const std::string& inputName );
		BitcoinExchange( const BitcoinExchange& copy );
		BitcoinExchange& operator=( const BitcoinExchange& src );
		~BitcoinExchange( void );

		//Getters
		const std::string&						getInputName( void ) const;
		const std::map<std::string, double>&	getExchangeRates( void ) const;

		//Will be called with database name, and populates exchange rate hashmap.
		int		loadDatabase( const std::string& database );

		//Loads input received at construction in _inputName
		int		loadInput( void );

};

#endif
