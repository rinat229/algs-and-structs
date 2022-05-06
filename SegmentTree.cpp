#include <vector>
#include <iostream>

long long int operation(long long int a, long long int b){
    return a + b;
}

class SegmentTree{
    long long int neutral_element;
    std::vector<long long int> _container;
    int _size;
  public:
    SegmentTree(const std::vector<long long int>& vec): neutral_element(0){
        this->_size = 1;
        for(; this->_size < vec.size(); this->_size <<= 1);
        // std::cout << this->_size;
        if(this->_size < vec.size()){
            this->_size <<= 1;
        }
        _container.resize(2 * this->_size - 1);

        for(int i = 0; i < vec.size(); ++i){
            _container[this->_size - 1 + i] = vec[i];
        }

        for(int i = vec.size(); i < _size; ++i){
            _container[this->_size - 1 + i] = neutral_element;
        }

        for(int i = this->_size - 2; i >= 0; --i){
            _container[i] = operation(_container[2 * i + 1], _container[2 * i + 2]);
        }
    }

    long long int query(int a, int b){
        return query(0, a, b, 0, this->_size - 1);
    }

    long long int query(int node, int a, int b, int left, int right){
        if(b < left || a > right){
            return neutral_element;
        }
        else if(a <= left && b >= right){
            return _container[node];
        }
        else{
            int middle = (left + right) / 2;
            return operation(query(node * 2 + 1, a, b, left, middle), query(node * 2 + 2, a, b, middle + 1, right));
        }
    }
};


int main(){
    freopen("test", "r", stdin);
    int n;
    std::cin >> n;
    std::vector<long long int> a(n);
    for(int i = 0; i < n; ++i){
        std::cin >> a[i];
    }
    
    SegmentTree tree(a);
    int m;
    std::cin >> m;
    for(int i = 0; i < m; ++i){
        int left, right;
        std::cin >> left >> right;
        std::cout << tree.query(left - 1, right - 1) << '\n';
    }
}