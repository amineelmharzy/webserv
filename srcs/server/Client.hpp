/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 07:43:16 by ayakoubi          #+#    #+#             */
/*   Updated: 2024/07/16 09:12:17 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <ctime>
#include "../request/HTTPParser.hpp"
#include "../request/HTTPResponse.hpp"
#include "../request/HTTPRequest.hpp"

class Client
{
	private:
		std::string request;
		size_t readNum;
		size_t sendNum;
		int isChunked;
		std::string	restBody;
		HTTPParser	*httpParser;
	public:
		bool isHeader;
		bool isBody;
		std::string body;
		size_t lastActivity;
		size_t timeKeepAlive;
		bool isKeepAlive;
		HTTPRequest *httpRequest;
	public:
		Client();
		~Client();
		
		void	setRequest(const std::string& request);
		void	setReadNum(const size_t& readNum);
		void	setSendNum(const size_t& sendNum);
		void 	setRestBody(const std::string& restBody);
		void	setIsChunked(const int& isChunked);
		void	setHTTPParser(HTTPParser *httpParser);
		// void	setHTTPRequest(HTTPRequest *httpRequest);

		std::string	getRequest() const;
		std::string	getRestBody() const;
		size_t getReadNum() const;
		size_t getSendNum() const;
		int getIsChunked() const;
		HTTPParser*	getHTTPParser() const;

		bool	handleTimeOut(int sock);
};

#endif
