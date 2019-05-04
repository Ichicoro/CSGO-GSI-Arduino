#include <Arduino.h>
#include <Utils.h>

bool isNumber(String input) {
    for (int i=0; i<input.length(); i++) {
        char t = input.charAt(i);
        if (t != '\n' && !isdigit(t))
            return false;
    }
    return true;
}
