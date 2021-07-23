
# include "../incs/Request.hpp"

Request::Request() :  _method("GET"), _url("/"), _accept_charsets("basic"), _accept_language("fr-FR"), _host("localhost"), _referer("/"), _user_agent("/"), _unknown(0)
{
}

Request::Request(Request const &ref) :  _method("GET"), _url("/"), _accept_charsets(ref._accept_charsets), _accept_language(ref._accept_language), _host(ref._host), _referer(ref._referer), _user_agent(ref._user_agent), _unknown(ref._unknown)
{
}

Request::Request(std::string request, std::string client_ip, server_info config,  bool chunked) : _config(config), _request(request), _unknown(0)
{
	std::string				line;
	std::string				tmp;
	std::string::iterator	it;
	std::string::iterator	ite;
	int						i;
	this->setCLientIP(client_ip);

	PRINT_STR(request);
	this->_arguments = std::vector<std::string>(0);

	//method
	i = 0;
	while (request[i] == ' ')
		++i;
	if (request[i] == '\0')
		return ;
	it = request.begin() + i;
	while (request[i] != ' ' && request[i] != '\r' && request[i] != '\n' && request[i] != '\0')
		++i;
	ite = request.begin() + i;
	this->_method.assign(it, ite);

	//url
	while (request[i] == ' ')
		++i;
	if (request[i] == '\0')
		return ;
	it = request.begin() + i;
	while (request[i] != ' ' && request[i] != '\r' && request[i] != '\n' && request[i] != '\0' && request[i] != '?')
		++i;
	ite = request.begin() + i;
	this->_url.assign(it, ite);

	//arguments
	if (request[i] == '?')
	{
		
		std::string::iterator	pos = request.begin() + i + 1;
		it = request.begin() + i;
		++i;
		while (request[i] != ' ')
		{
			if (request[i] == '&')
				++i;
			while (request[i] != ' ' && request[i] != '&')
			{
				it = request.begin() + i;
				while (request[i] != ' ' && request[i] != '=')
					i++;
				ite = request.begin() + i;
				this->_arguments.push_back(std::string(it, ite));
				++i;
				ite = request.begin() + i;
				while (request[i] != ' ' && request[i] != '&')
					i++;
				it = request.begin() + i;
				this->_arguments.push_back(std::string(ite, it));
			}
		}
		ite = request.begin() + i;
		this->_query.assign(pos, ite);
	}

	//http version
	while (request[i] == ' ')
		++i;
	if (request[i] == '\0')
		return ;
	it = request.begin() + i;
	while (request[i] != ' ' && request[i] != '\r' && request[i] != '\n' && request[i] != '\0')
		++i;
	ite = request.begin() + i;
	this->_http_version.assign(it, ite);

	if (*ite == '\0')
		return ;
	while (*ite != '\r' && *ite != '\n' && *ite != '\0')
		++ite;

	//headers
	line.assign(++ite, request.end());
	// std::cout << "assign ok\n\n";
	// std::cout << "chunked end 1 = " << chunked << std::endl << "\n";
	this->parsing(line, chunked);
	// std::cout << "parsing ok\n\n";
}

Request::~Request()
{
}

Request		&Request::operator=(Request const &rhs)
{
	this->_method = rhs.getMethod();
	this->_arguments = rhs.getArguments();
	this->_url = rhs.getURL();
	this->_query = rhs.getQuery();
	this->_http_version = rhs.getHTTPVersion();
	this->_unknown = rhs.getUnknown();
	this->_accept_charsets = rhs.getAcceptCharsets();
	this->_accept_language = rhs.getAcceptLanguage();
	this->_host = rhs.getHost();
	this->_referer = rhs.getReferer();
	this->_user_agent = rhs.getUserAgent();
	this->_config = rhs.getConfig();
	this->_request = rhs.getRequest();
	this->_content = rhs.getContent();
	this->_contentLength = rhs.getContentLength();
	this->_contentType = rhs.getContentType();
	this->_clientIP = rhs.getClientIP();
	return (*this);
}

void		Request::parsing(std::string str, bool chunked)
{
	std::string				line;
	std::string::iterator	it;
	std::string::iterator	ite;

	// std::cout << "PARSING BEG str = |" << str << "|\n";
	it = str.begin();
	while (*it != '\0')
	{
		while (*it == ' ' || *it == '\n' || *it == '\r')
		{
			if (*it == '\r')
				this->_unknown = 2;
			++it;
		}
		if (*it == '\0')
			return ;
		ite = it;
		while (*it != '\n' && *it != '\0')
			++it;
		line.assign(ite, it);
		// std::cout << "line = |" << line << "|\n";
		// std::cout << "unknown = |" << _unknown << "|\n";
		if (this->_unknown == 2 && this->_method.compare("POST") == 0)
		{
			line.assign(ite, str.end());
			// std::cout << "chunked = " << chunked << std::endl << "\n";
			// std::cout << "line = |" << line << "|\n";
			this->ParseBody(line, chunked);
			return ;
		}
		else if (setHeader(line) == -2)
			this->_unknown = 2;
	}
	// std::cout << "end pasring ok\n\n";
}

int			Request::setHeader(std::string str)
{
	std::string				line;
	std::string::iterator	it;
	std::string::iterator	ite;

	it = str.begin();
	while (*it != ' ' && *it != '\0' && *it != '\n')
		++it;
	line.assign(str.begin(), it);
	while (*it == ' ')
	 ++it;
	ite = it;
	while (*ite != '\n' && *ite != '\0' && *ite != '\r')
		++ite;
	// std::cout << line << std::endl;
	if (line.compare("Accept-Charset:") == 0)
		this->setAcceptCharsets(std::string(it, ite));
	else if (line.compare("Accept-Language:") == 0)
		this->setAcceptLanguage(std::string(it, ite));
	else if (line.compare("Host:") == 0)
		this->setHost(std::string(it, ite));
	else if (line.compare("Referer:") == 0)
		this->setReferer(std::string(it, ite));
	else if (line.compare("User-Agent:") == 0)
		this->setUserAgent(std::string(it, ite));
	else if (line.compare("Content-Length:") == 0)
		this->setContentLength(std::string(it, ite));
	else if (line.compare("Content-Type:") == 0)
		this->setContentType(std::string(it, ite));
	else if (line.compare("\r") == 0)
		return (-2);
	else
		return (-1);
	return (0);
}

