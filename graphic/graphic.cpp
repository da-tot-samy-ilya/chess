#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

Sprite figures[32];
int k = 0;
int size = 56;
int board[8][8] = {
	{1,2,3,4,5,3,2,1},
	{6,6,6,6,6,6,6,6},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
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

int main() {
	RenderWindow window(VideoMode(456, 456), "Chess");
	Texture board_texture, figure_texture;

	board_texture.loadFromFile("images/board0.png");
	figure_texture.loadFromFile("images/figures1.png");

	Sprite sprite_board;
	sprite_board.setTexture(board_texture);

	for (int i = 0; i < 32; ++i) {
		figures[i].setTexture(figure_texture);
	}
	setFigures();
	while (window.isOpen()) {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			Vector2i localPosition = Mouse::getPosition(window);
			std::cout << localPosition.x << " " << localPosition.y << "\n";
		}
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

		}

		window.clear();
		window.draw(sprite_board);
		for (int i = 0; i < 32; ++i) {
			window.draw(figures[i]);
		}

		window.display();

	}

	return 0;
}