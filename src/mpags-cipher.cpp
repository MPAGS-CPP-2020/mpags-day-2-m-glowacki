// Standard Library includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::string runCaesarCipher(const std::string& inputText, 
                            const std::string& key, const bool encrypt)
{

  /* function to encypt text by shifting character postitions along the alphabet by specified key
     will also decrypt by doing the reverse
     alphabet = vector of alphabet chars
     index_vec = vector which holds the inicies of alpahabet chars from input text
     encrypt/decrypt_ind = vectors to hold new indicies of chars after being shiftec by the key
     */

    const std::vector <char> alphabet {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char in_char{'X'};
    std::vector <int> index_vec {};
    std::string outputText {""};
    if (key == "caesar") {
      int key_ind{6};
    
    
    for (int j{0}; j < inputText.size(); j++)
    {   
        in_char = inputText[j];
    for (size_t i{0}; i < alphabet.size(); ++i){
       
    if (in_char == alphabet[i]){
        index_vec.push_back(i);
     
    }
    }
    }
    

  
   for (int i{0}; i < index_vec.size(); i ++){
       
   if(encrypt){
    std::vector <int> encrypt_ind {index_vec};
    encrypt_ind[i] = (index_vec[i] + key_ind);
     if (encrypt_ind[i] > alphabet.size()){
       encrypt_ind[i] = encrypt_ind[i] - alphabet.size();
     }
     outputText += alphabet[(encrypt_ind[i])];
   }

   else if (!encrypt)
   {
    
     std::vector <int> decrypt_ind {index_vec};
     decrypt_ind[i]= (index_vec[i] - key_ind);
     if(decrypt_ind[i] < 0) {
       decrypt_ind[i] = alphabet.size() - (std::abs(int(index_vec[i] - key_ind)));
     }
     outputText += alphabet[(decrypt_ind[i])];
  }
   }
    }
    
   return outputText;
   
   
}

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

std::string transformChar(const char inputChar)
  {
    /* function to turn lower case input to upper case 
       also replaces digits with strings e.g. 1 == ONE
       inputChar = text to be converted
       */

   std::string inputText {""};
    // Uppercase alphabetic characters
    if (std::isalpha(inputChar)) {
      inputText += std::toupper(inputChar);
      return inputText;
    }

    // Transliterate digits to English words
    switch (inputChar) {
      case '0':
	inputText += "ZERO";
	break;
      case '1':
	inputText += "ONE";
	break;
      case '2':
	inputText += "TWO";
	break;
      case '3':
	inputText += "THREE";
	break;
      case '4':
	inputText += "FOUR";
	break;
      case '5':
	inputText += "FIVE";
	break;
      case '6':
	inputText += "SIX";
	break;
      case '7':
	inputText += "SEVEN";
	break;
      case '8':
	inputText += "EIGHT";
	break;
      case '9':
	inputText += "NINE";
	break;
    }

    // If the character isn't alphabetic or numeric, DONT add it.
    // Our ciphers can only operate on alphabetic characters.

    return inputText;

  }

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

