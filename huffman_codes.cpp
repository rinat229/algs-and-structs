    #include <iostream>
    #include <queue>
    #include <vector>

    class Graph{
    protected:
        using __container_type = std::vector<int>;
        std::vector<__container_type > adj_list;
        int next_vertex;
    public:
        void add_edge(std::pair<int, int> edge){
            // std::cout << edge.first - 1 << ' ' << edge.second - 1 << '\n';
            adj_list[edge.first - 1].push_back(edge.second - 1);
            adj_list[edge.second - 1].push_back(edge.first - 1);
        }

        Graph(int vert_number){
            adj_list = std::vector<std::vector<int> >(vert_number, __container_type());
            next_vertex = vert_number + 1;
        }

        int add_vertex(){
            adj_list.push_back(__container_type());
            return next_vertex++;
        }
        __container_type& neighbours(int vertex){
            return adj_list[vertex];
        }

        void print_vertices(){
            for(auto &a : adj_list){
                for(auto &elem : a)
                    std::cout << elem + 1 << ' ';
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
        std::vector<int> __d, __f, depth;
        int __time;
        int n;
        int depth_start;


    public:
        DFS(Graph_type& __graph) : graph(__graph), n(__graph.size()), 
        __d(std::vector<int>(__graph.size(), 0)), 
        depth(std::vector<int>(__graph.size(), 0)), __time(1), depth_start(0) {}

        void search(){
            
            for (size_t u = 0; u < n; u++){
                if(__d[u] == 0){
                    depth[u] = depth_start;
                    search(u, depth_start + 1);

                }
            }
        }

        void search(int u, int _depth){
            __d[u] = __time++;
            depth[u] = _depth;
            for (auto &i : graph.neighbours(u)){
                if(__d[i] == 0)
                    search(i, _depth + 1);
            }
            // __f[u] = __time++;
        }

        std::vector<int>& return_depth(){
            return depth;
        }

        std::vector<int> return_final(){
            return __f;
        }
    };


    int main(){
        // freopen("test", "r", stdin);
        using pair_type = std::pair<int, int>;
        std::priority_queue<pair_type, std::vector<pair_type>, std::greater<pair_type>> heap;
        int n;
        std::cin >> n;
        std::vector<int> freq(n);
        for(int i = 1; i <= n; ++i){
            int a_i;
            std::cin >> a_i;
            heap.push(std::make_pair(a_i, i));
            freq[i - 1] = a_i;
        }

        Tree tree(n);
        for(int i = 0; i < n - 1; ++i){
            auto first_min = heap.top();
            heap.pop();
            auto second_min = heap.top();
            heap.pop();
            int temp_vertex = tree.add_vertex();
            tree.add_edge(std::make_pair(first_min.second, temp_vertex));
            tree.add_edge(std::make_pair(second_min.second, temp_vertex));
            heap.push(std::make_pair(first_min.first + second_min.first, temp_vertex));
        }

        DFS dfs(tree);

        dfs.search(tree.size() - 1, 0);
        auto depth = dfs.return_depth();

        int result = 0;
        for(int i = 0; i < n; ++i){
            result += depth[i] * freq[i];
        }
        std::cout << result << '\n';
    }