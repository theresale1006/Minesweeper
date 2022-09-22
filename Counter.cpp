#include "Counter.h"
Counter::Counter(int rows, int mines) : size(21, 32), hy(Textures::Get("digits")) {
    counter = "000";
    neg = false;
    hy.setTextureRect(sf::IntRect(digits[10], size));
    hy.setPosition(0.0f, rows * 32.0f);
    icons[0].setPosition(21.0f, rows * 32.0f);
    icons[1].setPosition(42.0f, rows * 32.0f);
    icons[2].setPosition(63.0f, rows * 32.0f);
    CounterDisplay(to_string(mines));
    UpdateText();
}
void Counter::CounterDisplay(string right) {
    if (right.length() == 1) {
        counter[0] = '0';
        counter[1] = '0';
        counter[2] = right[0];
    }
    else if (right.length() == 2) {
        counter[0] = '0';
        counter[1] = right[0];
        counter[2] = right[1];
    }
    else
        counter = right;
}
void Counter::UpdateText() {
    SetRec(counter[0], icons[0]);
    SetRec(counter[1], icons[1]);
    SetRec(counter[2], icons[2]);
}
void Counter::SetRec(char& digit, sf::Sprite& icon) {
    switch (digit) {
    case '0': {
        icon.setTextureRect(sf::IntRect(digits[0], size));
        break;
    }
    case '1': {
        icon.setTextureRect(sf::IntRect(digits[1], size));
        break;
    }
    case '2': {
        icon.setTextureRect(sf::IntRect(digits[2], size));
        break;
    }
    case '3': {
        icon.setTextureRect(sf::IntRect(digits[3], size));
        break;
    }
    case '4': {
        icon.setTextureRect(sf::IntRect(digits[4], size));
        break;
    }
    case '5': {
        icon.setTextureRect(sf::IntRect(digits[5], size));
        break;
    }
    case '6': {
        icon.setTextureRect(sf::IntRect(digits[6], size));
        break;
    }
    case '7': {
        icon.setTextureRect(sf::IntRect(digits[7], size));
        break;
    }
    case '8': {
        icon.setTextureRect(sf::IntRect(digits[8], size));
        break;
    }
    case '9': {
        icon.setTextureRect(sf::IntRect(digits[9], size));
        break;
    }
    }
}
void Counter::Draw(sf::RenderWindow& win) {
    if (neg)
        win.draw(hy);
    for (sf::Sprite icon : icons)
        win.draw(icon);
}
void Counter::Add() {
    int counterInt = stoi(counter);
    if (neg) {
        if (counterInt == 1) {
            neg = false;
            counter = "000";
            UpdateText();
            return;
        }
        else
            counterInt--;
    }
    else
        counterInt++;
    CounterDisplay(to_string(counterInt));
    UpdateText();
}
void Counter::Minus() {
    int counterInt = stoi(counter);
    if (counterInt != 0) {
        if (neg)
            counterInt++;
        else
            counterInt--;
    }
    else {
        neg = true;
        counter = "001";
        UpdateText();
        return;
    }
    CounterDisplay(to_string(counterInt));
    UpdateText();
}