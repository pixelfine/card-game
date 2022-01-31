#include "Player.hpp"

void Player::addHand(std::shared_ptr<Card> c) {
    this->hand.push_back(c);
}

std::shared_ptr<Card> Player::removeHand(int index) {
    std::shared_ptr<Card> c = hand[index];
    this->hand.erase(hand.begin()+index);
    return c;
}

void Player::pushDeck(std::shared_ptr<Card> c) {
    deck.push(c);
}

std::shared_ptr<Card> Player::popDeck() {
    std::shared_ptr<Card> c = deck.top();
    deck.pop();
    return c;
}


void Player::addFront(std::shared_ptr<Card> c){
    this->front.push_back(c);
}

std::shared_ptr<Card> Player::removeFront(int index){
    std::shared_ptr<Card> c = front[index];
    this->front.erase(front.begin()+index);
    return c;
}


std::vector<std::shared_ptr<Card>>& Player::getHand(){
    return hand;
}

std::stack<std::shared_ptr<Card>>&  Player::getDeck(){
    return deck;
}

std::vector<std::shared_ptr<Card>>& Player::getFront(){
    return front;
}