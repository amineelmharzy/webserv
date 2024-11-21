#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string>
#include<fstream>
#include<vector>
#include<cstddef>
#include<sstream>
#include "../config/Config.hpp"
#include "Cgi.hpp"
#include "../request/utils/Utils.hpp"
#include <signal.h>

CGI::CGI(std::map<std::string, std::string> env) : env(env)
{
}

std::string	CGI::get_cgi_output() const
{
	return (output);
}

char** CGI::set_env()
{
    char **env = new char*[this->env.size() + 1];
    size_t i = 0;
    for (std::map<std::string, std::string>::iterator it = this->env.begin(); it != this->env.end(); ++it)
    {
        std::string env_var = it->first + "=" + it->second;
        env[i] = new char[env_var.size() + 1];
        std::copy(env_var.begin(), env_var.end(), env[i]);
        env[i][env_var.size()] = '\0';
        i++;
    }
    env[i] = NULL;
    return env;
}

std::vector<std::pair<std::string, std::string> > CGI::get_cgi_heahers()
{
	return (headers);
}

bool	CGI::exec_cgi()
{
	std::pair<String, String> header;
	std::pair<Iterator, String> temp;
    std::string path = env["PATH_INFO"] + env["SCRIPT_NAME"];

    int pipefd[2];
    if (pipe(pipefd) == -1)
        return (false);
    char **env = set_env();
    pid_t pid = fork();
    if (pid == -1)
    {
        close(pipefd[0]);
        close(pipefd[1]);
        return (false);
    }
    else if (pid == 0)
    {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
        {
            close(pipefd[1]);
            exit(EXIT_FAILURE);
        }
		char *args[] = { (char *)path.c_str(), NULL };
        execve(args[0], args, env);
        exit(EXIT_FAILURE);
    }
    else
    {
		const int time_out = 10;
		fd_set readfds;
		struct timeval tv;
        char buffer[1024] = {0};
        int bytesRead;
        close(pipefd[1]);
		while (true) {
			FD_ZERO(&readfds);
			FD_SET(pipefd[0], &readfds);
			tv.tv_sec = time_out;
			tv.tv_usec = 0;

			int result = select(pipefd[0] + 1, &readfds, NULL, NULL, &tv);
			if (result == -1) {
				close(pipefd[0]);
				return false;
			}
			else if (!result)
			{
                kill(pid, SIGKILL);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
				break ;
			}
			else
			{
				if (FD_ISSET(pipefd[0], &readfds))
				{
					bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);
					if (bytesRead > 0)
					{
						buffer[bytesRead] = 0;
						output += buffer;
					}
					else
						break ;
				}
			}
		}
		close(pipefd[0]);
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            return false;
    }
	temp = Utils::parseToken(output.begin(), output.end(), "\n");
	while (!temp.second.empty())
	{
		if (temp.second.find(":") != std::string::npos)
		{
			header.first = temp.second.substr(0, temp.second.find(":"));
			header.second = temp.second.substr(temp.second.find(":") + 2, temp.second.length());
		}
		headers.push_back(header);
		header.first.clear();
		header.second.clear();
		temp = Utils::parseToken(temp.first, output.end(), "\n");
	}
	output = String(temp.first, output.end());
    return true;
}
