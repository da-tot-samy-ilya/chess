#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
using namespace std;

Texture aside_texture, main_background_texture, numbers_texture, letters_texture;
Texture first_button, second_button, third_button;
Texture black_square, white_square, red_black_square, red_white_square, yellow_black_square, yellow_white_square, green_black_square, green_white_square;
Texture figure_texture;
Font font;
Text header;
Text text;
Texture ip_ok_button_texture;
void loadTexures() {
	figure_texture.loadFromFile("images/figures.png");
	aside_texture.loadFromFile("images/aside_background.png");
	main_background_texture.loadFromFile("images/grey_texture.png");
	numbers_texture.loadFromFile("images/numbers.png");
	letters_texture.loadFromFile("images/letters.png");
	first_button.loadFromFile("images/button1.png");
	second_button.loadFromFile("images/button2.png");
	third_button.loadFromFile("images/button3.png");
	black_square.loadFromFile("images/black_texture.png");
	white_square.loadFromFile("images/white_texture.png");
	red_black_square.loadFromFile("images/red_black_texture.png");
	red_white_square.loadFromFile("images/red_white_texture.png");
	yellow_black_square.loadFromFile("images/yellow_black_texture.png");
	yellow_white_square.loadFromFile("images/yellow_white_texture.png");
	green_black_square.loadFromFile("images/green_black_texture.png");
	green_white_square.loadFromFile("images/green_white_texture.png");
	font.loadFromFile("images/Roboto-Bold.ttf");
	ip_ok_button_texture.loadFromFile("images/enter_ip_ok.png");
}

const int board_offset_x = 187;
const int board_offset_y = 20;
const int square_size = 56;
string IP = "";
string  t = "";
enum IsChoosingMove { CHOOSING_MOVE, NOT_CHOOSING_MOVE };
enum ColorOfSquare {RED, GREEN, YELLOW, NONE_COLOR};

class Button {
public:
	Sprite sprite;
	Vector2f bPosition;
	IntRect bSprite;
	string name = "";
	Button(Texture& texture, Vector2f bPosition, IntRect bSprite) {
		sprite.setTexture(texture);
		this->bPosition = bPosition;
		this->bSprite = bSprite;
		sprite.setTextureRect(bSprite);
		sprite.setPosition(bPosition);
	}
};
std::vector<Button> buttons_main_window;
std::vector<Button> buttons_ip_window;
class InterfaceElement {
private:
	Vector2f bPosition;
	IntRect bSprite;
public:
	Sprite sprite;
	InterfaceElement(Texture& texture, Vector2f bPosition, IntRect bSprite) {
		sprite.setTexture(texture);
		this->bPosition = bPosition;
		this->bSprite = bSprite;
		sprite.setTextureRect(bSprite);
		sprite.setPosition(bPosition);
	}
};
void setFigures(Board* board) {
	int x, y;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece* piece = board->square[i][j];
			TypePiece n = piece->GetName();
			Colour color = piece->GetColour();
			if (n != EMPTY) {
				x = n - 1;
				color == WHITE ? y = 0: y = 1;
				piece->SetTextureFigures(figure_texture);
				piece->setVisualFigures(Vector2f(board_offset_x + square_size * j, board_offset_y - 2 + square_size * i), IntRect(square_size * x, square_size * y, square_size, square_size));
			}
		}
	}
}
void setSquaresPositions(Board* board) {
	int k = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece* piece = board->square[i][j];
			k = (k + 1) % 2;
			if (k == 1) {
				piece->SetTextureSquares(black_square);
			}
			else {
				piece->SetTextureSquares(white_square);
			}
			piece->setVisualSquares(Vector2f(board_offset_x + square_size * j, board_offset_y + square_size * i), IntRect(50, 50, square_size, square_size));
		}
		k = (k + 1) % 2;
	}

}

