#include <catch2/catch_all.hpp>
#include <Signal/Property.hpp>

namespace {
int g_value;

TEST_CASE("Property: lambda function connection", "[Property]") {
	Signal::Property<int> prop(0);
	REQUIRE(prop.size() == 0);
	g_value = 0;
	REQUIRE(g_value == 0);
	{
		auto c = prop.connect([&](int val) { g_value = val; });
		REQUIRE(prop.size() == 1);
		REQUIRE_NOTHROW(prop.set(7));
		CHECK(prop.get() == 7);
		CHECK(g_value == 7);
	}
	REQUIRE(prop.size() == 0);
	REQUIRE_NOTHROW(prop.set(8));
	CHECK(prop.get() == 8);
	CHECK(g_value == 7);
}

void
freeFunction(const int& val) {
	g_value = val;
}

TEST_CASE("Property: Free function connection", "[Property]") {
	g_value = 0;
	REQUIRE(g_value == 0);
	Signal::Property<int> prop;
	REQUIRE(prop.size() == 0);

	SECTION("Connect using lambda") {
		{
			auto c0 = prop.connect([=](int val) { freeFunction(val); });
			REQUIRE(prop.size() == 1);
			REQUIRE_NOTHROW(prop.set(3));
			CHECK(g_value == 3);
		}
		REQUIRE(prop.size() == 0);
		REQUIRE_NOTHROW(prop.set(4));
		CHECK(g_value == 3);
	}
	SECTION("using std::bind") {
		{
			auto c1 = prop.connect(std::bind(&freeFunction, std::placeholders::_1));
			REQUIRE(prop.size() == 1);
			REQUIRE_NOTHROW(prop.set(3));
			CHECK(g_value == 3);
		}
		REQUIRE(prop.size() == 0);
		REQUIRE_NOTHROW(prop.set(4));
		CHECK(g_value == 3);
	}
	SECTION("using functor") {
		{
			auto c2 = prop.connect(&freeFunction);
			REQUIRE(prop.size() == 1);
			REQUIRE_NOTHROW(prop.set(5));
			CHECK(g_value == 5);
		}
		REQUIRE(prop.size() == 0);
		REQUIRE_NOTHROW(prop.set(6));
		CHECK(g_value == 5);
	}
	REQUIRE(prop.size() == 0);
}

struct Foo {
	Foo() = default;
	void handler(const int& val) { value = val; }
	int value;
};

TEST_CASE("Property: Member function connection", "[Property]") {
	std::shared_ptr<Foo> fooPtr = std::make_shared<Foo>();
	REQUIRE(fooPtr);
	fooPtr->value = 0;
	REQUIRE(fooPtr->value == 0);
	Signal::Property<int> prop;
	REQUIRE(prop.size() == 0);

	SECTION("Connect via lambda") {
		{
			auto hdl = prop.connect([=](int val) { fooPtr->handler(val); });
			REQUIRE(prop.size() == 1);
			REQUIRE_NOTHROW(prop.set(5));
			CHECK(fooPtr->value == 5);
		}
		REQUIRE(prop.size() == 0);
	}
	SECTION("Connect via bind") {
		{
			auto hdl = prop.connect(std::bind(&Foo::handler, fooPtr, std::placeholders::_1));
			REQUIRE(prop.size() == 1);
			REQUIRE_NOTHROW(prop.set(3));
			CHECK(fooPtr->value == 3);
		}
		REQUIRE(prop.size() == 0);
	}
	SECTION("Connect via functor") {
		{
			// compiler can infer the "prop.connect<Foo>"
			auto hdl = prop.connect(fooPtr.get(), &Foo::handler);
			REQUIRE(prop.size() == 1);
			REQUIRE_NOTHROW(prop.set(7));
			CHECK(fooPtr->value == 7);
		}
		REQUIRE(prop.size() == 0);
	}
}

TEST_CASE("Property: destruction", "[Property]") {
	g_value = 0;
	REQUIRE(g_value == 0);
	SECTION("Delete Property then delete Connection") {
		Signal::Property<int>* propPtr = new Signal::Property<int>();
		REQUIRE(propPtr->size() == 0);
		auto hdl = propPtr->connect(&freeFunction);
		REQUIRE_NOTHROW(propPtr->set(2));
		CHECK(g_value == 2);
		REQUIRE_NOTHROW(delete propPtr);
	}
	SECTION("Disconnect Connection, delete Property then delete Connection") {
		Signal::Property<int>* propPtr = new Signal::Property<int>();
		REQUIRE(propPtr->size() == 0);
		Signal::Connection hdl = propPtr->connect(&freeFunction);
		REQUIRE_NOTHROW(propPtr->set(3));
		CHECK(g_value == 3);
		REQUIRE_NOTHROW(hdl.disconnect());
		REQUIRE_NOTHROW(delete propPtr);
	}
}
} // namespace
