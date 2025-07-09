/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:18:03 by ilevy             #+#    #+#             */
/*   Updated: 2025/07/09 16:41:43 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Inclusion de la classe BitcoinExchange */
#include "BitcoinExchange.hpp"

/**
 * @brief Fonction main
 * @param argc le nombre d'arguments
 * @param argv les arguments
 * @return 0 si tout se passe bien, 1 sinon
 */
int main(int argc, char* argv[])
{
    /* Vérification si le nombre d'arguments est exactement 2 */
    if (argc != 2)
    {
        std::cerr << RED << "Usage: ./btc input.txt" << RESET << std::endl;
        return -1;
    }

    /* Bloc try pour gérer les exceptions */
    try
    {
        /* Création de l'instance exchange de la classe BitcoinExchange */
        BitcoinExchange exchange(argv[1]);

        /* Chargement de la base de données data.csv */
        exchange.loadDatabase("data.csv");

        /* Traitement de l'entrée input.txt */
        exchange.loadInput();
    }

    /* Gestion des exceptions */
    catch (const std::exception& e)
    {
        std::cerr << RED << e.what() << RESET << std::endl;
        return -1;
    }

    return 0;
}
