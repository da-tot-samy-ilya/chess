#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>
#include <string>

#include "ChessFigure.h"

using namespace sf;


const int figures_count = 32;

const int board_offset_x = 187;
const int board_offset_y = 20;

Sprite figures[figures_count];
Sprite squares[64];

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
		
	};;
};

std::vector<Button> buttons_main_window;
std::vector<Button> buttons_ip_window;

int k = 0;
int size = 56;

std::string IP = "";
std::string  t = "";

//int board[8][8] = {
//	{5,4,3,2,1,3,4,5},
//	{6,6,6,6,6,6,6,6},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{-6,-6,-6,-6,-6,-6,-6,-6},
//	{-5,-4,-3,-2,-1,-3,-4,-5},
//};

void setFigures() {
	int n;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			n = board->square[i][j].type_piece;

			if (n != 0) {
				int x = abs(n) - 1;
				int y;
				if (n < 0) {
					y = 0;
				}
				else {
					y = 1;
				}
				figures[k].setTextureRect(IntRect(size * x, size * y, size, size));
				figures[k].setPosition(board_offset_x + size * j, board_offset_y - 2 + size * i);
				k++;
			}
		}
	}
}
void setSquaresPositions() {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			k = (k + 1) % 2;
			squares[i * 8 + j].setTextureRect(IntRect(50, 50, size, size));
			squares[i * 8 + j].setPosition(board_offset_x + size * j, board_offset_y + size * i);

		}
		k = (k + 1) % 2;
	}

}

void setInterface() {
	//Aside
	Texture aside_texture;
	aside_texture.loadFromFile("images/aside_background.png");
	Sprite aside;
	aside.setTexture(aside_texture);
	aside.setTextureRect(IntRect(0, 0, 167, 488));
	aside.setPosition(0, 0);

	//Main_background
	Texture main_background_texture;
	main_background_texture.loadFromFile("images/grey_texture.png");
	Sprite main_background;
	main_background.setTexture(main_background_texture);
	main_background.setTextureRect(IntRect(0, 0, 488, 488));
	main_background.setPosition(167, 0);

	//Numbers
	Texture numbers_texture;
	numbers_texture.loadFromFile("images/numbers.png");
	Sprite numbers;
	numbers.setTexture(numbers_texture);
	numbers.setTextureRect(IntRect(0, 0, 20, 488));
	numbers.setPosition(167, 0);

	//Letters
	Texture letters_texture;
	letters_texture.loadFromFile("images/letters.png");
	Sprite letters;
	letters.setTexture(letters_texture);
	letters.setTextureRect(IntRect(0, 0, 488, 20));
	letters.setPosition(167, 468);

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
	//Create window for enter ip
	button3.onClick = []() {
		CreateIpWindow();
	};
	button3.hasOnClick = true;
	buttons_main_window.push_back(button3);
}

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
	
	
	RenderWindow window(VideoMode(655, 488), "Chess");
	
	//Background, buttons
	setInterface();

	//Figures
	Texture figure_texture;
	figure_texture.loadFromFile("images/figures.png");

	for (int i = 0; i < figures_count; ++i) {
		figures[i].setTexture(figure_texture);
	}
	setFigures();

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
			k = (k + 1) % 2;
			if (k == 1) {
				squares[i * 8 + j].setTexture(black_square);
			}
			else {
				squares[i * 8 + j].setTexture(white_square);
			}

		}
		k = (k + 1) % 2;
	}
	setSquaresPositions();
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
					int cursor_x_for_board = (cursor_x - board_offset_x) / size;
					int cursor_y_for_board = (cursor_y - board_offset_y) / size;
					if (cursor_x_for_board <= 7 && cursor_x_for_board >= 0 &&
						cursor_y_for_board <= 7 && cursor_y_for_board >= 0) {
						if ((cursor_y_for_board + cursor_x_for_board) % 2 == 0) {
							squares[cursor_y_for_board * 8 + cursor_x_for_board].setTexture(red_black_square);
						}
						else {
							squares[cursor_y_for_board * 8 + cursor_x_for_board].setTexture(red_white_square);
						}
						
					}
				}
			}
			else if (event.type == Event::MouseMoved) {
				mouse_x = (event.mouseMove.x - board_offset_x) / size;
				mouse_y = (event.mouseMove.y - board_offset_y) / size;
				
				if ((temp_mouse_x != mouse_x || temp_mouse_y != mouse_y) &&
					mouse_x <= 7 && mouse_x >= 0 && mouse_y <= 7 && mouse_y >= 0 &&
					event.mouseMove.x - board_offset_x > 0 && event.mouseMove.y - board_offset_y > 0) {
					if ((temp_mouse_y + temp_mouse_x) % 2 == 0) {
						squares[temp_mouse_y * 8 + temp_mouse_x].setTexture(black_square);
					}
					else {
						squares[temp_mouse_y * 8 + temp_mouse_x].setTexture(white_square);
					}
					if ((mouse_y + mouse_x) % 2 == 0) {
						squares[mouse_y * 8 + mouse_x].setTexture(yellow_black_square);
					}
					else {
						squares[mouse_y * 8 + mouse_x].setTexture(yellow_white_square);
					}
					
					temp_mouse_x = mouse_x;
					temp_mouse_y = mouse_y;
				}
				if (mouse_x > 7 || event.mouseMove.x - board_offset_x < 0 || mouse_y > 7 || event.mouseMove.y - board_offset_y < 0) {
					if ((temp_mouse_y + temp_mouse_x) % 2 == 0) {
						squares[temp_mouse_y * 8 + temp_mouse_x].setTexture(black_square);
					}
					else {
						squares[temp_mouse_y * 8 + temp_mouse_x].setTexture(white_square);
					}
				}
				//std::cout << mouse_x << " " << mouse_y <<  " "<< event.mouseMove.x - board_offset_x << " " << event.mouseMove.y - board_offset_y <<"\n";
			}
			
		}

		window.clear();
		
		window.draw(aside);
		window.draw(main_background);
		window.draw(numbers);
		window.draw(letters);

		for (int i = 0; i < 64; ++i) {
			window.draw(squares[i]);
		}
		for (int i = 0; i < buttons_main_window.size(); ++i) {
			window.draw(buttons_main_window[i].sprite);
		}
		for (int i = 0; i < figures_count; ++i) {
			window.draw(figures[i]);
		}

		window.display();

	}

	return 0;
}