void colorSquare(Piece* piece, int x, int y, ColorOfSquare color) {
	switch (color) {
	case RED:
		(y + x) % 2 == 0 ? piece->square_sprite.setTexture(red_black_square) : piece->square_sprite.setTexture(red_white_square);
		break;
	case GREEN:
		(y + x) % 2 == 0 ? piece->square_sprite.setTexture(green_black_square) : piece->square_sprite.setTexture(green_white_square);
		break;
	case YELLOW:
		(y + x) % 2 == 0 ? piece->square_sprite.setTexture(yellow_black_square) : piece->square_sprite.setTexture(yellow_white_square);
		break;
	case NONE_COLOR:
		(y + x) % 2 == 0 ? piece->square_sprite.setTexture(black_square) : piece->square_sprite.setTexture(white_square);
		break;
	}
}

void CreateIpWindow() {
	RenderWindow ip_window(VideoMode(200, 100), "Question", Style::Default);
	Sprite background_sprite;
	background_sprite.setTexture(aside_texture);
	background_sprite.setTextureRect(IntRect(0, 0, 200, 100));
	background_sprite.setPosition(0, 0);
	header.setFont(font);
	header.setString("Enter your ip:");
	header.setCharacterSize(20);
	header.setFillColor(Color::Black);
	header.setPosition(15, 10);
	text.setFont(font);
	if (IP != "") {
		text.setString(IP);
	}
	text.setCharacterSize(20);
	text.setFillColor(Color::Blue);
	text.setPosition(15, 37);

	Button ip_ok_button(ip_ok_button_texture, Vector2f(119, 70), IntRect(0, 0, 69, 23));
	ip_ok_button.name = "close_ok";
	buttons_ip_window.push_back(ip_ok_button);

	int ip_size = IP.size();
	while (ip_window.isOpen()) {
		Event event1;
		while (ip_window.pollEvent(event1)) {
			if (event1.type == Event::Closed) {
				ip_window.close();
			}
			else if (event1.type == sf::Event::KeyPressed) {
				if (event1.key.code >= 26 && event1.key.code <= 35 || event1.key.code == 50 || event1.key.code == 59) {
					if (event1.key.code == 50 && ip_size < 15) {
						text.setString(t + ".");
						ip_size++;
					}
					else if (event1.key.code == 59 && ip_size > 0) {
						text.setString(t.substr(0, ip_size - 1));
						ip_size--;
					}
					else if (ip_size < 15 && event1.key.code != 59) {
						text.setString(t + to_string(event1.key.code - 26));
						ip_size++;
					}
				}
				t = text.getString();
			}
			else if (event1.type == Event::MouseButtonPressed) {
				if (event1.mouseButton.button == Mouse::Left) {
					int cursor_x = Mouse::getPosition(ip_window).x;
					int cursor_y = Mouse::getPosition(ip_window).y;
					for (int i = 0; i < buttons_ip_window.size(); ++i) {
						if (cursor_x > buttons_ip_window[i].bPosition.x && cursor_x < buttons_ip_window[i].bPosition.x + buttons_ip_window[i].bSprite.width &&
							cursor_y > buttons_ip_window[i].bPosition.y && cursor_y < buttons_ip_window[i].bPosition.y + buttons_ip_window[i].bSprite.height) {
							if (buttons_ip_window[i].name == "close_ok") {
								IP = t;
								ip_window.close();
							}
						}
					}
				}
			}
		}
		ip_window.clear();
		ip_window.draw(background_sprite);
		ip_window.draw(header);
		ip_window.draw(text);
		for (int i = 0; i < buttons_ip_window.size(); ++i) {
			ip_window.draw(buttons_ip_window[i].sprite);
		}
		ip_window.display();
	}
}

