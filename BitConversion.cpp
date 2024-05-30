#include <iostream>
#include <string>
using namespace std;

//                                                  FORMATTING

// pads a string with leading zeros until it matches the specified length
int zeropad(string* instring, int length) {
    string outstr = "";
    for (int i = instring->length(); i < length; i++) {
        outstr += "0";
    }
    outstr += *instring;
    *instring = outstr;
    return 0;
}

// if a hex string is valid it returns the string, otherwise it returns "***"
string formathex(string hexin) {
    string outstring = "";
    for (int i = 0; i < hexin.length(); i++) {
        if (int(hexin[i]) >= 48 && int(hexin[i]) <= 57) outstring += hexin[i];
        else if (int(hexin[i]) >= 65 && int(hexin[i]) <= 70) outstring += hexin[i];
        else if (int(hexin[i]) >= 97 && int(hexin[i]) <= 102) outstring += char(int(hexin[i]) - 32);
        else return "***";
    }
    return outstring;
}

// if a binary string is valid it returns the string, otherwise it returns "***"
string formatbin(string binin) {
    for (int i = 0; i < binin.length(); i++) {
        if (binin[i] != '0' && binin[i] != '1') return "***";
    }
    return binin;
}

//                                                  CHARACTER CONVERSIONS

const char hexchars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

// converts an integer between 0 and 16 to it's corresponding hexadecimal character, returns '#' on failure
char decchartohex(int decchar) {
    if (decchar <= 16 && decchar >= 0) return hexchars[decchar];
    cerr << "decchartohex received invalid input" << endl;
    return '#';
}

// finds the corresponding integer value for a hexadecimal character
int hexchartodec(char hexchar) {
    for (int i = 0; i < 16; i++) {
        if (hexchar == hexchars[i]) return i;
    }
    return -1;
}

//                                                  STRING CONVERSIONS

// returns a hexadecimal string based on a provided integer value and length
string dectohex(int innum, int hexlen = 0) {
    int mult = 1;
    int chgnum = innum;
    int minlen = 0;
    string outstring = "";

    if (chgnum < 0) chgnum *= -1;

    // finds the minimum hex length and max divisor
    while (mult < chgnum) {
        mult *= 16;
        minlen++;
    }
    mult /= 16;
    minlen--;

    // pads string
    zeropad(&outstring, hexlen - minlen - 1);

    // converts decimal to hex
    while (mult > 0) {
        outstring += hexchars[chgnum / mult];
        chgnum -= int(chgnum / mult) * mult;
        mult /= 16;
    }
    return outstring;
}

// returns a binary string based on a provided integer value and length
string dectobin(int innum, int binlen = 0) {
    int mult = 1;
    int chgnum = innum;
    int minlen = 0;
    string outstring = "";

    if (chgnum < 0) chgnum *= -1;

    // finds the minimum binary length and max divisor
    while (mult < chgnum) {
        mult *= 2;
        minlen++;
    }
    mult /= 2;
    minlen--;

    // pads string
    zeropad(&outstring, binlen - minlen - 1);

    // converts decimal to binary
    while (mult > 0) {
        outstring += char((chgnum / mult) + 48);
        chgnum -= int(chgnum / mult) * mult;
        mult /= 2;
    }
    return outstring;
}

// returns an integer value for a provided hexadecimal string
int hextodec(string hexstring) {
    int outnum = 0;
    int multiplier = 1;
    for (int letter = hexstring.length() - 1; letter >= 0; letter--) {
        for (int hex = 0; hex <= 16; hex++) {
            cout << hexstring.at(letter) << ", " << hexchars[hex] << ", " << multiplier << ", " << outnum << endl;
            if (hexstring.at(letter) == hexchars[hex]) {
                outnum += (hex * multiplier);
                multiplier *= 16;
                hex = 16;
            }
        }
    }
    cout << outnum << endl;
    return outnum;
}

// returns an integer value for a provided binary string
int bintodec(string binstring) {
    int outnum = 0;
    int multiplier = 1;
    for (int letter = binstring.length() - 1; letter >= 0; letter--) {
        for (int bin = 0; bin <= 2; bin++) {
            cout << binstring.at(letter) << ", " << char(bin) << ", " << multiplier << ", " << outnum << endl;
            if (binstring.at(letter) == char(bin)) {
                outnum += (bin * multiplier);
                multiplier *= 2;
                bin = 2;
            }
        }
    }
    cout << outnum << endl;
    return outnum;
}

//                                                  ARITHMETIC

