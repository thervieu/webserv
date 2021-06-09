
#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Webserv.hpp"
# include "Request.hpp"
//# include "CGI.hpp"

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
		location		_location;

	public:

		Response();
		Response(Response const &ref);
		Response(Request const &request);
		~Response();

		Response			&operator=(Response const &rhs);
		void				setRequest(Request request);
		int					findLocation(std::string cpy);
		std::string			itos(int nb);
		std::string			itos(long nb);
		std::string			getDate(int type);
		std::string			getDay(long day);
		std::string			getNumberDay(long day);
		std::string			getCode(void);
		std::string			getMessage(int code);
		std::string			getLocation(void);
		std::string			getServer(void);
		std::string			getRetryAfter(void);
		std::string			getLastModified(void);
		std::string			getContentLength(void);
		std::string			getContentType(void);
		std::string			getExtension(std::string extension);
		std::string			getContentLanguage(void);
		std::string			getWWWAuthentificate(void);
		std::string 		getTransferEncoding(void);
		std::string 		getAllow(void);
		std::string 		find_error_page(void);
		std::string			findIndex(void);


		location			getLocation(std::string url, std::vector<location> locations);

		bool				isAllowedMethod(void);

		std::vector<char>	GETResponse(void);
		std::vector<char>	POSTResponse(void);
		std::vector<char>	DELETEResponse(void);
		// std::vector<char>	TRACEResponse(void);
		// std::vector<char>	OPTIONSResponse(void);
		std::vector<char>	wrongMethodReponse(void);

		std::vector<char>	sendResponse(void);
		std::vector<char>	getContent(void);
};

#endif
