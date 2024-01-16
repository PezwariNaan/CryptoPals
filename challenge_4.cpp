#include "resources.h"
#include "cryptoPals.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "usage: ";
        cout << argv[0];
        cout << " [file.txt]"; 
        return 1;
    }
    
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
      { 'P', 9  }, {'Q', 1 } 
    };
    

    ifstream myFile(argv[1]);
    string read_text;
    
    float highscore = 0;
    char key;
    vector<char> message;

    while (getline(myFile, read_text)) {
        vector<char> bytes =  HexToBytes(read_text);
        auto score_key_itr =  GetScore(bytes);
        float score = score_key_itr->first;
        char current_key = score_key_itr->second;

        if (score > highscore) {
            highscore = score;
            key = current_key;
            message = bytes;
        }
    } 
    cout << highscore << endl;
    cout << key << endl;
    for ( int i = 0; i < message.size(); i++ ){
        char xord = message[i] ^ key;
        cout << xord;
    }
    return 0;
}
