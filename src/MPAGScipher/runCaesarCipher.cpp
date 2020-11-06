#include <fstream>
#include <string>
#include <vector>
#include <iostream>


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
