
# include "../incs/Response.hpp"

Response::Response() : _encoding_type("plain"), _content(""), _code(0)
{
}

Response::Response(Request const &request) : _request(request), _encoding_type("plain"), _content(""), _code(0)
{
}

Response::Response(Response const &ref) : _request(ref._request),  _encoding_type(ref._encoding_type), _content(ref._content), _code(ref._code)
{
}

Response::~Response()
{
}

void				Response::setRequest(Request & request)
{
	_request = request;
}

std::string			Response::itos(int nb)
{
	std::string			ret;
	std::stringstream	conv;

	conv << nb;
	ret = conv.str();
	return (ret);
}

std::string			Response::itos(long nb)
{
	std::string			ret;
	std::stringstream	conv;

	conv << nb;
	ret = conv.str();
	return (ret);
}

std::string			Response::getNumberDay(long nbday)
{
	long		nbyear;
	std::string ret;

	ret = "";
	nbyear = nbday / DAY_PER_YEAR;
	nbday -= DAY_PER_YEAR * nbyear;
	if (nbday < 31)
	{
		if (nbday < 10)
			ret += "0" + this->itos(nbday + 1);
		else
			ret += this->itos(nbday + 1);
		ret += " Jan " + this->itos(nbyear + 1970);
		return (ret);
	}
	nbday -= 31;
	if (nbday < 28)
	{
		if (nbday < 10)
			ret += "0" + this->itos(nbday + 1);
		else
			ret += this->itos(nbday + 1);
		ret += " Feb " + this->itos(nbyear + 1970);
		return (ret);
	}
	nbday -= 28;
	if (nbday < 31)
	{
		if (nbday < 10)
			ret += "0" + this->itos(nbday + 1);
		else
			ret += this->itos(nbday + 1);
		ret += " Mar " + this->itos(nbyear + 1970);
		return (ret);
	}
	nbday -= 31;
	if (nbday < 30)
	{
		if (nbday < 10)
			ret += "0" + this->itos(nbday + 1);
		else
			ret += this->itos(nbday + 1);
		ret += " Apr " + this->itos(nbyear + 1970);
		return (ret);
	}
	nbday -= 30;
	if (nbday < 31)
	{
		if (nbday < 10)
			ret += "0" + this->itos(nbday + 1);
		else
			ret += this->itos(nbday + 1);
		ret += " May " + this->itos(nbyear + 1970);
		return (ret);
	}
	nbday -= 31;
	if (nbday < 30)
	{
		if (nbday < 10)
			ret += "0" + this->itos(nbday + 1);
		else
			ret += this->itos(nbday + 1);
		ret += " Jun " + this->itos(nbyear + 1970);
		return (ret);
	}
	nbday -= 30;
	if (nbday < 31)
	{
		if (nbday < 10)
			ret += "0" + this->itos(nbday + 1);
		else
			ret += this->itos(nbday + 1);
		ret += " Jul " + this->itos(nbyear + 1970);
		return (ret);
	}
	nbday -= 31;
	if (nbday < 31)
	{
		if (nbday < 10)
			ret += "0" + this->itos(nbday + 1);
		else
			ret += this->itos(nbday + 1);
		ret += " Aug " + this->itos(nbyear + 1970);
		return (ret);
	}
	nbday -= 31;
	if (nbday < 30)
	{
		if (nbday < 10)
			ret += "0" + this->itos(nbday + 1);
		else
			ret += this->itos(nbday + 1);
		ret += " Sep " + this->itos(nbyear + 1970);
		return (ret);
	}
	nbday -= 30;
	if (nbday < 31)
	{
		if (nbday < 10)
			ret += "0" + this->itos(nbday + 1);
		else
			ret += this->itos(nbday + 1);
		ret += " Oct " + this->itos(nbyear + 1970);
		return (ret);
	}
	nbday -= 31;
	if (nbday < 30)
	{
		if (nbday < 10)
			ret += "0" + this->itos(nbday + 1);
		else
			ret += this->itos(nbday + 1);
		ret += " Nov " + this->itos(nbyear + 1970);
		return (ret);
	}
	nbday -= 30;
	if (nbday < 10)
		ret += "0" + this->itos(nbday + 1);
	else
		ret += this->itos(nbday + 1);
	ret += " Dec " + this->itos(nbyear + 1970);
	return (ret);
}

