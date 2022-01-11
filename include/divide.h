#ifndef CS225_DIVIDE_H_
#define CS225_DIVIDE_H_
#include "binary_op.h"
#include <memory>
#include <string>
namespace cs225
{
	class divide : public binary_op
	{
	public:
		using binary_op::binary_op; 
// <-- "inheriting" constructor

		double combine(double left, double right)const override;
/*
Computes the value of the binary expression, given the computed values of the left and right subexpressions.

Parameters
left	The value of the left subexpression
right	The value of the right subexpression
Returns
the value for this expression
*/

	};

}
#endif