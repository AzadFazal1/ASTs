#ifndef CS225_BINARY_OP_H_
#define CS225_BINARY_OP_H_

#include "node.h"
#include <iostream>
#include <memory>
#include <string>


namespace cs225 {
class binary_op : public node {
public:
  binary_op(std::unique_ptr<node> left, std::unique_ptr<node> right);
  /*
          Constructs a new node with the given children.

          Parameters:
          left:	The left child
          right:	The right child
  */
  double value() const;
  /*
          Returns:
          the value of the expression rooted at this node
  */
  virtual double combine(double left, double right) const = 0;
  /*
          Computes the value of the binary expression, given the computed values
     of the left and right subexpressions.

          Parameters:
          left:	The value of the left subexpression
          right:	The value of the right subexpression
          Returns:
          the value for this expression
  */

private:
  std::unique_ptr<node> left_;
  // 	The left child.

  std::unique_ptr<node> right_;
  //	The right child.
};
//	Convenience factory function for making binary operator nodes.

std::unique_ptr<node> make_binary_op(const std::string &op,
                                     std::unique_ptr<node> left,
                                     std::unique_ptr<node> right);

} // namespace cs225
#endif