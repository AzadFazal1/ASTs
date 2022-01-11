#ifndef CS225_NODE_H_
#define CS225_NODE_H_


namespace cs225
{

//The base class node for our equation AST.

class node
{
	public:

		/*
		Returns:
		the value of the expression rooted at this node.
		*/

		virtual double value() const = 0 ;

		//Virtual destructor for inheritance purposes.
		
		virtual ~node() = default;
		
};
}
#endif