std::string			Response::getDay(long day)
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
		default:
			return ("Wtf, ");
	}
}

std::string			Response::getDate(int type)
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

	int hour = hms / SEC_PER_HOUR + 2;
	int min = (hms % SEC_PER_HOUR) / SEC_PER_MIN;
	int sec = (hms % SEC_PER_HOUR) % SEC_PER_MIN;
	
	date.append(this->getDay(day));
	date.append(this->getNumberDay(day));
	date.push_back(' ');
	if (hour < 10)
		date.push_back('0');
	date += this->itos(hour) + ":";
	if (min < 10)
		date.push_back('0');
	date += this->itos(min) + ":";
	if (sec < 10)
		date.push_back('0');
	date += this->itos(sec) + " GMT";
	return (date);
}

std::string			Response::getMessage(int code)
{
	switch (code)
	{
		case 200:
			return ("OK");
		case 201:
			return ("Created");
		case 202:
			return ("Accepted");
		case 204:
			return ("No Content");
		case 301:
			return ("Moved Permanently");
		case 302:
			return ("Found");
		case 307:
			return ("Temporary Redirect");
		case 400:
			return ("Bad Request");
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
		case 413:
			return ("Request entity too large");
		case 429:
			return ("Too Many Requests");
		case 500:
			return ("Internal Server Error");
		case 501:
			return ("Not Implemented");
		case 504:
			return ("Gateway Time-Out");
		case 505:
			return ("HTTP Version Not Supported");
		default:
			return ("Error Not Found");
	}
}

std::string			Response::getCode()
{
	std::string	ret;

	ret = "HTTP/1.1 ";
	ret += this->itos(this->_code) + " ";
	ret += this->getMessage(this->_code);
	return (ret);
}

std::string			Response::getLocation()
{
	std::string	ret;

	ret = "Location: " + this->_content;
	return (ret);
}

std::string			Response::getServer()
{
	std::string ret;

	ret = "Server: Webserv/1.0";
	return (ret);
}

std::string			Response::getRetryAfter()
{
	std::string	ret;

	ret = "Retry-After: ";
	if (this->_code == 429)
		ret += "1";
	else if (this->_code == 301 || this->_code == 302)
		ret += "3";
	else if (this->_code == 504)
		ret += this->getDate(1);
	return (ret);
}

std::string			Response::getLastModified()
{
	std::string	ret;
	struct stat	time;
	char		buff[50];

	stat(this->_content.c_str(), &time);
	ret = "Last-Modified: ";
	strftime(buff, 50, "%a, %d %b %Y %T GMT", localtime(&(time.st_mtim.tv_sec)));
	ret += buff;
	return (ret);
}

#include <string.h>

std::string			Response::getContentLength()
{
	std::string	ret;
	struct stat	stt;

	stat(this->_content.c_str(), &stt);
	ret = "Content-Length: ";
	ret += this->itos(stt.st_size);
	return (ret);
}

std::string			Response::getExtension(std::string extension)
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

std::string			Response::getContentType()
{
		std::string				ret;
	if (this->_content.length() < 1000000)
	{
		std::string::iterator	it;

		it = this->_content.end();
		--it;
		while (*it != '.')
			--it;
		std::string	extension(it, this->_content.end());
		ret = "Content-Type: ";
		ret += this->getExtension(extension);
	}
	else
	{
		ret = "Content-Type: ";
		ret += this->getExtension("");
	}
	return (ret);
}

std::string			Response::getContentLanguage()
{
	std::string	ret;

	ret = "Content-Language: en-US, fr-FR";
	return (ret);
}

