#include "resources.h"

using namespace std;

vector<char> HexToBytes(const string& hex);
string Base64Encode(const vector<char> input);
string Base64Decode(const string &input);
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

string Base64Decode(const std::string &encoded_string) {
    const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    std::vector<int> decoding_table(256, -1);
    for (int i = 0; i < 64; ++i) {
        decoding_table[base64_chars[i]] = i;
    }

    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    char char_array_4[4], char_array_3[3];
    std::string decoded_string;

    while (in_len-- && (encoded_string[in_] != '=') && (isalnum(encoded_string[in_]) || (encoded_string[in_] == '+') || (encoded_string[in_] == '/'))) {
        char_array_4[i++] = encoded_string[in_];
        in_++;
        if (i == 4) {
            for (i = 0; i < 4; ++i) {
                char_array_4[i] = decoding_table[char_array_4[i]];
            }

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; i < 3; ++i) {
                decoded_string += char_array_3[i];
            }
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; ++j) {
            char_array_4[j] = 0;
        }

        for (j = 0; j < 4; ++j) {
            char_array_4[j] = decoding_table[char_array_4[j]];
        }

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); ++j) {
            decoded_string += char_array_3[j];
        }
    }

    return decoded_string;
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

char GetScore(string ciphertext) {
    vector<char> letters = {'E','T','A','O','I','N',
                            'S','H','R','D','L','U', ' '};
    
    //string ciphertext_hex = readfile(argv[1]);
    //vector<char> ciphertext = HexToBytes(ciphertext_hex);
    int highscore = 0;
    char likely_key;

    for (int i = 0; i < 256; i++) {
        int score = 0;
        for (int j = 0; j < ciphertext.size(); j ++) {
            //cout << "testing: " << i;
            //cout << ", Against: " << ciphertext[j] << endl;
            vector<char>::iterator iterator = letters.begin();
            char xor_byte = ciphertext[j] ^ i;
            while (iterator != letters.end()) {
                if (toupper(xor_byte) == *iterator) {
                    score++;
                    break;
                } else {
                    iterator++;
                }
            }
        }
        if (score > highscore) {
            highscore = score;
            likely_key = i;
            }
    }
    //cout << "Likely Key: " << likely_key << endl;
    
    //for (int i = 0; i < ciphertext.size() -1; i++) {
    //    char decyphered_byte = ciphertext[i] ^ likely_key;
    //    plaintext += decyphered_byte;
    //} 
    
    //cout << plaintext << endl;;
    return likely_key;
}
