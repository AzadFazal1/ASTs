#ifndef CS225_TERMINAL_H_
#define CS225_TERMINAL_H_

#include "node.h"
#include <memory>

namespace cs225
{

//An expression node representing a "terminal" in a mathematic expression (as in, a single number).

class terminal : public node
{
	public:
		/*
		Constructs a terminal containing the given value.

		Parameters:
		value	The value for this terminal node.
		*/

		terminal(double value);

		/*
		Returns:
		the value of the expression rooted at this node
		*/
		
		double value() const override;

	private:
		double value_;
		
};
//Helper factory function to create terminal nodes.
		std::unique_ptr<node> make_term (double value);
		
}
#endif