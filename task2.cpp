#include "SDL.h"
#include <iostream>
#include <math.h>
#include <time.h>
#include <string>
using namespace std;

class Point2D {
private:
	float x;
	float y;
public:
	Point2D() {
		x = 0;
		y = 0;
	}

	Point2D(float nx, float ny) {
		x = nx;
		y = ny;
	}

	void setx(float set_x) {
		x = set_x;
	}

	void sety(float set_y) {
		y = set_y;
	}

	float getx() {
		return x;
	}

	float gety() {
		return y;
	}

	string toString() {
		string output = "[";
		output = output + to_string(x) + "," + to_string(y) + "]\n";
		return output;
	}

	float distanceBetween(Point2D otherPoint) {
		//Chosen because of pythagoran theorem
		float A = x - otherPoint.x;
		float B = y - otherPoint.y;
		float C;
		C = sqrt(pow(A, 2) + pow(B, 2));
		return C;
	}
};

/*/Shape
shape::shape() {
	Point2D point;
	RGBA[0] = RGBA[1] = RGBA[2] = RGBA[3] = 0;
	point.setx(0);
	point.sety(0);
}

shape::shape(float x_pos, float y_pos, int red, int green, int blue, int alpha) {
	if (red < 256 && 0 <= red && green < 256 && 0 <= green && blue < 256 && 0 <= blue && alpha < 256 && 0 <= alpha) {
		RGBA[0] = red;
		RGBA[1] = green;
		RGBA[2] = blue;
		RGBA[3] = alpha;
		position.setx(x_pos);
		position.sety(y_pos);
	}
}

void shape::render(SDL_Renderer* renderer) {
	cout << "draws a generic shape\n";
}
*/

class rectangle {
private:
	float height;
	float width;
	int red, green, blue, alpha;

public:
	Point2D position;
	rectangle(float pos_x, float pos_y, int nred, int ngreen, int nblue, int nalpha, double nwidth, double nheight) {
		position.setx(pos_x);
		position.sety(pos_y);
		red = nred;
		green = ngreen;
		blue = nblue;
		alpha = nalpha;
		width = nwidth;
		height = nheight;
	}

	rectangle() {
		position.setx(0);
		position.sety(0);
		red = 0;
		green = 0;
		blue = 0;
		alpha = 255;
		width = 100;
		height = 100;
	}

	float getWidth() {
		return width;
	}

	float getHeight() {
		return height;
	}

	void setWidth(float nw) {
		width = nw;
	}

	void setHeight(float nh) {
		height = nh;
	}

	void setRed(int nred) {
		red = nred;
	}

	void setGreen(int ngreen){
		green = ngreen;
	}

	void setBlue(int nblue) {
		blue = nblue;
	}

	void setAlpha(int nalpha) {
		alpha = nalpha;
	}

	void render(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
		SDL_RenderDrawLine(renderer, position.getx(), position.gety(), position.getx() + width, position.gety());
		SDL_RenderDrawLine(renderer, position.getx() + width, position.gety(), position.getx() + width, position.gety() + height);
		SDL_RenderDrawLine(renderer, position.getx() + width, position.gety() + height, position.getx(), position.gety() + height);
		SDL_RenderDrawLine(renderer, position.getx(), position.gety() + height, position.getx(), position.gety());


	}
};


class board {
public:
	int tilesData[20] = { 1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10 };
	bool tilesShown[20];
	rectangle rect[20];
	SDL_Rect rect2[20];

	//Initializes board, is separate from constructor if you wanted to play several games in a row, then you would just call init again for a fresh board
	void init(){
		srand(time(0));
		int count = 0;
		int count2 = 0;
		int temp = 0;
		int rand1 = 0;
		int rand2 = 0;
		while (count < 20) {
			tilesShown[count] = false;
			rect[count].position.setx(count * 80 - (count2 * 400) + 20);
			rect2[count].x = count * 80 - (count2 * 400) + 20;
			rect[count].position.sety(count2 * 80 + 20);
			rect2[count].y = count2 * 80 + 20;
			rect[count].setRed(255);
			rect[count].setGreen(255);
			rect[count].setBlue(255);
			rect[count].setAlpha(255);
			rect[count].setHeight(70);
			rect2[count].h = 70;
			rect[count].setWidth(70);
			rect2[count].w = 70;
			count++;
			if (count % 5 == 0) {
				count2++;
			}
		}
		count = 0;
		while (count < 300) {
			rand1 = rand() % 20;
			rand2 = rand() % 20;
			temp = tilesData[rand1];
			tilesData[rand1] = tilesData[rand2];
			tilesData[rand2] = temp;
			count++;
		}
	}

	board() {
		init();
	}

	//Renders the background and face-down tiles
	void boardRender(SDL_Renderer* renderer) {
		int count = 0;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		while (count < 20) {
			rect[count].render(renderer);
			count++;
		}
	}

	//Flips the two called tiles, checks if they match, and flips them back down if they don't
	void flipTiles(SDL_Renderer* renderer, int tile1, int tile2) {
		tilesShown[tile1] = true;
		tilesShown[tile2] = true;
		renderFlipped(renderer);
		SDL_Delay(1000);
		if (tilesData[tile1] != tilesData[tile2]) {
			tilesShown[tile1] = tilesShown[tile2] = false;
		}
		boardRender(renderer);
		renderFlipped(renderer);
	}