std::string			Response::getWWWAuthentificate()
{
	std::string ret;

	ret = "WWW-Authentificate: basic realm=\"localhost\"";
	return (ret);
}

std::string			Response::getTransferEncoding()
{
	std::string ret;

	if (this->_encoding_type.compare("plain") == 0)
		return ("");
	ret = "Transfer-Encoding: " + this->_encoding_type;
	return (ret);
}

std::string			Response::getAllow()
{
	std::string		cpy;
	std::string		ret;
	unsigned int	i;

	ret = "Allow:";
	cpy.assign(this->_content.begin() + 18, this->_content.end());
	while (ret.size() == 6 && cpy.size() > 0)
	{
		i = -1;
		ret += " ";
		if (this->_location._methods.size() != 0)
		{
			while (++i < this->_location._methods.size() - 1)
				ret += this->_location._methods[i] + ", ";
			ret += this->_location._methods[i];
		}
		do
		{
			cpy = cpy.substr(0, cpy.size() - 1);
		} while (cpy[cpy.size() - 1] != '/' && cpy.size() > 0);
	}
	if (ret.size() == 6)
		ret += " GET, HEAD, OPTIONS";
	return (ret);
}

std::vector<char>	Response::getContent()
{
	std::vector<char> file;
	char buffer[1];
	int rtn_value;
	int fd;

	fd = open(this->_content.c_str(), O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		this->_code = 403;
		this->_content = this->_root + find_error_page();
		fd = open(this->_content.c_str(), O_RDONLY);
		if (fd == -1)
		{
			close(fd);
			this->_content = this->_root + "error.html";
			fd = open(this->_content.c_str(), O_RDONLY);
		}
	}
	while (fd >= 0 && (rtn_value = read(fd, buffer, 1)) > 0)
		file.push_back(buffer[0]);
	close(fd);
	return (file);
}

std::vector<char>	Response::getAutoindex(void)
{
	size_t						pos;
	size_t						pos2;
	DIR							*directory;
	struct dirent				*file;
	std::stringstream			ss;
	std::string					rep;
	std::string					file_to_open;
	std::string					repeated_line;
	std::string					tmp;
	std::string					str;
	std::vector<std::string>	repeated_lines;
	char						buffer[1];
	int							rtn_value;
	int 						fd;

	//open html template
	fd = open("./srcs/autoindex.html", O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		this->_code = 403;
		this->_content = this->_root + find_error_page();
		fd = open(this->_content.c_str(), O_RDONLY);
		if (fd == -1)
		{
			close(fd);
			this->_content = this->_root + "error.html";
			fd = open(this->_content.c_str(), O_RDONLY);
		}
	}
	while (fd >= 0 && (rtn_value = read(fd, buffer, 1)) > 0)
		rep.push_back(buffer[0]);
	close(fd);

	//open directory
	if (this->_root.compare("." + this->_request.getConfig()._root.substr(0, this->_request.getConfig()._root.size() - (this->_request.getConfig()._root[this->_request.getConfig()._root.size() - 1] == '/' ? 1 : 0))) != 0)
		file_to_open = this->_root;
	else
		file_to_open = this->_root + this->_location._name;
	directory = opendir(file_to_open.c_str());
	if (directory == NULL || this->_content.compare("ERROR") == 0)
	{
		rep = "ERROR: directory could not be opened.";
		return (std::vector<char>(rep.begin(), rep.end()));
	}

	//replace html variables
	while ((pos = rep.find("$d_name", 0)) != std::string::npos)
		rep.replace(pos, strlen("$d_name"), this->_location._name);
	pos = rep.find("$repeat");
	pos2 = rep.find("\n", pos);
	repeated_line = rep.substr(pos, pos2 - pos + 1);
	while ((file = readdir(directory)) != NULL)
	{
		tmp = repeated_line;
		tmp.replace(0, strlen("$repeat"), "");
		ss.str("");
		ss.clear();
		ss << file->d_reclen;
		tmp.replace(tmp.find("$size"), strlen("$size"), ss.str());
		//std::cout << "||| " << this->_location._name << std::endl << file->d_name << " |||" << std::endl;
		str = this->_location._name + file->d_name;
		tmp.replace(tmp.find("$name"), strlen("$name"), str);
		tmp.replace(tmp.find("$name"), strlen("$name"), file->d_name);
		repeated_lines.push_back(tmp);
	}
	std::sort(repeated_lines.begin(), repeated_lines.end());
	tmp = "";
	for (size_t i = 0; i < repeated_lines.size(); i++)
		tmp.append(repeated_lines[i]);
	pos = rep.find("$repeat");
	pos2 = rep.find("\n", pos);
	rep.replace(pos, pos2 - pos + 1, tmp);
	closedir(directory);
	return (std::vector<char>(rep.begin(), rep.end()));
}

