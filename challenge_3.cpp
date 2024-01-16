#include "resources.h"
#include "cryptoPals.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "usage: ";
        cout << argv[0];
        cout << " [hex string]"; 
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
      { 'P', 9 },  {'Q', 1 } 
    };
    
    map<float, char> scores_and_keys;
    string hex_string = argv[1];
    
    vector<char> bytes =  HexToBytes(hex_string);
    map<float, char> scores = GetScore(bytes);
    auto map_itr = scores.end();
    map_itr--;
    cout << "Score: " << map_itr->first << endl;
    cout << "Key: " << map_itr->second << endl;
    return 0;
}
