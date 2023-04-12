#pragma once
#include <string>

class human
{
public:
	explicit human(std::string a_name);

	std::string name()const;

	size_t name_length()const;

	void set_name(std::string);

private:
	std::string m_name;

};

std::ostream& operator<<(std::ostream& a_ostream, const human& a_human);