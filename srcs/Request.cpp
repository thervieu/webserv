
# include "../incs/Request.hpp"

Request::Request() : _accept_charsets("basic"), _accept_language("fr"), _host("localhost"), _referer("/"), _user_agent("/")
{
}

Request::Request(Request const &ref) : _accept_charsets(ref._accept_charsets), _accept_language(ref._accept_language), _host(ref._host), _referer(ref._referer), _user_agent(ref._user_agent)
{
}

Request::~Request()
{
}

Request		&Request::operator=(Request const &rhs)
{
	(void)rhs;
	this->_accept_charsets = "basic";
	this->_accept_language = "fr";
	this->_host = "localhost";
	this->_referer = "/";
	this->_user_agent = "/";
	return (*this);
}