// subtracts hexB from hexA and returns the output
string hexsub(string hexA, string hexB) {
    string revouthex = "";
    int hexApos = 0;
    int hexBpos = 0;
    int newpos = 0;
    int borrow = 0;

    // completes any neccessary padding for hexB
    string hexBmod = "";
    for (int i = hexB.size(); i < hexA.size(); i++) {
        hexBmod += "0";
    }
    hexBmod += hexB;

    // subtraction operation
    for (int i = hexA.size() - 1; i >= 0; i--) {
        hexApos = hexchartodec(hexA.at(i));
        hexBpos = hexchartodec(hexBmod.at(i));

        newpos = hexApos - hexBpos - borrow;
        borrow = 0;
        if (newpos < 0) {
            borrow += 1;
            newpos += 16;
        }
        revouthex += decchartohex(newpos);
    }

    // reverses string for printing
    string outhex = "";
    for (int i = revouthex.size() - 1; i >= 0; i--) {
        outhex += revouthex.at(i);
    }

    return outhex;
}

string hexadd(string hexA, string hexB) {
    string revouthex = "";
    int hexApos = 0;
    int hexBpos = 0;
    int carryover = 0;
    int newpos = 0;

    // completes any neccessary padding for hexB
    string hexBmod = "";
    for (int i = hexB.size(); i < hexA.size(); i++) {
        hexBmod += "0";
    }
    hexBmod += hexB;

    // hex addition
    for (int i = hexA.size() - 1; i >= 0; i--) {
        hexApos = hexchartodec(hexA.at(i));
        hexBpos = hexchartodec(hexBmod.at(i));
        newpos = (hexApos + hexBpos + carryover) % 16;
        carryover = (hexApos + hexBpos + carryover) / 16;
        revouthex += hexchars[newpos];
    }

    // reverses string for printing
    string outhex = "";
    for (int i = revouthex.size() - 1; i >= 0; i--) {
        outhex += revouthex.at(i);
    }

    return outhex;
}

// binary Class
class binary {
private:
    int sign = 0;
    int binlen = 0;
    int hexlen = 0;
    int decval = 0;

public:
    // sets the hex string based on a decimal value
    int setbydec(int decimal) {
        // verifies innum and sets decval
        if (decimal < 0) {
            sign = 1;
        }

        decval = decimal;
        return 0;
    }

    // sets the decimal value based on a hexadecimal string
    int setbyhex(string hexin) {
        string outstring = formathex(hexin);
        if (outstring == "***") {
            cerr << "setbyhex function received invalid hexstring" << endl;
            return 1;
        }

        decval = hextodec(outstring);
        return 0;
    }

    // sets the decimal value based on a binary string
    int setbybin(string binin) {
        string outstring = formatbin(binin);
        if (outstring == "***") {
            cerr << "setbybin function received invalid binstring" << endl;
            return 1;
        }

        decval = bintodec(outstring);
        return 0;
    }

    int sethexlen(int new_hexlen) {
        if (new_hexlen < 0) {
            cerr << "invalid hex length value" << endl;
            return 1;
        }
        hexlen = new_hexlen;
        return 0;
    }

    int setbinlen(int new_binlen) {
        if (new_binlen < 0) {
            cerr << "invalid bin length value" << endl;
            return 1;
        }
        binlen = new_binlen;
        return 0;
    }

    int getdec() {
        return decval;
    }

    string gethex() { 
        // returns an unsigned hexadecimal string
        if (sign == 0) {
            return dectohex(decval, hexlen);
        }

        // returns a signed hexadecimal string
        else if (hexlen >= 1 && sign == 1) {
            // gets the unsigned hex string
            string unsignedhex = dectohex(decval, hexlen);

            // gets a string of all Fs up to the hexlen
            string maxhex = "";
            for (int i = 0; i < hexlen; i++) {
                maxhex += "F";
            }

            // subtracts the maxhex from the unsignedhex and returns the signedhex string
            return hexsub(maxhex, unsignedhex);
        }

        else if (hexlen == 0 && sign == 1) {
            cerr << "gethex cannot print a signed hexadecimal string without a specified length" << endl;
            return "***";
        }

        else {
            cerr << "ERROR in gethex" << endl;
            return "***";
        }

    }

    string getbin() { 
        if (binlen == 0 && sign == 1) {
            cerr << "getbin cannot print a signed binary string without a specified length" << endl;
            return "***";
        }
        return dectobin(decval, binlen); 
    }
};
