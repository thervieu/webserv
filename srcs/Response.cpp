
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
	date += std::to_string(sec) + " GMT\n";
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
	//insert algo here...;
	this->_code = 200;
	ret += std::to_string(this->_code) + " ";
	ret += this->getMessage(this->_code) + "\n";
	return (ret);
}

std::string		Response::getLocation(std::string url)
{
	std::string	ret;

	ret = "Location: " + url + "\n";
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
		ret += "1\n";
	else if (this->_code == 301)
		ret += "3\n";
	else if (this->_code == 503)
		ret += this->getDate(1);
}

std::string		Response::getLastModified(const char *file)
{
	std::string	ret;
	struct stat	time;
	char		buff[50];

	stat(file, &time);
	ret = "Last-Modified: ";
	strftime(buff, 50, "%a, %d %b %Y %T GMT\n", localtime(time.st_mtim));
	ret += buff;
	return (ret);
}

std::string		Response::getContentLength(const char *file)
{
	std::string	ret;
	struct stat	stt;

	stat(file, &stt);
	ret = "Content-Length: ";
	ret += stt.st_size;
	return (ret);
}

std::string		Response::getExtension(std::string extension)
{
	switch (extension)
	{
		case ".aac":
			return ("audio/aac");
		case ".abw":
			return ("application/x-abiword");
		case ".arc":
			return ("application/octet-stream");
		case ".avi":
			return ("video/x-msvideo");
		case ".azw":
			return ("application/vnd.amazon.ebook");
		case ".bin":
			return ("application/octet-stream");
		case ".bmp":
			return ("image/bmp");
		case ".bz":
			return ("application/x-bzip");
		case ".bz2":
			return ("application/x-bzip2");
		case ".csh":
			return ("application/x-csh");
		case ".css":
			return ("text/css");
		case ".csv":
			return ("text/csv");
		case ".doc":
			return ("application/msword");
		case ".docx":
			return ("application/vnd.openxmlformats-officedocument.wordprocessingml.document");
		case ".eot":
			return ("application/vnd.ms-fontobject");
		case ".epub":
			return ("application/epub+zip");
		case ".gif":
			return ("image/gif");
		case ".htm":
			return ("text/html");
		case ".html":
			return ("text/html");
		case ".ico":
			return ("image/x-icon");
		case ".ics":
			return ("text/calendar");
		case ".jar":
			return ("application/java-archive");
		case ".jpeg":
			return ("image/jpeg");
		case ".jpg":
			return ("image/jpeg");
		case ".js":
			return ("application/javascript");
		case ".json":
			return ("application/json");
		case ".mid":
			return ("audio/midi");
		case ".midi":
			return ("audio/midi");
		case ".mpeg":
			return ("video/mpeg");
		case ".mpkg":
			return ("application/vnd.apple.installer+xml");
		case ".odp":
			return ("application/vnd.oasis.opendocument.presentation");
		case ".ods":
			return ("application/vnd.oasis.opendocument.spreadsheet");
		case ".odt":
			return ("application/vnd.oasis.opendocument.text");
		case ".oga":
			return ("audio/ogg");
		case ".ogv":
			return ("video/ogg");
		case ".ogx":
			return ("application/ogg");
		case ".otf":
			return ("font/otf");
		case ".png":
			return ("image/png");
		case ".pdf":
			return ("application/pdf");
		case ".ppt":
			return ("application/vnd.ms-powerpoint");
		case ".pptx":
			return ("application/vnd.openxmlformats-officedocument.presentationml.presentation");
		case ".rar":
			return ("application/x-rar-compressed");
		case ".rtf":
			return ("application/rtf");
		case ".sh":
			return ("application/x-sh");
		case ".svg":
			return ("image/svg+xml");
		case ".swf":
			return ("application/x-shockwave-flash");
		case ".tar":
			return ("application/x-tar");
		case ".tif":
			return ("image/tiff");
		case ".tiff":
			return ("image/tiff");
		case ".ts":
			return ("application/typescript");
		case ".ttf":
			return ("font/ttf");
		case ".vsd":
			return ("application/vnd.visio");
		case ".wav":
			return ("audio/x-wav");
		case ".weba":
			return ("audio/webm");
		case ".webm":
			return ("video/webm");
		case ".webp":
			return ("image/webp");
		case ".woff":
			return ("font/woff");
		case ".woff2":
			return ("font/woff2");
		case ".xhtml":
			return ("application/xhtml+xml");
		case ".xls":
			return ("application/vnd.ms-excel");
		case ".xlsx":
			return ("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
		case ".xml":
			return ("application/xml");
		case ".xul":
			return ("application/vnd.mozilla.xul+xml");
		case ".zip":
			return ("application/zip");
		case ".3gp":
			return ("video/3gpp");
		case ".3g2":
			return ("video/3gpp2");
		case ".7z":
			return ("application/x-7z-compressed");
		default:
			return ("Unknown Type");
	}
}

std::string		Response::getContentType(std::string file)
{
	std::string				ret;
	std::string::iterator	it;

	it = file.end();
	--it;
	while (*it != '.')
		--it;
	std::string	extension(it, file.end());
	ret = "Content-Type: ";
	ret += this->getExtension(extension) + "\n";
	return (ret);
}

std::string		Response::getContentLanguage()
{
	std::string	ret;

	ret = "Content-Language: en-US, fr-FR\n";
	return (ret);
}