void		Request::setConfig(server_info config)
{
	this->_config = config;
}

server_info		Request::getConfig(void) const
{
	return (this->_config);
}

void			Request::setAcceptCharsets(std::string str)
{
	this->_accept_charsets.assign(str);
}

std::string		Request::getAcceptCharsets(void) const
{
	return (this->_accept_charsets);
}

void			Request::setAcceptLanguage(std::string str)
{
	this->_accept_language.assign(str);
}

std::string		Request::getAcceptLanguage(void) const
{
	return (this->_accept_language);
}

void			Request::setHost(std::string str)
{
	this->_host.assign(str);
}

std::string		Request::getHost(void) const
{
	return (this->_host);
}

void			Request::setReferer(std::string str)
{
	this->_referer.assign(str);
}

std::string		Request::getReferer(void) const
{
	return (this->_referer);
}

void			Request::setUserAgent(std::string str)
{
	this->_user_agent.assign(str);
}

std::string		Request::getUserAgent(void) const
{
	return (this->_user_agent);
}

void			Request::setURL(std::string str)
{
	this->_url.assign(str);
}

void			Request::setCLientIP(std::string str)
{
	this->_clientIP.assign(str);
}

void			Request::setContentLength(std::string str)
{
	this->_contentLength.assign(str);
}

void			Request::setContentType(std::string str)
{
	this->_contentType.assign(str);
}

std::string		Request::getContentLength(void) const
{
	return (this->_contentLength);
}

std::string		Request::getContentType(void) const
{
	return (this->_contentType);
}

std::string		Request::getURL(void) const
{
	return (this->_url);
}

std::string		Request::getHTTPVersion(void) const
{
	return (this->_http_version);
}

std::string		Request::getMethod(void) const
{
	return (this->_method);
}

int				Request::getUnknown(void) const
{
	return (this->_unknown);
}

std::string		Request::getRequest(void) const
{
	return (this->_request);
}

std::string		Request::getQuery(void) const
{
	return (this->_query);
}

std::string		Request::getClientIP(void) const
{
	return (this->_clientIP);
}

void	Request::setContent(std::string	content)
{
	_content.assign(content);
}

std::string		Request::getContent(void) const
{
	return (this->_content);
}

std::vector<std::string>	Request::getArguments(void) const
{
	return (this->_arguments);
}

size_t						Request::hexatoi(std::string hex) const
{
	size_t		i;
	size_t		nb;

	i = 0;
	nb = 0;
	while ((hex[i] >= '0' && hex[i] <= '9') || (hex[i] >= 'a' && hex[i] <= 'f'))
	{
		if (hex[i] >= '0' && hex[i] <= '9')
			nb = (nb * 16) + (hex[i++] - '0');
		else
			nb = (nb * 16) + hex[i++] - 'a' + 10;
	}
	// std::cout << "nb = " << nb << std::endl;
	return (nb);
}

void			Request::ParseBody(std::string request, bool chunked)
{
	std::string				updated_request;
	size_t					i;
	size_t					j;
	std::string::iterator	it;
	std::string::iterator	ite;
	size_t					next_line_size;

	i = 0;
	next_line_size = 0;
	if (chunked == true)
	{
		j = 0;
		while (request[i] != '\0' && i < request.length())
		{
			if (i + 4 < request.length() && request[i] == '0' && request[i + 1] == '\r' && request[i + 2] == '\n' && request[i + 3] == '\r' && request[i + 4] == '\n')
				break;
			else if (j == 0)
			{
				next_line_size = hexatoi(request.substr(i, request.length() - i));
				while (request[i] != '\n')
					++i;
				++i;
				j = 1;
			}
			else
			{
				updated_request += request.substr(i, next_line_size);
				// std::cout << "||||| " << updated_request << " |||||" << std::endl;
				// std::cout << "updated request line size = |" << updated_request.length() << "|\n";
				i += next_line_size + 2;
				j = 0;
			}
		}
		this->setContent(updated_request);
	}
	else
		this->setContent(request);
	i = 0;
	while (this->_content[i] != '\0' && i < this->_content.length())
	{
		if (this->_content[i] == '&')
			++i;
		while (this->_content[i] != '\r' && this->_content[i] != '\n' && this->_content[i] != 0 && this->_content[i] != '&' && i < this->_content.length())
		{
			it = this->_content.begin() + i;
			while (this->_content[i] != '\r' && this->_content[i] != '\n' && this->_content[i] != '=' && i < this->_content.length())
				i++;
			ite = this->_content.begin() + i;
			if (this->_content[i] != '=')
				break;
			this->_arguments.push_back(std::string(it, ite));
			++i;
			ite = this->_content.begin() + i;
			while (this->_content[i] != '\r' && this->_content[i] != '\n' && this->_content[i] != '&' && this->_content[i] != '\0' && i < this->_content.length())
				i++;
			it = this->_content.begin() + i;
			this->_arguments.push_back(std::string(ite, it));
		}
		++i;
	}
	// for (size_t i = 0; i < this->_arguments.size(); i++)
	// {
	// 	std::cout << "argument number " << i << ": " << this->_arguments[i] << std::endl;
	// }
}
