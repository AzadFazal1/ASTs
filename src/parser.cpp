

#include "parser.h"
#include "binary_op.h"
#include "number.h"
#include "operation.h"
#include "terminal.h"
#include "unary_op.h"
#include <cassert>
#include <iostream>

namespace cs225 {

/**
 * A "private class" for helping us parse expressions. Maintains all of the
 * state necessary to perform Dijkstra's shunting-yard algorithm.
 *
 * @see https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 */
class parser {
public:
  /**
   * @param tokens The tokens to parse
   * @return the root of the parse tree for that expression
   */
  std::unique_ptr<node> parse(queue<std::unique_ptr<token>> &tokens);

private:
  // add lots of other helper methods here!

  queue<std::unique_ptr<token>>
  post_fix_conversion(queue<std::unique_ptr<token>> &tokens);

  std::unique_ptr<node>
  post_fix_evaluation(queue<std::unique_ptr<token>> &postfix_queue);

  bool is_operation(const std::unique_ptr<token> &tokens) {
    if (tokens->type() == token_type::OPERATION) {
      return true;
    }
    return false;
  }
  bool is_number(const std::unique_ptr<token> &tokens) {
    if (tokens->type() == token_type::NUMBER) {
      return true;
    }
    return false;
  }

  int precedence(const std::unique_ptr<token> &tokens) {
    return tokens->as_operation()->precedence();
  }

  associativity associativity(const std::unique_ptr<token> &tokens) {
    return tokens->as_operation()->associativity();
  }

  bool open_paren(token *tokens) {
    return tokens && tokens->type() == token_type::TEXT &&
           tokens->text() == "(";
  }

  bool close_paren(token *tokens) {
    return tokens && tokens->type() == token_type::TEXT &&
           tokens->text() == ")";
  }
  /**
   * The stack to hold the operator tokens encountered. This is the "side
   * rail" in the shunting yard algorithm.
   */
  stack<std::unique_ptr<token>> ops_;

  queue<std::unique_ptr<token>> post_fix_; // Queue for making a postfix
                                           // expression.

  /**
   * What is this for? It is a mystery (and a hint)!
   */
  stack<std::unique_ptr<node>> nodes_;
};

std::unique_ptr<node> parse(queue<std::unique_ptr<token>> &tokens) {
  parser p;
  return p.parse(tokens);
}

std::unique_ptr<node> parser::parse(queue<std::unique_ptr<token>> &tokens) {

  auto postfix_queue = post_fix_conversion(tokens);
  return post_fix_evaluation(postfix_queue);
}

queue<std::unique_ptr<token>>
parser::post_fix_conversion(queue<std::unique_ptr<token>> &tokens) {

  while (!tokens.empty()) {
    auto &tok = tokens.front();

    /// @todo handle the token
    if (is_number(tok)) {
      post_fix_.push(std::move(tok));
      tokens.pop();
    } else if (is_operation(tok)) {
      if (ops_.empty()) {
        ops_.push(std::move(tok));
        tokens.pop();
        std::cout << "REACHED LINE" << __LINE__ << std::endl;

      } else {
        auto &ops_t = ops_.top();
        while (
            ((is_operation(ops_t) && (precedence(ops_t) > precedence(tok))) ||
             ((precedence(ops_t)) == precedence(std::move(tok)) &&
              (associativity(ops_t)) == associativity::LEFT)) &&
            !open_paren(ops_t.get())) {
          post_fix_.push(std::move(ops_t));
          ops_.pop();
          ops_.push(std::move(tok));
        }
      }
    } else if (open_paren(tok.get())) {
      ops_.push(std::move(tok));
    } else if (close_paren(tok.get())) {
      while (!open_paren(ops_.top().get())) {
        post_fix_.push(std::move(ops_.top()));

        if (ops_.empty()) {
          std::cout << "REACHED LINE" << __LINE__ << std::endl;
          throw std::runtime_error{"Input has unbalanced paranthesis"};
        }
      }
      if (open_paren(ops_.top().get())) {
        ops_.pop();
      }
    }
  }
  tokens.pop();

  /// @todo clean up remaining operators
  while (!ops_.empty()) {
    post_fix_.push(std::move(ops_.top()));
    ops_.pop();
  }
  return post_fix_;
}

std::unique_ptr<node>
parser::post_fix_evaluation(queue<std::unique_ptr<token>> &postfix_queue) {

  /// @todo return the root of your tree
  while (!postfix_queue.empty()) {
    auto &p_front = postfix_queue.front();
    if (is_number(p_front)) {
      auto term = make_term(p_front->as_number()->value());
      nodes_.push(std::move(term));
    }
    auto &top_node = nodes_.top();
    if (is_operation(p_front)) {
      switch (p_front->as_operation()->args()) {
      case '2': {
        auto right = make_term(top_node->value());
        nodes_.pop();
        auto left = make_term(top_node->value());
        nodes_.pop();
        auto output =
            make_binary_op(p_front->text(), std::move(left), std::move(right));
        nodes_.push(std::move(output));
        postfix_queue.pop();
      } break;
      case '1': {
        auto arg = make_term(top_node->value());
        nodes_.pop();
        auto out = make_unary_op(p_front->text(), std::move(arg));
        nodes_.push(std::move(out));
        postfix_queue.pop();
        break;
      }
      }
    }
  }

  auto output = std::move(nodes_.top());
  return output;
}

} // namespace cs225
