/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:18:00 by ilevy             #+#    #+#             */
/*   Updated: 2025/06/27 15:26:52 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# pragma once

# include <iostream>
# include <map>

// This exercise, I've made the choice to use a hashmap in order to make full use of the key/value pair
// that it provides.
// Indeed, we need to find the value of the bitcoin at a specific date, hence date as a string and value as a float.

class BitcoinExchange
{
	private:
		std::map<std::string, float> _map;
	public:
	
		//
		BitcoinExchange( void );
		BitcoinExchange( const BitcoinExchange& copy );
		BitcoinExchange& operator=( const BitcoinExchange& src );
		~BitcoinExchange( void );
	
};

#endif