#include <iostream>
#include <string>
#include <vector>
#include <fstream>

auto processCommandLine(
const std::vector<std::string>& args);

std::string runCaesarCipher(const std::string& inputText, 
                            const std::string& key, const bool encrypt);

std::string transformChar(const char inputChar);


int main(int argc, char* argv[])
{ 

  
    const std::vector<std::string> cmdLineArgs {argv, argv+argc};
    std::string inputText {""};
    std::string outputText {""};
    char inputChar {'x'}; 
    std::fstream fs;

    auto [helpRequested, versionRequested, encrypt, key, inputFile, outputFile] = processCommandLine(cmdLineArgs);
    
    if (helpRequested) {
    // Line splitting for readability
    std::cout
      << "Usage: mpags-cipher [-i <file>] [-o <file>]\n\n"
      << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      << "Available options:\n\n"
      << "  -h|--help        Print this help message and exit\n\n"
      << "  --version        Print version information\n\n"
      << "  -i FILE          Read text to be processed from FILE\n"
      << "                   Stdin will be used if not supplied\n\n"
      << "  -o FILE          Write processed text to FILE\n"
      << "                   Stdout will be used if not supplied\n\n";
    // Help requires no further action, so return from main
    // with 0 used to indicate success
    return 0;
  }

  // Handle version, if requested
  // Like help, requires no further action,
  // so return from main with zero to indicate success
  if (versionRequested) {
    std::cout << "0.1.0" << std::endl;
    return 0;
  }

  // Initialise variables for processing input text


  // Read in user input from stdin/file
  // Warn that input file option not yet implemented
  
  fs.open(inputFile);
   if (fs.is_open()) {
                std::ifstream in_file {inputFile};
                std::string msg {"file has been opened"};
                std::cout << msg <<std::endl;
                 while(in_file >> inputChar){
                 inputText += transformChar(inputChar);
                 outputText = runCaesarCipher(inputText, key, encrypt);
                 }
                fs.close();
  }

    else if (!inputFile.empty()) {
    std::cout << "[warning] input from file ('"
              << inputFile
              << "') not implemented yet, using stdin\n";
  }

  // Loop over each character from user input
  // (until Return then CTRL-D (EOF) pressed)


  // Output the transliterated text
  // Warn that output file option not yet implemente
  std::ofstream out_file {outputFile};
  bool ok_to_write = out_file.good();

   if (ok_to_write) 
   {
         out_file << outputText << std::endl;
         std::string msg {"file saved"};
         std::cout << msg << std::endl;
  }
  
  
  else if (!outputFile.empty()) {
    std::cout << "[warning] output to file ('"
              << outputFile
              << "') not implemented yet, using stdout\n";
  }
  // No requirement to return from main, but we do so for clarity
  // and for consistency with other functions
  return 0;

  //while(std::cin >> inputChar){
    // inputText += transformChar(inputChar);
     //}
}

