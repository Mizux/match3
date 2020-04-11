#include <Catch/Catch.hpp>
#include <Signal/Signal.hpp>

namespace {
int g_value;

TEST_CASE("Signal::Signal: lambda function connection", "[Signal]") {
	Signal::Signal<int> sig;
	REQUIRE(sig.empty());
	g_value = 0;
	REQUIRE(g_value == 0);
	{
		auto c = sig.connect([&](int val) { g_value = val; });
		REQUIRE(sig.size() == 1);
		REQUIRE_NOTHROW(sig.emit(7));
		CHECK(g_value == 7);
	}
	REQUIRE(sig.empty());
	REQUIRE_NOTHROW(sig.emit(8));
	CHECK(g_value == 7);
}

void
freeFunction(const int& val) {
	g_value = val;
}

TEST_CASE("Signal::Signal: Free function connection", "[Signal]") {
	g_value = 0;
	REQUIRE(g_value == 0);
	Signal::Signal<int> sig;
	REQUIRE(sig.empty());

	SECTION("Connect using lambda") {
		{
			auto c0 = sig.connect([=](int val) { freeFunction(val); });
			REQUIRE(sig.size() == 1);
			REQUIRE_NOTHROW(sig.emit(3));
			CHECK(g_value == 3);
		}
		REQUIRE(sig.empty());
		REQUIRE_NOTHROW(sig.emit(4));
		CHECK(g_value == 3);
	}
	SECTION("Connect using std::bind") {
		{
			auto c1 = sig.connect(std::bind(&freeFunction, std::placeholders::_1));
			REQUIRE(sig.size() == 1);
			REQUIRE_NOTHROW(sig.emit(3));
			CHECK(g_value == 3);
		}
		REQUIRE(sig.empty());
		REQUIRE_NOTHROW(sig.emit(4));
		CHECK(g_value == 3);
	}
	SECTION("Connect using functor") {
		{
			auto c2 = sig.connect(&freeFunction);
			REQUIRE(sig.size() == 1);
			REQUIRE_NOTHROW(sig.emit(5));
			CHECK(g_value == 5);
		}
		REQUIRE(sig.empty());
		REQUIRE_NOTHROW(sig.emit(6));
		CHECK(g_value == 5);
	}
	REQUIRE(sig.empty());
}

struct Foo {
	Foo() = default;
	void handler(const int& val) { g_value = val; }
};

TEST_CASE("Signal::Signal: Member function connection", "[Signal]") {
	std::shared_ptr<Foo> fooPtr = std::make_shared<Foo>();
	REQUIRE(fooPtr);
	g_value = 0;
	REQUIRE(g_value == 0);
	Signal::Signal<int> sig;
	REQUIRE(sig.empty());

	SECTION("Connect via lambda") {
		{
			auto hdl = sig.connect([=](int val) { fooPtr->handler(val); });
			REQUIRE(sig.size() == 1);
			REQUIRE_NOTHROW(sig.emit(5));
			CHECK(g_value == 5);
		}
		REQUIRE(sig.empty());
	}
	SECTION("Connect via bind") {
		{
			auto hdl = sig.connect(std::bind(&Foo::handler, fooPtr, std::placeholders::_1));
			REQUIRE(sig.size() == 1);
			REQUIRE_NOTHROW(sig.emit(3));
			CHECK(g_value == 3);
		}
		REQUIRE(sig.empty());
	}
	SECTION("Connect via functor") {
		{
			// compiler can infer the "sig.connect<Foo>"
			auto hdl = sig.connect(fooPtr.get(), &Foo::handler);
			REQUIRE(sig.size() == 1);
			REQUIRE_NOTHROW(sig.emit(7));
			CHECK(g_value == 7);
		}
		REQUIRE(sig.empty());
	}
}

TEST_CASE("Signal::Signal: destruction", "[Signal]") {
	g_value = 0;
	REQUIRE(g_value == 0);
	SECTION("Delete Signal::Signal then delete Connection") {
		Signal::Signal<int>* sigPtr = new Signal::Signal<int>();
		REQUIRE(sigPtr->empty());
		auto hdl = sigPtr->connect(&freeFunction);
		REQUIRE_NOTHROW(sigPtr->emit(2));
		CHECK(g_value == 2);
		REQUIRE_NOTHROW(delete sigPtr);
	}
	SECTION("Disconnect Connection, delete Signal::Signal then delete Connection") {
		Signal::Signal<int>* sigPtr = new Signal::Signal<int>();
		REQUIRE(sigPtr->empty());
		Signal::Connection hdl = sigPtr->connect(&freeFunction);
		REQUIRE_NOTHROW(sigPtr->emit(3));
		CHECK(g_value == 3);
		REQUIRE_NOTHROW(hdl.disconnect());
		REQUIRE_NOTHROW(sigPtr->emit(4));
		CHECK(g_value == 3);
		REQUIRE_NOTHROW(delete sigPtr);
	}
	SECTION("Kill Instance, then delete Signal::Signal") {
		Signal::Signal<int>* sigPtr = new Signal::Signal<int>();
		REQUIRE(sigPtr->empty());
		std::shared_ptr<Foo> fooPtr = std::make_shared<Foo>();
		std::weak_ptr<Foo> fooWkPtr = {fooPtr};
		Signal::Connection hdl      = sigPtr->connect([=](int value) -> void {
      std::shared_ptr<Foo> tmp = fooWkPtr.lock();
      if (tmp) tmp->handler(value);
    });
		REQUIRE_NOTHROW(sigPtr->emit(7));
		CHECK(g_value == 7);
		REQUIRE_NOTHROW(fooPtr.reset());
		REQUIRE_NOTHROW(sigPtr->emit(4));
		CHECK(g_value == 7);
		REQUIRE_NOTHROW(delete sigPtr);
	}
}
} // namespace
