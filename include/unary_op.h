#ifndef CS225_UNARY_OP_H_
#define CS225_UNARY_OP_H_

#include "node.h"

#include <memory>
#include <string>

namespace cs225 {

class unary_op : public node {
public:
  unary_op(std::unique_ptr<node> arg);

  /*
  Constructs a new unary operation with the given child.

  Parameters:
  arg	The child for this unary operation
  */
  double value() const override;
  /*
  Returns:
  the value of the expression rooted at this node
  */
  virtual double compute(double val) const = 0;
  /*
  Computes the value of the unary expression, given the computed value of the
  child expression.

  Parameters:
  val	The value of the child expression
  Returns:
  the value for this expression
  */
private:
  // The child node.

  std::unique_ptr<node> arg_;
};
// Convenience factory function for making unary operator nodes.

std::unique_ptr<node> make_unary_op(const std::string &op,
                                    std::unique_ptr<node> arg); 
  /*
  {
  std::unique_ptr<node> temp;
  if (op == "#") {
    temp = new uplus{std::move(arg)};
  } else if (op == "~") {
    temp = new uminus{std::move(arg)};

  } else {
    throw std::runtime_error("Invalid unary operator " + op);
  }
  return temp;
}
*/

} // namespace cs225
#endif