// Minhlee Lam
// Class (CECS 325-02)
// Prog 2 - More WAR (Cards)
// 02/26/2024
//
// I certify that this program is my own original work. I did not copy any part
// of this program from any other source. I further certify that I typed each
// and every line of code in this program.

#include <iostream>
using namespace std;

// Card Class
class Card {
public:
  Card(); // default constructor – needed for array in Deck class
  Card(char rank,
       char suit); // constructor to create a card, setting the suit and rank
  void display();  // display the card example: AC, 10S, KD
  int compare(Card other); // return 1 for win, 0 for tie, -1 for lose

private:
  char rank;
  char suit;
};

// Deck Class
class Deck {
public:
  Deck();         // constructor which creates a deck of 52 cards
  Card deal();    // deal a card if you can – otherwise raise an exception
  void display(); // show all the cards in the deck
  void shuffle(); // shuffle the cards in the deck
  bool isEmpty(); // return true if deck is empty

private:
  Card cards[52];
  int numCards;
};

int main() {
  Deck deck;

  // testing cases
  // Card card1('A', 'S'); // Ace of Spades
  // Card card2('2', 'D'); // 2 of Diamonds
  // int result = card1.compare(card2);
  // cout << result << endl;

  // Prompt usernames
  string p1, p2;
  int numOfGames;
  cout << "Enter the name of player 1: ";
  cin >> p1;
  cout << "Enter the name of player 2: ";
  cin >> p2;
  cout << "How many games do you want to play? ";
  cin >> numOfGames;

  // Display original and shuffled decks
  cout << "\nOriginal Deck:\n";
  deck.display();

  deck.shuffle();
  cout << "Shuffled Deck" << endl;
  deck.display();
  cout << endl;

  // Loop x number of games & display results
  int player1Wins = 0, player2Wins = 0, ties = 0;
  for (int i = 1; i <= numOfGames; ++i) {
    std::cout << "Game " << i << std::endl;
    std::cout << "--------" << std::endl;
    try {
      Card player1Card = deck.deal();
      Card player2Card = deck.deal();

      std::cout << p1 << "=>" << std::flush;
      player1Card.display();
      std::cout << std::endl;
      std::cout << p2 << "=>" << std::flush;
      player2Card.display();
      std::cout << std::endl;

      int result = player1Card.compare(player2Card);
      if (result == 1) {
        std::cout << p1 << " => Winner" << std::endl;
        player1Wins++;
      } else if (result == -1) {
        std::cout << p2 << " => Winner" << std::endl;
        player2Wins++;
      } else {
        std::cout << "Tie game" << std::endl;
        ties++;
      }
      std::cout << std::endl;
    } catch (
        // note: more efficient, as catches original exeception obj by const ref
        // good because avoids unnecessary copying
        const range_error &e) {
      std::cerr << "Exception caught: " << e.what() << std::endl;
      break; // Exit the loop if an exception occurs
    }
  }

  // Print game stat
  std::cout << "------Final Stats-------" << std::endl;
  std::cout << p1 << " vs. " << p2 << std::endl;
  std::cout << "Wins " << player1Wins << " " << player2Wins << std::endl;
  std::cout << "Losses " << player2Wins << " " << player1Wins << std::endl;
  std::cout << "Ties " << ties << " " << ties << std::endl;

  return 0;
}

// Card Implementations
Card::Card(){};
Card::Card(char rank, char suit)
    : rank(rank), suit(suit) {} // constructor w/ initializer list
void Card::display() {
  string rankStr;
  string suitStr;

  switch (rank) {
  case 'T':
    rankStr = "10";
    break;
  case 'J':
    rankStr = "J";
    break;
  case 'Q':
    rankStr = "Q";
    break;
  case 'K':
    rankStr = "K";
    break;
  case 'A':
    rankStr = "A";
    break;
  default:
    rankStr = rank;
  }
  switch (suit) {
  case 'C':
    suitStr = "C";
    break;
  case 'S':
    suitStr = "S";
    break;
  case 'D':
    suitStr = "D";
    break;
  case 'H':
    suitStr = "H";
    break;
  default:
    suitStr = suit;
  }

  cout << rankStr << suitStr << endl;
}
int Card::compare(Card other) {
  int rankVal = 0;
  int otherRankVal = 0;

  switch (rank) {
  case 'A':
    rankVal = 14;
    break;
  case 'K':
    rankVal = 13;
    break;
  case 'Q':
    rankVal = 12;
    break;
  case 'J':
    rankVal = 11;
    break;
  case 'T':
    rankVal = 10;
    break;
  default:
    rankVal = rank - '0';
  }

  switch (other.rank) {
  case 'A':
    otherRankVal = 14;
    break;
  case 'K':
    otherRankVal = 13;
    break;
  case 'Q':
    otherRankVal = 12;
    break;
  case 'J':
    otherRankVal = 11;
    break;
  case 'T':
    otherRankVal = 10;
    break;
  default:
    otherRankVal = other.rank - '0';
  }

  if (rankVal == otherRankVal) {
    return 0;
  } else if (rankVal > otherRankVal) {
    return 1;
  } else {
    return -1;
  }
}

// Deck Implementation
Deck::Deck() {
  // create a deck of 52 cards
  char suits[] = {'S', 'H', 'D', 'C'};
  char ranks[] = {'A', '2', '3', '4', '5', '6', '7',
                  '8', '9', 'T', 'J', 'Q', 'K'};

  int index = 0;
  for (char suit : suits) {
    for (char rank : ranks) {
      cards[index] = Card(rank, suit);
      ++index;
      // cards.push_back(Card(rank, suit));
    }
  }
  numCards = sizeof(cards) / sizeof(cards[0]); // get size of cards array
}
Card Deck::deal() {
  // deal a card if you can – otherwise raise an exception
  if (isEmpty())
    throw range_error("Deck is empty!");

  Card card = cards[numCards - 1];
  cards[numCards - 1] = Card(); // reset the last card in the array
  numCards--;                   // Decrement numCards after dealing a card
  return card;
}
void Deck::display() {
  for (size_t i = 0; i < numCards; ++i) {
    cards[i].display();
    if (i < numCards - 1) {
      cout << "";
    }
  }
  cout << endl;
}
void Deck::shuffle() {
  srand(time(0));

  int n = numCards;
  for (int i = n - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    swap(cards[i], cards[j]);
  }
}
bool Deck::isEmpty() { return numCards == 0; } // return true if empty
