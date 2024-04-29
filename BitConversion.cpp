#include <iostream>
#include <string>
using namespace std;

//                                                  USEFUL TOOLS

// pads a string with leading zeros until it matches the specified length
string zeropad(string instring, int length) {
    string outstr = "";
    for (int i = instring.length(); i < length; i++) {
        outstr += "0";
    }
    outstr += instring;
    return outstr;
}

//                                                  HEX CONVERSIONS

// hex to dec
const char hexchars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
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
int hexchartodec(char hexchar) {
    for (int i = 0; i < 16; i++) {
        if (hexchar == hexchars[i]) return i;
    }
    return -1;
}

// dec to hex
string dectohex(int innum, int hexlen) {
    int mult = 1;
    int chgnum = innum;

    // finds the max value
    for (int i = 0; i < (hexlen - 1); i++) {
        mult = mult * 16;
    }
    cout << "mult: " << mult;

    // creates the outstring
    string outstring = "";
    while (mult > 0) {
        cout << chgnum << ", " << mult << ", " << chgnum / mult << endl;
        outstring += hexchars[chgnum / mult];
        chgnum -= int(chgnum / mult) * mult;
        mult /= 16;
    }
    return outstring;
}
char decchartohex(int decchar) {
    if (decchar <= 16 && decchar >= 0) return hexchars[decchar];
    return '#';
}

const string hexbin[16] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111" };

// bin to hex WIP
string bintohex(string binstring) {
    string hexstring = "";
    
    // pad with zeros
    if (binstring.size() % 4) {
        zeropad(binstring, binstring.size() + (4 - binstring.size() % 4));
    }

    // search
    for (int i = binstring.size(); i >= 0; i -= 4) {
        for (int hex = 0; hex < 16; hex++) {
            if (hexbin[hex].at(0) == binstring.at(i) && hexbin[hex].at(1) == binstring.at(i + 1) && hexbin[hex].at(2) == binstring.at(i + 2) && hexbin[hex].at(3) == binstring.at(i + 3)) {
                hexstring += hexchars[hex];
            }
        }
    }

    return hexstring;
}

// hex to bin
string hextobin(string hexstring) {
    string outstring;
    for (int letter = 0; letter < hexstring.length(); letter++) {
        for (int hex = 0; hex < 16; hex++) {
            if (hexchars[hex] == hexstring.at(letter)) {
                outstring += hexbin[hex];
                hex = 16;
            }
        }
    }
    return outstring;
}

//                                                  HEX MATH

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

//                                                  HEX CHECKER

// checks to see if a string contains only valid hex characters and additional specified characters
bool ishex(string inhex, string additchars = "") {
    int match = 0;
    
    // checks each character of inhex
    for (int i = 0; i < inhex.size() - 1; i++) {
        
        // checks for valid hex chars
        for (int hex = 0; hex < 16; hex++) {
            if (inhex.at(i) == hexchars[hex]) {
                match += 1;
                break;
            }
        }

        // checks for characters listed under additchars
        for (int addit = 0; addit < additchars.size() - 1; addit++) {
            if (inhex.at(i) == additchars.at(addit)) {
                match += 1;
                break;
            }
        }

        if (match > 0) return 1;
        match = 0;
    }
    return 0;
}

//                                                  BINARY CONVERSIONS

// dec to bin
string dectobin(int innum, int bitlen) {
    int mult = 1;
    int chgnum = innum;

    // finds the max value
    for (int i = 0; i < bitlen; i++) {
        mult = mult * 2;
    }
    cout << "mult: " << mult;

    // creates the outstring
    string outstring = "";
    while (mult > 0) {
        cout << chgnum << ", " << mult << ", " << chgnum / mult << endl;
        if (chgnum / mult == 1) {
            outstring += '1';
            chgnum -= mult;
        }
        else {
            outstring += '0';
        }
        mult /= 2;
    }
    return outstring;
}
