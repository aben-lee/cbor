#include "CborObject.h"
#include <iostream>

int main() {
    CborObject::CborObject obj;

    // 测试 AddAsFirst(int64_t)
    if (obj.AddAsFirst(987654321LL)) {
        std::cout << "AddAsFirst(int64_t) passed." << std::endl;
    }
    else {
        std::cout << "AddAsFirst(int64_t) failed." << std::endl;
    }

    // 测试 AddAsFirst(string)
    std::string testString = "Test String";
    if (obj.AddAsFirst(testString)) {
        std::cout << "AddAsFirst(string) passed." << std::endl;
    }
    else {
        std::cout << "AddAsFirst(string) failed." << std::endl;
    }

    // 测试 Replace 函数
    if (obj.Replace(0, "New String")) {
        std::cout << "Replace passed." << std::endl;
    }
    else {
        std::cout << "Replace failed." << std::endl;
    }

    // 测试 Delete 函数
    if (obj.Delete(0)) {
        std::cout << "Delete passed." << std::endl;
    }
    else {
        std::cout << "Delete failed." << std::endl;
    }

    // 测试 AddNullAsFirst 函数
    if (obj.AddNullAsFirst()) {
        std::cout << "AddNullAsFirst passed." << std::endl;
    }
    else {
        std::cout << "AddNullAsFirst failed." << std::endl;
    }

    return 0;
}
