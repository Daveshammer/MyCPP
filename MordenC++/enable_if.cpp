#include <iostream>
#include <type_traits>
#include <memory>

class Test1
{
public:
	// 1. the return type (bool) is only valid if T is an integral type:
	template <class T>
	//typename std::enable_if<std::is_integral<T>::value, bool>::type
	std::enable_if_t<std::is_integral<T>::value, bool> // using enable_if_t instead of enable_if
		is_odd(T i) { return bool(i % 2); }

	// 2. the second template argument is only valid if T is an integral type:
	template < class T,
		class = typename std::enable_if<std::is_integral<T>::value>::type>
	bool is_even(T i) { return !bool(i % 2); }

	void test() {

		int i = 1;  

		std::cout << std::boolalpha;
		std::cout << "i is odd: " << is_odd(i) << std::endl; // output: i is odd: true
		std::cout << "i is even: " << is_even(i) << std::endl; // output: i is even: false

		//double d = 2.0; 
		//std::cout << "d is odd: " << is_odd(d) << std::endl; // code does not compile if type of d is not integral
		//std::cout << "d is even: " << is_even(d) << std::endl; 
	}
};

class Test2
{
public:
	template <typename T>
	struct is_smart_pointer_helper : public std::false_type {};

	template <typename T>
	struct is_smart_pointer_helper<std::shared_ptr<T> > : public std::true_type {};

	template <typename T>
	struct is_smart_pointer_helper<std::unique_ptr<T> > : public std::true_type {};

	template <typename T>
	struct is_smart_pointer_helper<std::weak_ptr<T> > : public std::true_type {};

	template <typename T>
	struct is_smart_pointer
		: public is_smart_pointer_helper<typename std::remove_cv<T>::type>
	{
	};

	template <typename T>
	//typename std::enable_if<is_smart_pointer<T>::value, int>::type
	//typename std::enable_if<is_smart_pointer<T>::value>::type // 默认为void
	std::enable_if_t<is_smart_pointer<T>::value, void>
		check_smart_pointer(const T& t)
	{
		std::cout << "is smart pointer" << std::endl;
	}

	template <typename T>
	typename std::enable_if<!is_smart_pointer<T>::value, void>::type
		check_smart_pointer(const T& t)
	{
		std::cout << "not smart pointer" << std::endl;
	}

	void test()
	{
		int* p(new int(2));
		std::shared_ptr<int> pp(new int(2));
		std::unique_ptr<int> upp(new int(4));

		check_smart_pointer(p); // output: not smart pointer
		check_smart_pointer(pp); // output: is smart pointer
		check_smart_pointer(upp); // output: is smart pointer
		delete[] p;
	}
};

int main()
{
	Test1 t1;
	t1.test();

	Test2 t2;
	t2.test();

	return 0;
}
