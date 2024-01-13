#include <iostream>
#include <vector>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

using namespace std;

vector<char> HexToBytes(const string& hex) {
  vector<char> bytes;

  for (unsigned int i = 0; i < hex.length(); i += 2) {
    string byteString = hex.substr(i, 2);
    char byte = (char) strtol(byteString.c_str(), NULL, 16);
    cout << byte;
    bytes.push_back(byte);
  }
    cout << endl;
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

int main(void){
    string hex_string = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    vector<char> bytes = HexToBytes(hex_string);
    string b64_string = Base64Encode(bytes);
    cout << b64_string << endl;
    return 0;
}
