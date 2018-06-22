#include "Player.h"
#include <iostream>
Player::Player() : isHuman_{false}, score_{0}{}

void Player::setHand(Card **cards){
    for(int i = 0; i < 13; i++)
        hand.push_back(Card(*cards[i]));
}

std::vector<Card> Player::getValidMoves(Table &table){
    std::vector<Card> validMoves;
    if(this->hasCard(Card(SPADE,SEVEN))){
        validMoves.push_back(Card(SPADE,SEVEN));
        return validMoves;
    }
    for(std::vector<Card>::iterator it = hand.begin(); it != hand.end(); it++)
        if(table.isLegal(*it)) validMoves.push_back(Card(*it));
    return validMoves;
}

void Player::swapControl(){
    isHuman_ = !isHuman_;
}

bool Player::isHuman(){return isHuman_;}

bool Player::hasCard(const Card &card){
    for(std::vector<Card>::iterator it = hand.begin(); it != hand.end(); it++)
        if((*it) == card) return true;
    return false;
}

void Player::removeCard(const Card &card){
    for(std::vector<Card>::iterator it = hand.begin(); it != hand.end(); it++)
        if((*it) == card){
            hand.erase(it);
            return;
        }
}

bool Player::hasCards(){
    return hand.size() != 0;
}

Card Player::getFirst(){
    return hand.front();
}

int Player::score(){return score_;}

void Player::addScore(int score){score_ += score;}

std::ostream &operator<<(std::ostream &o, Player &p){
    o << "Your hand:";
    for(std::vector<Card>::iterator it = p.hand.begin(); it != p.hand.end(); it++)
        o << " " << (*it);
    o << "\n";
    return o;
}
