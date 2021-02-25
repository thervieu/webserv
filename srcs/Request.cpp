
# include "../incs/Request.hpp"

Request::Request() : _accept_charsets(0), _accept_language("fr"), _referer("/"), _user_agent("/"), _host("localhost")
{
}

Request::Request(Request const &ref) : _accept_charsets(ref._accept_charsets), _accept_language(ref._accept_language), _referer(ref._referer), _user_agent(ref._user_agent), _host(ref._host)
{
}

Request::~Request()
{
}
