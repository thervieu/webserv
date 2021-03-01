
# include "../incs/Response.hpp"

Response::Response() : _request(Request()), _code(0), _encoding_type("plain")
{
}

Response::Response(Request const &request) : _request(request), _code(0), _encoding_type("plain")
{
}

Response::Response(Response const &ref) : _request(ref._request), _code(ref._code), _encoding_type(ref._encoding_type)
{
}

Response::~Response()
{
}

std::string		Response::getNumberDay(long nbday)
{
	long		nbyear;
	std::string ret;

	ret = "";
	nbyear = nbday / DAY_PER_YEAR;
	nbday -= DAY_PER_YEAR * nbyear;
	if (nbday < 31)
	{
		if (nbday < 10)
			ret += "0" + std::to_string(nbday + 1);
		else
			ret += std::to_string(nbday + 1);
		ret += " Jan " + std::to_string(nbyear + 1970);
		return (ret);
	}
	nbday -= 31;
	if (nbday < 28)
	{
		if (nbday < 10)
			ret += "0" + std::to_string(nbday + 1);
		else
			ret += std::to_string(nbday + 1);
		ret += " Feb " + std::to_string(nbyear + 1970);
		return (ret);
	}
	nbday -= 28;
	if (nbday < 31)
	{
		if (nbday < 10)
			ret += "0" + std::to_string(nbday + 1);
		else
			ret += std::to_string(nbday + 1);
		ret += " Mar " + std::to_string(nbyear + 1970);
		return (ret);
	}
	nbday -= 31;
	if (nbday < 30)
	{
		if (nbday < 10)
			ret += "0" + std::to_string(nbday + 1);
		else
			ret += std::to_string(nbday + 1);
		ret += " Apr " + std::to_string(nbyear + 1970);
		return (ret);
	}
	nbday -= 30;
	if (nbday < 31)
	{
		if (nbday < 10)
			ret += "0" + std::to_string(nbday + 1);
		else
			ret += std::to_string(nbday + 1);
		ret += " May " + std::to_string(nbyear + 1970);
		return (ret);
	}
	nbday -= 31;
	if (nbday < 30)
	{
		if (nbday < 10)
			ret += "0" + std::to_string(nbday + 1);
		else
			ret += std::to_string(nbday + 1);
		ret += " Jun " + std::to_string(nbyear + 1970);
		return (ret);
	}
	nbday -= 30;
	if (nbday < 31)
	{
		if (nbday < 10)
			ret += "0" + std::to_string(nbday + 1);
		else
			ret += std::to_string(nbday + 1);
		ret += " Jul " + std::to_string(nbyear + 1970);
		return (ret);
	}
	nbday -= 31;
	if (nbday < 31)
	{
		if (nbday < 10)
			ret += "0" + std::to_string(nbday + 1);
		else
			ret += std::to_string(nbday + 1);
		ret += " Aug " + std::to_string(nbyear + 1970);
		return (ret);
	}
	nbday -= 31;
	if (nbday < 30)
	{
		if (nbday < 10)
			ret += "0" + std::to_string(nbday + 1);
		else
			ret += std::to_string(nbday + 1);
		ret += " Sep " + std::to_string(nbyear + 1970);
		return (ret);
	}
	nbday -= 30;
	if (nbday < 31)
	{
		if (nbday < 10)
			ret += "0" + std::to_string(nbday + 1);
		else
			ret += std::to_string(nbday + 1);
		ret += " Oct " + std::to_string(nbyear + 1970);
		return (ret);
	}
	nbday -= 31;
	if (nbday < 30)
	{
		if (nbday < 10)
			ret += "0" + std::to_string(nbday + 1);
		else
			ret += std::to_string(nbday + 1);
		ret += " Nov " + std::to_string(nbyear + 1970);
		return (ret);
	}
	nbday -= 30;
	if (nbday < 10)
		ret += "0" + std::to_string(nbday + 1);
	else
		ret += std::to_string(nbday + 1);
	ret += " Dec " + std::to_string(nbyear + 1970);
	return (ret);
}

std::string		Response::getDay(long day)
{
	day = day % 7;
	switch (day)
	{
		case 0:
			return ("Thu, ");
		case 1:
			return ("Fri, ");
		case 2:
			return ("Sat, ");
		case 3:
			return ("Sun, ");
		case 4:
			return ("Mon, ");
		case 5:
			return ("Tue, ");
		case 6:
			return ("Wed, ");
	}
}

