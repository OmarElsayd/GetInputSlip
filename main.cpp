//Omar Elsayd
//CST-201

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
 * Slips:
 * Its first character is either a 'D' or an 'E'
 * The first character is followed by a string of one or more 'F's
 * The string of one or more 'F's is followed by either a Slip or a 'G'
 * The Slip or 'G' that follows the F's ends the Slip
 * Nothing else is a Slip
 */

bool Slip(string &input) {
    if(input[0] == 'D' || input[0] == 'E') {
        if(input[1] == 'F') {
            for(int i = 1; input[i] == 'F'; i++) {
                if(input[i + 1] == 'D' || input [i + 1] == 'E')
                    return Slip(input = input.substr(i + 1, input.length()));
                else if (input[i + 1] == 'G') {
                    input = input.substr(i + 2, input.length());
                    return true;
                }
            }
        }
    }
    return false;
}

/*
 * Slaps:
 * Its first character is an 'A'
 * If it is a two-character Slap then its second and last character is an 'H'
 * If it is not a two-character Slap, then it is in one of these two forms:
 * 	'A' followed by 'B' followed by a Slap, followed by a 'C'
 * 	'A' followed by a Slip (see above) followed by a ‘C’
 * Nothing else is a Slap
 */
bool Slap(string &input) {
    if(input[0] == 'A') {
        if(input[1] == 'H') {
            input = input.substr(2, input.length());
            return true;
        }
        else if(input[1] == 'B') {
            if(Slap(input = input.substr(2, input.length()))) {
                if(input[0] == 'C') {
                    input = input.substr(1, input.length());
                    return true;
                }
            }
        }
        else if(Slip(input = input.substr(1, input.length()))) {
            if(input[0] == 'C') {
                input = input.substr(1, input.length());
                return true;
            }
        }
    }
    return false;
}

/*
 * Slops:
 * A Slap followed by a Slip
 */
bool Slop(string &input) {
    return Slap(input) && Slip(input);
}

int main() {

    /*
     * input file with text to check
     */
    fstream file("input.in");
    int size;

    /*
     * insert total strings to check against slop
     */
    file >> size;
    string words[size];

    for (int i = 0; !file.eof(); ++i) {
        file >> words[i];
    }

    file.close();

    /*
     * Run words against slop
     */
    cout << "SLOPS OUTPUT" << endl;
    for (string &input : words) { cout << (Slop(input) ? "YES" : "NO") << endl; }
    cout << "END OUTPUT" << endl;

    return 0;
}