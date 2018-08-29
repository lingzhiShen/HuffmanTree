#include "HuffmanTree.h"
#include <stack>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

typedef pair<BinNode *, int> HUFFMAN_PAIR;
bool CompareByVal(const HUFFMAN_PAIR &parameter1, const HUFFMAN_PAIR &parameter2)
{
    return parameter1.second < parameter2.second;
}

HuffmanTree::HuffmanTree()
    :__T(NULL), __m_content("")
{
    __m_huffmanTable.clear();
    //ctor
}

HuffmanTree::HuffmanTree(std::string content)
    :__T(NULL), __m_content(content)
{
    __m_huffmanTable.clear();
}

static void ReleaseNode(BinNode *node)
{
    free(node);
}

HuffmanTree::~HuffmanTree()
{
    //dtor
    __RetrOrderTravel_rec(__T, ReleaseNode);
}

void HuffmanTree::CreateHuffmanTree()
{
    if (__m_content.empty())
    {
        return ;
    }

    map<char, int> charPowerMap;
    map<BinNode *, int> huffmanPowerMap;
    // assemble data and power
    for (int i = 0; i < __m_content.size(); ++i)
    {
        if (charPowerMap.find(__m_content[i]) != charPowerMap.end())
        {
            charPowerMap[__m_content[i]]++;
        }
        else
        {
            charPowerMap.insert(make_pair(__m_content[i], 1));
        }
    }

    // char & power node translate to HuffmanNode
    for (map<char, int>::iterator iter = charPowerMap.begin(); iter != charPowerMap.end(); ++iter)
    {
        BinNode *node = new BinNode;
        node->data = iter->first;
        node->lChild = NULL;
        node->rChild = NULL;
        huffmanPowerMap.insert(make_pair(node, iter->second));
    }

    // sort by power
    vector<HUFFMAN_PAIR> vec(huffmanPowerMap.begin(), huffmanPowerMap.end());
    sort(vec.begin(), vec.end(), CompareByVal);

    vector<HUFFMAN_PAIR>::iterator iter = vec.begin();
    while ( iter != vec.end() && iter+1 != vec.end())
    {
        //cout << iter->first->data << " / " << iter->second << endl;
        BinNode *limbNode = new BinNode;
        // TO DEBUG
//        static int flogs = 'h';
//        int ii = flogs++;
        limbNode->data = ' ';
        limbNode->lChild = iter->first;
        limbNode->rChild = (iter+1)->first;

        vec.erase(iter, iter+2);
        vec.push_back(make_pair(limbNode, limbNode->rChild->data+limbNode->lChild->data));
        sort(vec.begin(), vec.end(), CompareByVal);
        iter = vec.begin();
    }

    __T = vec[0].first;
}

void HuffmanTree::CreateHuffmanTree(const std::map<TElemType, std::string> &codeTable)
{
    if (__T != NULL)
        return ;

    __T = new BinNode;
    __T->lChild = NULL;
    __T->rChild = NULL;
    __T->data = ' ';
    BinNode *p = __T;
    for (map<TElemType, std::string>::const_iterator con_iter = codeTable.begin(); con_iter != codeTable.end(); ++con_iter)
    {
        string code = con_iter->second;
        for (int i = 0; i < code.size(); ++i)
        {
            if (code[i] == '0')
            {
                if (p->lChild == NULL)
                {
                    p->lChild = new BinNode;
                    p->lChild->data = ' ';
                    p->lChild->lChild = NULL;
                    p->lChild->rChild = NULL;
                }
                p = p->lChild;
            }
            else if (code[i] == '1')
            {
                if (p->rChild == NULL)
                {
                    p->rChild = new BinNode;
                    p->rChild->data = ' ';
                    p->rChild->lChild = NULL;
                    p->rChild->rChild = NULL;
                }
                p = p->rChild;
            }
        }
        p->data = con_iter->first;
        p = __T;
    }
}

static void printNodeData(BinNode *node)
{
    cout << "v : " << node->data << endl;
}

void HuffmanTree::TravelHuffmanTree_in()
{
    cout << "----------TravelHuffmanTree_inOrd------------" << endl;
    __InOrderTravel_rec(__T, printNodeData);
    cout << "/////////////////////////////" << endl;
}

void HuffmanTree::TravelHuffmanTree_pre()
{
    cout << "----------TravelHuffmanTree_pre------------" << endl;
    __PreOrderTravel_rec(__T, printNodeData);
    cout << "/////////////////////////////" << endl;
}

