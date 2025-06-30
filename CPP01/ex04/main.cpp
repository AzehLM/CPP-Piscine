#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

static std::string	replacing(const std::string& content, const std::string& to_find, const std::string& replacement)
{
	std::string 			ret;
	std::string::size_type	pos = 0;
	std::string::size_type	found = 0;

	found = content.find(to_find, pos);
	while (found != std::string::npos)
	{
		ret.append(content, pos, found - pos);
		ret.append(replacement);
		pos = found + to_find.length();
		found = content.find(to_find, pos);
	}
	ret.append(content, pos, std::string::npos);
	return (ret);
}

int	parameterCheck(const std::string& filename, const std::string& to_find)
{
	if (filename.empty() || to_find.empty())
	{
		std::cout << "Cannot have empty parameters" << std::endl;
		return (1);
	}

	std::ifstream	inputFile(filename.c_str());
	if (!inputFile)
	{
		std::cout << "File doesn't exist" << std::endl;
		return (1);
	}

	if (!inputFile.is_open())
	{
		std::cout << "Error: cannot open file '" << filename << "'" << std::endl;
		return (1);
	}

	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 4) {
		std::cout << "Usage, ./losing_it <filename> <to_replace> <replacement>" << std::endl;
		return (EXIT_FAILURE);
	}

	std::string	filename = av[1];
	std::string to_find = av[2];
	std::string replacement = av[3];

	std::ifstream	inputFile(filename.c_str());
	if (parameterCheck(filename, to_find))
		return(EXIT_FAILURE);

	std::stringstream	buffer;
	buffer << inputFile.rdbuf();
	std::string	content = buffer.str();
	inputFile.close();

	std::string replaceContent = replacing(content, to_find, replacement);

	std::string newFile = filename + ".replace";

	std::ofstream outputFile(newFile.c_str());
	if (!outputFile.is_open())
	{
		std::cout << "Error: cannot open file '" << newFile << "'" << std::endl;
		return (1);
	}
	
	outputFile << replaceContent;
	outputFile.close();
	return (0);
}
