//
// Created by Olcay Taner YILDIZ on 2019-04-20.
//

#include <string>
#include "Symbol.h"

Symbol::Symbol(string name) : Word(move(name)) {
}

bool Symbol::isVerb() {
    return contains(verbLabels, name);
}

bool Symbol::isVP() {
    return name == VPLabel;
}

bool Symbol::isTerminal() {
    int i;
    if (name == "," || name == "." || name == "!" || name == "?" || name == ":"
        || name == ";" || name == "\"" || name == "''" || name == "'" || name == "`"
        || name == "``" || name == "..." || name == "-" || name == "--")
        return true;
    if (contains(nonTerminalList, name)){
        return false;
    }
    if (name == "I" || name == "A")
        return true;
    for (i = 0; i < name.size(); i++){
        if (name[i] >= 'a' && name[i] <= 'z'){
            return true;
        }
    }
    return false;
}

bool Symbol::isChunkLabel() {
    if (Word::isPunctuation(name) || contains(sentenceLabels, Word::replaceAll(name, "-.*","")) || contains(phraseLabels, Word::replaceAll(name, "-.*", "")))
        return true;
    return false;
}

bool Symbol::contains(vector<string> list, string searchedItem) {
    for (const string &item : list){
        if (item == searchedItem){
            return true;
        }
    }
    return false;
}

Symbol Symbol::trimSymbol() {
    int minusIndex, equalIndex;
    if (Word::startsWith(name, "-") || (name.find('-') == string::npos && name.find('=') == string::npos)){
        return *this;
    }
    minusIndex = name.find('-');
    equalIndex = name.find('=');
    if (minusIndex != string::npos || equalIndex != string::npos){
        if (minusIndex != string::npos && equalIndex != string::npos){
            if (minusIndex < equalIndex){
                return Symbol(name.substr(0, minusIndex));
            } else {
                return Symbol(name.substr(0, equalIndex));
            }
        } else {
            if (minusIndex != string::npos){
                return Symbol(name.substr(0, minusIndex));
            } else {
                return Symbol(name.substr(0, equalIndex));
            }
        }
    } else {
        return *this;
    }
}
