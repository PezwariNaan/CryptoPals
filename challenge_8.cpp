#include "resources.h"
#include "cryptoPals.h"

const int BLOCKSIZE = 16;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./challenge_8 [ciphertext.txt]" << endl;
        return 1;
    }

    string ciphertext = readFile(argv[1]);
    int j = 0;
    vector<string> blocks;
    map<string, vector<int>> matching_blocks_info;

    // Break ciphertext into 16-byte blocks
    for (int i = BLOCKSIZE; i <= ciphertext.length(); i += BLOCKSIZE) {
        blocks.push_back(ciphertext.substr(j, BLOCKSIZE));
        j = i;
    }

    // Compare each distinct pair of blocks and store line numbers
    for (int i = 0; i < blocks.size(); ++i) {
        for (int j = i + 1; j < blocks.size(); ++j) {
            if (blocks[i] == blocks[j]) {
                matching_blocks_info[blocks[i]].push_back(i + 1);  // Line numbers start from 1
                matching_blocks_info[blocks[i]].push_back(j + 1);
            }
        }
    }

    // Print the matching blocks, their count, and line numbers
    for (const auto& entry : matching_blocks_info) {
        cout << "Block: " << entry.first << ", Count: " << entry.second.size() / 2 << ", Line Numbers: ";
        for (size_t i = 0; i < entry.second.size(); i += 2) {
            cout << entry.second[i];
            if (i + 2 < entry.second.size()) {
                cout << ", ";
            }
        }
        cout << '\n';
    }

    return 0;
}
