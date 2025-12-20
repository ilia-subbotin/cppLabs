#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <iomanip>

enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

struct Card {
    Rank rank;
    int getValue() const {
        if (rank >= TEN) return 10;
        if (rank == ACE) return 11;
        return rank;
    }
    std::string toString() const {
        static const std::string ranks[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
        return ranks[rank - 1];
    }
};

class Hand {
public:
    std::vector<Card> cards;
    int getScore() const {
        int score = 0, aces = 0;
        for (const auto& c : cards) {
            score += c.getValue();
            if (c.rank == ACE) aces++;
        }
        while (score > 21 && aces > 0) {
            score -= 10;
            aces--;
        }
        return score;
    }
};

class Player {
public:
    std::string name;
    Hand hand;
    bool isStanding = false;
    bool isBusted = false;

    double calculateWinChance(std::vector<Card> remainingDeck, int dealerVisibleScore) {
        if (hand.getScore() > 21) return 0.0;
        int wins = 0;
        const int simulations = 1000;
        std::random_device rd;
        std::mt19937 g(rd());
        for (int i = 0; i < simulations; ++i) {
            std::vector<Card> simDeck = remainingDeck;
            std::shuffle(simDeck.begin(), simDeck.end(), g);
            int simDealerScore = dealerVisibleScore;
            int deckIdx = 0;
            while (simDealerScore < 17 && deckIdx < (int)simDeck.size()) {
                int val = simDeck[deckIdx++].getValue();
                simDealerScore += val;
                if (simDealerScore > 21 && val == 11) simDealerScore -= 10;
            }
            int myScore = hand.getScore();
            if (simDealerScore > 21 || (myScore <= 21 && myScore > simDealerScore)) wins++;
            else if (myScore == simDealerScore) wins++;
        }
        return (double)wins / simulations;
    }
};

class BlackjackGame {
private:
    std::vector<Card> deck;
    std::vector<Player> players;
    Hand dealerHand;
    void createDeck() {
        deck.clear();
        for (int r = ACE; r <= KING; ++r)
            for (int s = 0; s < 4; ++s) deck.push_back({ static_cast<Rank>(r) });
        std::shuffle(deck.begin(), deck.end(), std::mt19937(std::random_device{}()));
    }
    Card drawCard() {
        if (deck.empty()) createDeck();
        Card c = deck.back();
        deck.pop_back();
        return c;
    }
public:
    BlackjackGame(int n) {
        for (int i = 0; i < n; ++i) players.push_back({ "Player " + std::to_string(i + 1) });
    }
    void play() {
        createDeck();
        for (int i = 0; i < 2; ++i) {
            for (auto& p : players) p.hand.cards.push_back(drawCard());
            dealerHand.cards.push_back(drawCard());
        }
        bool gameActive = true;
        while (gameActive) {
            gameActive = false;
            for (auto& p : players) {
                if (p.isBusted || p.isStanding) continue;
                std::cout << "\n--- " << p.name << "'s Turn ---" << std::endl;
                std::cout << "Dealer shows: [" << dealerHand.cards[0].toString() << "]" << std::endl;
                std::cout << "Your hand: ";
                for (auto& c : p.hand.cards) std::cout << "[" << c.toString() << "] ";
                std::cout << "| Score: " << p.hand.getScore() << std::endl;
                double winProb = p.calculateWinChance(deck, dealerHand.cards[0].getValue());
                std::cout << "Win Probability: " << std::fixed << std::setprecision(1) << winProb * 100 << "%" << std::endl;
                std::cout << "Action: (h)it or (s)tand? ";
                char choice; std::cin >> choice;
                if (choice == 'h') {
                    p.hand.cards.push_back(drawCard());
                    if (p.hand.getScore() > 21) {
                        p.isBusted = true;
                        std::cout << "Result: Busted!" << std::endl;
                    }
                    else gameActive = true;
                }
                else p.isStanding = true;
            }
            bool stillPlaying = false;
            for (const auto& p : players) if (!p.isBusted && !p.isStanding) stillPlaying = true;
            gameActive = stillPlaying;
        }
        std::cout << "\n--- Dealer's Final Turn ---" << std::endl;
        while (dealerHand.getScore() < 17) dealerHand.cards.push_back(drawCard());
        std::cout << "Dealer's score: " << dealerHand.getScore() << std::endl;
        std::cout << "\n--- Final Results ---" << std::endl;
        int dScore = dealerHand.getScore();
        for (auto& p : players) {
            int pScore = p.hand.getScore();
            std::cout << p.name << ": ";
            if (p.isBusted) std::cout << "LOST (Bust)";
            else if (dScore > 21 || pScore > dScore) std::cout << "WON!";
            else if (pScore == dScore) std::cout << "PUSH (Tie)";
            else std::cout << "LOST";
            std::cout << " (" << pScore << " vs " << dScore << ")" << std::endl;
        }
    }
};

int main() {
    std::cout << "Enter number of players: ";
    int n;
    if (!(std::cin >> n) || n < 1) n = 1;
    BlackjackGame game(n);
    game.play();
    return 0;
}