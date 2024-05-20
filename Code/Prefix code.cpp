#include <bits/stdc++.h>
using namespace std;

struct Node
// Định nghĩa cấu trúc Node
{
    char data;  // Lưu kí tự
    int64_t freq; // Lưu tần số
    Node *left, *right; //Nút trái, phải của nút hiện tại
};

struct compare
// Hàm so sánh để sắp xếp các nút trong hàng đợi
{
    bool operator()(Node* l, Node* r)
    {
        return l->freq > r->freq;
    }
};

Node* createNode(char data, int64_t freq, Node* left, Node* right)
// Hàm tạo một nút mới
{
    Node* node = new Node();
    node->data = data;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

unordered_map<char, int64_t> freq;
void f(string s)
// Hàm đếm tần suất xuất hiện của các kí tự trong dữ liệu
{
    for (auto ch : s) freq[ch]++;
}

Node* HuffmanTree(string text)
// Hàm xây dựng cây Huffman và trả về nút gốc
{
    // Tạo hàng đợi ưu tiên chứa các nút lá
    priority_queue<Node*, vector<Node*>, compare> pq;
    // Thêm các nút lá vào hàng đợi
    for (auto pair : freq) pq.push(createNode(pair.first, pair.second, nullptr, nullptr));
    // Xây dựng cây Huffman
    while (pq.size()!= 1)
    {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        int sumFreq = left->freq + right->freq;
        pq.push(createNode('\0', sumFreq, left, right));
    }
    // Trả về nút gốc của cây Huffman
    Node* root = pq.top();
    if (root->left == NULL && root->right == NULL)
    // Nếu freq chỉ có 1 kí tự, pq sẽ rỗng và root là NULL. Nên ta xử lí riêng trường hợp này
    {
        auto i = freq.begin();
        Node* tmp = createNode(i->first, i->second, NULL, NULL);
        root->left = tmp;
    }
    return root;
}

void printCodes(Node* root, string str, unordered_map<char, string>& codes)
// Xây dựng bảng mã từ cây Huffman
{
    if (!root) return;
    if (root->data!= '\0')
        codes[root->data] = str;
    printCodes(root->left, str + "0", codes);
    printCodes(root->right, str + "1", codes);
}

void Prefixcode(Node* root)
// In bảng prefix code
{
    unordered_map<char, string> codes;
    printCodes(root, "", codes);
    ofstream output("Prefix_code.txt");
    output << freq.size() << '\n';
    for (auto ch: freq)
        output << ch.first << ":" << codes[ch.first] << '\n';
    output.close();
}

int main()
{
    string text;
    getline(cin, text);
    // Đếm tần số của các kí tự trong dữ liệu
    f(text);
    // Xây dựng cây Huffman từ dữ liệu đầu vào
    Node* root = HuffmanTree(text);
    // In bảng prefix code
    Prefixcode(root);
    return 0;
}
