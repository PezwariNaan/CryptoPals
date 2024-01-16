#include "resources.h"

using namespace std;

vector<char> HexToBytes(const string& hex);
string Base64Encode(const vector<char> input);
auto GetScore(vector<char> bytes);


vector<char> HexToBytes(const string& hex) {
  vector<char> bytes;

  for (unsigned int i = 0; i < hex.length(); i += 2) {
    string byteString = hex.substr(i, 2);
    char byte = (char) strtol(byteString.c_str(), NULL, 16);
    bytes.push_back(byte);
  }
  return bytes;
}


string Base64Encode(const vector<char> input) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;
 
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
 
    BIO_write(bio, input.data(), input.size());
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
 
    string encoded(bufferPtr->data, bufferPtr->length);
    BIO_free_all(bio);
 
    return encoded;
}

auto GetScore(vector<char> bytes) {
    unordered_map<char, int> letter_frequency = { 
      { 'E', 26 }, {'M', 13 }, 
      { 'A', 24 }, {'H', 18 }, 
      { 'R', 21 }, {'G', 11 }, 
      { 'I', 20 }, {'B', 07 },
      { 'O', 23 }, {'F', 15 }, 
      { 'T', 25 }, {'Y', 10 },
      { 'N', 22 }, {'W', 8 },
      { 'S', 19 }, {'K', 5 },
      { 'L', 16 }, {'V', 6 },
      { 'C', 14 }, {'X', 3 },
      { 'U', 12 }, {'Z', 2 },
      { 'D', 17 }, {'J', 4 },
      { 'P', 9 },  {'Q', 1 } 
    };
    
    map<float, char> scores_and_keys;
    
    for (int i = 0; i < 256; i++) {
        float score = 0;
        for (int j = 0; j < bytes.size(); j++) {
            char xord_byte = bytes[j] ^ i;
            auto result = letter_frequency.find(toupper(xord_byte));
            if (result != letter_frequency.end()) {
                score += result->second;
            }
        }
        scores_and_keys.insert(pair<float, char>(score, i));
    }
    auto map_itr = scores_and_keys.end();
    map_itr--;
    return map_itr;
}
