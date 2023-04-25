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

    void insert(const std::string& word) // ���j insert word 
    {
        if (word.empty())   // ���j�פ���� �p�G�r��.empty()��true�A�N�� m_isWord = true;
        {
            m_isWord = true;
            return;
        }

        const char c = word[0]; // "w"

        if (!m_children.count(c)) // �p�Groot��m_children���s�b���"w"
        {
            m_children[c] = new TrieNode;  //�Nnew�@��TrieNode�A�åB�ŧi����map m_children����"w"�ҹ�������(�a�})
        }
        
        m_children[c]->insert(word.substr(1)); //insert ord 
        //ex. APP & APE 
        // 
        //TrieNode root 
        //bool false m_isWord;     
        //map<char,TrieNode*> m_children;   
        
        //construct root��m_isWord�Ofalse
        //�i�j�Ω����ݩ�֪�m_children

        //�g�J"APP"

        //m_children�iroot�j���s�b���'A'
        //
        //��O�ŧim_children['A']�iroot�j���ȬOnew TrieNode
        //m_children['A']�O�@�ӫ��СA���V��~new��TrieNode�A�M��b�Ӫ������insert function (�@�����j)
        //���檺�Ѽ�word�쥻�O"APP"����Fsubstr(1)�h���Ĥ@�Ӧr�Aword�]�N�O"PP"
        
        //m_children['A']�iroot�j
        //  �̭���m_children�iroot �� A�j ���s�b���'P'
        // 
        //��O�ŧim_children['P']�iroot �� A�j���ȬOnew TrieNode
        //m_children['P']�O�@�ӫ��СA���V��~new��TrieNode
        //  �M��b�Ӫ������insert function (�G�����j)
        //���檺�Ѽ�word�쥻�O"PP"����Fsubstr(1)�h���Ĥ@�Ӧr�Aword�]�N�O"P"
        
        //root��m_children['A']�iroot�j
        //  �̭���m_children['P']�iroot �� A�j
        //      �̭���m_children�iroot �� A �� P�j ���s�b���'P'
        // 
        //��O�ŧim_children['P']�iroot �� A �� P�j���ȬOnew TrieNode
        //m_children['P']�iroot �� A �� P �� P�j�O�@�ӫ��СA���V��~new��TrieNode
        //  �M��b�Ӫ������insert function (�T�����j)
        //���檺�Ѽ�word�쥻�O"P"����Fsubstr(1)�h���Ĥ@�Ӧr�Aword�]�N�O""
        //����ĤT�����j�ɡA�]���I�Wword.empty()���u�A��O����m_isWord���u�A�òפ�j�C
        
        //�g�J"APE"
       
        //m_children�iroot�j�s�b���'A'
        //
        //��O��������m_children['A']�iroot�j->insert(word.substr(1));
        //m_children['A']�O�@�ӫ��СA���V��~�w�g�إߦn��TrieNode�A�M��b�Ӫ������insert function (�@�����j)
        //���檺�Ѽ�word�쥻�O"APE"����Fsubstr(1)�h���Ĥ@�Ӧr�Aword�]�N�O"PE"

        //m_children['A']�iroot�j��m_children�iroot �� A�j�s�b���'P'
        //
        //��O��������m_children['P']�iroot �� A�j->insert(word.substr(1));
        //m_children['P']�iroot �� A�j�O�@�ӫ��СA���V��~�w�g�إߦn��TrieNode�A�M��b�Ӫ������insert function (�G�����j)
        //���檺�Ѽ�word�쥻�O"PE"����Fsubstr(1)�h���Ĥ@�Ӧr�Aword�]�N�O"E"

        //m_children['P']�iroot �� A�j���s�b���'E'
        //
        //��O��������m_children['P']�iroot �� A�j->insert(word.substr(1));
        //m_children['P']�iroot �� A�j�O�@�ӫ��СA���V��~�w�g�إߦn��TrieNode�A�M��b�Ӫ������insert function (�G�����j)
        //���檺�Ѽ�word�쥻�O"PE"����Fsubstr(1)�h���Ĥ@�Ӧr�Aword�]�N�O"E"
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

        for (const char c : prefix) // �r��̪��v�Ӧr
        {
            if (!node->children().count(c))  // ! node->children �]�N�Oconst std::map <char,TrieNode*>&  .count(c)
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
            print_words_check(child.second, prefix + child.first);  //���j+�r
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