int main() {
	loadTexures();
	Board* board = CreateBoard();
	
	IsChoosingMove IS_CHOOSING_MOVE = NOT_CHOOSING_MOVE;
	std::vector<std::pair<int, int>> temp_pieceGetPossibleMoves;
	Piece* piece_wants_to_move = nullptr;

	//count figures
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece* piece = board->square[i][j];
			if (piece->GetName() != EMPTY) {
				board->figures_count++;
			}
		}
	}
	RenderWindow window(VideoMode(655, 488), "Chess");

	InterfaceElement aside(aside_texture, Vector2f(0, 0), IntRect(0, 0, 167, 488));
	InterfaceElement main_background(main_background_texture, Vector2f(167, 0), IntRect(0, 0, 488, 488));
	InterfaceElement numbers(numbers_texture, Vector2f(167, 0), IntRect(0, 0, 20, 488));
	InterfaceElement letters(letters_texture, Vector2f(167, 468), IntRect(0, 0, 488, 20));
	Button button1(first_button, Vector2f(10, 200), IntRect(0, 0, 146, 36));
	Button button2(second_button, Vector2f(26, 250), IntRect(0, 0, 110, 36));
	Button button3(third_button, Vector2f(40, 438), IntRect(0, 0, 88, 30));
	button1.name = "create_server";
	button2.name = "play_again";
	button3.name = "enter_ip";
	buttons_main_window.push_back(button1);
	buttons_main_window.push_back(button2);
	buttons_main_window.push_back(button3);

	setFigures(board);
	setSquaresPositions(board);

	//for mouse_move
	int mouse_x = 0;
	int mouse_y = 0;
	int temp_mouse_x = 0;
	int temp_mouse_y = 0;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();

			else if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					int cursor_x = Mouse::getPosition(window).x;
					int cursor_y = Mouse::getPosition(window).y;

					//find buttons
					for (int i = 0; i < buttons_main_window.size(); ++i) {
						if (cursor_x > buttons_main_window[i].bPosition.x && cursor_x < buttons_main_window[i].bPosition.x + buttons_main_window[i].bSprite.width &&
							cursor_y > buttons_main_window[i].bPosition.y && cursor_y < buttons_main_window[i].bPosition.y + buttons_main_window[i].bSprite.height) {
							if (buttons_main_window[i].name == "play_again") {
								board->SetBoard();
								setFigures(board);
								setSquaresPositions(board);
								cout << "Play again\n";
								piece_wants_to_move = nullptr;
								IS_CHOOSING_MOVE = NOT_CHOOSING_MOVE;
								temp_pieceGetPossibleMoves.clear();
							}
							else if (buttons_main_window[i].name == "create_server") {
								cout << "Create server\n";
							}
							else if (buttons_main_window[i].name == "enter_ip") {
								CreateIpWindow();
								cout << "Enter ip\n";
							}
						}						
					}

					//find squares
					int cursor_x_for_board = (cursor_x - board_offset_x) / square_size;
					int cursor_y_for_board = (cursor_y - board_offset_y) / square_size;
					Piece* piece = board->square[cursor_y_for_board][cursor_x_for_board];

					pair<int, int> click_square = make_pair(cursor_y_for_board, cursor_x_for_board);
					auto is_found = find(temp_pieceGetPossibleMoves.begin(), temp_pieceGetPossibleMoves.end(), click_square);

					if (is_found != temp_pieceGetPossibleMoves.end()) {
						//move figure
						board->move(cursor_x_for_board, cursor_y_for_board, piece->GetColour(), piece_wants_to_move);
						setFigures(board);
						setSquaresPositions(board);

						piece_wants_to_move = nullptr;
						IS_CHOOSING_MOVE = NOT_CHOOSING_MOVE;
						temp_pieceGetPossibleMoves.clear();
					}
					else if (piece->GetName() != EMPTY ) {

						//squares backlight red with onclick
						piece_wants_to_move = piece;
						if (cursor_x_for_board <= 7 && cursor_x_for_board >= 0 &&
							cursor_y_for_board <= 7 && cursor_y_for_board >= 0) {
							colorSquare(piece, cursor_x_for_board, cursor_y_for_board, RED);
							
							std::vector<std::pair<int, int>> pieceGetPossibleMoves = *MakePossibleMoves(piece);
							if (IS_CHOOSING_MOVE == CHOOSING_MOVE) {
								//закрашиваем возможные ходы предыдущего выбора фигуры
								for (int i = 0; i < temp_pieceGetPossibleMoves.size(); ++i) {
									int possible_move_x = temp_pieceGetPossibleMoves[i].first;
									int possible_move_y = temp_pieceGetPossibleMoves[i].second;

									Piece* piece = board->square[possible_move_x][possible_move_y];
									colorSquare(piece, possible_move_x, possible_move_y, NONE_COLOR);
								}
							}
							else {
								for (int i = 0; i < pieceGetPossibleMoves.size(); ++i) {
									int possible_move_x = pieceGetPossibleMoves[i].first;
									int possible_move_y = pieceGetPossibleMoves[i].second;
									cout << "(" << possible_move_x << "," << possible_move_y << ") ";
									Piece* piece = board->square[possible_move_x][possible_move_y];
									colorSquare(piece, possible_move_x, possible_move_y, GREEN);
								}
								cout << endl;
								
								temp_pieceGetPossibleMoves = pieceGetPossibleMoves;
								IS_CHOOSING_MOVE = CHOOSING_MOVE;
							}
						}
					}
				}
			}
			else if (event.type == Event::MouseMoved) {
				mouse_x = (event.mouseMove.x - board_offset_x) / square_size;
				mouse_y = (event.mouseMove.y - board_offset_y) / square_size;
				pair<int, int> move_square_now = make_pair(mouse_y, mouse_x);
				pair<int, int> move_square_temp = make_pair(temp_mouse_y, temp_mouse_x);

				auto is_found_now = find(temp_pieceGetPossibleMoves.begin(), temp_pieceGetPossibleMoves.end(), move_square_now);
				auto is_found_temp= find(temp_pieceGetPossibleMoves.begin(), temp_pieceGetPossibleMoves.end(), move_square_temp);

				Piece* piece = board->square[mouse_y][mouse_x];
				Piece* piece_temp = board->square[temp_mouse_y][temp_mouse_x];

				if ((temp_mouse_x != mouse_x || temp_mouse_y != mouse_y) &&
					mouse_x <= 7 && mouse_x >= 0 && mouse_y <= 7 && mouse_y >= 0 &&
					event.mouseMove.x - board_offset_x > 0 && event.mouseMove.y - board_offset_y > 0) {

					//squares backlight yellow with hover
					if (is_found_now == temp_pieceGetPossibleMoves.end()) {
						colorSquare(piece, mouse_x, mouse_y, YELLOW);
						
					}
					if (is_found_temp == temp_pieceGetPossibleMoves.end()) {
						colorSquare(piece_temp, temp_mouse_x, temp_mouse_y, NONE_COLOR);
						
					}
					temp_mouse_x = mouse_x;
					temp_mouse_y = mouse_y;
				}
				//backlight black/white with moving mous out of board
				if (mouse_x > 7 || event.mouseMove.x - board_offset_x < 0 || mouse_y > 7 || event.mouseMove.y - board_offset_y < 0) {
					colorSquare(piece_temp, temp_mouse_x, temp_mouse_y, NONE_COLOR);
					
				}
				
			}

		}

		window.clear();

		window.draw(aside.sprite);
		window.draw(main_background.sprite);
		window.draw(numbers.sprite);
		window.draw(letters.sprite);

		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				Piece* piece = board->square[i][j];
				window.draw(piece->square_sprite);
				window.draw(piece->figure_sprite);
			}
		}
		for (int i = 0; i < buttons_main_window.size(); ++i) {
			window.draw(buttons_main_window[i].sprite);
		}

		window.display();

	}

	return 0;
}
