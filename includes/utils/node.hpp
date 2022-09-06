#ifndef NODE_HPP
# define NODE_HPP

namespace ft
{
    enum colour
    {
        BLACK,
        RED
    };

    template<class value_type>
    struct node
    {
        // Constructor for node, default colour is RED and NIL leaves are also set
        node(node* parent) : colour(RED), parent(parent), left(NULL), right(NULL) {}

        value_type* data;
        colour      colour;
        node*       parent;
        node*       left;
        node*       right;
    };
}

#endif
