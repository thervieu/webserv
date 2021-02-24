
# include "../incs/Response.hpp"

Response::Response() : _request(Request())
{
}

Response::Response(Request const &request) : _request(request)
{
}

Response::Response(Response const &ref) : _request(ref._request)
{
}

Response::~Response()
{
}
