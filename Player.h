#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Card.h"
#include "Table.h"
#include <ostream>
#include <istream>
class Player{
    friend std::ostream &operator<<(std::ostream &, Player &);
    bool isHuman_;
    std::vector<Card> hand;
    int score_;
    public:
        Player();
        void setHand(Card **);
        std::vector<Card> getValidMoves(Table &);
        void swapControl();
        bool isHuman();
        bool hasCard(const Card &);
        void removeCard(const Card &);
        bool hasCards();
        Card getFirst();
        int score();
        void addScore(int);
};
#endif