std::string		Response::getDate(int type)
{
	struct timeval	tv;
	struct timezone	tz;
	long			day;
	std::string		date;

	date = "";
	if (type == 0)
		date = "Date: ";
	gettimeofday(&tv, &tz);

	if (type == 1)
		tv.tv_sec += SEC_PER_DAY;
	day = tv.tv_sec / SEC_PER_DAY;
	long hms = tv.tv_sec % SEC_PER_DAY;

	hms += tz.tz_dsttime * SEC_PER_HOUR;
	hms -= tz.tz_minuteswest * SEC_PER_MIN;
	hms = (hms + SEC_PER_DAY) % SEC_PER_DAY;

	int hour = hms / SEC_PER_HOUR + 1;
	int min = (hms % SEC_PER_HOUR) / SEC_PER_MIN;
	int sec = (hms % SEC_PER_HOUR) % SEC_PER_MIN;
	
	date.append(this->getDay(day));
	date.append(this->getNumberDay(day));
	date.push_back(' ');
	if (hour < 10)
		date.push_back('0');
	date += std::to_string(hour) + ":";
	if (min < 10)
		date.push_back('0');
	date += std::to_string(min) + ":";
	if (sec < 10)
		date.push_back('0');
	date += std::to_string(sec) + " GMT";
	return (date);
}

std::string		Response::getMessage(int code)
{
	switch (code)
	{
		case 200:
			return ("OK");
		case 201:
			return ("Created");
		case 202:
			return ("Accepted");
		case 301:
			return ("Moved Permanently");
		case 302:
			return ("Found");
		case 401:
			return ("Unauthorized");
		case 403:
			return ("Forbidden");
		case 404:
			return ("Not Found");
		case 405:
			return ("Method Not Allowed");
		case 406:
			return ("Not Acceptable");
		case 429:
			return ("Too Many Requests");
		case 500:
			return ("Internal Server Error");
		case 504:
			return ("Gateway Time-Out");
	}
}

std::string		Response::getCode()
{
	std::string	ret;

	ret = "HTTP/1.1 ";
	ret += std::to_string(this->_code) + " ";
	ret += this->getMessage(this->_code);
	return (ret);
}

std::string		Response::getLocation()
{
	std::string	ret;

	ret = "Location: " + this->_content;
	return (ret);
}

std::string		Response::getServer()
{
	std::string ret;

	ret = "Server: Webserv/1.0";
	return (ret);
}

std::string		Response::getRetryAfter()
{
	std::string	ret;

	ret = "Retry-After: ";
	if (this->_code == 429)
		ret += "1";
	else if (this->_code == 301 || this->_code == 302)
		ret += "3";
	else if (this->_code == 504)
		ret += this->getDate(1);
}

std::string		Response::getLastModified()
{
	std::string	ret;
	struct stat	time;
	char		buff[50];

	stat(this->_content.c_str(), &time);
	ret = "Last-Modified: ";
	//strftime(buff, 50, "%a, %d %b %Y %T GMT\n", localtime(&(time.st_mtim)));
	//ret += buff;
	return (ret);
}

std::string		Response::getContentLength()
{
	std::string	ret;
	struct stat	stt;

	stat(this->_content.c_str(), &stt);
	ret = "Content-Length: ";
	ret += stt.st_size;
	return (ret);
}

