#include <iostream>
#include <iomanip>
#include "human.h"
#include <utility>

using namespace std;

human::human(string a_name)
	:
	m_name(move(a_name))
{
}

string human::name()const
{
	return m_name;
}

size_t human::name_length()const
{
	return m_name.length();
}

void human::set_name(string a_name)
{
	m_name = move(a_name);
}

std::ostream& operator<<(std::ostream& ostream, const human& a_human)
{
	return ostream << a_human.name();
}