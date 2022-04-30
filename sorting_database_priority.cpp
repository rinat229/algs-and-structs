#include <iostream>
#include <vector>
#include <algorithm>

template <class T, class key>
class priority_less{
    const std::vector<int> permutation;
  public:
    priority_less(const std::vector<int>& __permutation) : permutation(__permutation){}
    bool operator ()(const std::pair<std::vector<T>, key> &__rowA, const std::pair<std::vector<T>, key >& __rowB) const {
        return compare(__rowA.first, __rowB.first, 0);
    }
  private:
    bool compare(const std::vector<T> &__rowA, const std::vector<T>& __rowB, int num_priority) const {
        if(num_priority == permutation.size() - 1){
            return __rowA[permutation[num_priority]] < __rowB[permutation[num_priority]];
        }
        else{
            if(__rowA[permutation[num_priority]] == __rowB[permutation[num_priority]]){
                return compare(__rowA, __rowB, ++num_priority);
            }
            else{
                return __rowA[permutation[num_priority]] < __rowB[permutation[num_priority]];
            }
        }
    }
};

int main(){
    // freopen("test", "r", stdin);

    int N, k;
    std::cin >> N >> k;

    std::vector<int> permutation(k);
    for (int i = 0; i < k; i++){
        int p_i;
        std::cin >> p_i;
        permutation[i] = p_i - 1;
    }

    std::vector<std::pair<std::vector<int>, std::string> > db(N);

    for(int idx = 0; idx < N; idx++){
        std::string key;
        std::cin >> key;
        std::vector<int> row(k);
        for(int i = 0; i < k; i++){
            int a_i;
            std::cin >> a_i;
            row[i] = a_i;
        }

        db[idx].first = row;
        db[idx].second = key;
    }
    std::stable_sort(db.begin(), db.end(), priority_less<int, std::string>(permutation)); 

    for(auto iter = db.rbegin(); iter < db.rend(); ++iter){
        std::cout << iter->second << '\n';
    }
}
