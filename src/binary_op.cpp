#include "binary_op.h"
#include "plus.h"
#include "minus.h"
#include "times.h"
#include "divide.h"
#include "exponent.h"

namespace cs225
{
	binary_op::binary_op (std::unique_ptr< node > left, std::unique_ptr< node > right)
	{
		left_ = std::move(left);
		right_ = std::move(right);
	}

	double binary_op::value() const
	{
    return combine(left_->value(), right_->value());
	}
	std::unique_ptr<node> make_binary_op(const std::string &op,
                                     std::unique_ptr<node> left,
                                     std::unique_ptr<node> right) {
  

  if (op == "+") {
    std::unique_ptr<node> temp(new plus{std::move(left), std::move(right)});
    return temp;
  } else if (op == "-") {
    std::unique_ptr<node> temp(new minus{std::move(left), std::move(right)});
    return temp;
  } else if (op == "*") {
    std::unique_ptr<node> temp(new times{std::move(left), std::move(right)});
    return temp;
      } else if (op == "/") {
    std::unique_ptr<node> temp(new divide{std::move(left), std::move(right)});
    return temp;    
  } else if (op == "^") {
    std::unique_ptr<node> temp(new exponent{std::move(left), std::move(right)});
    return temp;
  } else {
    throw std::runtime_error("Invalid binary operator " + op);
  }  

}


}