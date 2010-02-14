


#include <fstream>
#include <cpptest.h>
#include <stdlib.h>
#include <string.h>
#include "testPlateau.hpp"
#include "testJeuxPuiss4.hpp"
#include "testIA.hpp"


using namespace std;

#ifdef NL_OS_WINDOWS
#	define NEL_UNIT_DATA ""
#endif

// Add a line here when adding a new test MODULE




#ifdef _MSC_VER

/** A special stream buffer that output in the 'output debug string' feature of windows.
 */
class CDebugOutput : public streambuf
{
	int_type overflow(int_type c)
	{
		string str(pbase(), pptr());

		if (c != traits_type::eof())
			str += c;
		OutputDebugString(str.c_str() );

		return c;
	}
};
// The instance of the streambug
ostream msvDebug(new CDebugOutput);

#endif

static void usage()
{
	cout << "usage: mytest [MODE]\n"
		 << "where MODE may be one of:\n"
		 << "  --compiler\n"
		 << "  --html\n"
		 << "  --text-terse (default)\n"
		 << "  --text-verbose\n";
	exit(0);
}

static auto_ptr<Test::Output> cmdline(int argc, char* argv[])
{
	if (argc > 2)
		usage(); // will not return
	
	Test::Output* output = 0;
	
	if (argc == 1)
		output = new Test::TextOutput(Test::TextOutput::Verbose);
	else
	{
		const char* arg = argv[1];
		if (strcmp(arg, "--compiler") == 0)
		{
#ifdef _MSC_VER
			output = new Test::CompilerOutput(Test::CompilerOutput::MSVC, msvDebug);
#elif defined(__GNUC__)
			output = new Test::CompilerOutput(Test::CompilerOutput::GCC);
#else
			output = new Test::CompilerOutput;
#endif
		}
		else if (strcmp(arg, "--html") == 0)
			output =  new Test::HtmlOutput;
		else if (strcmp(arg, "--text-terse") == 0)
			output = new Test::TextOutput(Test::TextOutput::Terse);
		else if (strcmp(arg, "--text-verbose") == 0)
			output = new Test::TextOutput(Test::TextOutput::Verbose);
		else
		{
			cout << "invalid commandline argument: " << arg << endl;
			usage(); // will not return
		}
	}

	return auto_ptr<Test::Output>(output);
}

// Main test program
//
int main(int argc, char *argv[])
{
	static const char *outputFileName = "unit_test.html";

	// init Nel context
	//new NLMISC::CApplicationContext;

	bool noerrors = false;

	try
	{
		Test::Suite ts;

		ts.add(auto_ptr<Test::Suite>(new PlateauTestSuite));
		ts.add(auto_ptr<Test::Suite>(new JeuxPuiss4TestSuite));
		ts.add(auto_ptr<Test::Suite>(new IATestSuite));
		// Add a line here when adding a new test MODULE

		auto_ptr<Test::Output> output(cmdline(argc, argv));
		noerrors = ts.run(*output);

		Test::HtmlOutput* const html = dynamic_cast<Test::HtmlOutput*>(output.get());
		if (html)
		{
			std::ofstream fout(outputFileName);
			html->generate(fout, true, "tests");
		}
	}
	catch (...)
	{
		cout << "unexpected exception encountered" << endl;
		return 0;
	}
	if(noerrors)
		cerr << "No errors during unit testing :" << outputFileName << endl ;
	else
		cerr << "Errors during unit testing" << endl ;
	return noerrors? 0 : 1;
}
