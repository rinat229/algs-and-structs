#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <queue>
#include <set>

struct Node{
    std::map<char, std::shared_ptr<Node> > sons;
    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> suff;
    std::shared_ptr<Node> up;
    char char_from_parent;
    bool is_terminal;
    bool is_root = false;
    int pattern_number = -1;

    std::shared_ptr<Node> suff_link(){
        if(!suff){
            if(is_root){ 
                suff = std::shared_ptr<Node>(this);
            }else if(parent->is_root){
                suff = parent;
            } 
            else{
                suff = get_link(parent->suff_link(), char_from_parent);
            }
        }
        return suff;
    }

    static std::shared_ptr<Node> get_link(std::shared_ptr<Node> node, char c){
        if(node->sons.find(c) != node->sons.end()){
            return node->sons[c];
        }
        else if(node->is_root){
            return node;
        }
        return get_link(node->suff, c);
    }

    std::shared_ptr<Node> get_up(){
        if(!up){
            if(suff->is_terminal || suff->is_root){
                up = suff;
            }
            else{
                up = suff->get_up();
            }
        }

        return up;
    }
};

class AhoCorasick{
    std::shared_ptr<Node> root;
    const std::vector<std::string> patterns;

    void add_string(std::string s, int num){
        std::shared_ptr<Node> cur = root;
        for(auto c : s){
            if(cur->sons.find(c) == cur->sons.end()){
                cur->sons[c] = std::make_shared<Node>();
                cur->sons[c]->parent = cur;
                cur->sons[c]->char_from_parent = c;
            }
            cur = cur->sons[c];
        }

        cur->is_terminal = true;
        cur->pattern_number = num;
    }

    void add_strings(){
        for(int i = 0; i < patterns.size(); ++i){
            add_string(patterns[i], i);
        }
    }

    void suff_links(){
        std::queue<std::shared_ptr<Node> > temp;
        temp.push(root);
        std::shared_ptr<Node> cur = root;
        while(temp.size() > 0){
            for(auto &v : cur->sons){
                temp.push(v.second);
            }
            cur->suff_link();
            cur->get_up();
            temp.pop();
            cur = temp.front();
        }   
    }
  public:
    AhoCorasick(const std::vector<std::string>& _patterns) : patterns(_patterns), 
    root(std::make_shared<Node>()) {
        root->is_root = true;
        add_strings();
        suff_links();
    };

    std::vector<std::pair<int, int> > search(const std::string& text){
        std::vector<std::pair<int, int> > result(patterns.size(), std::make_pair(0, 0));
        std::shared_ptr<Node> cur = root;
        // if(cur->sons.find(text[0]) != cur->sons.end()){
        //     cur = cur->sons[text[0]];
        // }

        for(int i = 0; i < text.size(); ++i){
            char c = text[i];

            if(cur->sons.find(c) != cur->sons.end()){
                cur = cur->sons[c];
            }
            else{
                cur = Node::get_link(cur->suff, c);
            }
            if(cur->is_terminal){
                int pattern_num = cur->pattern_number;
                if(result[pattern_num].first == 0){
                    result[pattern_num].first = i + 2 - patterns[pattern_num].size();
                    // std::cout << patterns[pattern_num].size() << ' ' << patterns[pattern_num] << '\n';
                }
                ++result[pattern_num].second;
            }

            if(cur->up != root){
                std::shared_ptr<Node> temp_up = cur->up;
                
                while(temp_up != root){
                    int pattern_num = temp_up->pattern_number;
                    if(result[pattern_num].first == 0){
                        result[pattern_num].first = i + 2 - patterns[pattern_num].size();
                    }
                    ++result[pattern_num].second;
                    temp_up = temp_up->up;

                }
            }
        }

        return result;
    }
};



int main(){
    // freopen("test", "r", stdin);
    std::ios::sync_with_stdio(false); std::cin.tie(0);

    std::vector<std::string> patt;
    std::string text;
    std::cin >> text;
    int t;
    std::cin >> t;
    for(int i = 0; i < t; ++i){
        std::string pattern;
        std::cin >> pattern;
        patt.push_back(pattern);
    }
    AhoCorasick search(patt);
    auto result = search.search(text);
    std::map<std::string, int> patt_uniq;

    for(int i = 0; i < t; ++i){
        if(patt_uniq.find(patt[i]) == patt_uniq.end()){
            patt_uniq[patt[i]] = i;
        }
        else{
            if(result[i].second != 0){
                patt_uniq[patt[i]] = i;
            }
        }
    }
    for(int i = 0; i < t; ++i){
        std::cout << result[patt_uniq[patt[i]]].second << ' ' << result[patt_uniq[patt[i]]].first << '\n';
    }
}