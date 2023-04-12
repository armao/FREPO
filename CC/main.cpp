#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>           // balance binary Tree(red-black tree)
#include <unordered_set> // hash table
#include <map>           // balance binary Tree(red-black tree)
#include <unordered_map> // hash table

// HW part. 1
// print�X�Ҧ���p�x�̤����ƪ��[���W��

// HW part. 2 plus
// ��part 1�@��print�X�[���W��
// ��print���Ĥ@���ɮת��W��~print�ĤG���ɮת��W��

// HW part. 3
// print�ɻ��o���[���X�{�b�X�ӥx



void add_viewer(std::vector<std::string>& vec, std::ifstream& input)
{
    do
    {
        std::string str;
        input >> str;
        if (!input.fail())
        {
            vec.push_back(str);
        }
        else
        {
            break;
        }

    } while (true);
}

std::vector<std::string> create_viewer_list(const std::string& fileName)
{
    std::ifstream file(fileName);
    std::vector<std::string> viewerList;

    add_viewer(viewerList, file);

    return viewerList;
}

void print_viewrs(const std::vector<std::string>& viewerList)
{
    for (const std::string s : viewerList)
    {
        std::cout << s << std::endl;
    }
}


struct viewer
{
    void add_times()
    {
        m_times += 1;
    }

    std::string m_name;
    int m_times = 0;
};

int main(int argc, char* argv[])
{
    print_viewrs(create_viewer_list("veiwers1.txt"));
    print_viewrs(create_viewer_list("veiwers2.txt"));
    print_viewrs(create_viewer_list("veiwers3.txt"));

    std::set<std::string> set1;

    for (const std::string s : create_viewer_list("veiwers1.txt"))
    {
        set1.insert(s);
    }

    for (const std::string s : create_viewer_list("veiwers2.txt"))
    {
        set1.insert(s);
    }

    for (const std::string s : create_viewer_list("veiwers3.txt"))
    {
        set1.insert(s);
    }

    std::map<std::string, viewer> map1;

    for (const auto& s : set1) 
    {
        map1[s] = {s};
        std::cout << s << " | ";
    }
    std::cout << std::endl;

    for (const auto& m : map1) {
        std::cout << "key: " << m.first << " name: " << m.second.m_name << " times: " << m.second.m_times << std::endl;
    }

    

    return 0;
}