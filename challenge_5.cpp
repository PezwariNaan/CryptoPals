#include "cryptoPals.h"
#include "resources.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage" << argv[0] << " [String to Encrypt]" << endl;
        return 1;
    }
    
    char char_array[3] = { 'I', 'C', 'E' };

    string to_encode = argv[1];
    vector<char> encrypted_string;
    int length = 0;
    int i = 0;
    char current_letter = to_encode[i];

    while (current_letter != '\0') {
        length++;
        i++;
        current_letter = to_encode[i];
    }   
    
    for (i = 0; i < length; i++) {
        char encrypted_byte = to_encode[i] ^ char_array[i % 3];
        encrypted_string.push_back(encrypted_byte);
        cout << setw(2) << setfill('0') << hex << (int)encrypted_byte;
    }
        cout << endl;

    return 0;
}
