#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <bits/stdc++.h>
#include "readwrite.h"

using namespace std;

vector<int> freq(256, 0);

void CountFreq(vector<uint8_t> arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        freq[int(arr[i])]++;
    }
}

class TreeNode
{
public:
    int pixel;
    int freq;
    //int width;
    //int hight;

    TreeNode *left;
    TreeNode *right;

    TreeNode(int data, int frequency)
    {
        pixel = data;
        freq = frequency;
        left = right = NULL;
    }
};

class Compare
{
public:
    bool operator()(TreeNode *l, TreeNode *r)
    {
        return l->freq > r->freq;
    }
};

TreeNode *generateTree(priority_queue<TreeNode *, vector<TreeNode *>, Compare> pq)
{

    // We keep on looping till
    // only one node remains in
    // the Priority Queue
    while (pq.size() != 1)
    {

        TreeNode *left = pq.top();

        pq.pop();

        TreeNode *right = pq.top();

        pq.pop();

        TreeNode *node = new TreeNode(-1, left->freq + right->freq);
        node->left = left;
        node->right = right;

        pq.push(node);
    }

    return pq.top();
}

void storeCodes(TreeNode *root, map<int, string> &codes, string top)
{
    if (root->pixel != -1)
        codes[root->pixel] = top;
    if (root->left != NULL)
        storeCodes(root->left, codes, top + "0");
    if (root->right != NULL)
        storeCodes(root->right, codes, top + "1");
}

map<int, string> HuffmanCodes(vector<int> freq)
{

    priority_queue<TreeNode *, vector<TreeNode *>, Compare> pq;

    for (int i = 0; i < 256; ++i)
        if (freq[i] > 0)
            pq.push(new TreeNode(i, freq[i]));

    TreeNode *root = generateTree(pq);

    string top = "";
    map<int, string> codes;
    storeCodes(root, codes, top);
    return codes;
}

map<string, int> InverseCode(const map<int, string> encTable)
{
    map<string, int> invTable;
    //Constructing an inverse table for the coded table
    for (auto it = encTable.begin(); it != encTable.end(); it++)
        invTable[it->second] = it->first;
    return invTable;
}

vector<uint8_t> decode(const string bits, map<string, int> &invTable, const int width, const int height)
{
    string temp = "";

    int x = 0;
    vector<uint8_t> newimg;
    for (int i = 0; i < bits.size(); i++) //making the origin data
    {

        temp += bits[i];
        if (invTable.count(temp))
        {
            newimg.push_back(invTable[temp]);
            temp = "";
        }
    }
    return newimg;
}


#endif // HUFFMANTREE_H
