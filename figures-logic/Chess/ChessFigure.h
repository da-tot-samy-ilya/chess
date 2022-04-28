#pragma once
#include <iostream>
#include <vector>
enum TypePiece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
enum IsChosenForMove { NOT_CHOSEN, CHOSEN };

class Piece
{
private:
    TypePiece type_piece = EMPTY;
    IsChosenForMove is_choosen_for_move = NOT_CHOSEN;
protected:
    char colour; // цвет фигуры
    int vertical; // буквы
    int horizontal;// цифры
    bool canMove = true;
    std::vector<std::pair<int, int>> PossibleMoves;
public:
    Vector2f bPosition;
    IntRect bSprite;

    Sprite figure_sprite;
    Sprite square_sprite;
    Piece() : colour('n'), vertical(-1), horizontal(-1) {};
    Piece(char colour, int vert, int hor) : colour(colour), vertical(vert), horizontal(hor) {};
    Piece(Piece& f)
    {
        colour = f.colour;
        vertical = f.vertical;
        horizontal = f.horizontal;
    };
    virtual bool move(int vert, int hor, char col) { return false; };
    virtual bool cut_down(Piece& f) { return false; };
    virtual bool getFirstMove() { return false; }

    char GetColour() { return this->colour; };
    int GetVert() { return this->vertical; };
    int GetHor() { return this->horizontal; };
    TypePiece GetName() { return this->type_piece; };
    IsChosenForMove GetIsChosenForMove() {
        return is_choosen_for_move;
    }
    void SetIsChosenForMove(IsChosenForMove is_choosen_for_move) {
        this->is_choosen_for_move = is_choosen_for_move;
    }
    Sprite GetSpriteFigure() {
        return this->figure_sprite;
    }
    Sprite GetSpriteSquare() {
        return this->square_sprite;
    }
    void SetTextureFigures(Texture& texture) {
        figure_sprite.setTexture(texture);
    }
    void SetTextureSquares(Texture& texture) {
        square_sprite.setTexture(texture);
    }
    void setVisualFigures(Vector2f bPosition, IntRect bSprite) {
        this->bPosition = bPosition;
        this->bSprite = bSprite;
        figure_sprite.setTextureRect(bSprite);
        figure_sprite.setPosition(bPosition);
    }
    void setVisualSquares(Vector2f bPosition, IntRect bSprite) {
        this->bPosition = bPosition;
        this->bSprite = bSprite;
        square_sprite.setTextureRect(bSprite);
        square_sprite.setPosition(bPosition);
    }
    
};

bool Check(int vert, int hor)
{
    if (vert != -1 && vert != 8 && hor != -1 && hor != 8)
        return false;
    return true;
}