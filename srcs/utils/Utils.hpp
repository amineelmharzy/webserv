/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:28:38 by ael-mhar          #+#    #+#             */
/*   Updated: 2024/07/07 12:03:01 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <sstream>
# include <string>

namespace Utils
{
	template <typename T>
	std::string toMyString(T value);
	std::string toString(int value);
	size_t toSize_t(const std::string& str);
};

#endif
