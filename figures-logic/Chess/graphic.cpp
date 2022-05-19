#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Board.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "LocalServer.h"
using namespace std;

//Server
Server server("127.0.0.1", 1111);
Client client("127.0.0.1", 1111);
SOCKET cl;
bool isServer = false;
bool waitAnswer = false;
bool serverGame = false;
void CreateServer(string ip, int port) {
	server = Server(ip.c_str(), port);
	isServer = true;
	server.start();
	cl = server.getNewConnection();
}
void CreateServer(int port) {
	server = Server(server.getMyIp().c_str(), port);
	isServer = true;
	server.start();
	cl = server.getNewConnection();
}
void CreateClient(string ip, int port) {
	client = Client(ip.c_str(), port);
	client.Connnect();
}
void Send(char lastPos, char newPos) {
	if (isServer) server.sendMsg(string({ (char)lastPos, (char)newPos, '\0' }).c_str(), cl);
	else client.sendMsg(string({ (char)lastPos, (char)newPos, '\0' }).c_str());
}
string Get() {
	string msg;
	int lenMsg;
	if (isServer) msg = server.getMsg(lenMsg, cl);
	else msg = client.getMsg(lenMsg);
	return string(msg);
}
//Server end

Texture aside_texture, main_background_texture, numbers_texture, letters_texture;
Texture first_button, second_button, third_button;
Texture black_square, white_square, red_black_square, red_white_square, yellow_black_square, yellow_white_square, green_black_square, green_white_square;
Texture figure_texture;
Font font;
Text header;
Text result_header;
Text is_moving_now;
Text text;
Texture ok_button_texture;
Texture check_info_texture;
Texture is_moving_now_pic_black_texture, is_moving_now_pic_white_texture;
Texture cry_cat_texture, laughing_cat_texture, naughty_cat_texture;
void loadTexures() {
	is_moving_now_pic_black_texture.loadFromFile("images/is_mopving_now_pic_black.png");
	is_moving_now_pic_white_texture.loadFromFile("images/is_mopving_now_pic_white.png");
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
	ok_button_texture.loadFromFile("images/enter_ip_ok.png");
	cry_cat_texture.loadFromFile("images/cry_cat.png");
	laughing_cat_texture.loadFromFile("images/laughing_cat.png");
	naughty_cat_texture.loadFromFile("images/naughty_cat.png");
	check_info_texture.loadFromFile("images/check_info.png");
}

