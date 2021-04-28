
#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Webserv.hpp"
# include "Request.hpp"

# define SEC_PER_MIN 60
# define SEC_PER_HOUR 3600
# define SEC_PER_DAY 86400
# define DAY_PER_YEAR 365.25

class Response
{

	private:

		Request			_request;
		std::string		_encoding_type;
		std::string		_content;
		int				_code;

	public:

		Response();
		Response(Response const &ref);
		Response(Request const &request);
		~Response();

		Response	&operator=(Response const &rhs);
		void		setRequest(Request request);
		int			findLocation(void);
		std::string	itos(int nb);
		std::string	itos(long nb);
		std::string	getDate(int type);
		std::string	getDay(long day);
		std::string	getNumberDay(long day);
		std::string	getCode(void);
		std::string	getMessage(int code);
		std::string	getLocation(void);
		std::string	getServer(void);
		std::string	getRetryAfter(void);
		std::string	getLastModified(void);
		std::string	getContentLength(void);
		std::string	getContentType(void);
		std::string	getExtension(std::string extension);
		std::string	getContentLanguage(void);
		std::string	getWWWAuthentificate(void);
		std::string getTransferEncoding(void);
		std::string getAllow(void);
		std::string find_error_page(void);

		std::string	sendResponse(void);
		std::string getContent(void);
};

#endif
