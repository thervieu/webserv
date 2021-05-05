
# include "../incs/Request.hpp"

Request::Request() : _method("GET"), _url("/"), _accept_charsets("basic"), _accept_language("fr-FR"), _host("localhost"), _referer("/"), _user_agent("/"), _unknown(0)
{
}

Request::Request(Request const &ref) : _method("GET"), _url("/"), _accept_charsets(ref._accept_charsets), _accept_language(ref._accept_language), _host(ref._host), _referer(ref._referer), _user_agent(ref._user_agent), _unknown(ref._unknown)
{
}

Request::Request(std::string request, server_info config) : _config(config), _request(request), _unknown(0)
{
	std::string				line;
	std::string::iterator	it;
	std::string::iterator	ite;
	int						i;

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
	while (request[i] != ' ' && request[i] != '\r' && request[i] != '\n' && request[i] != '\0')
		++i;
	ite = request.begin() + i;
	this->_url.assign(it, ite);

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
	this->_url = rhs.getURI();
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
			++it;
		if (*it == '\0')
			return ;
		ite = it;
		while (*it != '\n' && *it != '\0')
			++it;
		line.assign(ite, it);
		if (setHeader(line) == -1)
			this->_unknown = 1;
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

void			Request::setURI(std::string str)
{
	this->_url.assign(str);
}

std::string		Request::getURI(void) const
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
