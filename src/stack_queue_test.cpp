
#include <cassert>

#include "stack.h"
#include "queue.h"
#include <iostream>

using namespace cs225;

void test_stack()
{

    stack<int> st;
    for (int i = 0; i <= 20; ++i)
        
        st.push(i);

    for (int i = 0; i <= 20; ++i)
    {
        assert(st.top() == 20 - i);
        st.pop();

    }
}

void test_queue()
{
    queue<int> q;
    for (int i = 0; i <= 20; ++i)
        q.push(i);

    for (int i = 0; i <= 20; ++i)
    {
        assert(q.front() == i);
        q.pop();
    }
}

int main()
{
    test_stack();
    test_queue();
    return 0;
}
