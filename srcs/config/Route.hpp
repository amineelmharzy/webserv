/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:07:10 by hkasbaou          #+#    #+#             */
/*   Updated: 2024/07/29 21:42:27 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include "http.h"
#include <map>
#include "Config.hpp"

// typedef enum
// {
// 	GET,
// 	PUT,
// 	POST,
// 	HEAD,
// 	TRACE,
// 	PATCH,
// 	DELETE,
// 	CONNECT,
// 	OPTIONS
// }	Method;
class Route {
    private:
        std::string                 path;
        std::vector<Method>         methods;
        std::string                 directory;
        std::string                 redirect;
        std::string                 file; 
        std::string                 default_file;
        std::string                 upload;
        // std::string                 cgi_bin;
        // std::string                 cgi_extension;
        bool                        useCGI;
        bool                        directory_listing;
    
    public:
    
        //geters
        std::string get_path();
        std::vector<Method> get_methods();
        std::string get_directory();
        std::string get_redirect();
        std::string get_file();
        std::string get_default_file();
        bool get_useCGI();
        std::string get_upload();
        // std::string get_cgi_bin();
        // std::string get_cgi_extension();
        bool get_directory_listing();
		bool is_allowed_method(Method method);
        
        //setters
        void set_path(std::string path);
        void set_methods(Method metod);
        void set_directory(std::string directory);
        void set_redirect(std::string redirect);
        void set_file(std::string file);
        void set_default_file(std::string default_file);
        void set_useCGI(bool cgi);
        void set_upload(std::string upload);
        // void set_cgi_bin(std::string cgi_bin);
        // void set_cgi_extension(std::string cgi_extension);
        void set_directory_listing(bool directory_listing);
        //copy assigment 
        // Route(const Route &route);
        Route &operator=(const Route &route);
        
        //methods
        void clear_route();
        Route();
        ~Route();
        // Add getters and setters as needed
};
