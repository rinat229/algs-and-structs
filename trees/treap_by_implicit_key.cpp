#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>

int operation(int a, int b, int c){
    return std::min(std::min(a, b), c);
}

struct TreapNode{
    static int const neutral_element = INT32_MAX;
    int value;
    int priority;
    int size = 1;
    int query_ans;
    std::unique_ptr<TreapNode> left_node;
    std::unique_ptr<TreapNode> right_node;

    TreapNode(int value, int priority) : value(value), priority(priority),
    query_ans(value), left_node(nullptr), right_node(nullptr){}
    TreapNode() : left_node(nullptr), right_node(nullptr) {}
    void update(){
        size = l_size() + r_size() + 1;
        query_update();
    }

    void query_update(){
        int left_val = left_node ? left_node->query_ans : neutral_element;
        int right_val = right_node ? right_node->query_ans : neutral_element;
        query_ans = operation(left_val, value, right_val);
    }
    int l_size(){
        return left_node == nullptr ? 0 : left_node->size;
    }

    int r_size(){
        return right_node == nullptr ? 0 : right_node->size;
    }
};

using node_type = std::unique_ptr<TreapNode>;


int size(node_type& __node){
    return __node == nullptr ? 0 : __node->size;
}


class Treap{
    std::pair<node_type, node_type> split(node_type &treap_node, int count);
    node_type merge(node_type &treap_node1, node_type &treap_node2);
    
    public:
        std::vector<int> order;
        void update(int position);
        node_type root;
        void insert(int value, int priority, int position);
        void remove(int key);
        void preorder(node_type &node, bool print = true);
        void preorder();
        void print_values();
        void move_to_front(int l_i, int r_i);
        int query(int l_i, int r_i);
        Treap() : root(nullptr){}
};

std::pair<node_type, node_type> Treap::split(node_type &treap_node, int count){
    if (treap_node == nullptr){
        return std::make_pair(std::move(nullptr), std::move(nullptr));
    }

    int __l_size = size(treap_node->left_node) + 1;
    if (__l_size <= count){
        auto __pair = split((*treap_node).right_node, count - __l_size);
        (*treap_node).right_node = std::move(__pair.first);
        treap_node->update();
        return std::make_pair(std::move(treap_node), std::move(__pair.second));
    }

    else{
        auto __pair = split((*treap_node).left_node, count);
        (*treap_node).left_node = std::move(__pair.second);
        treap_node->update();
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
        treap_node1->right_node = merge(treap_node1->right_node, treap_node2);
        treap_node1->update();
        return std::move(treap_node1);
    }

    else{
        treap_node2->left_node = merge(treap_node1, treap_node2->left_node);
        treap_node2->update();
        return std::move(treap_node2);
    }
}

void Treap::insert(int value, int priority, int position){
    auto __pair = split(root, position);
    auto new_treap_node = std::make_unique<TreapNode>(value, priority);

    auto T1 = merge(__pair.first, new_treap_node);
    root = merge(T1, __pair.second);
    // root = T2;
}


void Treap::move_to_front(int l_i, int r_i){
    auto __pair1 = split(root, r_i);
    auto __pair2 = split(__pair1.first, l_i);

    auto T1 = merge(__pair2.second, __pair2.first);
    auto T2 = merge(T1, __pair1.second);
    root = std::move(T2);
}

int Treap::query(int l_i, int r_i){
    auto __pair1 = split(root, r_i);
    auto __pair2 = split(__pair1.first, l_i);

    int result = __pair2.second->query_ans;
    auto T1 = merge(__pair2.first, __pair2.second);
    root = merge(T1, __pair1.second);

    return result;
}

void Treap::update(int position){
    auto __pair = split(root, position);
    root = merge(__pair.first, __pair.second);
}

void Treap::preorder(){
    order.clear();
    preorder(root, false);
}

void Treap::print_values(){
    preorder(root, true);
}
void Treap::preorder(node_type &node, bool print){
    if(node != nullptr){
        preorder(node->left_node);
        if (print) {
            std::cout << node->value << ' '; //<< node->size << '\t';
        }
        else{
            order.push_back(node->value);
        }
        preorder(node->right_node);
    }
}


int main(){
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    Treap treap;
    std::srand(std::time(nullptr));
    int n;
    std::cin >> n;

    for(int idx = 0; idx < n; idx++){
        char type;
        int l, r;
        std::cin >> type >> l >> r;
        if(type == '+'){
            treap.insert(r, rand() % 100000, l);
        }
        else if(type == '?'){
            std::cout << treap.query(l - 1, r) << '\n';
        }
    }
}