std::string			Response::find_error_page(void)
{
	unsigned int		i;
	std::ostringstream	convert;
	std::string			code;

	i = 0;
	convert << this->_code;
	code = convert.str();
	// std::cout << "ERROR+PGES\n";
	while (i < this->_request.getConfig()._error_pages.size() && this->_request.getConfig()._error_pages[i].compare(code) != 0)
		i += 2;
	// std::cout << "i = " << i << "\n";
	if (i < this->_request.getConfig()._error_pages.size())
		return (this->_request.getConfig()._error_pages[i + 1]);
	// std::cout << "DEFAULT ERROR\n";
	return ("/error_pages/error.html");
}

std::string			Response::findIndex(void)
{
	std::string		cpy;
	std::string		ret;

	ret = this->_content;
	cpy.assign(this->_content.begin() - this->_root.size(), this->_content.end());
	if (this->_location._index.compare("") != 0)
	{
		int rtn;
		rtn = -5;
		struct stat sb;
		if ((rtn = stat(ret.c_str(), &sb)) == 0 && (rtn = S_ISREG(sb.st_mode)) == 1)
			return (ret);
		else
			this->_code = 404;
	}
	else if (this->_location._autoindex == true)
		ret = "autoindex.html";
	else
		ret = "forbidden";
	return (ret);
}

std::vector<char>	Response::changeContent(std::vector<char> content)
{
	size_t						i;
	std::vector<std::string>	arguments;
	std::string					to_change;
	std::vector<char>::iterator		it;
	std::vector<char>::iterator		ite;
	std::string					tmp;

	arguments = this->_request.getArguments();
	for (size_t j = 0; j < content.size(); j++)
	{
		if (content[j] == '$')
		{
			++j;
			it = content.begin() + j;
			while (content[j] != '$' && content[j] != '\0')
				++j;
			if (content[j] == 0)
				break;
			ite = content.begin() + j;
			to_change.assign(it, ite);
			i = 0;
			while (i < arguments.size())
			{
				if (arguments[i].compare(to_change) == 0)
				{
					content.erase(it - 1, ite + 1);
					it = content.begin() + j - to_change.length() - 1;
					j = 0;
					content.insert(it, arguments[i + 1].begin(), arguments[i + 1].end());
					break;
				}
				i += 2;
			}
		}
	}
	return (content);
}

#include <cerrno>

