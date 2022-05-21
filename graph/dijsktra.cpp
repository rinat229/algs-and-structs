#include <iostream>
#include <vector>
#include <limits>
#include <set>

class Graph{
  protected:
    using __container_type = std::vector<std::pair<int, float> >;
    std::vector<__container_type > adj_list;
  public:
    void add_edge(std::pair<int, int> edge, float weight){
        adj_list[edge.first - 1].push_back(std::make_pair(edge.second - 1, weight));
        adj_list[edge.second - 1].push_back(std::make_pair(edge.first - 1, weight));
        // adj_list[edge.second - 1].push_back(edge.first - 1);
    }

    Graph(int vert_number){
        adj_list = std::vector<__container_type>(vert_number, __container_type());
    }

    __container_type& neighbours(int vertex){
        return adj_list[vertex];
    }

    void print_vertices(){
        for(auto &a : adj_list){
            for(auto &elem : a)
                std::cout << elem.first + 1 << ' ' << elem.second << "\t\t";
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


struct dejkstra{

    using Graph_type = Graph;
    int vertex_from;
    std::vector<float> distances;
    int n;
    Graph_type graph;
    std::vector<int > parents;
    dejkstra(Graph_type& __graph, int _n, int _vertex_from) : n(_n), vertex_from(_vertex_from - 1), 
    distances(std::vector<float>(_n, std::numeric_limits<float>::infinity())), graph(__graph),
    parents(std::vector<int>(n, -1)){
        distances[vertex_from] = 0;
    }

    void search(){
        std::set<std::pair<float, int> > fast_dst;
        std::vector<bool> attended(n);

        for(int i = 0; i < n; i++){
            fast_dst.insert(std::make_pair(distances[i], i));
            attended[i] = false;
        }

        for(int i = 0; i < n; i++){
            auto top_vertex = fast_dst.begin();

            for(auto &[vertex, edge_length] : graph.neighbours(top_vertex->second)){
                if(!attended[vertex]){
                    if(distances[vertex] > distances[top_vertex->second] + edge_length){
                        auto finded_vert = fast_dst.find(std::make_pair(distances[vertex], vertex));
                        distances[vertex] = distances[top_vertex->second] + edge_length;

                        fast_dst.erase(finded_vert);
                        fast_dst.insert(std::make_pair(distances[vertex], vertex));

                        parents[vertex] = top_vertex->second;
                    }
                }
            }

            attended[top_vertex->second] = true;
            fast_dst.erase(top_vertex);
        }
    }
};

int main(){
    // freopen("test", "r", stdin);
    // std::ios::sync_with_stdio(false); std::cin.tie(0);
    int N, m, s, t;
    std::cin >> N >> m >> s >> t;

    Tree graph(N);
    for(int i = 0; i < m; i++){
        float weight;
        std::pair<int, int> edge;

        std::cin >> edge.first >> edge.second >> weight;
        graph.add_edge(edge, weight);
    }


    // graph.print_vertices();
    dejkstra dist(graph, N, s);

    dist.search();

    bool not_exist = dist.distances[t - 1] == std::numeric_limits<float>::infinity();
    std::cout << (not_exist ? -1 : dist.distances[t - 1]) << '\n';

    if(!not_exist){
        int parent = dist.parents[t - 1];

        std::vector<int> path;

        path.push_back(t - 1);
        while(parent != s - 1){
            path.push_back(parent);
            parent = dist.parents[parent];
        }
        path.push_back(s - 1);

        for(auto iter = path.rbegin(); iter < path.rend(); ++iter){
            std::cout << *iter + 1 << ' ';
        }
        std::cout << '\n';
    }
}