	//Renders flipped cards
	void renderFlipped(SDL_Renderer* renderer) {
		int count = 0;
		while (count < 20) {
			if (tilesShown[count] == true) {
				//A switch case didn't work for some reason so I set up an if-statement list insetad. It's more ineficient, but at least it works
				//RED
				if (tilesData[count] == 1) {
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					SDL_RenderFillRect(renderer, &rect2[count]);
					
				}
				//GREEN
				else if (tilesData[count] == 2) {
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
					SDL_RenderFillRect(renderer, &rect2[count]);
					
				}
				//BLUE
				else if (tilesData[count] == 3) {
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
					SDL_RenderFillRect(renderer, &rect2[count]);
					
				}
				//YELLOW
				else if (tilesData[count] == 4) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
					SDL_RenderFillRect(renderer, &rect2[count]);
					
				}
				//CYAN
				else if (tilesData[count] == 5) {
					SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
					SDL_RenderFillRect(renderer, &rect2[count]);
					
				}
				//ORANGE/BROWN
				else if (tilesData[count] == 6) {
					SDL_SetRenderDrawColor(renderer, 150, 80, 0, 255);
					SDL_RenderFillRect(renderer, &rect2[count]);
					
				}
				//MAGENTA
				else if (tilesData[count] == 7) {
					SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
					SDL_RenderFillRect(renderer, &rect2[count]);
					
				}
				//PURPLE
				else if (tilesData[count] == 8) {
					SDL_SetRenderDrawColor(renderer, 90, 0, 90, 255);
					SDL_RenderFillRect(renderer, &rect2[count]);
					
				}
				//D-GREEN
				else if (tilesData[count] == 9) {
					SDL_SetRenderDrawColor(renderer, 45, 80, 27, 255);
					SDL_RenderFillRect(renderer, &rect2[count]);
					
				}
				//GREY
				else if (tilesData[count] == 10) {
					SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);
					SDL_RenderFillRect(renderer, &rect2[count]);
					
				}
			}
			count++;
		}
		SDL_RenderPresent(renderer);
	}

	//Checks if all tiles are fliped
	bool testWinState() {
		bool ans = true;
		int count = 0;
		while (count < 20) {
			if (tilesShown[count] == false)
				ans = false;
			count++;
		}
		return ans;
	}

	//Main body of game, calls other functions and moves cursor
	void game(SDL_Renderer* renderer) {
		int currentPos = 0;
		SDL_Event event;

		bool win = false;
		bool first = true;
		
		int firstSelect;
		int secondSelect;
		
		SDL_Rect cursor;
		SDL_Rect prevSelect;
		
		cursor.h = 70;
		cursor.w = 70;
		prevSelect.h = 70;
		prevSelect.w = 70;
		cursor.x = 20;
		cursor.y = 20;

		//Renders cursor at start of game
		boardRender(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &cursor);
		SDL_RenderPresent(renderer);
		
		//Controlls
		while (!win) {
			SDL_WaitEvent(&event);
			switch (event.key.keysym.sym) {
			//Move left if you can
			case SDLK_LEFT:
				if (currentPos % 5 > 0) {
					cursor.x = cursor.x - 80;
					boardRender(renderer);
					renderFlipped(renderer);
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderFillRect(renderer, &cursor);
					if (first == false) {
						SDL_RenderFillRect(renderer, &prevSelect);
					}
					SDL_RenderPresent(renderer);
					currentPos--;
				}
				break;
			//Move right if you can
			case SDLK_RIGHT:
				if (currentPos % 5 < 4) {
					cursor.x = cursor.x + 80;
					boardRender(renderer);
					renderFlipped(renderer);
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderFillRect(renderer, &cursor);
					if (first == false) {
						SDL_RenderFillRect(renderer, &prevSelect);
					}
					SDL_RenderPresent(renderer);
					currentPos++;
				}
				break;
			//Move up if you can
			case SDLK_UP:
				if (currentPos / 5 >= 1) {
					cursor.y = cursor.y - 80;
					boardRender(renderer);
					renderFlipped(renderer);
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderFillRect(renderer, &cursor);
					if (first == false) {
						SDL_RenderFillRect(renderer, &prevSelect);
					}
					SDL_RenderPresent(renderer);
					currentPos=currentPos-5;
				}
				break;
			//Move down if you can
			case SDLK_DOWN:
				if (currentPos / 5 < 3) {
					cursor.y = cursor.y + 80;
					boardRender(renderer);
					renderFlipped(renderer);
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderFillRect(renderer, &cursor);
					if (first == false) {
						SDL_RenderFillRect(renderer, &prevSelect);
					}
					SDL_RenderPresent(renderer);
					currentPos = currentPos + 5;
				}
				break;
			//Select a tile, and if it is the second tile, flip it
			case SDLK_RETURN:
				if (first == true) {
					firstSelect = currentPos;
					prevSelect.x = (currentPos % 5) * 80 + 20;
					prevSelect.y = (currentPos / 5) * 80 + 20;
					first = false;
				}
				else {
					secondSelect = currentPos;
					flipTiles(renderer, firstSelect, secondSelect);
					win = testWinState();
					first = true;
				}
				break;
			}
			SDL_WaitEvent(&event);
		}
	}

	//Destructor
	~board() {
		delete rect;
		delete rect2;
	}
};



int main(int argc, char* argv[]) {
	bool win = false;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Rect test;
	SDL_Window* window = SDL_CreateWindow("Memory", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 440, 360, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	


	//Draws black background for start
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);

	//Draws cards
	board game;
	game.init();
	game.game(renderer);
	cout << "VICTORY";
	SDL_Delay(3000);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	system("pause");
	return 0;
}