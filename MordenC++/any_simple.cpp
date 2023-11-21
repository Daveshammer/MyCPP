#include <iostream>
#include <memory>

class Any
{
public:
	Any() = default;
	~Any() = default;
	Any(const Any&) = delete;
	Any& operator=(const Any&) = delete;
	Any(Any&&) = default;
	Any& operator=(Any&&) = default;

	template<typename T>
	Any(T data) : base_(std::make_unique<Derive<T>>(data))
	{}

	// 这个方法能把Any对象里面存储的data数据提取出来
	template<typename T>
	T cast_()
	{
		// 智能指针 =》 基类指针 =》 派生类指针
		Derive<T>* derive = dynamic_cast<Derive<T>*>(base_.get());
		if (derive == nullptr)
		{
			throw "type is unmatch!";
		}
		return derive->data_;
	}
private:
	class Base
	{
	public:
		virtual ~Base() = default;
	};
	template<typename T>
	class Derive : public Base
	{
	public:
		Derive(T data) : data_(data) {}
		T data_;
	};
private:
	std::unique_ptr<Base> base_;
};

int main()
{
    Any a(1);
    std::cout << a.cast_<int>() << std::endl;
    Any b(1.1);
    std::cout << b.cast_<double>() << std::endl;
    Any c("hello");
    std::cout << c.cast_<const char*>() << std::endl;
    return 0;
}