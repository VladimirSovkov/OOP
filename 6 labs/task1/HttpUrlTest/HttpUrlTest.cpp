#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HttpUrl/HttpUrl.h"

TEST_CASE("constructor check receiving string url")
{
	WHEN("the correct url without port is input")
	{
		CHttpUrl url("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");

		CHECK(Protocol::HTTP == url.GetProtocol());
		CHECK("www.mysite.com" == url.GetDomain());
		CHECK(80 == url.GetPort());
		CHECK("/docs/document1.html?page=30&lang=en#title" == url.GetDocument());
	}

	WHEN("the correct url with port is input")
	{
		CHttpUrl url("https://www.mysite.com:325/docs/document1.html?page=30&lang=en#title");

		CHECK(Protocol::HTTPS == url.GetProtocol());
		CHECK("www.mysite.com" == url.GetDomain());
		CHECK(325 == url.GetPort());
		CHECK("/docs/document1.html?page=30&lang=en#title" == url.GetDocument());
	}

	WHEN("url with incorrect protocol")
	{
		CHECK_THROWS(CHttpUrl("h://www.mysite.com:325/docs/document1.html?page=30&lang=en#title"));
	}

	WHEN("url without domain")
	{
		CHECK_THROWS(CHttpUrl("http://"));
	}

	WHEN("url with incorrect port")
	{
		CHECK_THROWS(CHttpUrl("http://www.mysite.com:0/docs/document1.html?page=30&lang=en#title"));
		CHECK_THROWS(CHttpUrl("http://www.mysite.com:65536/docs/document1.html?page=30&lang=en#title"));
	}
}

TEST_CASE("constructor accepts protocol, domain, document")
{
	WHEN("correct data with defualt protocol")
	{
		CHttpUrl url("www.mysite.com", "/docs/document1.html?page=30&lang=en#title");
		
		CHECK(Protocol::HTTP == url.GetProtocol());
		CHECK("www.mysite.com" == url.GetDomain());
		CHECK(80 == url.GetPort());
		CHECK("/docs/document1.html?page=30&lang=en#title" == url.GetDocument());
	}

	WHEN("correct data with protocol")
	{
		CHttpUrl url("www.mysite.com", "docs/document1.html?page=30&lang=en#title", Protocol::HTTPS);
		CHECK(Protocol::HTTPS == url.GetProtocol());
		CHECK("www.mysite.com" == url.GetDomain());
		CHECK(443 == url.GetPort());
		CHECK("/docs/document1.html?page=30&lang=en#title" == url.GetDocument());
	}

	WHEN("correct data with empty document")
	{
		CHttpUrl url("www.mysite.com", "", Protocol::HTTPS);
		CHECK(Protocol::HTTPS == url.GetProtocol());
		CHECK("www.mysite.com" == url.GetDomain());
		CHECK(443 == url.GetPort());
		CHECK("/" == url.GetDocument());
	}

	WHEN("incorrect domain")
	{
		CHECK_THROWS(CHttpUrl("www.mys/ite.com", "/docs/document1.html?page=30&lang=en#title"));
	}

	WHEN("domain is empty")
	{
		CHECK_THROWS(CHttpUrl("", "doc.doc"));
	}
}

TEST_CASE("constructor accepts protocol, domain, document and port")
{
	WHEN("correct data")
	{
		CHttpUrl url("www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 325);

		CHECK(Protocol::HTTP == url.GetProtocol());
		CHECK("www.mysite.com" == url.GetDomain());
		CHECK(325 == url.GetPort());
		CHECK("/docs/document1.html?page=30&lang=en#title" == url.GetDocument());
	}

	WHEN("incorrect value port")
	{
		CHECK_THROWS(CHttpUrl("www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTP, (unsigned short)65536));
	}
}

TEST_CASE("get url")
{
	WHEN("url with default port")
	{
		std::string urlLine = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		CHttpUrl url(urlLine);
		CHECK(urlLine == url.GetURL());
	}

	WHEN("url with port")
	{
		std::string urlLine = "http://www.mysite.com:325/docs/document1.html?page=30&lang=en#title";
		CHttpUrl url(urlLine);
		CHECK(urlLine == url.GetURL());
	}

	WHEN("url with default port specified")
	{
		CHttpUrl url("http://www.mysite.com:80/docs/document1.html?page=30&lang=en#title");
		CHECK("http://www.mysite.com/docs/document1.html?page=30&lang=en#title" == url.GetURL());
	}
}