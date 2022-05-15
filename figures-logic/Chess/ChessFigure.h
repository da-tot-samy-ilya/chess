#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

enum TypePiece { EMPTY, KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN };
enum IsChosenForMove { NOT_CHOSEN, CHOSEN };
enum Colour { WHITE, BLACK, NONE };

class Piece
{
private:
    IsChosenForMove is_choosen_for_move = NOT_CHOSEN;
protected:
    TypePiece type_piece;
    Colour colour = NONE; // цвет фигуры
    int vertical; // буквы
    int horizontal;// цифры
    bool canMove = true;
    int moveCount = 0;
    std::vector<std::pair<int, int>> PossibleMoves;
public:
    Vector2f bPosition;
    IntRect bSprite;
    Sprite figure_sprite;
    Sprite square_sprite;
    Piece() : colour(NONE), vertical(-1), horizontal(-1), type_piece(EMPTY){};
    Piece(Colour colour, int vert, int hor, TypePiece type) : colour(colour), vertical(vert), horizontal(hor), type_piece(type) {};
    Piece(Piece& f)
    {
        colour = f.colour;
        vertical = f.vertical;
        horizontal = f.horizontal;
    };
    virtual int* getMoveCount() { return &(this->moveCount); }// move(Piece &t) in Board

    Colour* GetColour() { return &(this->colour); };
    int* GetVert() { return &(this->vertical); };
    int* GetHor() { return &(this->horizontal); };
    TypePiece* GetName() { return &(this->type_piece); };
    IsChosenForMove GetIsChosenForMove() {
        return is_choosen_for_move;
    }

    bool* GetCanMove() { return &(this->canMove); };

    std::vector<std::pair<int, int>>* GetPossibleMoves() { 
        return &PossibleMoves; 
    };

    void SetIsChosenForMove(IsChosenForMove is_choosen_for_move) {
        this->is_choosen_for_move = is_choosen_for_move;
    }
    sf::Sprite GetSpriteFigure() {
        return this->figure_sprite;
    }
    sf::Sprite GetSpriteSquare() {
        return this->square_sprite;
    }
    void SetTextureFigures(sf::Texture& texture) {
        figure_sprite.setTexture(texture);
    }
    void SetTextureSquares(sf::Texture& texture) {
        square_sprite.setTexture(texture);
    }
    void setVisualFigures(sf::Vector2f bPosition, sf::IntRect bSprite) {
        this->bPosition = bPosition;
        this->bSprite = bSprite;
        figure_sprite.setTextureRect(bSprite);
        figure_sprite.setPosition(bPosition);
    }
    void setVisualSquares(sf::Vector2f bPosition, sf::IntRect bSprite) {
        this->bPosition = bPosition;
        this->bSprite = bSprite;
        square_sprite.setTextureRect(bSprite);
        square_sprite.setPosition(bPosition);
    }
    
};

bool Check(int vert, int hor)
{
    if (vert <= -1 || vert >= 8 || hor <= -1 || hor >= 8)
        return false;
    return true;
}