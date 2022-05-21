#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>

struct TreapNode{
    int value;
    int key;
    int priority;
    std::unique_ptr<TreapNode> left_node;
    std::unique_ptr<TreapNode> right_node;

    TreapNode(int key, int priority) : key(key), priority(priority),
    left_node(nullptr), right_node(nullptr) {}
    TreapNode() : left_node(nullptr), right_node(nullptr) {}
};


using node_type = std::unique_ptr<TreapNode>;
class Treap{
    std::pair<node_type, node_type> split(node_type &treap_node, int key);
    node_type merge(node_type &treap_node1, node_type &treap_node2);

    public:
        node_type root;
        void insert(int key, int priority);
        void remove(int key);
        void print_values(node_type &node);
        Treap() : root(nullptr){}
};

std::pair<node_type, node_type> Treap::split(node_type &treap_node, int key){
    if (treap_node == nullptr){
        return std::make_pair(std::move(nullptr), std::move(nullptr));
    }

    if (treap_node->key < key){
        auto __pair = split((*treap_node).right_node, key);
        (*treap_node).right_node = std::move(__pair.first);
        return std::make_pair(std::move(treap_node), std::move(__pair.second));
    }

    else{
        auto __pair = split((*treap_node).left_node, key);
        (*treap_node).left_node = std::move(__pair.second);
        return std::make_pair(std::move(__pair.first), std::move(treap_node));
    }
}


node_type Treap::merge(node_type &treap_node1, node_type &treap_node2){
    if(treap_node2 == nullptr){
        return std::move(treap_node1);
    }

    if(treap_node1 == nullptr){
        return std::move(treap_node2);
    }

    else if((*treap_node1).priority > (*treap_node2).priority){
        (*treap_node1).right_node = merge((*treap_node1).right_node, treap_node2);
        return std::move(treap_node1);
    }

    else{
        (*treap_node2).left_node = merge(treap_node1, (*treap_node2).left_node);
        return std::move(treap_node2);
    }
}


void Treap::insert(int key, int priority){
    auto __pair = split(root, key);
    auto new_treap_node = std::make_unique<TreapNode>(key, priority);

    auto T1 = merge(__pair.first, new_treap_node);
    auto T2 = merge(T1, __pair.second);
    root = std::move(T2);
}


void Treap::remove(int key){
    auto __pair = split(root, key);
    TreapNode *__left_node = __pair.second.get();
    
    if(__left_node->left_node != nullptr){
        while(__left_node->left_node->left_node != nullptr){
            __left_node = __left_node->left_node.get();
        }

        if(__left_node->left_node->key == key){
            __left_node->left_node = nullptr;
        }
    }
    else{
        if(__left_node->key == key){
            __pair.second = std::move(__left_node->right_node);
        }
    }
    auto T = merge(__pair.first, __pair.second);
    root = std::move(T);
}


void Treap::print_values(node_type &node){
    if(node != nullptr){
        print_values((*node).left_node);
        std::cout << (*node).key << ' ';
        print_values((*node).right_node);
    }
}


int main(){
    Treap treap;
    std::vector<int> a{9, 13, 1, 10, 4, 7};
    std::srand(std::time(nullptr));

    for(auto &val : a){
        treap.insert(val, rand()%1000);
    }

    // treap.remove(9);
    // treap.remove(3);
    treap.print_values(treap.root);
    std::cout << '\n';
    for(auto &val : a){
        treap.remove(val);
        treap.print_values(treap.root);
        std::cout << '\n';
    }

}