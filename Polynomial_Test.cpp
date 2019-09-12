#include <sstream>
#include <cstring>
#include "Polynomial.h"
#include "catch.hpp"

using namespace std;

#define LISTA

string get_expression(Polynomial& p) {
	stringstream ss;
	ss << p;
	return ss.str();
}

TEST_CASE("Polynomial") {
	SECTION("Create a polynomial from a list or by adding each term individual") {

#ifdef LISTA
		Polynomial p = { {1, 0}, {-1, 1}, {6, 3} };
#else
		Polynomial p;
		p.add({ 1, 0 });
		p.add({ -1, 1 });
		p.add({ 6, 3 });
#endif

		REQUIRE(get_expression(p) == "1-1x^1+6x^3");
	}
	SECTION("Create a polynomial by copy") {

#ifdef LISTA
		Polynomial p1 = { {1, 0}, {-1, 1}, {6, 3} };
#else
		Polynomial p1;
		p1.add({ 1, 0 });
		p1.add({ -1, 1 });
		p1.add({ 6, 3 });
#endif
		auto p2 = p1;
		p2 = p2 + 10;

		REQUIRE(get_expression(p1) == "1-1x^1+6x^3");
		REQUIRE(get_expression(p2) == "11-1x^1+6x^3");
	}
	SECTION("Degree of a polynomial") {

#ifdef LISTA
		Polynomial p1 = { {1, 0}, {-1, 1}, {6, 3} };
#else
		Polynomial p1;
		p1.add({ 1, 0 });
		p1.add({ -1, 1 });
		p1.add({ 6, 3 });
#endif
		REQUIRE(p1.degree() == 3);
	}
	SECTION("Sum two (2) polymonial") {

#ifdef LISTA
		Polynomial p1 = { {1, 0}, {-1, 1}, {6, 3} };
		Polynomial p2 = { {-1, 1}, {4, 2}, {3, 3} };
#else
		Polynomial p1;
		p1.add({ 1, 0 });
		p1.add({ -1, 1 });
		p1.add({ 6, 3 });

		Polynomial p2;
		p2.add({ -1, 1 });
		p2.add({ 4, 2 });
		p2.add({ 3, 3 });
#endif

		auto p3 = p1 + p2;
		p1 += p2;
		REQUIRE(get_expression(p2) == "-1x^1+4x^2+3x^3");
		REQUIRE(get_expression(p3) == "1-2x^1+4x^2+9x^3");
		REQUIRE(get_expression(p1) == "1-2x^1+4x^2+9x^3");
	}

	SECTION("Sum two a constant + a polymonial") {
#ifdef LISTA
		Polynomial p1 = { {-1, 1}, {4, 2}, {3, 3} };
#else
		Polynomial p1;
		p1.add({ -1, 1 });
		p1.add({ 4, 2 });
		p1.add({ 3, 3 });
#endif
		auto p2 = 10 + p1;
		auto p3 = p1 + 10;
		p1 += 10;
		REQUIRE(get_expression(p2) == "10-1x^1+4x^2+3x^3");
		REQUIRE(get_expression(p3) == "10-1x^1+4x^2+3x^3");
		REQUIRE(get_expression(p1) == "10-1x^1+4x^2+3x^3");
	}

	SECTION("Multiply two polymonials") {
#ifdef LISTA
		Polynomial p1 = { {1, 0}, { 3, 1} };
		Polynomial p2 = { {1, 0}, {-3, 1} };
#else
		Polynomial p1;
		p1.add({ 1, 0 });
		p1.add({ 3, 1 });

		Polynomial p2;
		p2.add({ 1, 0 });
		p2.add({ -3, 1 });
#endif
		auto p3 = p1 * p2;
		REQUIRE(get_expression(p1) == "1+3x^1");
		REQUIRE(get_expression(p2) == "1-3x^1");
		REQUIRE(get_expression(p3) == "1-9x^2");
	}

	SECTION("Multiply a polymonials by a constant") {
#ifdef LISTA
		Polynomial p1 = { {1, 0}, { 3, 1} };
#else
		Polynomial p1;
		p1.add({ 1, 0 });
		p1.add({ 3, 1 });
#endif
		auto p2 = p1 * 10;
		auto p3 = 20 * p1;
		REQUIRE(get_expression(p1) == "1+3x^1");
		REQUIRE(get_expression(p2) == "10+30x^1");
		REQUIRE(get_expression(p3) == "20+60x^1");
	}

	SECTION("Multiply same polymonials twice") {
#ifdef LISTA
		Polynomial p1 = { {1, 0}, {1, 1} };
#else
		Polynomial p1;
		p1.add({ 1, 0 });
		p1.add({ 1, 1 });
#endif
		auto p2 = p1 * p1;
		REQUIRE(get_expression(p1) == "1+1x^1");
		REQUIRE(get_expression(p2) == "1+2x^1+1x^2");
	}

	SECTION("Multiply same polymonials three times") {
#ifdef LISTA
		Polynomial p1 = { {1, 0}, {1, 1} };
#else
		Polynomial p1;
		p1.add({ 1, 0 });
		p1.add({ 1, 1 });
#endif
		auto p2 = p1 * p1 * p1;
		REQUIRE(get_expression(p2) == "1+3x^1+3x^2+1x^3");
	}
	SECTION("Potential") {
#ifdef LISTA
		Polynomial p1 = { {1, 0}, {1, 1} };
#else
		Polynomial p1;
		p1.add({ 1, 0 });
		p1.add({ 1, 1 });
#endif
		auto p2 = p1 ^ 3;
		REQUIRE(get_expression(p2) == "1+3x^1+3x^2+1x^3");
	}

	SECTION("Duplicated terms") {
		try {
#ifdef LISTA
			Polynomial p1 = { {1, 1}, {1, 1} };
#else
			Polynomial p1;
			p1.add({ 1, 1 });
			p1.add({ 1, 1 });
#endif
		}
		catch (const exception& e) {
			REQUIRE(strcmp(e.what(), "Term exists in Polynomial") == 0);
		}
	}
}