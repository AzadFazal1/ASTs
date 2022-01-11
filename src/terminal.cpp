
#include "terminal.h"

namespace cs225
{
	terminal::terminal(double value):value_{value}
	{

	}

	double terminal::value()const
	{
		return value_;
	}
std::unique_ptr<node> make_term (double value)
		{
		
			std::unique_ptr<node> term(new terminal(value));
			return term;
		}
}
