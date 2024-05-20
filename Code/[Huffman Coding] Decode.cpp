#include <bits/stdc++.h>

using namespace std;

struct Node
// Định nghĩa cấu trúc Node
{
    char data;  // Lưu kí tự
    int64_t freq; // Lưu tần số
    Node *left, *right; //Nút trái, phải của nút hiện tại
};

Node* createNode(char data, Node* left, Node* right)
// Hàm tạo một nút mới
{
    Node* node = new Node();
    node->data = data;
    node->left = left;
    node->right = right;
    return node;
}

Node* HuffmanTree(Node* root, const string& s, char data)
// Hàm xây dựng cây Huffman và trả về nút gốc
{
    Node* current = root;
    for (char ch : s)
    {
        if (ch == '0') // Nếu là bit 0 thì chuyển sang nút trái
        {
            if (!current->left)
                current->left = createNode('\0', nullptr, nullptr);
            current = current->left;
        }
        else // Ngược lại chuyển sang nút phait
        {
            if (!current->right)
                current->right = createNode('\0', nullptr, nullptr);
            current = current->right;
        }
    }
    current->data = data; // Gán nút lá là kí tự
    return root;
}

// Hàm giải nén
string decode(Node* root, const string& encodedText)
{
    string decodedText;
    Node* curr = root;
    for (char bit : encodedText)
    {
        if (bit == '0')
            curr = curr->left;
        else
            curr = curr->right;

        if (curr->left == nullptr && curr->right == nullptr)
        {
            decodedText += curr->data;
            curr = root;
        }
    }
    return decodedText;
}

int main()
{
    ifstream encoded("Encoded.txt"), prefix("Prefix_code.txt");
    string encodedText;
    getline(encoded, encodedText);
    int n;
    prefix >> n;
    prefix.ignore();
    Node* root = new Node();
    for (int i = 0; i < n; i++)
    {
        string text;
        getline(prefix, text);
        string s = text.substr(2);
        root = HuffmanTree(root, s, text[0]);
    }
    prefix.close(); encoded.close();
    // Giải nén
    string decodedText = decode(root, encodedText);
    cout << decodedText;
    return 0;
}

