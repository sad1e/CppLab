#pragma once

#include <iostream>
#include <string>

struct singleton_base
{
    singleton_base() = default;
    virtual ~singleton_base() { std::cout << "singleton_base dtor.\n"; }
    singleton_base(const singleton_base&) = default;
    singleton_base& operator=(const singleton_base&) = default;

    static void static_method()
    {
        std::cout << "call static method.\n";
    }

    struct inner_struct
    {
        int i_inner{ 128 };
    };

    template<typename T>
    void tmpl_func(T value)
    {
        std::cout << "template test.\n";
    }

    int ivalue{ -1 };
    std::string svalue{ "string" };
};

struct singleton : public singleton_base
{
    ~singleton() override {}

    static singleton* get_instance()
    {
        if (ptr_singleton == nullptr) { ptr_singleton = new singleton(); }
        return ptr_singleton;
    }

    static void release()
    {
        if (ptr_singleton != nullptr) { delete ptr_singleton; }
    }

    void simple_method()
    {
        std::cout << "call simple method.\n";
    }

protected:
    singleton() : singleton_base{} {}
    static singleton* ptr_singleton;
};

singleton* singleton::ptr_singleton;

void test_singleton()
{
    singleton::get_instance()->simple_method();
    // call static from base.
    singleton_base::static_method();
    // call static from inherited.
    singleton::static_method();
    // call template function.
    singleton::get_instance()->tmpl_func<int>(3);

    singleton::release();

    // decl inner struct from inherited.
    singleton::inner_struct decl_test;
    std::cout << decl_test.i_inner << std::endl;

}
