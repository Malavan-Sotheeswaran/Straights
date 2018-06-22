#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <ostream>
#include "Card.h"
class Table{
    friend std::ostream &operator<<(std::ostream &, Table &);
    std::vector<Card> clubs;
    std::vector<Card> diamonds;
    std::vector<Card> hearts;
    std::vector<Card> spades;
    public:
        Table();
        void playCard(Card);
        bool isLegal(Card &);
};
#endif
