#include <vector>
#include <iostream>

struct node{
    long long int value;
    long long int d;
};

long long int operation(long long int a, long long int b){
    return a + b;
}

long long int update_operation(long long int a, long long int b){
    return b;
}

class SegmentTree{
    int neutral_element;
    std::vector<node> tree;
    int _size;
  public:
    SegmentTree(const std::vector<int>& vec, int _neutral_element): 
    neutral_element(_neutral_element){
        _size = 1;
        for(; _size < vec.size(); _size <<= 1);
        if(_size < vec.size()){
            _size <<= 1;
        }
        tree.resize(2 * _size - 1);

        for(int i = 0; i < vec.size(); ++i){
            tree[_size - 1 + i] = {vec[i], -1};
        }

        for(int i = vec.size(); i < _size; ++i){
            tree[_size - 1 + i] = {neutral_element, -1};
        }

        for(int i = _size - 2; i >= 0; --i){
            tree[i] = {operation(tree[2 * i + 1].value, tree[2 * i + 2].value), -1};
        }
    }

    void push(int node, int left, int right){
        // tree[2 * node + 1].d = update_operation(tree[2 * node + 1].d, tree[node].d);
        // tree[2 * node + 2].d = update_operation(tree[2 * node + 2].d, tree[node].d);
        // tree[node].d = neutral_element_updatable;
        if(tree[node].d != -1){
            tree[node].value = tree[node].d * (right - left + 1);
            // std::cout << "assign " << tree[node].d << ' ' << right - left << ' ' << tree[node].value << '\n';
            if(2 * node + 2 < tree.size()){
                tree[node * 2 + 1].d = tree[node].d;
                tree[node * 2 + 2].d = tree[node].d;
                // std::cout << "this assign\n";
            }
        }
        tree[node].d = -1;
    }

    void update(int a, int b, int val){
        update(0, a, b, 0, _size - 1, val);
    }

    void update(int node, int a, int b, int left, int right, int val){
        push(node, left, right);
        if(b < left || a > right){
            return;
        }
        else if(a <= left && b >= right){
            tree[node].d = val;
            push(node, left, right);
        }
        else{
            int middle = (left + right) / 2;
            update(node * 2 + 1, a, b, left, middle, val);
            update(node * 2 + 2, a, b, middle + 1, right, val);

            tree[node].value = operation(tree[node * 2 + 1].value, tree[node * 2 + 2].value);
        }
    }
    long long int query(int a, int b){
        return query(0, a, b, 0, _size - 1);
    }

    long long int query(int node, int a, int b, int left, int right){
        push(node, left, right);
        if(b < left || a > right){
            return neutral_element;
        }
        else if(a <= left && b >= right){
            return tree[node].value;
        }
        else{
            int middle = (left + right) / 2;
            return operation(query(node * 2 + 1, a, b, left, middle), query(node * 2 + 2, a, b, middle + 1, right));
            
        }
    }
};


int main(){
    // freopen("test", "r", stdin);
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    
    SegmentTree tree(a, 0);
    for(int i = 0; i < k; ++i){
        char type;
        int left, right;
        std::cin >> type >> left >> right;
        if(type == 'A'){
            int x;
            std::cin >> x;
            // std::cout << x << '\n';
            tree.update(left - 1, right - 1, x);
        }
        else{
            std::cout << tree.query(left - 1, right - 1) << '\n';
        }
    }
}