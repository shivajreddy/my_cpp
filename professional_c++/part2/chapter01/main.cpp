#include <format>
#include <iostream>

/* Exercise: 4-1 */

class Card
{
public:
    // Member properties
    enum class Number {
        Ace,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King
    };
    enum class Suit { Diamond, Heart, Spade, Club };

private:
    Number m_number { Number::Ace };
    Suit m_suit { Suit::Diamond };

public:
    // Constructors
    Card() {}
    Card(Number number, Suit suit) : m_number(number), m_suit(suit) {}

    // Getters
    Number get_number() { return m_number; }
    Suit get_suit() { return m_suit; }

    // Print Card
    void print()
    {
        std::cout << static_cast<int>(m_suit) << " : "
                  << static_cast<int>(m_number) << std::endl;
    }
};

int main()
{
    std::cout << "Exercise: 4" << std::endl;

    Card deck[52];

    Card c;
    c.print();

    return 0;
}
