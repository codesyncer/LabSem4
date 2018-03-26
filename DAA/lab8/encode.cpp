#include <queue>
#include <map>
#include <iostream>
using namespace std;

class Node {
public:
int freq;
char sym;
Node *left, *right;
Node(){

}
Node(char sym, int freq, Node *left=nullptr, Node *right=nullptr){
        this->sym = sym;
        this->freq = freq;
        this->left = left;
        this->right = right;
}
void set(char sym, int freq, Node *left=nullptr, Node *right=nullptr){
        this->sym = sym;
        this->freq = freq;
        this->left = left;
        this->right = right;
}
bool leaf(){
        return this->left == nullptr && this->right == nullptr;
}
};
void print(Node *root, string &encode){
        if (root->leaf())
                cout<<root->sym<<": "<<encode<<endl;
        else{
                encode.append(1,'0');
                print(root->left, encode);
                encode.pop_back();
                encode.append(1,'1');
                print(root->right, encode);
                encode.pop_back();
        }
}
void deleteTree(Node *root){
        if(root == nullptr) return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
}
struct cmp
{
        bool operator()(const Node * lhs, const Node * rhs) const
        {
                return lhs->freq > rhs->freq;
        }
};
int main(){
        int n = 6;
        char symTable[n] = {'a', 'b', 'c','d', 'e', 'f'};
        int freqTable[n] = {20, 12, 10, 8, 4, 3};
        priority_queue<Node*, vector<Node*>, cmp> heap;
        for(int i=0; i<n; ++i)
                heap.push(new Node(symTable[i], freqTable[i]));
        while(heap.size() >= 2) {
                Node *t1 = heap.top(); heap.pop();
                Node *t2 = heap.top(); heap.pop();
                heap.push(new Node('x', t1->freq+t2->freq, t2, t1));
        }
        Node *root = heap.top();
        string str = string("");
        print(root, str);
        deleteTree(root);
        return 0;
}