void HuffmanTree::__PreOrderTravel_rec(BinTree node, visitFunc func)
{
    if (node == NULL)
        return ;

    func(node);
    __PreOrderTravel_rec(node->lChild, func);
    __PreOrderTravel_rec(node->rChild, func);
}

void HuffmanTree::__InOrderTravel_rec(BinTree node, visitFunc func)
{
    if (node == NULL)
        return ;

    __InOrderTravel_rec(node->lChild, func);
    func(node);
    __InOrderTravel_rec(node->rChild, func);
}

void HuffmanTree::__RetrOrderTravel_rec(BinTree node, visitFunc func)
{
    if (node == NULL)
        return ;

    __RetrOrderTravel_rec(node->lChild, func);
    __RetrOrderTravel_rec(node->rChild, func);
    func(node);
}

void HuffmanTree::__PreOrderTravel(BinTree node, visitFunc func)
{
    stack<BinNode *> s;
    BinNode *p = __T;

    while (p != NULL || !s.empty())
    {
        while (p != NULL)
        {
            func(p);
            s.push(p);
            p = p->lChild;
        }

        if (!s.empty())
        {
            p = s.top();
            s.pop();
            p = p->rChild;
        }
    }
}

void HuffmanTree::__TraceRoute(BinTree node)
{
    static vector<char> route;
    if (node != NULL)
    {
        route.push_back('0');
        __TraceRoute(node->lChild);
        if (node->data != ' ')
        {
            string code(route.begin(), route.end());
            __m_huffmanTable.insert(make_pair(node->data, code));
        }
        route.push_back('1');
        __TraceRoute(node->rChild);
    }
    route.pop_back();
}

// in order to travel binTree
void HuffmanTree::GenHuffmanCodeTable()
{
    if (__T == NULL)
        return ;

    BinNode *p = __T;
    __TraceRoute(p);
}

void HuffmanTree::EnCode(std::string &code)
{
    for (int i = 0; i < __m_content.size(); ++i)
    {
        code += __m_huffmanTable[__m_content[i]];
    }
    __m_huffmanCode = code;
}

void HuffmanTree::EnCode(std::string &code, const std::string &content)
{
    // TO DO
    __m_content = content;
    CreateHuffmanTree();
    GenHuffmanCodeTable();
    EnCode(code);
}

void HuffmanTree::DeCode(std::string &content)
{
    if (__T == NULL)
        return ;

    BinNode *p = __T;
    for (int i = 0; i < __m_huffmanCode.size(); ++i)
    {
        if (__m_huffmanCode[i] == '0')
        {
            p = p->lChild;
        }
        else if (__m_huffmanCode[i] == '1')
        {
            p = p->rChild;
        }

        if (p->data != ' ')
        {
            content += p->data;
            p = __T;
        }
    }
}

void HuffmanTree::DeCode(std::string &content, const std::string &code, const std::map<TElemType, std::string> &codeTable)
{
    CreateHuffmanTree(codeTable);
    __m_huffmanCode = code;
    DeCode(content);
}

void HuffmanTree::DeCode(std::string &content, const std::string &code)
{
    __m_huffmanCode = code;
    DeCode(content);
}

void HuffmanTree::PrintHuffmanTable()
{
    for (map<char, string>::iterator iter = __m_huffmanTable.begin(); iter != __m_huffmanTable.end(); ++iter)
    {
        cout << "data : " << iter->first << "   code : " << iter->second << endl;
    }
}

void HuffmanTree::StoreHuffmanTree()
{
    ofstream file("HuffmanTree");
    if (file.is_open())
    {
        for (map<TElemType ,std::string>::iterator iter = __m_huffmanTable.begin(); iter != __m_huffmanTable.end(); ++iter)
        {
            string data = "x";
            data[0] = iter->first;
            string item = data + string("=") + iter->second;
            file << item << endl;
        }

        file.close();
    }
}

void HuffmanTree::RestoreHuffmanTree()
{
    char buffer[256];
    ifstream file("HuffmanTree");
    if (file.is_open())
    {
        map<TElemType, string> huffmanTable;
        while (file.peek() != EOF)
        {
            file.getline(buffer, 256);
            string item = buffer;

            string::size_type pos;
            pos = item.find("=");

            string key = item.substr(0, pos);
            string value = item.substr(pos+1, item.length()+1);

            huffmanTable.insert(make_pair(key[0], value));
        }
        CreateHuffmanTree(huffmanTable);
        file.close();
    }
}
