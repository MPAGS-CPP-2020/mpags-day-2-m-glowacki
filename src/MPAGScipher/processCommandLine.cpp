#include <fstream>
#include <string>
#include <vector>
#include <iostream>

auto processCommandLine(
const std::vector<std::string>& args)
{
    bool helpRequested {false};
    bool versionRequested {false};
    bool encrypt {false};
    std::string inputFile{""};
    std::string outputFile{""};
    std::string key("");
    
  std::fstream fs;
  char inputChar {'x'};
  typedef std::vector<std::string>::size_type size_type;
  const size_type nArgs {args.size()};

  for (size_type i {1}; i < nArgs; ++i) {

    if(args[i] == "-e"){
      encrypt = true;
    }

    else if(args[i] == "-d"){
      encrypt = false;
    }

    else if (args[i] == "-h" || args[i] == "--help") {
      helpRequested = true;
    }
    else if (args[i] == "--version") {
      versionRequested = true;
    }
    else if (args[i] == "-k") {
      // Handle key file option
      // Next element is key unless -k is the last argument
      if (i == nArgs-1) {
	std::cerr << "[error] -k requires an input" << std::endl;
	// exit main with non-zero return to indicate failure
	//return 1;
      }
      else {
	// Got key, so assign value and advance past it
	   key = args[i+1];
	   ++i;
      }
    }
    else if (args[i] == "-i") {
      // Handle input file option
      // Next element is filename unless -i is the last argument
      if (i == nArgs-1) {
	std::cerr << "[error] -i requires a filename argument" << std::endl;
	// exit main with non-zero return to indicate failure
	//return 1;
      }
      else {
	// Got filename, so assign value and advance past it
	inputFile = args[i+1];
	++i;
      }
    }
    else if (args[i] == "-o") {
      // Handle output file option
      // Next element is filename unless -o is the last argument
      if (i == nArgs-1) {
	std::cerr << "[error] -o requires a filename argument" << std::endl;
	// exit main with non-zero return to indicate failure
	//return 1;
      }
      else {
	// Got filename, so assign value and advance past it
	outputFile = args[i+1];
	++i;
      }
    }
    else {
      // Have an unknown flag to output error message and return non-zero
      // exit status to indicate failure
      std::cerr << "[error] unknown argument '" << args[i] << "'\n";
      //return 1;
    }
  }

   struct retVals {        // Declare a local structure 
    bool helpRequested;
    bool versionRequested;
    bool encrypt;
    std::string key;
    std::string inputFile;
    std::string outputFile;
  };

  return retVals{helpRequested, versionRequested, encrypt, key, inputFile, outputFile};
  //return 0 
} 
