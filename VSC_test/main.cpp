#include <iostream>
#include <vector>
#include <string>

using namespace std;

const size_t DEFAULT_SIZE = 8;
const size_t RESIZE_FACTOR = 2;
const double MAX_ALPHA = 2/3;

template <typename T>
struct HashNode
{
    HashNode() : mark("clear") {}
    HashNode(const T &key, string mark)
        : key(key), mark(mark)
    {
        
    }
    T key;
    string mark;
};

size_t Hash(const std::string &s, size_t size)
{
    size_t hash = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        hash = hash * 73 + s[i];
    }
    return hash % size;
}

template <typename T>
class HashTable
{
public:
    HashTable(size_t size = DEFAULT_SIZE)
        : table(size, nullptr), size(0)
    {
        
    }
    ~HashTable()
    {
        for (size_t i = 0; i < table.size(); i++)
        {
            HashNode<T> *node = table[i];
            delete node;
        }
    }
    
    bool Add(const T &key)
    {
        if (size > table.size() * 2/3)
            grow();
        
        size_t hash = Hash(key, table.size());
        
        HashNode<T> *node = table[hash];
        size_t step = 1;
        while (node != nullptr)
        {
            if ((table[hash])->key == key && node->mark != "deleted") {
                return false;
            }
            hash = (hash + step) % table.size();
            node = table[hash];
            step++;
        }
        
        table[hash] = new HashNode<T>(key, "occupied");
        size++;
        return true;
    }
    
    bool Delete(const T &key)
    {
        size_t hash = Hash(key, table.size());
        
        HashNode<T> *node = table[hash];
        size_t step = 1;
        if (node == nullptr)
            return false;
        while (node->mark == "deleted" || (table[hash])->key != key  )
        {
            hash = (hash + step) % table.size();
            node = table[hash];
            step++;
            if (node == nullptr)
                return false;
        }
                
        node->mark = "deleted";
        return true;
    }
    
    bool Has(const T &key)
    {
        size_t hash = Hash(key, table.size());
        
        HashNode<T> *node = table[hash];
        size_t step = 1;
        if (node == nullptr)
            return false;
        while (node->key != key || node->mark == "deleted")
        {
            hash = (hash + step) % table.size();
            node = table[hash];
            step++;
            if (node == nullptr)
                return false;
        }
        
        return node != nullptr;
    }
private:
    std::vector<HashNode<T>*> table;
    size_t size;
    const double alpha = 2/3;
    
    void grow()
    {
        std::vector<HashNode<T>*> newTable(table.size() * RESIZE_FACTOR, nullptr);
        
        for (size_t i = 0; i < table.size(); i++)
        {
            HashNode<T> *node = table[i];
            if (node == nullptr) {
                continue;
            }
            if (node->mark == "deleted") {
                delete table[i];
                continue;
            }
            size_t newHash = Hash(node->key, newTable.size());
            size_t step = 1;
            HashNode<T> *tmp = newTable[newHash];
            while (tmp != nullptr)
            {
                newHash = (newHash + step) % newTable.size();
                tmp = newTable[newHash];
                step++;
            }
            newTable[newHash] = new HashNode<T>(node->key, "occupied");
            delete table[i];
        }
        table = std::move(newTable);
    }
};

int main(int argc, const char * argv[]) {
    HashTable<std::string> *h = new HashTable<std::string>;
    
    char op;
    std::string key;
    while (std::cin >> op >> key)
    {
        if (op == '+')
        {
            std::cout << (h->Add(key) ? "OK" : "FAIL") << std::endl;
        }
        if (op == '-')
        {
            std::cout << (h->Delete(key) ? "OK" : "FAIL") << std::endl;
        }
        if (op == '?')
        {
            std::cout << (h->Has(key) ? "OK" : "FAIL") << std::endl;
        }
    }
    delete h;
    return 0;
}
