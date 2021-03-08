
# include "../incs/Request.hpp"

Request::Request() : _method("GET"), _url("/"), _accept_charsets("basic"), _accept_language("fr-FR"), _host("localhost"), _referer("/"), _user_agent("/"), _unknwon(0)
{
}

Request::Request(Request const &ref) : _method("GET"), _url("/"), _accept_charsets(ref._accept_charsets), _accept_language(ref._accept_language), _host(ref._host), _referer(ref._referer), _user_agent(ref._user_agent), _unknwon(ref._unknown)
{
}

Request::Request(std::string request) : _unknwon(0)
{
	std::string				line;
	std::string::iterator	it;
	std::string::iterator	ite;

	//method
	ite = request.begin();
	while (*ite == ' ' && *ite != '\0')
		++ite;
	if (*ite == '\0')
		return ;
	it = ite;
	while (*ite != ' ' && *ite != '\n' && *ite != '\0')
		++ite;
	this->_method.assign(it, ite);

	//url
	while (*ite == ' ' && *ite != '\0')
		++ite;
	if (*ite == '\0')
		return ;
	it = ite;
	while (*ite != ' ' && *ite != '\n' && *ite != '\0')
		++ite;
	this->_url.assign(it, ite);
	if (*ite == '\0')
		return ;

	//http version
	while (*ite == ' ' && *ite != '\0')
		++ite;
	if (*ite == '\0')
		return ;
	it = ite;
	while (*ite != ' ' && *ite != '\n' && *ite != '\0')
		++ite;
	this->_http_version.assign(it, ite);
	if (*ite == '\0')
		return ;
	while (*ite == ' ')
		++ite;
	if (*ite != '\n' && *ite != '\0')
		return ;

	//headers
	line.assign(ite, request.end());
	this->parsing(line);
}

Request::~Request()
{
}

Request		&Request::operator=(Request const &rhs)
{
	(void)rhs;
	this->_accept_charsets = "basic";
	this->_accept_language = "fr-FR";
	this->_host = "localhost";
	this->_referer = "/";
	this->_user_agent = "/";
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
		while (*it == ' ')
			++it;
		ite = it;
		while (*it != '\n')
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
	while (*it != ' ')
		++it;
	line.assign(str.begin(), it);
	ite = it;
	while (*ite != '\n' && *ite != '\0')
		++ite;
	if (line.compare("Accept-Charset:") == 0)
		this->setAcceptCharset(std::string(it, ite));
	if (line.compare("Accept-Language:") == 0)
		this->setAcceptLanguage(std::string(it, ite));
	if (line.compare("Host:") == 0)
		this->setHost(std::string(it, ite));
	if (line.compare("Referer:") == 0)
		this->setReferer(std::string(it, ite));
	if (line.compare("User-Agent:") == 0)
		this->setUserAgent(std::string(it, ite));
	return (0);
}

void		Request::setAcceptCharsets(std::string str)
{
	this->_accept_charsets.copy(str);
}

void		Request::setAcceptLanguage(std::string str)
{
	this->_accept_language.copy(str);
}

void		Request::setHost(std::string str)
{
	this->_host.copy(str);
}

void		Request::setReferer(std::string str)
{
	this->_referer.copy(str);
}

void		Request::setUserAgent(std::string str)
{
	this->_user_agent.copy(str);
}
