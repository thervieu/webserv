
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

std::string		Response::getDate()
{
	struct timeval	tv;
	struct timezone	tz;
	long			day;
	std::string		date;

	date = "Date: ";
	gettimeofday(&tv, &tz);

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
