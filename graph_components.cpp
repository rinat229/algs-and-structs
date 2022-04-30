#include <iostream>
#include <vector>


class Graph{
  protected:
    using __container_type = std::vector<int>;
    std::vector<__container_type > adj_list;
  public:
    void add_edge(std::pair<int, int> edge){
        adj_list[edge.first - 1].push_back(edge.second - 1);
        // adj_list[edge.second - 1].push_back(edge.first - 1);
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
  protected:
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


class component_search : public DFS{
    using Graph_type = Tree;
  protected:
    Graph_type graph_T;
  public:  
    std::vector<int> order;
    std::vector<std::vector<int> > component;
    component_search(Graph_type& graph) : DFS::DFS(graph), graph_T(graph.size()) {}

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
        order.push_back(u);

        __f[u] = __time++;
    }


    void graph_transpose(){
        for(int i = 0; i < graph_T.size(); i++){
            for(auto &neigh : graph.neighbours(i)){
                graph_T.add_edge(std::make_pair(neigh+1, i+1));
            }
        }
    }

    void search_second(){
        // __d.assign(__d.size(), 0);
        // __f.assign(__d.size(), 0);
        __d = std::vector<int>(n, 0);
        __f = std::vector<int>(n, 0);
        __time = 0;
        for(size_t i = 0; i < n; i++){
            int u = order[n - i - 1];
            if(__d[u] == 0){
                component.push_back(std::vector<int>());
                search_second(u);
            }
        }
    }

    void search_second(int u){
        __d[u] = ++__time;
        component.back().push_back(u);
        for (auto &i : graph_T.neighbours(u)){
            if(__d[i] == 0)
                search_second(i);
        }

        __f[u] = ++__time;
    }

    void comp_search(){
        search();
        graph_transpose();
        search_second();
    }
};


int main(){
    // freopen("test", "r", stdin);

    int N;
    std::cin >> N;

    Tree graph(N);
    for (size_t i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            int ch;
            std::cin >> ch;
            if(ch == 1){
                graph.add_edge(std::make_pair(i, j));
            }
        }
    }

    // for(int i = 0; i < N; i++){
    //     std::pair<int, int> edge;
    //     std::cin >> edge.first >> edge.second;
    //     graph.add_edge(edge);
    // }

    component_search comp(graph);

    comp.comp_search();

    // for(auto &c : comp.component){
    //     for(auto &a : c){
    //         std::cout << a << ' ';
    //     }
    //     std::cout << '\n';
    // }
    
    std::cout << comp.component.size() << '\n';
}