std::string	Response::upload(void)
{
	int fd;
	struct stat			filestat;
	
	size_t pos = _request.getURL().rfind("/");
	
	std::string urlFile = _request.getURL().substr(pos + 1 , _request.getURL().length() - pos - 1);
	std::string path = this->_root + _location._upload_path + (_location._upload_path[_location._upload_path.size() - 1] == '/' ? "" : "/") + urlFile;

	int ret = stat(path.c_str(), &filestat);
	
	if (ret == 0 && S_ISREG(filestat.st_mode))
	{
		if ((fd = open(path.c_str(), O_WRONLY | O_TRUNC, 0644)) == -1)
		{
			std::cerr << "could not open " << path << std::endl;
			throw std::exception();
		}
		write(fd, _request.getContent().c_str(), _request.getContent().length());
		close(fd);
		this->_code = 200;
		path = "Content-Location: " + path;
	}
	else
	{
		if ((fd = open(path.c_str(), O_CREAT | O_APPEND | O_WRONLY, 0644)) == -1)
		{
			std::cerr << "could not create " << path << std::endl;
			throw std::exception();
		}
		write(fd, _request.getContent().c_str(), _request.getContent().length());
		close(fd);
		this->_code = 201;
		path = "Location: " + path;
	}
	return (path);
}

std::vector<char>	Response::MAINResponse(void)
{
	std::string			response;
	std::vector<char>	file_content;
	std::vector<char>	f_response;
	std::stringstream	ss;
	std::string upload_rtn;

	if (this->_encoding_type.compare("plain") == 0)
	{
		if ((this->_code > 500 && this->_code < 600) || this->_code == 413 || this->_code == 404 || this->_code == 405 || this->_code == 403 || this->_code == 400)
		{
			this->_content = "." + this->_request.getConfig()._root;
			this->_content = this->_content.substr(0, this->_content.size() - 1) + find_error_page();
		}
		if (this->_content.compare("autoindex.html") != 0 && (this->_code != 301 && this->_code != 307) && _cgi == false)
		{
			file_content = this->getContent();
			file_content = this->changeContent(file_content);
		}
		if (_request.getMethod().compare("POST") == 0 && _location._upload_path.length() != 0)
			upload_rtn = upload();
		response = this->getCode() + "\r\n";
		if (this->_code == 301 || this->_code == 302 || this->_code == 307)
		{
			response += this->getLocation() + "\r\n";
			response += this->getRetryAfter() + "\r\n";
		}
		if (_request.getMethod().compare("POST") == 0 && _location._upload_path.length() != 0)
			response += upload_rtn + "\r\n";
		response += this->getDate(0) + "\r\n";
		response += this->getServer() + "\r\n";
		if (this->_code == 401)
			response += this->getWWWAuthentificate() + "\r\n";
		if (this->_code == 405)
			response += this->getAllow() + "\r\n";
		if (this->_code == 429 || this->_code == 504)
			response += this->getRetryAfter() + "\r\n";
		if (this->_content.compare("autoindex.html") == 0)
		{
			file_content = this->getAutoindex();
			ss << file_content.size();
			response += "Content-Length: " + ss.str() + "\r\n";
		}
		else
		{
			if (_cgi == true)
			{
				for (size_t i = 0; i < _content.size(); i++)
					file_content.push_back(_content[i]);
			}
			ss << file_content.size();
			response += "Content-Length: " + ss.str() + "\r\n";
			response += this->getLastModified() + "\r\n";
		}
		response += this->getTransferEncoding();
		response += this->getContentType() + "\r\n";
		response += this->getContentLanguage() + "\r\n\r\n";
		f_response.assign(response.begin(), response.end());
		if (this->_request.getMethod().compare("GET") == 0 || this->_request.getMethod().compare("POST") == 0)
			std::copy(file_content.begin(), file_content.end(), std::back_inserter<std::vector<char> >(f_response));
	}
	return (f_response);
}

std::vector<char>		Response::DELETEResponse(void)
{
	std::string			response;
	std::vector<char>	f_response;

	if (std::remove(this->_content.c_str()) != 0)
		this->_code = 404;
	else
		this->_code = 204;
	response = this->getCode() + "\r\n";
	response += this->getDate(0) + "\r\n";
	if (this->_code == 404)
	{

		this->_content = "." + this->_request.getConfig()._root;
		this->_content = this->_content.substr(0, this->_content.size() - 1) + find_error_page();

		response += this->getServer() + "\r\n";
		response += this->getContentType() + "\r\n";
		response += this->getContentLength() + "\r\n";
		response += this->getContentLanguage() + "\r\n";
		response += this->getLastModified() + "\r\n\r\n";
		f_response.assign(response.begin(), response.end());
		
		std::vector<char> file_content = this->getContent();
		std::copy(file_content.begin(), file_content.end(), std::back_inserter<std::vector<char> >(f_response));
		return (f_response);
	}
	response += "\r\n";
	f_response.assign(response.begin(), response.end());
	return (f_response);
}

