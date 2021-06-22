
# include "../incs/Request.hpp"

Request::Request() :  _method("GET"), _url("/"), _accept_charsets("basic"), _accept_language("fr-FR"), _host("localhost"), _referer("/"), _user_agent("/"), _unknown(0)
{
}

Request::Request(Request const &ref) :  _method("GET"), _url("/"), _accept_charsets(ref._accept_charsets), _accept_language(ref._accept_language), _host(ref._host), _referer(ref._referer), _user_agent(ref._user_agent), _unknown(ref._unknown)
{
}

Request::Request(std::string request, std::string client_ip, server_info config) :   _config(config), _request(request), _clientIP(client_ip), _unknown(0)
{
	std::string				line;
	std::string				tmp;
	std::string::iterator	it;
	std::string::iterator	ite;
	int						i;

	std::cout << request << std::endl;
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
//	while (request[i] != ' ' && request[i] != '\r' && request[i] != '\n' && request[i] != '\0')
//		++i;

	//arguments
	if (request[i] == '?')
	{
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
		this->_query.assign(it, ite);
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
	this->parsing(line);
}

Request::~Request()
{
}

Request		&Request::operator=(Request const &rhs)
{
	this->_method = rhs.getMethod();
	this->_arguments = rhs.getArguments();
	this->_url = rhs.getURL();
	this->_http_version = rhs.getHTTPVersion();
	this->_unknown = rhs.getUnknown();
	this->_accept_charsets = rhs.getAcceptCharsets();
	this->_accept_language = rhs.getAcceptLanguage();
	this->_host = rhs.getHost();
	this->_referer = rhs.getReferer();
	this->_user_agent = rhs.getUserAgent();
	this->_config = rhs.getConfig();
	this->_request = rhs.getRequest();
	return (*this);
}

void		Request::parsing(std::string str)
{
	std::string				line;
	std::string::iterator	it;
	std::string::iterator	ite;

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
		if (this->_unknown == 2 && this->_method.compare("POST") == 0)
			this->ParseBody(line);
		else if (setHeader(line) == -2)
			this->_unknown = 2;
	}
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
	else if (line.compare("\r") == 0)
		return (-2);
	else
		return (-1);
	return (0);
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

std::vector<std::string>	Request::getArguments(void) const
{
	return (this->_arguments);
}

void			Request::ParseBody(std::string request)
{
	int		i;
	std::string::iterator	it;
	std::string::iterator	ite;

	i = 0;
	std::cout << request << std::endl;
	while (request[i] != '\r' && request[i] != '\n' && request[i] != '\0')
	{
		if (request[i] == '&')
			++i;
		while (request[i] != '\r' && request[i] != '\n' && request[i] != 0 && request[i] != '&')
		{
			it = request.begin() + i;
			while (request[i] != '\r' && request[i] != '\n' && request[i] != '=')
				i++;
			ite = request.begin() + i;
			this->_arguments.push_back(std::string(it, ite));
			++i;
			ite = request.begin() + i;
			while (request[i] != '\r' && request[i] != '\n' && request[i] != '&' && request[i] != '\0')
				i++;
			it = request.begin() + i;
			this->_arguments.push_back(std::string(ite, it));
		}
	}
}
