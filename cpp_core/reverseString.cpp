#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

void reverseString(std::string &s){
    int left = 0;
    int right = static_cast<int>(s.size()) - 1;

    while (right > left)
    {
        std::swap(s[right], s[left]);
        ++left;
        --right;
    }

}

std::vector<int> twoSum(const std::vector<int> &nums, int target)
{
    std::unordered_map<int, int> seen;

    for(int i=0; i < static_cast<int>(nums.size()); ++i){
        int complement = target - nums[i];

        auto it = seen.find(complement);

        if(it != seen.end())
            return {it->second, i};
        
        seen[nums[i]] = i;
    }

    return {};
}

bool isPalindrome(const std::string &s)
{
    int left = 0;
    int right = static_cast<int>(s.size()) - 1;

    while (right > left)
    {
        if((s[right]!= s[left]))
            return false;
        ++left;
        --right;
    }

    return true;
}

template<typename T>
class Stack
{
    std::vector<T> vec;

public:

    void push(const T &value){
        vec.push_back(value);
    }

    void pop(){
        if(!vec.empty())
        {
            vec.pop_back();
        }
    }

    void T &top() const{
        return vec.back();
    }

    bool empty() const{
        return vec.empty();
    }

    size_t size() const{
        return vec.size();
    }
};

void removeDuplicates(std::vector<int> &v)
{
    std::unordered_set<int> seen;
    std::vector<int> result;
    
    for (int x : v)
    {
        if (seen.insert(x).second)  // insert возвращает pair<iterator, bool>
        {
            result.push_back(x);
        }
    }
    
    v = std::move(result);
}

void removeDuplicates(std::vector<int> &v)
{
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
}