std::vector<char>		Response::wrongMethodReponse(void)
{
	std::string			response;
	std::vector<char>	f_response;
	std::vector<char>	file_content;

	this->_code = 405;
	this->_content = "." + this->_request.getConfig()._root;
	this->_content = this->_content.substr(0, this->_content.size() - 1) + find_error_page();
	response = this->getCode() + "\r\n";
	response += this->getDate(0) + "\r\n";
	response += this->getServer() + "\r\n";
	response += this->getContentType() + "\r\n";
	response += this->getContentLength() + "\r\n";
	response += this->getContentLanguage() + "\r\n";
	response += this->getLastModified() + "\r\n\r\n";
	f_response.assign(response.begin(), response.end());
	file_content = this->getContent();
	std::copy(file_content.begin(), file_content.end(), std::back_inserter<std::vector<char> >(f_response));
	return (f_response);
}

std::vector<char>		Response::OPTIONSResponse(void)
{
	std::vector<char>	f_response;
	std::string			response;

	this->_code = 200;
	response = this->getCode() + "\r\n";
	response += this->getDate(0) + "\r\n";
	response += this->getServer() + "\r\n";
	response += "Content-Length: 0\r\n";
	response += this->getAllow() + "\r\n\r\n";
	f_response.assign(response.begin(), response.end());
	return (f_response);
}


location	Response::getLocation(std::string url, std::vector<location> locations)
{
	if (url[url.size() - 1] != '/')
		url.append("/");
	for (size_t i = 0; i < locations.size(); i++)
	{
		if (locations[i]._name == url)
			return (locations[i]);
	}

	size_t max_len = 0;
	size_t max_index = 0;

	for (size_t i = 0; i < locations.size(); i++)
	{
		if (url.rfind(locations[i]._name, 0) == 0)
		{
			if (locations[i]._name.size() > max_len)
			{
				max_index = i;
				max_len = locations[i]._name.size();
			}
		}
	}
	return (locations[max_index]);
}

bool		Response::VerifyHost(void) const
{
	std::ostringstream	convert;
	std::string			tmp;

	convert << this->_request.getConfig()._port;
	for (size_t i = 0; i < this->_request.getConfig()._names.size(); i++)
	{
		tmp = this->_request.getConfig()._names[i] + ":" + convert.str();
		if (tmp.compare(this->_request.getHost()) == 0)
			return (true);
	}
	tmp = this->_request.getConfig()._host + ":" + convert.str();
	if (tmp.compare(this->_request.getHost()) == 0)
		return (true);
	return (false);
}

bool		Response::IsCGICalled(std::string url)
{
	size_t dot;

	dot = url.rfind(".");
	if (dot == std::string::npos)
		return (false);
	std::string extension = url.substr(dot, url.length() - dot);
	for (size_t i = 0; i < _location._cgi_extensions.size(); i++)
	{
		if (extension.compare(_location._cgi_extensions[i]) == 0)
			return (true);
	}
	return (false);
}

bool Response::isAllowedMethod(void)
{
	for (size_t i = 0; i < _location._methods.size(); i++)
	{
		if (_request.getMethod().compare(_location._methods[i]) == 0)
			return (true);
	}
	return (false);
}

std::string		getScriptName(std::string url)
{
	size_t pos = url.rfind("/");

	std::string name = url.substr(pos + 1, url.length() - (pos + 1));
	return (name);
}

