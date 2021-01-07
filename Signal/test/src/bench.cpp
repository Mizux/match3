#include <catch2/catch_all.hpp>
#include <Signal/Signal.hpp>
#include <chrono>

using namespace std::chrono;

#define LOOP 2'000'000

namespace {
int g_value;

TEST_CASE("Bench Signal: Lambda", "[Bench]") {
	Signal::Signal<int> sig;
	REQUIRE(sig.size() == 0);
	g_value = 0;
	REQUIRE(g_value == 0);
	auto c = sig.connect([&](int val) { g_value += val; });
	REQUIRE(sig.size() == 1);

	auto before = system_clock::now();
	for (std::size_t loop = 0; loop < LOOP; ++loop) {
		sig.emit(1);
	}
	auto after = system_clock::now();
	CHECK(g_value == LOOP);
	double call =
	  LOOP * 1000. / double(duration_cast<milliseconds>(after - before).count());
	WARN(call << "calls/s");
}

void
freeFunction(const int& val) {
	g_value += val;
}

TEST_CASE("Bench Signal: Free function", "[Bench]") {
	g_value = 0;
	REQUIRE(g_value == 0);
	Signal::Signal<int> sig;
	REQUIRE(sig.size() == 0);

	SECTION("Connect using lambda") {
		{
			auto c0 = sig.connect([=](int val) { freeFunction(val); });
			REQUIRE(sig.size() == 1);

			auto before = system_clock::now();
			for (std::size_t loop = 0; loop < LOOP; ++loop) {
				sig.emit(1);
			}
			auto after = system_clock::now();
			CHECK(g_value == LOOP);
			double call =
			  LOOP * 1000. / double(duration_cast<milliseconds>(after - before).count());
			WARN(call << "calls/s");
		}
		REQUIRE(sig.size() == 0);
	}
	SECTION("Connect using std::bind") {
		{
			auto c1 = sig.connect(std::bind(&freeFunction, std::placeholders::_1));
			REQUIRE(sig.size() == 1);

			auto before = system_clock::now();
			for (std::size_t loop = 0; loop < LOOP; ++loop) {
				sig.emit(1);
			}
			auto after = system_clock::now();
			CHECK(g_value == LOOP);
			double call =
			  LOOP * 1000. / double(duration_cast<milliseconds>(after - before).count());
			WARN(call << "calls/s");
		}
		REQUIRE(sig.size() == 0);
	}
	SECTION("Connect using functor") {
		{
			auto c2 = sig.connect(&freeFunction);
			REQUIRE(sig.size() == 1);

			auto before = system_clock::now();
			for (std::size_t loop = 0; loop < LOOP; ++loop) {
				sig.emit(1);
			}
			auto after = system_clock::now();
			CHECK(g_value == LOOP);
			double call =
			  LOOP * 1000. / double(duration_cast<milliseconds>(after - before).count());
			WARN(call << "calls/s");
		}
		REQUIRE(sig.size() == 0);
	}
}

struct Foo {
	Foo() = default;
	void handler(const int& val) { value += val; }

	int value;
};

TEST_CASE("Bench Signal: Member function connection", "[Bench]") {
	std::shared_ptr<Foo> fooPtr = std::make_shared<Foo>();
	REQUIRE(fooPtr);
	fooPtr->value = 0;
	REQUIRE(fooPtr->value == 0);
	Signal::Signal<int> sig;
	REQUIRE(sig.size() == 0);

	SECTION("Connect via lambda") {
		{
			auto hdl = sig.connect([=](int val) { fooPtr->handler(val); });
			REQUIRE(sig.size() == 1);

			auto before = system_clock::now();
			for (std::size_t loop = 0; loop < LOOP; ++loop) {
				sig.emit(1);
			}
			auto after = system_clock::now();
			CHECK(g_value == LOOP);
			double call =
			  LOOP * 1000. / double(duration_cast<milliseconds>(after - before).count());
			WARN(call << "calls/s");
		}
		REQUIRE(sig.size() == 0);
	}
	SECTION("Connect via bind") {
		{
			auto hdl = sig.connect(std::bind(&Foo::handler, fooPtr, std::placeholders::_1));
			REQUIRE(sig.size() == 1);

			auto before = system_clock::now();
			for (std::size_t loop = 0; loop < LOOP; ++loop) {
				sig.emit(1);
			}
			auto after = system_clock::now();
			CHECK(g_value == LOOP);
			double call =
			  LOOP * 1000. / double(duration_cast<milliseconds>(after - before).count());
			WARN(call << "calls/s");
		}
		REQUIRE(sig.size() == 0);
	}
	SECTION("Connect via functor") {
		{
			// compiler can infer the "sig.connect<Foo>"
			auto hdl = sig.connect(fooPtr.get(), &Foo::handler);
			REQUIRE(sig.size() == 1);

			auto before = system_clock::now();
			for (std::size_t loop = 0; loop < LOOP; ++loop) {
				sig.emit(1);
			}
			auto after = system_clock::now();
			CHECK(g_value == LOOP);
			double call =
			  LOOP * 1000. / double(duration_cast<milliseconds>(after - before).count());
			WARN(call << "calls/s");
		}
		REQUIRE(sig.size() == 0);
	}
}
} // namespace
