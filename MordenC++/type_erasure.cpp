#include <iostream>
#include <memory>

class FunctionWrapper
{
    // 类型擦除的基础类型
    struct impl_base
    {
        virtual void call() = 0;

        virtual ~impl_base() = default;
    };

    // 类型擦除的实现类型
    template <typename F>
    struct impl_type : public impl_base
    {
        F f;

        explicit impl_type(F &&f) : f(std::move(f))
        {
        }

        void call() override
        {
            f();
        }
    };

public:
    template <typename F>
    FunctionWrapper(F &&func) : m_impl(new impl_type<F>(std::forward<F>(func)))
    {
    }

    FunctionWrapper(FunctionWrapper &&other) noexcept : m_impl(std::move(other.m_impl))
    {
    }

    FunctionWrapper() = default;

    FunctionWrapper &operator=(FunctionWrapper &&other) noexcept
    {
        m_impl = std::move(other.m_impl);
        return *this;
    }

    void operator()()
    {
        m_impl->call();
    }

    FunctionWrapper(FunctionWrapper const &) = delete;

    FunctionWrapper(FunctionWrapper &) = delete;

    FunctionWrapper &operator=(FunctionWrapper &) = delete;

private:
    std::unique_ptr<impl_base> m_impl;
};

int main()
{
    FunctionWrapper func([]
                         { std::cout << "Hello from lambda!" << std::endl; });
    func();

    FunctionWrapper func2 = std::move(func); // 转移所有权
    func2();

    return 0;
}