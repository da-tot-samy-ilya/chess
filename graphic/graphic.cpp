#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

const int figures_count = 32;

Sprite figures[figures_count];
Sprite squares[64];

int k = 0;
int size = 56;
int board[8][8] = {
	{1,2,3,4,5,3,2,1},
	{6,6,6,6,6,6,6,6},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{-6,-6,-6,-6,-6,-6,-6,-6},
	{-1,-2,-3,-4,-5,-3,-2,-1},
};

void setFigures() {
	int n;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			n = board[i][j];

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
				figures[k].setPosition(size * j, size * i);
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
				squares[i * 8 + j].setPosition(size * j, size * i);

		}
		k = (k + 1) % 2;
	}
	
}

int main() {
	RenderWindow window(VideoMode(448, 448), "Chess");

	Texture figure_texture, black_square, white_square;
	figure_texture.loadFromFile("images/figures1.png");

	for (int i = 0; i < figures_count; ++i) {
		figures[i].setTexture(figure_texture);
	}
	setFigures();
	
	black_square.loadFromFile("images/black_texture.jpg");
	white_square.loadFromFile("images/white_texture.jpg");

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
	
	while (window.isOpen()) {
		bool check_figure = false;
		int temp_x = 0;
		int temp_y = 0;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !check_figure) {
			Vector2i localPosition1 = Mouse::getPosition(window);
			/*std::cout << localPosition.x/size << " " << localPosition.y/size << "\n";*/
			/*std::cout << board[localPosition1.y / size][localPosition1.x / size];*/
			int temp_x = localPosition1.x / size;
			int temp_y = localPosition1.y / size;
			check_figure = true;
			/*for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 8; ++j) {
					std::cout << board[i][j] << " ";
				}
				std::cout << std::endl;
			}*/
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && check_figure) {
			Vector2i localPosition2 = Mouse::getPosition(window);
			board[localPosition2.y / size][localPosition2.x / size] = board[temp_y][temp_x];
			check_figure = false;
			//std::cout << localPosition2.y / size << " " << localPosition2.x / size << " " << temp_y << " " << temp_x << "\n";
			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 8; ++j) {
					std::cout << board[i][j] << " ";
				}
				std::cout << std::endl;
			}
		}
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

		}

		window.clear();
		for (int i = 0; i < 64; ++i) {
			window.draw(squares[i]);
		}
		
		for (int i = 0; i < figures_count; ++i) {
			window.draw(figures[i]);
		}

		window.display();

	}

	return 0;
}