#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Function to calculate the determinant of a 2x2 matrix
int determinant(int key[2][2]) {
    return key[0][0] * key[1][1] - key[0][1] * key[1][0];
}

// Function to calculate the modular multiplicative inverse of a number a modulo m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

// Function to encrypt plaintext using Hill cipher
string encrypt(string plaintext, int key[2][2]) {
    string ciphertext = "";
    int n = plaintext.length();

    // Pad plaintext with 'X' if its length is odd
    if (n % 2 != 0) {
        plaintext += 'X';
        n++;
    }

    // Encrypt in pairs of letters
    for (int i = 0; i < n; i += 2) {
        int letter1 = plaintext[i] - 'A';
        int letter2 = plaintext[i + 1] - 'A';

        int encrypted1 = (key[0][0] * letter1 + key[0][1] * letter2) % 26;
        int encrypted2 = (key[1][0] * letter1 + key[1][1] * letter2) % 26;

        ciphertext += char(encrypted1 + 'A');
        ciphertext += char(encrypted2 + 'A');
    }

    return ciphertext;
}

// Function to decrypt ciphertext using Hill cipher
string decrypt(string ciphertext, int key[2][2]) {
    string decryptedtext = "";
    int n = ciphertext.length();

    // Decrypt in pairs of letters
    for (int i = 0; i < n; i += 2) {
        int letter1 = ciphertext[i] - 'A';
        int letter2 = ciphertext[i + 1] - 'A';

        // Calculate inverse of the key matrix
        int det = determinant(key);
        int inv_det = modInverse(det, 26);

        // Calculate the inverse matrix
        int inv_key[2][2];
        inv_key[0][0] = (key[1][1] * inv_det) % 26;
        inv_key[0][1] = (-key[0][1] * inv_det) % 26;
        inv_key[1][0] = (-key[1][0] * inv_det) % 26;
        inv_key[1][1] = (key[0][0] * inv_det) % 26;

        // Ensure all elements are non-negative
        for (int r = 0; r < 2; r++) {
            for (int c = 0; c < 2; c++) {
                if (inv_key[r][c] < 0) {
                    inv_key[r][c] += 26;
                }
            }
        }

        // Decrypt the letters
        int decrypted1 = (inv_key[0][0] * letter1 + inv_key[0][1] * letter2) % 26;
        int decrypted2 = (inv_key[1][0] * letter1 + inv_key[1][1] * letter2) % 26;

        decryptedtext += char(decrypted1 + 'A');
        decryptedtext += char(decrypted2 + 'A');
    }

    return decryptedtext;
}

int main() {
    // Key matrix for Hill cipher (2x2)
    int key[2][2];
    cout << "Enter the 2x2 key matrix for Hill Cipher (4 numbers in row-major order):" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> key[i][j];
        }
    }

    // Input plaintext or ciphertext from the user
    string text;
    cout << "Enter the plaintext or ciphertext (only uppercase letters):" << endl;
    cin >> text;

    // Encrypt or Decrypt based on user choice
    char choice;
    cout << "Enter 'E' for Encryption or 'D' for Decryption: ";
    cin >> choice;

    string result;
    switch (choice) {
        case 'E':
            result = encrypt(text, key);
            cout << "Encrypted text: " << result << endl;
            break;
        case 'D':
            result = decrypt(text, key);
            cout << "Decrypted text: " << result << endl;
            break;
        default:
            cout << "Invalid choice. Please enter 'E' or 'D'." << endl;
            break;
    }

    return 0;
}