const int board_offset_x = 187;
const int board_offset_y = 20;
const int square_size = 56;
string IP = "";
string  t = "";
enum IsChoosingMove { CHOOSING_MOVE, NOT_CHOOSING_MOVE };
enum ColorOfSquare { RED, GREEN, YELLOW, NONE_COLOR };
enum GameResult { WIN, LOSE, DRAW };

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
std::vector<Button> buttons_result_window;
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
			TypePiece n = *(piece->GetName());
			Colour color = *(piece->GetColour());
			if (n != EMPTY) {
				x = n - 1;
				color == WHITE ? y = 0 : y = 1;
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

void CreateIpWindow(Colour* a) {
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

	Button ip_ok_button(ok_button_texture, Vector2f(119, 70), IntRect(0, 0, 69, 23));
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
								CreateClient(t, 1111);
								serverGame = true;
								waitAnswer = true;
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
void CreateChooseFigureWindow(int y, int x, Board* board) {
	Piece* chooseFigures[4];
	if (y == 0) {
		chooseFigures[0] = new Queen(BLACK, 0, 0, QUEEN, 0);
		chooseFigures[1] = new Rook(BLACK, 0, 0, ROOK, 0);
		chooseFigures[2] = new Knight(BLACK, 0, 0, KNIGHT, 0);
		chooseFigures[3] = new Bishop(BLACK, 0, 0, BISHOP, 0);
	}
	else if (y == 7) {
		chooseFigures[0] = new Queen(WHITE, 0, 0, QUEEN, 0);
		chooseFigures[1] = new Rook(WHITE, 0, 0, ROOK, 0);
		chooseFigures[2] = new Knight(WHITE, 0, 0, KNIGHT, 0);
		chooseFigures[3] = new Bishop(WHITE, 0, 0, BISHOP, 0);
	}
	Colour color = *(chooseFigures[0]->GetColour());
	for (int i = 0; i < 4; ++i) {
		int x, y;
		Piece* piece = chooseFigures[i];
		TypePiece n = *(piece->GetName());
		Colour color = *(piece->GetColour());
		x = n - 1;
		color == WHITE ? y = 0 : y = 1;
		piece->SetTextureFigures(figure_texture);
		piece->setVisualFigures(Vector2f(square_size * i, 0), IntRect(square_size * x, square_size * y, square_size, square_size));
	}

	RenderWindow choose_figure_window(VideoMode(230, 60), "Choose figure", Style::Default);
	Sprite background_sprite;
	background_sprite.setTexture(aside_texture);
	background_sprite.setTextureRect(IntRect(0, 0, 230, 60));
	background_sprite.setPosition(0, 0);

	while (choose_figure_window.isOpen()) {
		Event event;
		while (choose_figure_window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				choose_figure_window.close();
			}
			else if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							cout << *(board->square[i][j]->GetName()) << " ";
						}
						cout << "\n";
					}
					cout << "\n";
					int cursor_x = (Mouse::getPosition(choose_figure_window).x) / square_size;
					TypePiece type = *(chooseFigures[cursor_x]->GetName());
					switch (type) {
					case (QUEEN):
						board->square[y][x] = new Queen(color, x, y, type, 0);
						break;
					case(BISHOP):
						board->square[y][x] = new Bishop(color, x, y, type, 0);
						break;
					case(KNIGHT):
						board->square[y][x] = new Knight(color, x, y, type, 0);
						break;
					case(ROOK):
						board->square[y][x] = new Rook(color, x, y, type, 0);
						break;
					}
					choose_figure_window.close();
				}
			}
		}
		choose_figure_window.clear();
		choose_figure_window.draw(background_sprite);
		for (int i = 0; i < 4; ++i) {
			choose_figure_window.draw(chooseFigures[i]->figure_sprite);
		}
		choose_figure_window.display();
	}
}
void CreateResultWindow(InterfaceElement& check_info, GameResult result, Board* board, IsChoosingMove& IS_CHOOSING_MOVE, std::vector<std::pair<int, int>>& temp_pieceGetPossibleMoves, Piece* piece_wants_to_move, Colour& IS_NOW_PLAYING) {
	RenderWindow result_window(VideoMode(200, 100), "Result", Style::Default);
	Sprite background_sprite;
	background_sprite.setTexture(aside_texture);
	background_sprite.setTextureRect(IntRect(0, 0, 200, 100));
	background_sprite.setPosition(0, 0);

	Sprite cat;
	cat.setTexture(aside_texture);
	cat.setTextureRect(IntRect(0, 0, 56, 56));
	cat.setPosition(120, 11);

	//индикатор наличия шаха
	check_info.sprite.setTexture(check_info_texture);

	result_header.setFont(font);
	result_header.setCharacterSize(20);
	result_header.setPosition(15, 20);
	Button result_ok_button(ok_button_texture, Vector2f(65, 70), IntRect(0, 0, 69, 23));
	result_ok_button.name = "close_ok";
	buttons_result_window.push_back(result_ok_button);

	if (result == WIN) {
		result_header.setString("You win!");
		result_header.setFillColor(Color::Color(97, 206, 101));
		cat.setTexture(laughing_cat_texture);
	}
	else if (result == LOSE) {
		result_header.setString("You lose!");
		result_header.setFillColor(Color::Color(251, 94, 94));
		cat.setTexture(cry_cat_texture);
	}
	else {
		result_header.setString("Draw!");
		result_header.setFillColor(Color::Color(239, 210, 60));
		cat.setTexture(naughty_cat_texture);
	}
	while (result_window.isOpen()) {
		Event event;
		while (result_window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				result_window.close();
			}
			else if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					int cursor_x = Mouse::getPosition(result_window).x;
					int cursor_y = Mouse::getPosition(result_window).y;
					for (int i = 0; i < buttons_result_window.size(); ++i) {
						if (cursor_x > buttons_result_window[i].bPosition.x && cursor_x < buttons_result_window[i].bPosition.x + buttons_result_window[i].bSprite.width &&
							cursor_y > buttons_result_window[i].bPosition.y && cursor_y < buttons_result_window[i].bPosition.y + buttons_result_window[i].bSprite.height) {
							if (buttons_result_window[i].name == "close_ok") {
								board->SetBoard();
								setFigures(board);
								setSquaresPositions(board);
								piece_wants_to_move = nullptr;
								IS_CHOOSING_MOVE = NOT_CHOOSING_MOVE;
								temp_pieceGetPossibleMoves.clear();
								IS_NOW_PLAYING = WHITE;
								result_window.close();
							}
						}
					}

				}
			}
		}
		result_window.clear();
		result_window.draw(background_sprite);
		result_window.draw(result_header);
		result_window.draw(cat);
		for (int i = 0; i < buttons_result_window.size(); ++i) {
			result_window.draw(buttons_result_window[i].sprite);
		}
		result_window.display();
	}
}
void ChangeColorIsMovingNow(Colour& IS_NOW_PLAYING) {
	if (IS_NOW_PLAYING == WHITE) {
		IS_NOW_PLAYING = BLACK;
	}
	else if (IS_NOW_PLAYING == BLACK) {
		IS_NOW_PLAYING = WHITE;
	}
}
int main() {
	loadTexures();
	Board* board = CreateBoard();

	IsChoosingMove IS_CHOOSING_MOVE = NOT_CHOOSING_MOVE;
	std::vector<std::pair<int, int>> temp_pieceGetPossibleMoves;
	Piece* piece_wants_to_move = nullptr;
	Colour IS_NOW_PLAYING = WHITE;

	//count figures
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece* piece = board->square[i][j];
			if (*(piece->GetName()) != EMPTY) {
				board->figures_count++;
			}
		}
	}
	RenderWindow window(VideoMode(655, 488), "Chess");
	Music music;
	music.openFromFile("music/music.ogg");
	music.play();

	InterfaceElement aside(aside_texture, Vector2f(0, 0), IntRect(0, 0, 167, 488));
	InterfaceElement main_background(main_background_texture, Vector2f(167, 0), IntRect(0, 0, 488, 488));
	InterfaceElement numbers(numbers_texture, Vector2f(167, 0), IntRect(0, 0, 20, 488));
	InterfaceElement letters(letters_texture, Vector2f(167, 468), IntRect(0, 0, 488, 20));
	InterfaceElement is_mopving_now_pic(is_moving_now_pic_white_texture, Vector2f(106, 13), IntRect(0, 0, 35, 35));
	InterfaceElement check_info(aside_texture, Vector2f(47, 56), IntRect(0, 0, 73, 36));

	is_moving_now.setFont(font);
	is_moving_now.setString("Moving now:");
	is_moving_now.setCharacterSize(16);
	is_moving_now.setFillColor(Color::Blue);
	is_moving_now.setPosition(10, 20);

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
		if (waitAnswer) {
			int first_hor;
			int first_vert;
			int second_hor;
			int second_vert;
			string msg;
			int len;
			if (isServer) msg = server.getMsg(len, cl);
			else msg = client.getMsg(len);
			first_hor = msg[0] % 8;
			first_vert = msg[0] / 8;
			second_hor = msg[1] % 8;
			second_vert = msg[1] / 8;
			piece_wants_to_move = board->square[first_vert][first_hor];

			Piece* piece = board->square[second_vert][second_hor];
			if (*(piece->GetName()) == EMPTY) {
				board->move(second_hor, second_vert, *(piece->GetColour()), piece_wants_to_move);
			}
			else {
				board->cut_down(second_hor, second_vert, *(piece->GetColour()), piece_wants_to_move);
			}
			if ((second_vert == 7 || second_vert == 0) && (*piece_wants_to_move->GetName()) == PAWN) {
				CreateChooseFigureWindow(second_vert, second_hor, board);
			}
			setFigures(board);
			setSquaresPositions(board);

			piece_wants_to_move = nullptr;
			IS_CHOOSING_MOVE = NOT_CHOOSING_MOVE;
			temp_pieceGetPossibleMoves.clear();

			ChangeColorIsMovingNow(IS_NOW_PLAYING);
			waitAnswer = false;
		}
		else {
			Event event;
			if (IS_NOW_PLAYING == WHITE) {
				is_mopving_now_pic.sprite.setTexture(is_moving_now_pic_white_texture);
			}
			else if (IS_NOW_PLAYING == BLACK) {
				is_mopving_now_pic.sprite.setTexture(is_moving_now_pic_black_texture);
			}
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) window.close();

				else if (event.type == Event::MouseButtonPressed) {
					if (event.mouseButton.button == Mouse::Left) {
						setFigures(board);
						setSquaresPositions(board);
						/*for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++) {
								cout << *(board->square[i][j]->GetName()) << " ";
							}
							cout << "\n";
						}
						cout << "\n";*/
						int cursor_x = Mouse::getPosition(window).x;
						int cursor_y = Mouse::getPosition(window).y;

						//BUTTONS
						for (int i = 0; i < buttons_main_window.size(); ++i) {
							if (cursor_x > buttons_main_window[i].bPosition.x && cursor_x < buttons_main_window[i].bPosition.x + buttons_main_window[i].bSprite.width &&
								cursor_y > buttons_main_window[i].bPosition.y && cursor_y < buttons_main_window[i].bPosition.y + buttons_main_window[i].bSprite.height) {
								if (buttons_main_window[i].name == "play_again") {
									board->SetBoard();
									setFigures(board);
									setSquaresPositions(board);
									cout << "Play again\n";

									// создание окна результата
									CreateResultWindow(check_info, DRAW, board, IS_CHOOSING_MOVE, temp_pieceGetPossibleMoves, piece_wants_to_move, IS_NOW_PLAYING);

									piece_wants_to_move = nullptr;
									IS_CHOOSING_MOVE = NOT_CHOOSING_MOVE;
									temp_pieceGetPossibleMoves.clear();
									IS_NOW_PLAYING = WHITE;
								}
								else if (buttons_main_window[i].name == "create_server") {
									cout << "Create server\n";
									CreateServer(1111);
									serverGame = true;
								}
								else if (buttons_main_window[i].name == "enter_ip") {
									CreateIpWindow(&IS_NOW_PLAYING);

									cout << "Enter ip\n";
								}
							}
						}

						//SQUARES
						int cursor_x_for_board = (cursor_x - board_offset_x) / square_size;
						int cursor_y_for_board = (cursor_y - board_offset_y) / square_size;
						if (cursor_x_for_board <= 7 && cursor_x_for_board >= 0 && cursor_y_for_board <= 7 && cursor_y_for_board >= 0) {
							Piece* piece = board->square[cursor_y_for_board][cursor_x_for_board];
							pair<int, int> click_square = make_pair(cursor_y_for_board, cursor_x_for_board);
							auto is_found = find(temp_pieceGetPossibleMoves.begin(), temp_pieceGetPossibleMoves.end(), click_square);

							if (is_found != temp_pieceGetPossibleMoves.end()) {
								//move figure
								if (serverGame) {
									char first_pos = *(piece_wants_to_move->GetHor()) * 8 + *(piece_wants_to_move->GetVert());
									char second_pos = cursor_y_for_board * 8 + cursor_x_for_board;
									string a = "";
									a += first_pos;
									a += second_pos;
									if (isServer) server.sendMsg(a.c_str(), cl);
									else client.sendMsg(a.c_str());
									waitAnswer = true;
								}
								if ((*piece->GetName()) == EMPTY) {
									board->move(cursor_x_for_board, cursor_y_for_board, *(piece->GetColour()), piece_wants_to_move);
								}
								else {
									board->cut_down(cursor_x_for_board, cursor_y_for_board, *(piece->GetColour()), piece_wants_to_move);
								}
								if ((cursor_y_for_board == 7 || cursor_y_for_board == 0) && (*piece_wants_to_move->GetName()) == PAWN) {
									CreateChooseFigureWindow(cursor_y_for_board, cursor_x_for_board, board);
								}
								setFigures(board);
								setSquaresPositions(board);

								piece_wants_to_move = nullptr;
								IS_CHOOSING_MOVE = NOT_CHOOSING_MOVE;
								temp_pieceGetPossibleMoves.clear();

								ChangeColorIsMovingNow(IS_NOW_PLAYING);

							}
							else if (*(piece->GetName()) != EMPTY && *(piece->GetColour()) == IS_NOW_PLAYING) {
								if (piece_wants_to_move == piece) {
									for (int i = 0; i < temp_pieceGetPossibleMoves.size(); ++i) {
										int possible_move_x = temp_pieceGetPossibleMoves[i].first;
										int possible_move_y = temp_pieceGetPossibleMoves[i].second;

										Piece* piece = board->square[possible_move_x][possible_move_y];
										colorSquare(piece, possible_move_x, possible_move_y, NONE_COLOR);
									}
									piece_wants_to_move = nullptr;
									temp_pieceGetPossibleMoves.clear();
									IS_CHOOSING_MOVE = NOT_CHOOSING_MOVE;
								}
								else {
									//squares backlight red with onclick
									piece_wants_to_move = piece;
									colorSquare(piece, cursor_x_for_board, cursor_y_for_board, RED);
									std::vector<std::pair<int, int>> pieceGetPossibleMoves = *MakePossibleMoves(piece, true);

									if (IS_CHOOSING_MOVE == CHOOSING_MOVE) {
										//убираем возможные ходы предыдущего выбора фигуры
										for (int i = 0; i < temp_pieceGetPossibleMoves.size(); ++i) {
											int possible_move_x = temp_pieceGetPossibleMoves[i].first;
											int possible_move_y = temp_pieceGetPossibleMoves[i].second;

											Piece* piece = board->square[possible_move_x][possible_move_y];
											colorSquare(piece, possible_move_x, possible_move_y, NONE_COLOR);
										}
									}
									for (int i = 0; i < pieceGetPossibleMoves.size(); ++i) {
										int possible_move_x = pieceGetPossibleMoves[i].first;
										int possible_move_y = pieceGetPossibleMoves[i].second;
										/*cout << "(" << possible_move_x << "," << possible_move_y << ") ";*/
										Piece* piece = board->square[possible_move_x][possible_move_y];
										colorSquare(piece, possible_move_x, possible_move_y, GREEN);
									}
									/*cout << endl;*/
									temp_pieceGetPossibleMoves = pieceGetPossibleMoves;
									IS_CHOOSING_MOVE = CHOOSING_MOVE;
								}

							}
							else if (*(piece->GetName()) == EMPTY || (IS_NOW_PLAYING == WHITE && *(piece->GetColour()) == BLACK) || (IS_NOW_PLAYING == BLACK && *(piece->GetColour()) == WHITE)) {
								piece_wants_to_move = nullptr;
								for (int i = 0; i < temp_pieceGetPossibleMoves.size(); ++i) {
									int possible_move_x = temp_pieceGetPossibleMoves[i].first;
									int possible_move_y = temp_pieceGetPossibleMoves[i].second;

									Piece* piece = board->square[possible_move_x][possible_move_y];
									colorSquare(piece, possible_move_x, possible_move_y, NONE_COLOR);
								}
								temp_pieceGetPossibleMoves.clear();
								IS_CHOOSING_MOVE = NOT_CHOOSING_MOVE;
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
					auto is_found_temp = find(temp_pieceGetPossibleMoves.begin(), temp_pieceGetPossibleMoves.end(), move_square_temp);

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
		}
		window.clear();

		window.draw(aside.sprite);
		window.draw(main_background.sprite);
		window.draw(is_mopving_now_pic.sprite);
		window.draw(is_moving_now);
		window.draw(numbers.sprite);
		window.draw(letters.sprite);
		window.draw(check_info.sprite);

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