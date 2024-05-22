#include <optional>
#include <string_view>
#include <charconv> // for from_chars()
#include <iostream>

std::optional<int> asInt(std::string_view sv)
{
    int val;
    // 将字符串视图转换为int类型
    auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), val);

    if (ec == std::errc()) // no error
        return val;
    else
        return std::nullopt;
}

int main()
{
    for (auto s : {"42", "077", "hello", "100"})
    {
        std::optional<int> oi = asInt(s);
        if (oi)
            std::cout << "convert '" << s << "' to int: " << *oi << "\n";
        else
            std::cout << "can't convert '" << s << "' to int\n";
    }
}