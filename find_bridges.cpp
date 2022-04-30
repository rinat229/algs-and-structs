#include <iostream>
#include <vector>
#include <algorithm>

class Graph{
  protected:
    using __container_type = std::vector<std::pair<int, int> >;
    std::vector<__container_type > adj_list;
  public:
    void add_edge(std::pair<int, int> edge, int num){
        adj_list[edge.first - 1].push_back(std::make_pair(edge.second - 1, num));
        adj_list[edge.second - 1].push_back(std::make_pair(edge.first - 1, num));
    }

    Graph(int vert_number){
        adj_list = std::vector<__container_type >(vert_number, __container_type());
    }

    __container_type& neighbours(int vertex){
        return adj_list[vertex];
    }

    void print_vertices(){
        for(auto &a : adj_list){
            for(auto &elem : a)
                std::cout << elem.first << ' ';
            std::cout << '\n';
        }
    }

    int size(){
        return adj_list.size();
    }
};


class Tree : public Graph{
    int __root;
  public:
    Tree(int vert_number) : Graph(vert_number), __root(0) {}
    int& root(){
        return __root; 
    }

};


struct DFS{
    using Graph_type = Tree;
    Graph_type& graph;
    std::vector<int> __d, __f, ret, bridges;
    int __time;
    int n;
    int tc;


  public:
    DFS(Graph_type& __graph) : graph(__graph), n(__graph.size()), 
    __d(std::vector<int>(__graph.size(), 0)), 
    // __f(std::vector<int>(__graph.size(), 0)), 
    ret(std::vector<int>(__graph.size(), 0)),
    bridges(std::vector<int>()), __time(1), tc(0) {}

    void search(){
        for (size_t u = 0; u < n; u++){
            if(__d[u] == 0){
                search(u);

            }
        }
    }

    void search(int u, int parent = -1){
        __d[u] = __time++;
        ret[u] = __time;
        for (auto &[i, num] : graph.neighbours(u)){
            if(back_edge(u, i) && i != parent){
                ret[u] = std::min(ret[u], __d[i]);
                // std::cout << "back edge from " << u + 1 << " to " << i + 1<< "\n";
            }
            if(__d[i] == 0){
                search(i, u);
                ret[u] = std::min(ret[u], ret[i]);
                if(ret[i] > __d[u]){
                    bridges.push_back(num);
                }
            }

        }
        // __f[u] = __time++;
    }

    bool back_edge(int u, int parent){
        if(__d[parent] < __d[u] && __d[parent] != 0) return true;
        return false;
    }

    std::vector<int> return_discover(){
        return __d;
    }

    std::vector<int> return_final(){
        return __f;
    }
};

void print_vec(std::vector<int> &vec){
    for(auto &a : vec){
        std::cout << a << '\n';
    }
    // std::cout << '\n';
}

int main(){
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    
    int n, m;
    std::cin >> n >> m;


    Tree graph(n);
    for (size_t i = 1; i <= m; i++){
        std::pair<int, int> edge;
        std::cin >> edge.first >> edge.second;
        graph.add_edge(edge, i);
    }

    // graph.print_vertices();
    // std::cout << "__________\n";
    DFS dfs(graph);

    dfs.search();
    std::sort(dfs.bridges.begin(), dfs.bridges.end());
    std::cout << dfs.bridges.size() << '\n';
    print_vec(dfs.bridges);
}