#pragma once
#include <iostream>
#include <functional>
#include <string>
#include "CheckingForMove.h"
using namespace sf;
using namespace std;

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

int k = 0;
const int square_size = 56;

std::string IP = "";
std::string  t = "";

void setFigures(Board* board) {
	int n, x, y;
	char color;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece* piece = board->square[i][j];
			n = piece->GetName();
			color = piece->GetColour();
			if (n != EMPTY) {
				x = n - 1;
				if (color == 'w') {
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
			k = (k + 1) % 2;
			piece->setVisualSquares(Vector2f(board_offset_x + square_size * j, board_offset_y + square_size * i), IntRect(50, 50, square_size, square_size));
			/*squares[i * 8 + j].setTextureRect(IntRect(50, 50, size, size));
			squares[i * 8 + j].setPosition(board_offset_x + size * j, board_offset_y + size * i);*/
		}
		k = (k + 1) % 2;
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
		std::cout << IP << std::endl;
		text.setString(IP);
	}
	/*else {
		std::cout << "IP is empty\n" << std::endl;
	}*/

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

				if (event1.key.code >= '0' && event1.key.code <= '9' || event1.key.code == 50 || event1.key.code == 59) {

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
				//std::cout << count << " " << t << "\n";
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
									/*std::cout << "ip was entered: " << t << "\n";*/
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
	board->SetBoard();

	//count figures
	for (int i = 0; i < 64; ++i) {
		for (int j = 0; j < 64; ++j) {
			Piece* piece = board->square[i][j];
			if (piece->GetName() != EMPTY) {
				board->figures_count++;
			}
		}
	}

	RenderWindow window(VideoMode(655, 488), "ABOBA");

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
	/*for (int i = 0; i < board->figures_count; ++i) {

		figures[i].setTexture(figure_texture);
	}*/


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
				/*squares[i * 8 + j].setTexture(black_square);*/
			}
			else {
				piece->SetTextureSquares(white_square);
				//squares[i * 8 + j].setTexture(white_square);
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

					//squares backlight red with onclick
					if (cursor_x_for_board <= 7 && cursor_x_for_board >= 0 &&
						cursor_y_for_board <= 7 && cursor_y_for_board >= 0) {
						if ((cursor_y_for_board + cursor_x_for_board) % 2 == 0) {
							piece->square_sprite.setTexture(red_black_square);
							//use new methods later
							//piece->SetIsChosenForMove
							////squares backlight greeen with possible moves
							//for (int i = 0; i < 8; ++i) {
							//	for (int j = 0; j < 8; ++j) {
							//		Piece* to_move_piece = board->square[i][j];
							//		char to_move_color = to_move_piece->GetColour();
							//		if (piece->move(j, i,to_move_color)) {
							//			if ((i + j) % 2 == 0) {
							//				piece->square_sprite.setTexture(green_black_square);
							//			}
							//			else {
							//				piece->square_sprite.setTexture(green_white_square);
							//			}
							//			piece->SetTextureFigures(figure_texture);
							//		}
							//	}
							//}
							/*squares[cursor_y_for_board * 8 + cursor_x_for_board].setTexture(red_black_square);*/
						}
						else {
							piece->square_sprite.setTexture(red_white_square);
						}

					}
				}
			}
			else if (event.type == Event::MouseMoved) {
				mouse_x = (event.mouseMove.x - board_offset_x) / square_size;
				mouse_y = (event.mouseMove.y - board_offset_y) / square_size;
				Piece* piece = board->square[mouse_y][mouse_x];
				Piece* piece_temp = board->square[temp_mouse_y][temp_mouse_x];

				if ((temp_mouse_x != mouse_x || temp_mouse_y != mouse_y) &&
					mouse_x <= 7 && mouse_x >= 0 && mouse_y <= 7 && mouse_y >= 0 &&
					event.mouseMove.x - board_offset_x > 0 && event.mouseMove.y - board_offset_y > 0) {

					//squares backlight yellow with hover
					if ((temp_mouse_y + temp_mouse_x) % 2 == 0) {
						piece_temp->square_sprite.setTexture(black_square);
					}
					else {
						piece_temp->square_sprite.setTexture(white_square);
					}
					if ((mouse_y + mouse_x) % 2 == 0) {
						piece->square_sprite.setTexture(yellow_black_square);
					}
					else {
						piece->square_sprite.setTexture(yellow_white_square);
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
				window.draw(piece->figure_sprite);
				window.draw(piece->square_sprite);
			}
		}
		for (int i = 0; i < buttons_main_window.size(); ++i) {
			window.draw(buttons_main_window[i].sprite);
		}

		window.display();

	}

	return 0;
}