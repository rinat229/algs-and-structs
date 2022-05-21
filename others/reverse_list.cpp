#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr || head->next == nullptr){
            return head;
        }
        // else if(head->next->next == nullptr){
        //     ListNode* second = head->next;
        //     second->next = head;;
        //     head->next = nullptr;
        //     return second;
        // }
        else{
            ListNode *prev = head;
            ListNode *current = head->next;
            ListNode *iter = head->next->next;
            head->next = nullptr;
            for(;iter != nullptr; iter=iter->next){
                // std::cout << prev->val << ' ' << current->val << ' ' << iter->val << '\n';
                current->next = prev;
                prev = current;
                current = iter;
                // print(prev);
            }
            current->next = prev;
            return current;
        }
    }
    
    void print(ListNode *head){
        for(;head != nullptr; head=head->next)
            std::cout << head->val << ' ';
        std::cout << '\n';
    }
};