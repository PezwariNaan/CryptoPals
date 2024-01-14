#include "cryptoPals.h"
#include "resources.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "usage: ";
        cout << argv[0];
        cout << " [base64 encoded string] [base64 encoded string]";
        return 1;
    }
    
    string first_string  = argv[1];
    string second_string = argv[2];
    
    vector<char> first_string_bytes = HexToBytes(first_string);
    vector<char> second_string_bytes = HexToBytes(second_string);
    
    if (first_string_bytes.size() != second_string_bytes.size()) {
        cout << "Error: Input strings must have the same length." << endl;
        return 1;
    }

    vector<char> xord;
    for (size_t i = 0; i < first_string_bytes.size(); i++ ){
        char xor_result = first_string_bytes[i] ^ second_string_bytes[i];
        xord.push_back(xor_result);
    }

    string b64_string = Base64Encode(xord);
    for (char byte : xord) {
    cout << hex << static_cast<int>(byte);
    }
    
    cout << endl;
    return 0;
}
