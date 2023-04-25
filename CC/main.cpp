#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>           // balance binary Tree(red-black tree)
#include <unordered_set> // hash table
#include <map>           // balance binary Tree(red-black tree)
#include <unordered_map> // hash table
#include "human.h"

class TrieNode 
{
public:
    TrieNode() : m_isWord(false) {}

    ~TrieNode()
    {
        for (auto& node : m_children)
        {
            delete node.second;
            node.second = nullptr;
        }
    }

    void insert(const std::string& word) // 遞迴 insert word 
    {
        if (word.empty())   // 遞迴終止條件 如果字串.empty()為true，就讓 m_isWord = true;
        {
            m_isWord = true;
            return;
        }

        const char c = word[0]; // "w"

        if (!m_children.count(c)) // 如果root的m_children不存在鍵值"w"
        {
            m_children[c] = new TrieNode;  //就new一個TrieNode，並且宣告等於map m_children中鍵"w"所對應的值(地址)
        }
        
        m_children[c]->insert(word.substr(1)); //insert ord 
        //ex. APP & APE 
        // 
        //TrieNode root 
        //bool false m_isWord;     
        //map<char,TrieNode*> m_children;   
        
        //construct root的m_isWord是false
        //【】用於表示屬於誰的m_children

        //寫入"APP"

        //m_children【root】不存在鍵值'A'
        //
        //於是宣告m_children['A']【root】的值是new TrieNode
        //m_children['A']是一個指標，指向剛才new的TrieNode，然後在該物件執行insert function (一次遞迴)
        //執行的參數word原本是"APP"執行了substr(1)去掉第一個字，word也就是"PP"
        
        //m_children['A']【root】
        //  裡面的m_children【root → A】 不存在鍵值'P'
        // 
        //於是宣告m_children['P']【root → A】的值是new TrieNode
        //m_children['P']是一個指標，指向剛才new的TrieNode
        //  然後在該物件執行insert function (二次遞迴)
        //執行的參數word原本是"PP"執行了substr(1)去掉第一個字，word也就是"P"
        
        //root的m_children['A']【root】
        //  裡面的m_children['P']【root → A】
        //      裡面的m_children【root → A → P】 不存在鍵值'P'
        // 
        //於是宣告m_children['P']【root → A → P】的值是new TrieNode
        //m_children['P']【root → A → P → P】是一個指標，指向剛才new的TrieNode
        //  然後在該物件執行insert function (三次遞迴)
        //執行的參數word原本是"P"執行了substr(1)去掉第一個字，word也就是""
        //執行第三次遞迴時，因為碰上word.empty()為真，於是讓其m_isWord為真，並終止遞迴。
        
        //寫入"APE"
       
        //m_children【root】存在鍵值'A'
        //
        //於是直接執行m_children['A']【root】->insert(word.substr(1));
        //m_children['A']是一個指標，指向剛才已經建立好的TrieNode，然後在該物件執行insert function (一次遞迴)
        //執行的參數word原本是"APE"執行了substr(1)去掉第一個字，word也就是"PE"

        //m_children['A']【root】的m_children【root → A】存在鍵值'P'
        //
        //於是直接執行m_children['P']【root → A】->insert(word.substr(1));
        //m_children['P']【root → A】是一個指標，指向剛才已經建立好的TrieNode，然後在該物件執行insert function (二次遞迴)
        //執行的參數word原本是"PE"執行了substr(1)去掉第一個字，word也就是"E"

        //m_children['P']【root → A】不存在鍵值'E'
        //
        //於是直接執行m_children['P']【root → A】->insert(word.substr(1));
        //m_children['P']【root → A】是一個指標，指向剛才已經建立好的TrieNode，然後在該物件執行insert function (二次遞迴)
        //執行的參數word原本是"PE"執行了substr(1)去掉第一個字，word也就是"E"
    }

    bool isWord() const 
    {
        return m_isWord;
    }

    const std::map<char, TrieNode*>& children() const 
    {
        return m_children;
    }

private:
    bool m_isWord;
    std::map<char, TrieNode*> m_children;

};

class MultiWayTrie 
{
public:
    MultiWayTrie(const std::string& dictionary_file_path) 
    {
        std::ifstream input_file(dictionary_file_path);
        std::string word;

        while (getline(input_file, word)) 
        {
            m_root.insert(word);
        }

    }

    void print_prefix_words(const std::string& prefix) const 
    {
        const TrieNode* node = &m_root;

        for (const char c : prefix) // 字串裡的逐個字
        {
            if (!node->children().count(c))  // ! node->children 也就是const std::map <char,TrieNode*>&  .count(c)
            {
                return;
            }

            node = node->children().at(c);
        }

        print_words_check(node, prefix);
    }

private:
    void print_words_check(const TrieNode* node, const std::string& prefix) const
    {
        if (node->isWord()) 
        {
            std::cout << prefix << std::endl;
        }

        for (const auto& child : node->children())  
        {
            print_words_check(child.second, prefix + child.first);  //遞迴+字
        }

    }

    TrieNode m_root;
};

int main(int argc, char* argv[])
{
    std::string prefix;
    while (true) 
    {
        MultiWayTrie trie(argv[4]);

        
        std::cin >> prefix;

        trie.print_prefix_words(prefix);

    }

    //std::map<int, human*> m;
    //std::map<int, human> m2;
    //human* h = new human("bob");
    //human h2 ("dada");
    //std::cout << h->name() << std::endl;
    //std::cout << h2.name() << std::endl;
    //m[1] = h;
    //m[1]->set_name("ouo");
    //m2.emplace(1, h2);
    //m2.at(1).set_name("DAHDAH!");
    ////m2[1] = h2;
    ////m2[1].set_name("DAHDAH!");
    ////h2.set_name("DAHDAH!");

    //std::cout << *m[1] << std::endl;
    //std::cout << m2.at(1) << std::endl;
    //std::cout << h2.name() << std::endl;

    //delete h;

    return 0;
}