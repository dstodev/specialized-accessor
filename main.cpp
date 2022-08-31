#include <iostream>

enum value_t
{
	Zero = 0,
	One,
	Two
};

struct IContainer
{
	virtual ~IContainer()
	{}
	virtual value_t Value() const = 0;
};

template <typename T>
struct Accessor : IContainer
{
	virtual value_t Value() const
	{
		return T::value;
	}
};

template <value_t value_v>
struct Container : Accessor<Container<value_v>>
{
	static const value_t value = value_v;
};

// Specialize One to hold Two instead
template <>
struct Container<One> : Accessor<Container<One>>
{
	static const value_t value = Two;
};

int main()
{
	Container<Zero> a;
	std::cout << a.value << std::endl;
	std::cout << a.Value() << std::endl;

	Container<One> b;
	std::cout << b.value << std::endl;
	std::cout << b.Value() << std::endl;

	Container<Two> c;
	std::cout << c.value << std::endl;
	std::cout << c.Value() << std::endl;
}
