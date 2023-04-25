#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>           // balance binary Tree(red-black tree)
#include <unordered_set> // hash table
#include <map>           // balance binary Tree(red-black tree)
#include <unordered_map> // hash table

// HW part. 1
// print出所有實況台裡不重複的觀眾名單

// HW part. 2 plus
// 跟part 1一樣print出觀眾名單
// 但print完第一個檔案的名單才print第二個檔案的名單

// HW part. 3
// print時說這個觀眾出現在幾個台



void add_viewers(std::vector<std::string>& vec, std::ifstream& input)
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

void add_viewers(std::set<std::string>& set, const std::string& fileName)
{
    std::ifstream file(fileName);
    std::string name;
    while (getline(file, name))
    {
        set.insert(name);
    }

}

void add_viewers(std::map<std::string, int>& map, const std::string& fileName)
{
    std::ifstream file(fileName);
    std::string name;
    while (getline(file, name))
    {
        map[name]++;
    }

}

void print_viewrsFlie(const std::string& viewrsFlie)
{
    std::ifstream file(viewrsFlie);
    std::vector<std::string> viewerList;

    add_viewers(viewerList, file);

    for (const std::string s : viewerList)
    {
        std::cout << s << std::endl;
    }

}

int main(int argc, char* argv[])
{
    print_viewrsFlie(argv[1]);
    print_viewrsFlie(argv[2]);
    print_viewrsFlie(argv[3]);

    std::cout << std::endl;
    std::cout << "以上是原名單" << std::endl << std::endl;

    //part1
    std::set<std::string> viewersSet;
    std::cout << std::endl <<  "Part1: " << std::endl << std::endl;

    add_viewers(viewersSet, argv[1]);
    add_viewers(viewersSet, argv[2]);
    add_viewers(viewersSet, argv[3]);

    for (const auto& name : viewersSet)
    {
        std::cout << name << std::endl;
    }
    std::cout << std::endl;

    //part3
    std::map<std::string, int> viewersMap;

    add_viewers(viewersMap, argv[1]);
    add_viewers(viewersMap, argv[2]);
    add_viewers(viewersMap, argv[3]);

    std::cout  << std::endl << "Part3: " << std::endl << std::endl;
    for (const auto& [name, count] : viewersMap) {
        std::cout << name << " : " << count << " times." << std::endl;
    }

    //++婚
    std::vector<std::string> filesName = { argv[1], argv[2], argv[3] };
    std::set<std::string> names;
    
    std::cout << std::endl << std::endl << "++婚: " << std::endl << std::endl;
    
    for (const auto& files : filesName) 
    {
        std::ifstream input(files);
        std::string name;
        while (getline(input, name)) 
        {
            if (names.insert(name).second) 
            {
                std::cout << name << std::endl;
            }
        }
    }

    return 0;
}
