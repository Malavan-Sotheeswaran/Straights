#include <random>
#include "Card.h"
#include "Command.h"
#include "Player.h"
#include <iostream>
#ifndef CARD_COUNT
#define CARD_COUNT 52
#endif
#ifndef PLAYER_COUNT
#define PLAYER_COUNT 4
#endif

int seed = 0;
Card *cards_[CARD_COUNT] = {new Card(CLUB,ACE), new Card(CLUB,TWO), new Card(CLUB,THREE), new Card(CLUB,FOUR), new Card(CLUB,FIVE), new Card(CLUB,SIX), new Card(CLUB,SEVEN), new Card(CLUB,EIGHT), new Card(CLUB,NINE), new Card(CLUB,TEN), new Card(CLUB,JACK), new Card(CLUB,QUEEN), new Card(CLUB,KING), 
							new Card(DIAMOND,ACE), new Card(DIAMOND,TWO), new Card(DIAMOND,THREE), new Card(DIAMOND,FOUR), new Card(DIAMOND,FIVE), new Card(DIAMOND,SIX), new Card(DIAMOND,SEVEN), new Card(DIAMOND,EIGHT), new Card(DIAMOND,NINE), new Card(DIAMOND,TEN), new Card(DIAMOND,JACK), new Card(DIAMOND,QUEEN), new Card(DIAMOND,KING), 
							new Card(HEART,ACE), new Card(HEART,TWO), new Card(HEART,THREE), new Card(HEART,FOUR), new Card(HEART,FIVE), new Card(HEART,SIX), new Card(HEART,SEVEN), new Card(HEART,EIGHT), new Card(HEART,NINE), new Card(HEART,TEN), new Card(HEART,JACK), new Card(HEART,QUEEN), new Card(HEART,KING), 
							new Card(SPADE,ACE), new Card(SPADE,TWO), new Card(SPADE,THREE), new Card(SPADE,FOUR), new Card(SPADE,FIVE), new Card(SPADE,SIX), new Card(SPADE,SEVEN), new Card(SPADE,EIGHT), new Card(SPADE,NINE), new Card(SPADE,TEN), new Card(SPADE,JACK), new Card(SPADE,QUEEN), new Card(SPADE,KING)};

