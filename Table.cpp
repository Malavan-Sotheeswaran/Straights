#include "Table.h"
#include <algorithm>
Table::Table(){}

void Table::playCard(Card card){
    if(card.getSuit() == CLUB){
        for(std::vector<Card>::iterator it = clubs.begin(); it != clubs.end(); it++)
            if(card.getRank() < it->getRank()) {
                clubs.insert(it,Card(card));
                return;
            }
        clubs.push_back(Card(card));
    }
    else if(card.getSuit() == DIAMOND){
        for(std::vector<Card>::iterator it = diamonds.begin(); it != diamonds.end(); it++)
            if(card.getRank() < it->getRank()) {
                diamonds.insert(it,Card(card));
                return;
            }
        diamonds.push_back(Card(card));
    }
    else if(card.getSuit() == HEART){
        for(std::vector<Card>::iterator it = hearts.begin(); it != hearts.end(); it++)
            if(card.getRank() < it->getRank()) {
                hearts.insert(it,Card(card));
                return;
            }
        hearts.push_back(Card(card));
    }
    else if(card.getSuit() == SPADE){
        for(std::vector<Card>::iterator it = spades.begin(); it != spades.end(); it++)
            if(card.getRank() < it->getRank()) {
                spades.insert(it,Card(card));
                return;
            }
        spades.push_back(Card(card));
    }
}

bool Table::isLegal(Card &card){
    if(card.getRank() == SEVEN) return true;
    if(card.getSuit() == CLUB){
        for(std::vector<Card>::iterator it = clubs.begin(); it != clubs.end(); it++)
            if(card.canPlay(*it)) return true;
    }
    else if(card.getSuit() == DIAMOND){
        for(std::vector<Card>::iterator it = diamonds.begin(); it != diamonds.end(); it++)
            if(card.canPlay(*it)) return true;
    }
    else if(card.getSuit() == HEART){
        for(std::vector<Card>::iterator it = hearts.begin(); it != hearts.end(); it++)
            if(card.canPlay(*it)) return true;
    }
    else if(card.getSuit() == SPADE){
        for(std::vector<Card>::iterator it = spades.begin(); it != spades.end(); it++)
            if(card.canPlay(*it)) return true;
    }
    return false;
}

std::ostream &operator<<(std::ostream &o, Table &t){
    o << "Cards on the table:";
    o << "\nClubs:";
    for(std::vector<Card>::iterator it = t.clubs.begin(); it != t.clubs.end(); it++)
        o << " " << it->getRank() + 1;
    o << "\nDiamonds:";
    for(std::vector<Card>::iterator it = t.diamonds.begin(); it != t.diamonds.end(); it++)
        o << " " << it->getRank() + 1;
    o << "\nHearts:";
    for(std::vector<Card>::iterator it = t.hearts.begin(); it != t.hearts.end(); it++)
        o << " " << it->getRank() + 1;
    o << "\nSpades:";
    for(std::vector<Card>::iterator it = t.spades.begin(); it != t.spades.end(); it++)
        o << " " << it->getRank() + 1;
    o << "\n";
    return o;
}
