#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class DException : public std::exception
{
public:
	DException(std::string ss) : s(ss) {}
	virtual const char* what() const throw() { return s.c_str(); }
private:
	std::string s;
};

class NotImplementedException : public DException
{
public:
	NotImplementedException() : DException("Not implemented") {}
};

#endif