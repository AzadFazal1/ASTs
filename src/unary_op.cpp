
#include "unary_op.h"
#include "uminus.h"
#include "uplus.h"
#include <memory>
namespace cs225 {

unary_op::unary_op(std::unique_ptr<node> arg) { arg_ = std::move(arg); }

double unary_op::value() const { return compute(arg_->value()); }

std::unique_ptr<node> make_unary_op(const std::string &op,
                                    std::unique_ptr<node> arg) {
  if (op == "#") {
    std::unique_ptr<node> temp(new uplus{std::move(arg)});
    return temp;
  } else if (op == "~") {
    std::unique_ptr<node> temp(new uminus{std::move(arg)});
    return temp;
  } else {
    throw std::runtime_error("Invalid unary operator " + op);
  }
}
} // namespace cs225