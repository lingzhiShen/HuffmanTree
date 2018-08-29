#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <string>
#include <map>
#include <vector>

typedef char TElemType;

typedef struct BinTreeNode
{
    TElemType data;
    struct BinTreeNode *lChild;
    struct BinTreeNode *rChild;
}BinNode, *BinTree;

class HuffmanTree
{
    typedef void (*visitFunc)(BinNode *node);
    public:
        HuffmanTree();
        HuffmanTree(std::string content);
        virtual ~HuffmanTree();

        void SetContent(const std::string &content)
        {
            __m_content = content;
        }
        std::string GetContent() const
        {
            return __m_content;
        }

        void SetHuffmanCode(const std::string &code)
        {
            __m_huffmanCode = code;
        }
        std::string GetHuffmanCode() const
        {
            return __m_huffmanCode;
        }

        void CreateHuffmanTree();
        void CreateHuffmanTree(const std::string &content);
        void CreateHuffmanTree(const std::map<TElemType, std::string> &codeTable);

        void TravelHuffmanTree_in();
        void TravelHuffmanTree_pre();

        void GenHuffmanCodeTable();

        void EnCode(std::string &code);
        void EnCode(std::string &code, const std::string &content);
        void DeCode(std::string &content);
        void DeCode(std::string &content, const std::string &code);
        void DeCode(std::string &content, const std::string &code, const std::map<TElemType, std::string> &codeTable);

        void PrintHuffmanTable();

        void StoreHuffmanTree();
        void RestoreHuffmanTree();

    protected:

    private:
        BinTree __T;
        std::string __m_content;
        std::string __m_huffmanCode;
        std::map<TElemType ,std::string> __m_huffmanTable;

        //void PreOrderTravel();
        void __PreOrderTravel_rec(BinTree node, visitFunc func);
        void __InOrderTravel_rec(BinTree node, visitFunc func);
        void __RetrOrderTravel_rec(BinTree node, visitFunc func);

        void __PreOrderTravel(BinTree node, visitFunc func);

        void __TraceRoute(BinTree node);
};

#endif // HUFFMANTREE_H
