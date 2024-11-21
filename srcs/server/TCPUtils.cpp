/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPUtils.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 08:16:52 by ayakoubi          #+#    #+#             */
/*   Updated: 2024/06/27 22:10:02 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TCPUtils.hpp"

// __ Set Non Blocking _________________________________________________________
// =============================================================================
bool TCPUtils::setNonBlocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        // Failed to get socket flags
        return false;
    }

    // Set the socket to non-blocking mode
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        // Failed to set socket to non-blocking mode
        return false;
    }

    return true;
}

std::vector<char>	TCPUtils::storeDataInVec(char *buffer)
{
	std::vector<char> vec;

	vec.insert(vec.end(), buffer, buffer + strlen(buffer));
	return (vec);
}


long TCPUtils::stringToLong(const std::string& str)
{
    int octets[4];
    std::sscanf(str.c_str(), "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3]);
    

    return( (octets[0] << 24) | (octets[1] << 16) | (octets[2] << 8) | octets[3]);
}

int TCPUtils::hexCharToInt(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	return (0);
}

size_t TCPUtils::hexToDecimal(const std::string& hex)
{
    int result = 0;
    for (std::string::const_iterator it = hex.begin(); it != hex.end(); ++it) {
        result = result * 16 + hexCharToInt(*it);
    }
    return result;
}

std::string TCPUtils::parseChunkedBody(std::string chunk)
{
	size_t pos;
	size_t chunkedSize;
	std::string str;
	std::string tmp;

	while (chunk.size())
	{
		pos = chunk.find("\r\n");
		if (pos != std::string::npos)
		{
			tmp = chunk.substr(pos + 2, chunk.size());
			chunkedSize = hexToDecimal(chunk.substr(0, pos));
			if (chunkedSize == 0 && chunk.substr(0, pos) != "0")
				str.append(chunk, pos);
			else if (chunkedSize == 0)
				tmp.erase(tmp.begin(), tmp.end());
			else if (chunkedSize >= tmp.size())
			{
				str.append(tmp, tmp.size());
				tmp.erase(tmp.begin(), tmp.end());
			}
			else if (chunkedSize < tmp.size())
			{
				std::cout << chunkedSize << std::endl;
				str.append(tmp, 0, chunkedSize);
				tmp.erase(0, tmp.find("\r\n") + 2);
			}
			chunk = tmp;
		}
	}
	return (str);
}
