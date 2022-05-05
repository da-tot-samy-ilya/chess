#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"


const int board_offset_x = 187;
const int board_offset_y = 20;

class Button {
public:
	Vector2f bPosition;
	IntRect bSprite;
	Sprite sprite;
	bool hasOnClick = false;

	std::string buttonName = "";
	Button(Texture& texture, Vector2f bPosition, IntRect bSprite) {
		sprite.setTexture(texture);
		this->bPosition = bPosition;
		this->bSprite = bSprite;
		sprite.setTextureRect(bSprite);
		sprite.setPosition(bPosition);
	}
	std::function<void()> onClick = []() {

	};
};
class InterfaceElement {
public:
	Vector2f bPosition;
	IntRect bSprite;
	Sprite sprite;

	InterfaceElement(Texture& texture, Vector2f bPosition, IntRect bSprite) {
		sprite.setTexture(texture);
		this->bPosition = bPosition;
		this->bSprite = bSprite;
		sprite.setTextureRect(bSprite);
		sprite.setPosition(bPosition);
	}
};

std::vector<Button> buttons_main_window;
std::vector<Button> buttons_ip_window;
enum IsChoosingMove{CHOOSING_MOVE, NOT_CHOOSING_MOVE};
int k = 0;
const int square_size = 56;

std::string IP = "";
std::string  t = "";

void setFigures(Board* board) {
	int x, y;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece* piece = board->square[i][j];
			TypePiece n = piece->GetName();
			Colour color = piece->GetColour();
			if (n != EMPTY) {
				x = n - 1;
				if (color == BLACK) {
					y = 0;
				}
				else {
					y = 1;
				}
				piece->setVisualFigures(Vector2f(board_offset_x + square_size * j, board_offset_y - 2 + square_size * i), IntRect(square_size * x, square_size * y, square_size, square_size));
			}
		}
	}
}

void setSquaresPositions(Board* board) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece* piece = board->square[i][j];
			piece->setVisualSquares(Vector2f(board_offset_x + square_size * j, board_offset_y + square_size * i), IntRect(50, 50, square_size, square_size));
		}
	}

}
//использовать class InterfaceElement
void CreateIpWindow() {

	RenderWindow window1(VideoMode(200, 100), "Question", Style::Default);

	//background
	Texture aside_texture;
	aside_texture.loadFromFile("images/aside_background.png");
	Sprite background_sprite;
	background_sprite.setTexture(aside_texture);
	background_sprite.setTextureRect(IntRect(0, 0, 200, 100));
	background_sprite.setPosition(0, 0);

	Font font;
	font.loadFromFile("images/Roboto-Bold.ttf");

	//header
	Text header;
	header.setFont(font);
	header.setString("Enter your ip:");
	header.setCharacterSize(20);
	header.setFillColor(Color::Black);
	header.setPosition(15, 10);


	//enetring ip
	Text text;
	text.setFont(font);
	if (IP != "") {
		text.setString(IP);
	}

	text.setCharacterSize(20);
	text.setFillColor(Color::Blue);
	text.setPosition(15, 37);

	Texture ip_ok_button_texture;
	ip_ok_button_texture.loadFromFile("images/enter_ip_ok.png");

	Button ip_ok_button(ip_ok_button_texture, Vector2f(119, 70), IntRect(0, 0, 69, 23));

	ip_ok_button.hasOnClick = true;
	ip_ok_button.buttonName = "close_ok";
	buttons_ip_window.push_back(ip_ok_button);

	int count = IP.size();

	while (window1.isOpen()) {
		Event event1;
		while (window1.pollEvent(event1)) {
			if (event1.type == Event::Closed) {
				window1.close();
			}

			else if (event1.type == sf::Event::KeyPressed) {

				if (event1.key.code >= 26 && event1.key.code <= 35 || event1.key.code == 50 || event1.key.code == 59) {

					if (event1.key.code == 50 && count < 15) {
						text.setString(t + ".");
						count++;
					}
					else if (event1.key.code == 59 && count > 0) {
						text.setString(t.substr(0, count - 1));
						count--;
					}
					else if (count < 15 && event1.key.code != 59) {
						text.setString(t + std::to_string(event1.key.code - 26));
						count++;
					}

				}
				t = text.getString();
			}
			else if (event1.type == Event::MouseButtonPressed) {
				if (event1.mouseButton.button == Mouse::Left) {
					int cursor_x = Mouse::getPosition(window1).x;
					int cursor_y = Mouse::getPosition(window1).y;

					//find buttons
					for (int i = 0; i < buttons_ip_window.size(); ++i) {
						if (buttons_ip_window[i].hasOnClick) {
							if (cursor_x > buttons_ip_window[i].bPosition.x && cursor_x < buttons_ip_window[i].bPosition.x + buttons_ip_window[i].bSprite.width &&
								cursor_y > buttons_ip_window[i].bPosition.y && cursor_y < buttons_ip_window[i].bPosition.y + buttons_ip_window[i].bSprite.height) {
								if (buttons_ip_window[i].buttonName == "close_ok") {
									IP = t;
									window1.close();
								}
							}

						}
					}
				}
			}
			/*std::cout << count << "\n";*/

		}
		window1.clear();
		window1.draw(background_sprite);

		window1.draw(header);
		window1.draw(text);
		for (int i = 0; i < buttons_ip_window.size(); ++i) {
			window1.draw(buttons_ip_window[i].sprite);
		}


		window1.display();


	}
}