void shuffle(){
    static std::mt19937 rng(seed);

	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

int main(int argc, char **argv){
	if (argc == 2) seed = strtol(argv[1],nullptr,10);
	Player players[PLAYER_COUNT];
	int scores[PLAYER_COUNT];
	std::vector<Card> discards[PLAYER_COUNT];
	for(int i = 0; i < PLAYER_COUNT; i++){
		scores[i] = 0;
	}
	char isHuman;

	for(int i = 0; i < PLAYER_COUNT; i++){
		std::cout << "Is player " << (i+1) << " a human(h) or a computer(c)?" << "\n>";
		std::cin >> isHuman;
		if(isHuman == 'h') players[i].swapControl();
	}

	while(true){
		shuffle();
		players[0].setHand(cards_);
		players[1].setHand(cards_ + 13);
		players[2].setHand(cards_ + 26);
		players[3].setHand(cards_ + 39);
		int curPlayer;
		int numFinished = 0;
		Table table;
		bool gameDone = false;
		for(int i = 0; i < PLAYER_COUNT; i++)
			if(players[i].hasCard(Card(SPADE,SEVEN))) curPlayer = i;
		std::cout << "A new round begins. It's player " << (curPlayer+1) << "'s turn to play.\n";
		while(true){
			std::vector<Card> plays = players[curPlayer].getValidMoves(table);
			if(players[curPlayer].isHuman() && players[curPlayer].hasCards()){
				std::cout << table;
				std::cout << players[curPlayer];
				std::cout << "Legal Plays:";
				for(std::vector<Card>::iterator it = plays.begin(); it != plays.end(); it++)
					std::cout << " " << (*it);
				std::cout << "\n>";
				Command command;
				while(true){
					std::cin >> command;
					if(command.type == PLAY){
						if(table.isLegal(command.card)){
							std::cout << "Player " << (curPlayer+1) << " plays " << command.card << ".\n";
							table.playCard(command.card);
							players[curPlayer].removeCard(command.card);
							if (!players[curPlayer].hasCards()) numFinished++;
							break;
						}
						else{
							std::cout << "This is not a legal play.\n>";
						}
					}
					else if(command.type == DISCARD){
						if(plays.size() == 0){
							std::cout << "Player " << (curPlayer+1) << " discards " << command.card << ".\n";
							scores[curPlayer] += command.card.getRank() + 1;
							discards[curPlayer].push_back(Card(command.card));
							players[curPlayer].removeCard(command.card);
							if (!players[curPlayer].hasCards()) numFinished++;
							break;
						}
						else{
							std::cout << "You have a legal play. You may not discard.\n>";
						}
					}
					else if(command.type == DECK){
						for(int j = 0; j < 13; j++)
							std::cout << *cards_[j] << " ";
						std::cout << "\n";
						for(int j = 0; j < 13; j++)
							std::cout << *cards_[j + 13] << " ";
						std::cout << "\n";
						for(int j = 0; j < 13; j++)
							std::cout << *cards_[j + 26] << " ";
						std::cout << "\n";
						for(int j = 0; j < 13; j++)
							std::cout << *cards_[j + 39] << " ";
						std::cout << "\n>";
					}
					else if(command.type == QUIT){
						exit(0);
					}
					else if(command.type == RAGEQUIT){
						players[curPlayer].swapControl();
						std::cout << "Player " << (curPlayer+1) << "ragequits. A computer will now take over.";
						if(plays.size() == 0){
							std::cout << "Player " << (curPlayer+1) << " discards " << players[curPlayer].getFirst() << ".\n";
							scores[curPlayer] += players[curPlayer].getFirst().getRank() + 1;
							discards[curPlayer].push_back(Card(players[curPlayer].getFirst()));
							players[curPlayer].removeCard(players[curPlayer].getFirst());
							if (!players[curPlayer].hasCards()) numFinished++;
						}
						else{
							std::cout << "Player " << (curPlayer+1) << " plays " << plays[0] << ".\n";
							table.playCard(plays[0]);
							players[curPlayer].removeCard(plays[0]);
							if (!players[curPlayer].hasCards()) numFinished++;
						}
						break;
					}
				}
			}
			else if(players[curPlayer].hasCards()) {
				if(plays.size() == 0){
					std::cout << "Player " << (curPlayer+1) << " discards " << players[curPlayer].getFirst() << ".\n";
					scores[curPlayer] += players[curPlayer].getFirst().getRank() + 1;
					discards[curPlayer].push_back(Card(players[curPlayer].getFirst()));
					players[curPlayer].removeCard(players[curPlayer].getFirst());
					if (!players[curPlayer].hasCards()) numFinished++;
				}
				else{
					std::cout << "Player " << (curPlayer+1) << " plays " << plays[0] << ".\n";
					table.playCard(plays[0]);
					players[curPlayer].removeCard(plays[0]);
					if (!players[curPlayer].hasCards()) numFinished++;
				}
			}
			if(numFinished == PLAYER_COUNT){
				for(int i = 0; i < PLAYER_COUNT; i++){
					std::cout << "Player " << i+1 << "'s discards:";
					for(std::vector<Card>::iterator it = discards[i].begin(); it != discards[i].end(); it++)
						std::cout << " " << *it;
					discards[i].clear();
					std::cout << "\nPlayer " << i+1 << "'s score: " << players[i].score() << " + " << scores[i] << " = " << players[i].score() + scores[i] << "\n";
					players[i].addScore(scores[i]);
					scores[i] = 0;
					if(players[i].score() >= 80)
						gameDone = true;
				}
				break;
			}
			curPlayer++;
			curPlayer = curPlayer % 4;
		}
		if(gameDone){
			int minScore = INT32_MAX;
			for(int i = 0; i < PLAYER_COUNT; i++)
				if(players[i].score() < minScore) minScore = players[i].score();
			for(int i = 0; i < PLAYER_COUNT; i++)
				if(players[i].score() == minScore) std::cout << "Player " << i+1 << " wins!\n";
			break;
		}
	}
	for(int i = 0; i < CARD_COUNT; i++)
		delete cards_[i];
	return 0;
}
