#include "HuffmanTree.h"
#include <iostream>

using namespace std;

int main()
{
    HuffmanTree hfman;//("adswcdssdwaa");
//    hfman.CreateHuffmanTree();
//    hfman.TravelHuffmanTree_in();
//    hfman.TravelHuffmanTree_pre();
//    hfman.GenHuffmanCodeTable();
//    hfman.PrintHuffmanTable();

// TO ENCODE
//    string code;
//    hfman.EnCode(code, "dawdsfdgfddgfdgeqwqqbbnxcxvcxvqqqasd");
//    cout << "huffman code : " << code << endl;
//    hfman.StoreHuffmanTree();

// TO DECODE
    string content;
    hfman.RestoreHuffmanTree();
    hfman.DeCode(content, "00000000000101100000000110000100000000000110000100000000000000000110000100000000000110001001111011011000001100000110001101000100101000100101001101101100000100011000000");
    cout << "content : " << content << endl;


//    map<TElemType, std::string> table;
//    table.clear();
//    table.insert(make_pair('a', "0"));
//    table.insert(make_pair('b', "11"));
//    table.insert(make_pair('c', "10"));
//    string content1;
//    HuffmanTree tree;
//    tree.DeCode(content1, "0111000011", table);
//    tree.TravelHuffmanTree();
//    cout << "content1 : " << content1 << endl;

    return 0;
}