std::string		Response::getExtension(std::string extension)
{
	if (extension.compare(".aac") == 0)
		return ("audio/aac");
	if (extension.compare(".abw") == 0)
		return ("application/x-abiword");
	if (extension.compare(".arc") == 0)
		return ("application/octet-stream");
	if (extension.compare(".avi") == 0)
		return ("video/x-msvideo");
	if (extension.compare(".azw") == 0)
		return ("application/vnd.amazon.ebook");
	if (extension.compare(".bin") == 0)
		return ("application/octet-stream");
	if (extension.compare(".bmp") == 0)
		return ("image/bmp");
	if (extension.compare(".bz") == 0)
		return ("application/x-bzip");
	if (extension.compare(".bz2") == 0)
		return ("application/x-bzip2");
	if (extension.compare(".csh") == 0)
		return ("application/x-csh");
	if (extension.compare(".css") == 0)
		return ("text/css");
	if (extension.compare(".csv") == 0)
		return ("text/csv");
	if (extension.compare(".doc") == 0)
		return ("application/msword");
	if (extension.compare(".docx") == 0)
		return ("application/vnd.openxmlformats-officedocument.wordprocessingml.document");
	if (extension.compare(".eot") == 0)
		return ("application/vnd.ms-fontobject");
	if (extension.compare(".epub") == 0)
		return ("application/epub+zip");
	if (extension.compare(".gif") == 0)
		return ("image/gif");
	if (extension.compare(".htm") == 0)
		return ("text/html");
	if (extension.compare(".html") == 0)
		return ("text/html");
	if (extension.compare(".ico") == 0)
		return ("image/x-icon");
	if (extension.compare(".ics") == 0)
		return ("text/calendar");
	if (extension.compare(".jar") == 0)
		return ("application/java-archive");
	if (extension.compare(".jpeg") == 0)
		return ("image/jpeg");
	if (extension.compare(".jpg") == 0)
		return ("image/jpeg");
	if (extension.compare(".js") == 0)
		return ("application/javascript");
	if (extension.compare(".json") == 0)
		return ("application/json");
	if (extension.compare(".mid") == 0)
		return ("audio/midi");
	if (extension.compare(".midi") == 0)
		return ("audio/midi");
	if (extension.compare(".mpeg") == 0)
		return ("video/mpeg");
	if (extension.compare(".mpkg") == 0)
		return ("application/vnd.apple.installer+xml");
	if (extension.compare(".odp") == 0)
		return ("application/vnd.oasis.opendocument.presentation");
	if (extension.compare(".ods") == 0)
		return ("application/vnd.oasis.opendocument.spreadsheet");
	if (extension.compare(".odt") == 0)
		return ("application/vnd.oasis.opendocument.text");
	if (extension.compare(".oga") == 0)
		return ("audio/ogg");
	if (extension.compare(".ogv") == 0)
		return ("video/ogg");
	if (extension.compare(".ogx") == 0)
		return ("application/ogg");
	if (extension.compare(".otf") == 0)
		return ("font/otf");
	if (extension.compare(".png") == 0)
		return ("image/png");
	if (extension.compare(".pdf") == 0)
		return ("application/pdf");
	if (extension.compare(".ppt") == 0)
		return ("application/vnd.ms-powerpoint");
	if (extension.compare(".pptx") == 0)
		return ("application/vnd.openxmlformats-officedocument.presentationml.presentation");
	if (extension.compare(".rar") == 0)
		return ("application/x-rar-compressed");
	if (extension.compare(".rtf") == 0)
		return ("application/rtf");
	if (extension.compare(".sh") == 0)
		return ("application/x-sh");
	if (extension.compare(".svg") == 0)
		return ("image/svg+xml");
	if (extension.compare(".swf") == 0)
		return ("application/x-shockwave-flash");
	if (extension.compare(".tar") == 0)
		return ("application/x-tar");
	if (extension.compare(".tif") == 0)
		return ("image/tiff");
	if (extension.compare(".tiff") == 0)
		return ("image/tiff");
	if (extension.compare(".ts") == 0)
		return ("application/typescript");
	if (extension.compare(".ttf") == 0)
		return ("font/ttf");
	if (extension.compare(".vsd") == 0)
		return ("application/vnd.visio");
	if (extension.compare(".wav") == 0)
		return ("audio/x-wav");
	if (extension.compare(".weba") == 0)
		return ("audio/webm");
	if (extension.compare(".webm") == 0)
		return ("video/webm");
	if (extension.compare(".webp") == 0)
		return ("image/webp");
	if (extension.compare(".woff") == 0)
		return ("font/woff");
	if (extension.compare(".woff2") == 0)
		return ("font/woff2");
	if (extension.compare(".xhtml") == 0)
		return ("application/xhtml+xml");
	if (extension.compare(".xls") == 0)
		return ("application/vnd.ms-excel");
	if (extension.compare(".xlsx") == 0)
		return ("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
	if (extension.compare(".xml") == 0)
		return ("application/xml");
	if (extension.compare(".xul") == 0)
		return ("application/vnd.mozilla.xul+xml");
	if (extension.compare(".zip") == 0)
		return ("application/zip");
	if (extension.compare(".3gp") == 0)
		return ("video/3gpp");
	if (extension.compare(".3g2") == 0)
		return ("video/3gpp2");
	if (extension.compare(".7z") == 0)
		return ("application/x-7z-compressed");
	else
		return ("text/plain");
}

std::string		Response::getContentType()
{
	std::string				ret;
	std::string::iterator	it;

	it = this->_content.end();
	--it;
	while (*it != '.')
		--it;
	std::string	extension(it, this->_content.end());
	ret = "Content-Type: ";
	ret += this->getExtension(extension);
	return (ret);
}

std::string		Response::getContentLanguage()
{
	std::string	ret;

	ret = "Content-Language: en-US, fr-FR";
	return (ret);
}

std::string		Response::getWWWAuthentificate()
{
	std::string ret;

	ret = "WWW-Authentificate: basic realm=\"localhost\"";
	return (ret);
}

std::string		Response::getTransferEncoding()
{
	std::string ret;

	if (this->_encoding_type.compare("plain"))
		return ("");
	ret = "Transfer-Encoding: " + this->_encoding_type;
	return (ret);
}

std::string		Response::sendResponse()
{
	std::string	response;

	//insert algo here...
	this->_content = "/server-documents/index.html";
	this->_code = 200;
	this->_encoding_type = "plain"; // substitute of algo for now

	if (this->_encoding_type.compare("plain") == 0)
	{
		response = this->getCode() + "\n\n";
		response += this->getDate(0) + "\n";
		response += this->getServer() + "\n";
		if (this->_code < 400)
		{
			response += this->getTransferEncoding() + "\n";
			response += this->getContentType() + "\n";
			response += this->getContentLength() + "\n";
			response += this->getContentLanguage() + "\n";
			response += this->getLastModified() + "\n";
			if (this->_code == 301 || this->_code == 302)
			{
				response += this->getLocation();
				response += this->getRetryAfter();
			}
		}
		else
		{
			if (this->_code == 401)
				response += this->getWWWAuthentificate() + "\n";
		}
	}
	/*std::cout << response << std::endl;*/
	return (response);
}
