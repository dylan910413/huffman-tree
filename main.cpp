#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;
int number[26];
string code_list[26], Data, encode, input, huffman;
char word[26];
char word2[60];
int number2[60];
string code_list2[60];
struct Node {   
    int alphabet, weight;
    Node *left, *right;
};
struct compare{
    bool operator() (Node *a, Node *b) {
        return a -> weight > b -> weight;
    }
};
void encoding(Node *cur, string record){
    if (cur -> alphabet != -1) {
        code_list[cur -> alphabet] = record;
    }else {
        encoding(cur -> left, record + "0");
        encoding(cur -> right, record + "1");
    }
}
void encoding2(Node *cur, string record){
    if (cur -> alphabet != -1) {
        code_list2[cur -> alphabet] = record;
    }else {
        encoding2(cur -> left, record + "0");
        encoding2(cur -> right, record + "1");
    }
}
void decoding(Node *root) {
    cout << "decode : ";
    Node *cur = root;
    for (int i = 0; i < huffman.size(); i++) {
        if (huffman[i] == '0') {
            cur = cur -> left;
        }else {
            cur = cur -> right;
        }
        if (cur -> alphabet != -1) {
            cout << char(cur -> alphabet + 'A');
            cur = root;
        }
    }
    cout << endl;
}
void output2(){
    cout << "characters : " << Data << endl;
    cout << endl;
    int WEPL = 0;
    for (int i = 0; i < 60; i++) {
        if(code_list2[i]!="")
            cout << char (i + 'A') << " : " << code_list2[i] << endl;
            WEPL = WEPL + code_list2[i].size() * number2[i];
    }
    cout<<endl;
    cout << "Huffman code : " << huffman <<endl;
    cout << "WEPL : " << WEPL << endl;
}
void output1(){
    int WEPL = 0;
    for (int i = 0; i < 26; i++) {
        if(code_list[i]!="")
            cout << char (i + 'A') << " : " << code_list[i] << endl;
            WEPL = WEPL + code_list[i].size() * number[i];
    }
    cout << endl;
    cout << "WEPL : " << WEPL << endl;
}

int main(int argc, const char* argv[]){
    vector<string> all_args;
    all_args.assign(argv, argv + argc); // convert command line argument to string 

    cout << "DSOO-Program2-Demo: ";
    for(auto a : all_args){
        cout << a << " ";
    }
    cout << "\n";
    
    if(argc != 2){
        cout << "part1\n";
        for(int i=0;i<26;i++){
            word[i] = char(i+'A');
        }
        number[0] = 11; number[1] = 5; number[2] = 2; number[3] = 3; number[4] = 12; number[5] = 3; number[6] = 5;
        number[7] = 6; number[8] = 8; number[9] = 1; number[10] = 2; number[11] = 4; number[12] = 8; number[13] = 7;
        number[14] = 2; number[15] = 2; number[16] = 1; number[17] = 9; number[18] = 6; number[19] = 2; number[20] = 4;
        number[21] = 1; number[22] = 10; number[23] = 10; number[24] = 1; number[25] = 1;
        int change = 0;
        for(int i=0 ; i < 26; i++){
            if(number[i]>=10) cout<<word[i]<<" = "<<number[i]<<" | ";
            else cout<<word[i]<<" =  "<<number[i]<<" | ";
            change++;
            if(change == 10){
                cout<<endl;
                change = 0;
            } 
        }
        cout << endl;
        cout << endl;
        priority_queue<Node*, vector<Node*>, compare> pq1;
        for (int i = 0; i < 26; i++) {
            if (number[i] == 0) continue;
            Node *leaf = new Node;
            leaf -> weight = number[i];
            leaf -> alphabet = i;
            leaf -> left = leaf -> right = NULL;
            pq1.push(leaf);
        }
        while (pq1.size() > 1) {
            Node *cur = new Node, *a, *b;
            a = pq1.top();
            pq1.pop();
            b = pq1.top();
            pq1.pop();
            cur -> weight = a -> weight + b -> weight;
            cur -> alphabet = -1;
            cur -> left = a;
            cur -> right = b;
            pq1.push(cur);
        }
        Node *root = pq1.top();
        encoding(root, "");
        output1();


    }else{
        string filename = argv[1];
        cout << "read file from : " << "test/" << filename << endl;
        ifstream ifs(filename);
        int t=1;
        while(ifs>>Data>>huffman){
            break;
        }
        for (int i = 0; i < Data.size(); i++) {
            number2[Data[i] - 'A']++;
            word2[Data[i] - 'A'] = Data[i];
        }
        int change = 0;
        for(int i=0 ; i < 60; i++){
            if(number2[i]==0) continue;
            if(number2[i]>=10) cout<<word2[i]<<" = "<<number2[i]<<" | ";
            else cout<<word2[i]<<" =  "<<number2[i]<<" | ";
            change++;
            if(change == 10){
                cout<<endl;
                change = 0;
            } 
        }
        priority_queue<Node*, vector<Node*>, compare> pq;
        for (int i = 0; i < 60; i++) {
            if (number2[i] == 0) continue;
            Node *leaf = new Node;
            leaf -> weight = number2[i];
            leaf -> alphabet = int(word2[i])-'A';
            leaf -> left = leaf -> right = NULL;
            pq.push(leaf);
        }
        while (pq.size() > 1) {
            Node *cur = new Node, *a, *b;
            a = pq.top();
            pq.pop();
            b = pq.top();
            pq.pop();
            cur -> weight = a -> weight + b -> weight;
            cur -> alphabet = -1;
            cur -> left = a;
            cur -> right = b;
            pq.push(cur);
        }
        
        cout << endl;
        Node *root = pq.top();
        encoding2(root, "");
        output2();
        decoding(root); 
    }
    return 0;
}