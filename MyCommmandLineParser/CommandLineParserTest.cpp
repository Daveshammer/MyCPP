#include "CommandLineParser.hpp"

// ./a.out -i HelloWorld -o

int main(int argc, char* argv[])
{
	CommandLineParser cmdParser;
	cmdParser.add("help", { "-h", "--help" }, false, "Prints this help");
	cmdParser.add("input", { "-i", "--input" }, true, "Input string");
	cmdParser.add("output", { "-o", "--output" }, false, "Output string");

	cmdParser.parse(argc, argv);
	if (cmdParser.isSet("help")) {
		cmdParser.printHelp();
	}
	else {
		if (cmdParser.isSet("output")) {
			std::cout << "Output string: " << cmdParser.getValueAsString("input", "") << std::endl;
		}
	}
	return 0;
}