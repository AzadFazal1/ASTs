#ifndef CS225_UPLUS_H_
#define CS225_UPLUS_H_
#include <memory>
#include "unary_op.h"
namespace cs225
{

	//A unary expression node representing a unary plus (e.g., +1).

	class uplus : public unary_op
{
  public:
    using unary_op::unary_op; // <-- "inheriting" constructor

    /*
    Computes the value of the unary expression, given the computed value of the child expression.

		Parameters:
		val:	The value of the child expression
		Returns:
		the value for this expression
		*/

    double compute(double val) const override;

    
};
}
#endif