int main() {
	Board* board = CreateBoard();
	//Global statuses
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

	RenderWindow window(VideoMode(655, 488), "Chess GAYme");

	//Interface elements
	Texture aside_texture, main_background_texture, numbers_texture, letters_texture;
	aside_texture.loadFromFile("images/aside_background.png");
	main_background_texture.loadFromFile("images/grey_texture.png");
	numbers_texture.loadFromFile("images/numbers.png");
	letters_texture.loadFromFile("images/letters.png");
	InterfaceElement aside(aside_texture, Vector2f(0, 0), IntRect(0, 0, 167, 488));
	InterfaceElement main_background(main_background_texture, Vector2f(167, 0), IntRect(0, 0, 488, 488));
	InterfaceElement numbers(numbers_texture, Vector2f(167, 0), IntRect(0, 0, 20, 488));
	InterfaceElement letters(letters_texture, Vector2f(167, 468), IntRect(0, 0, 488, 20));

	//Buttons
	Texture first_button, second_button, third_button;
	first_button.loadFromFile("images/button1.png");
	second_button.loadFromFile("images/button2.png");
	third_button.loadFromFile("images/button3.png");

	Button button1(first_button, Vector2f(10, 200), IntRect(0, 0, 146, 36));
	button1.onClick = []() {
		std::cout << "Create server\n";
	};
	button1.hasOnClick = true;
	buttons_main_window.push_back(button1);

	Button button2(second_button, Vector2f(26, 250), IntRect(0, 0, 110, 36));
	button2.onClick = []() {
		std::cout << "Play again\n";
		
	};
	button2.hasOnClick = true;
	buttons_main_window.push_back(button2);

	Button button3(third_button, Vector2f(40, 438), IntRect(0, 0, 88, 30));
	button3.onClick = []() {
		CreateIpWindow();
	};
	button3.hasOnClick = true;
	buttons_main_window.push_back(button3);

	//Figures
	Texture figure_texture;
	figure_texture.loadFromFile("images/figures.png");
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece* piece = board->square[i][j];
			if (piece->GetName() != EMPTY) {
				piece->SetTextureFigures(figure_texture);
			}
		}
	}
	setFigures(board);
	//Squares
	Texture black_square, white_square,
		red_black_square, red_white_square,
		yellow_black_square, yellow_white_square,
		green_black_square, green_white_square;

	black_square.loadFromFile("images/black_texture.png");
	white_square.loadFromFile("images/white_texture.png");
	red_black_square.loadFromFile("images/red_black_texture.png");
	red_white_square.loadFromFile("images/red_white_texture.png");
	yellow_black_square.loadFromFile("images/yellow_black_texture.png");
	yellow_white_square.loadFromFile("images/yellow_white_texture.png");
	green_black_square.loadFromFile("images/green_black_texture.png");
	green_white_square.loadFromFile("images/green_white_texture.png");

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

		}
		k = (k + 1) % 2;
	}
	setSquaresPositions(board);

	//for mouse_move
	int mouse_x = 0;
	int mouse_y = 0;
	int temp_mouse_x = 0;
	int temp_mouse_y = 0;
	while (window.isOpen()) {
		bool check_figure = false;
		int temp_x = 0;
		int temp_y = 0;
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					/*for (int i = 0; i < 8; ++i) {
						for (int j = 0; j < 8; ++j) {
							cout << board->square[i][j]->GetName() << " ";
						}
						cout << "\n";
					}
					cout << "\n";*/
					int cursor_x = Mouse::getPosition(window).x;
					int cursor_y = Mouse::getPosition(window).y;

					//find buttons
					for (int i = 0; i < buttons_main_window.size(); ++i) {
						if (buttons_main_window[i].hasOnClick) {
							if (cursor_x > buttons_main_window[i].bPosition.x && cursor_x < buttons_main_window[i].bPosition.x + buttons_main_window[i].bSprite.width &&
								cursor_y > buttons_main_window[i].bPosition.y && cursor_y < buttons_main_window[i].bPosition.y + buttons_main_window[i].bSprite.height) {
								buttons_main_window[i].onClick();
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

						for (int i = 0; i < 8; ++i) {
							for (int j = 0; j < 8; ++j) {
								cout << board->square[i][j]->GetColour() << " ";
							}
							cout << "\n";
						}
						cout << "\n";
						
						pair<int, int> old_square = make_pair(piece_wants_to_move->GetHor(), piece_wants_to_move->GetVert());
						temp_pieceGetPossibleMoves.push_back(old_square);
						for (int i = 0; i < temp_pieceGetPossibleMoves.size(); ++i) {
							int x = temp_pieceGetPossibleMoves[i].first;
							int y = temp_pieceGetPossibleMoves[i].second;
							Piece* piece = board->square[x][y];
							if ((y + x) % 2 == 0) {
								piece->square_sprite.setTexture(black_square);
							}
							else {
								piece->square_sprite.setTexture(white_square);
							}
							
						}
						
						piece_wants_to_move = nullptr;
						IS_CHOOSING_MOVE = NOT_CHOOSING_MOVE;
						temp_pieceGetPossibleMoves.clear();
					}
					else {
						//squares backlight red with onclick
						piece_wants_to_move = piece;
						if (cursor_x_for_board <= 7 && cursor_x_for_board >= 0 &&
							cursor_y_for_board <= 7 && cursor_y_for_board >= 0) {
							if ((cursor_y_for_board + cursor_x_for_board) % 2 == 0) {
								piece->square_sprite.setTexture(red_black_square);
							}
							else {
								piece->square_sprite.setTexture(red_white_square);
							}

							std::vector<std::pair<int, int>> pieceGetPossibleMoves = *MakePossibleMoves(piece);
							if (IS_CHOOSING_MOVE == CHOOSING_MOVE) {
								for (int i = 0; i < temp_pieceGetPossibleMoves.size(); ++i) {
									int possible_move_x = temp_pieceGetPossibleMoves[i].first;
									int possible_move_y = temp_pieceGetPossibleMoves[i].second;
									Piece* piece = board->square[possible_move_x][possible_move_y];
									if ((possible_move_x + possible_move_y) % 2 == 0) {
										piece->square_sprite.setTexture(black_square);
									}
									else {
										piece->square_sprite.setTexture(white_square);
									}
								}
							}
							
							else {
								for (int i = 0; i < pieceGetPossibleMoves.size(); ++i) {
									
									int possible_move_x = pieceGetPossibleMoves[i].first;
									int possible_move_y = pieceGetPossibleMoves[i].second;

									cout << "(" << possible_move_x << "," << possible_move_y << ") ";
									Piece* piece = board->square[possible_move_x][possible_move_y];

									
									if ((possible_move_x + possible_move_y) % 2 == 0) {
										piece->square_sprite.setTexture(green_black_square);
									}
									else {
										piece->square_sprite.setTexture(green_white_square);
									}
								}
								cout << "\n";
								
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
						if ((mouse_y + mouse_x) % 2 == 0) {
							piece->square_sprite.setTexture(yellow_black_square);
						}
						else {
							piece->square_sprite.setTexture(yellow_white_square);
						}
					}
					if (is_found_temp == temp_pieceGetPossibleMoves.end()) {

						if ((temp_mouse_y + temp_mouse_x) % 2 == 0) {
							piece_temp->square_sprite.setTexture(black_square);
						}
						else {
							piece_temp->square_sprite.setTexture(white_square);
						}
					}
					temp_mouse_x = mouse_x;
					temp_mouse_y = mouse_y;
				}
				//backlight black/white with moving mous out of board
				if (mouse_x > 7 || event.mouseMove.x - board_offset_x < 0 || mouse_y > 7 || event.mouseMove.y - board_offset_y < 0) {
					if ((temp_mouse_y + temp_mouse_x) % 2 == 0) {
						piece_temp->square_sprite.setTexture(black_square);
					}
					else {
						piece_temp->square_sprite.setTexture(white_square);
					}
				}
				//std::cout << mouse_x << " " << mouse_y <<  " "<< event.mouseMove.x - board_offset_x << " " << event.mouseMove.y - board_offset_y <<"\n";
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