void					Response::VerifyRedirection()
{
	size_t		i;
	std::string	str;

	str = this->_location._name;
	if (str.size() > 0 && str[str.size() - 1] == '/')
		str.erase(str.end() - 1);
	i = 0;
	while (i < this->_location._redirections.size())
	{
		if (this->_content.compare(this->_root + str + std::string(this->_location._redirections[i].begin(), this->_location._redirections[i].end())) == 0)
		{
			this->_content = this->_location._redirections[i + 1];
			if (this->_location._redirections[i + 2].compare("permanent") == 0)
				this->_code = 301;
			else if (this->_location._redirections[i + 2].compare("temporary") == 0)
				this->_code = 307;
			return ;
		}
		i += 3;
	}
}

std::vector<char>		Response::sendResponse()
{
	std::vector<char>	f_response;
	struct stat			filestat;
	std::string rtn;

	_cgi = false;
	this->_code = 200;
	this->_root = "." + this->_request.getConfig()._root;
	this->_location = getLocation(_request.getURL(), _request.getConfig()._locations);
	_root = _root.substr(0, (_root[_root.length() - 1] == '/' ? _root.length() - 1 : _root.length()));
	if (this->_location._root.compare("") != 0)
	{
		this->_root = "." + this->_location._root;
		_root = _root.substr(0, (_root[_root.length() - 1] == '/' ? _root.length() - 1 : _root.length()));
		this->_content = this->_root;
		this->_content = this->_content + this->_request.getURL().substr(this->_location._name.size() - (_location._name[_location._name.size() - 1] == '/' ? 1 : 0), this->_request.getURL().size());
	}
	else
	{
		this->_content = this->_root;
		this->_content = this->_content.substr(0, this->_content.size() - ((this->_content[this->_content.size() - 1] == '/') ? 1 : 0)) + this->_request.getURL();
	}
	this->_encoding_type = "plain";
	if (this->_request.getHTTPVersion().compare("HTTP/1.1") != 0)
		this->_code = 505;
	else if (this->VerifyHost() == false)
		this->_code = 400;
	if (stat(this->_content.c_str(), &filestat) == -1)
		this->_code = 404;
	else if (S_ISDIR(filestat.st_mode))
	{
		this->_request.setURL(this->_request.getURL() + "/");
		this->_content.append("/");
		this->_content += this->_location._index;
		this->_content = this->findIndex();
		if (this->_content.compare("forbidden") == 0)
			this->_code = 403;
	}
	if (this->_location._redirections.size())
		this->VerifyRedirection();
	if ((size_t)atoi(_request.getContentLength().c_str()) > _location._client_max_body_size)
	{
		_code = 413;
		f_response = MAINResponse();
		for (size_t i = 0; i < f_response.size(); i++)
			rtn += f_response[i];
		PRINT_STR(rtn);
		return (f_response);
	}
	//CGI
	if (_code != 404 && IsCGICalled(_request.getURL()))
	{
		this->_cgi = true;
		std::string response = CGI(this->_request, this->_location, this->_root).executeCGI(getScriptName(this->_request.getURL()));
		this->_content = response;
		f_response = MAINResponse();
		std::string rtn;
		for (size_t i = 0; i < f_response.size(); i++)
			rtn += f_response[i];
		PRINT_STR(rtn);
		return (f_response);
	}
	if (isAllowedMethod() == false)
		f_response = wrongMethodReponse();
	else if (this->_request.getMethod().compare("GET") == 0 || this->_request.getMethod().compare("HEAD") == 0
		|| this->_request.getMethod().compare("POST") == 0)
		f_response = MAINResponse();
	else if (this->_request.getMethod().compare("DELETE") == 0)
		f_response = DELETEResponse();
	else if (this->_request.getMethod().compare("OPTIONS") == 0)
		f_response = OPTIONSResponse();
	for (size_t i = 0; i < f_response.size(); i++)
		rtn += f_response[i];
	PRINT_STR(rtn);
	return (f_response);
}
