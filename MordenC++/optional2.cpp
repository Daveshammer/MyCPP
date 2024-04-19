#include <iostream>
#include <fstream>
#include <optional>

std::optional<std::string> ReadFileAsString(const std::string& filepath)
{
    std::ifstream stream(filepath);
    if (stream)
    {
        // read file
        // 使用 istreambuf_iterator 和 string 构造函数一次性读取整个文件
        std::string result = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        stream.close();
        return result;
    }
    // return std::nullopt;
    return {};
}

int main()
{
    std::optional<std::string> data = ReadFileAsString("demo.txt");

    std::string value = data.value_or("Not present");
    std::cout << value << std::endl;
    if (data.has_value())
    {
        std::cout << "File read successfully!" << std::endl;
    }
    else
    {
        std::cout << "Failed to read file!" << std::endl;
    }
}