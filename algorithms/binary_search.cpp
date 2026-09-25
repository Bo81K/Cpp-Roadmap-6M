#include <cassert>
#include <cstddef>
#include <iostream>
#include <optional>
#include <vector>

std::optional<std::size_t> binary_search_index(
    const std::vector<int>& arr,
    int target)
{
    std::size_t left = 0;
    std::size_t right = arr.size(); //полуинтервал [left, right)

    while(left < right){
        std::size_t mid = left + (right - left) / 2;

        if(arr[mid] == target)
            return mid;

        if(arr[mid] < target)
            left = mid + 1;
        else
            right = mid; 
    }
    return std::nullopt;
}

void expect_found(const std::vector<int>& arr, int target, std::size_t expect_index){
    auto result = binary_search_index(arr, target);
    assert(result.has_value());
    assert(*result == expect_index);  
}

void expect_not_found(const std::vector<int>& arr, int target){
    auto result = binary_search_index(arr, target);
    assert(!result.has_value());
}

int main(){
    std::vector<int> numbers = {1, 3, 5, 7, 9, 11};

    expect_found(numbers, 1, 0);
    expect_found(numbers, 11, 5);
    expect_found(numbers, 5, 2);
    expect_found(numbers, 7, 3);

    expect_not_found(numbers, 0);
    expect_not_found(numbers, 4);
    expect_not_found(numbers, 12);

    std::vector<int> empty;
    expect_not_found(empty, 1);

    std::cout << "binary_search test passed\n";

    return 0;
}