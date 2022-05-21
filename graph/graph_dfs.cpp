#include <iostream>
#include <vector>


class Graph{
  protected:
    using __container_type = std::vector<int>;
    std::vector<__container_type > adj_list;
  public:
    void add_edge(std::pair<int, int> edge){
        adj_list[edge.first - 1].push_back(edge.second - 1);
        adj_list[edge.second - 1].push_back(edge.first - 1);
    }

    Graph(int vert_number){
        adj_list = std::vector<std::vector<int> >(vert_number, __container_type());
    }

    __container_type& neighbours(int vertex){
        return adj_list[vertex];
    }

    void print_vertices(){
        for(auto &a : adj_list){
            for(auto &elem : a)
                std::cout << elem << ' ';
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


class DFS{
    using Graph_type = Tree;
    Graph_type& graph;
    std::vector<int> __d, __f;
    int __time;
    int n;
    int tc;


  public:
    DFS(Graph_type& __graph) : graph(__graph), n(__graph.size()), 
    __d(std::vector<int>(__graph.size(), 0)), 
    __f(std::vector<int>(__graph.size(), 0)), __time(1), tc(0) {}

    void search(){
        for (size_t u = 0; u < n; u++){
            if(__d[u] == 0){
                search(u);

            }
        }
    }

    void search(int u){
        __d[u] = __time++;
        for (auto &i : graph.neighbours(u)){
            if(__d[i] == 0)
                search(i);
        }
        __f[u] = __time++;
    }

    std::vector<int> return_discover(){
        return __d;
    }

    std::vector<int> return_final(){
        return __f;
    }
};


int main(){
    int N;
    std::cin >> N;

    Tree graph(N);
    for (size_t i = 1; i <= N; i++){
        std::pair<int, int> edge;
        std::cin >> edge.first;
        edge.second = i;
        if(edge.first == 0){
            graph.root() = edge.second - 1;
        }
        else{
            graph.add_edge(edge);
        }
    }

    // graph.print_vertices();
    // std::cout << "__________\n";
    DFS dfs(graph);

    dfs.search(graph.root());

    std::vector<int> d_time = dfs.return_discover();
    std::vector<int> f_time = dfs.return_final();
    int m;
    std::cin >> m;

    for (int i = 0; i < m; ++i)    {
        std::pair<int, int> p;
        std::cin >> p.first >> p.second;
        std::cout << (d_time[p.first - 1] <= d_time[p.second - 1] && d_time[p.second - 1] <= f_time[p.second - 1] && f_time[p.second - 1] <= f_time[p.first - 1] ? 1 : 0) << '\n';
    }
    
}