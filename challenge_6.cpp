#include "cryptoPals.h"
#include "resources.h"

// The GetScores function needs re-writing so it produces the correct key 
// Not a close approximation
// We will write it from scratch 

int hammingDistance(unsigned x, unsigned y) {
    int distance = 0;

    // The ^ operators sets to 1 only the bits that are different
    for (unsigned val = x ^ y; val > 0; ++distance)
    {
        // We then count the bit set to 1 using the Peter Wegner way
        val = val & (val - 1); // Set to zero val's lowest-order 1
    }

    // Return the number of differing bits
    return distance;
}

int test(void) {
    string word1 = "this is a test";
    string word2 = "wokka wokka!!!";
    int count = 0;
    for (int i = 0; i < word1.length(); i++){
        count  += hammingDistance(word1[i], word2[i]);
    }

    return count;
}

string readFile(string filepath) {
    // This is the process of reading a file into buffer and then adding the buffer to a string variable
    string ciphertext;
    ifstream encrypted_file(filepath);
    stringstream buffer;
    buffer << encrypted_file.rdbuf();
    encrypted_file.close();
    ciphertext = buffer.str();

    return ciphertext;
}

int compareBlocks(string block_1, string block_2) {
    int distance = 0;
    for (int i = 0; i < block_1.length(); i++) {
        distance += hammingDistance(block_1[i], block_2[i]);
    }
    return distance;
}

int checkKeysize(int keysize, string& ciphertext) {
    const int max_keysize = 40;
    static int result = -1; 
    static float best_guess = 10;
    // Break out of the recursion loop
    if (keysize > max_keysize)
        return result;
    
    int i = 0;
    string first_block;
    string second_block;
    string third_block;
    string fourth_block;
    string fifth_block;

    while (i < keysize) {
        first_block += ciphertext[i];
        second_block += ciphertext[(i + keysize)];
        third_block += ciphertext[i + keysize * 2];
        fourth_block += ciphertext[i + keysize * 3];
        fifth_block += ciphertext[i + keysize * 4];
        i++;
    }

    vector<string> block_list;
    block_list.push_back(first_block);
    block_list.push_back(second_block);
    block_list.push_back(third_block);
    block_list.push_back(fourth_block);

    float distance = 0;
    for (int i = 0; i < block_list.size() - 1; i++) {
        for (int j = i + 1; j < block_list.size(); j++) {
            distance += compareBlocks(block_list[i], block_list[j]) / keysize;
        }
    }
    distance /= block_list.size() * (block_list.size() - 1) / 2;

    if (distance < best_guess) {
        best_guess = distance;
        result = keysize;
    }
    //cout << "Keysize: " << keysize;
    //cout << ", Avg Hamming Distance: " << distance << endl;
    
    return checkKeysize(keysize + 1, ciphertext);
}

string decrypt(string& ciphertext,string& key) {
    string plaintext;
    for (int i = 0; i < ciphertext.size(); i++) {
        plaintext += ciphertext[i] ^ key[i % key.size()];
    }
    return plaintext;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage:" << endl;
        return 1;
    }
    
    // The file loaded must be Base64 DECODED
    // ^ This cause me so much pain >o<
    string ciphertext = readFile(argv[1]);
    const int keysize = 2;
    int likely_keysize = checkKeysize(keysize, ciphertext);
    cout << "Most Likely Keysize: " << likely_keysize << endl;
    
    // Breaking the cipher text into keysized blocks 
    vector<string> keysize_blocks;
    vector<string> single_byte_blocks;
    for (int i = 0; i + likely_keysize < ciphertext.length(); i += likely_keysize) {
        //cout << "Block Start Pos : " << i;
        //cout << ", Block End Pos : " << i + likely_keysize << endl;
        keysize_blocks.push_back(ciphertext.substr(i, i + likely_keysize)) ;
    }
    // Creating a block that contains each byte at a given index for every block in keysize_blocks
    int j = 0;
    while (j < 29) {
        string buffer = "";
        for (int i = 0; i < keysize_blocks.size(); i++) {
            buffer += keysize_blocks[i][j];
        }
        single_byte_blocks.push_back(buffer);
        j++;
    }
    //cout << single_byte_blocks.size();

    // Treating each block in single_byte_blocks as a single key XOR 
    // This should return the key that produces the highest score
    string key; 
    for (int i = 0; i < single_byte_blocks.size(); i++) {
        key += GetScore(single_byte_blocks[i]);
    }
    cout << "Most Likely Key: ";
    cout << key << endl;
    
    // Use the key to decrypt the ciphertext!
    string plaintext = decrypt(ciphertext, key);
    cout << "\nPLAINTEXT\n";
    cout << plaintext << endl;
    return 0;
}

