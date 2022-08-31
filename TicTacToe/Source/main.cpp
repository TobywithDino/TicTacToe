#include <iostream>
#include <vector>
#include <SDL.h>
#include <time.h>
using std::vector;

struct Obj
{
	Obj(int px, int py);
	void Render(SDL_Renderer* renderer);

	bool o;
	int x, y;
private:
	static bool CURRENT_O;
};
bool Obj::CURRENT_O = true;

Obj::Obj(int px, int py) {
	if (CURRENT_O) {
		o = true;
		CURRENT_O = false;
	}
	else {
		o = false;
		CURRENT_O = true;
	}
	x = px;
	y = py;
}
void Obj::Render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	if (o) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, x - 45, y - 78, x + 45, y - 78);
		SDL_RenderDrawLine(renderer, x + 45, y - 78, x + 90, y);
		SDL_RenderDrawLine(renderer, x + 90, y, x + 45, y + 78);
		SDL_RenderDrawLine(renderer, x + 45, y + 78, x - 45, y + 78);
		SDL_RenderDrawLine(renderer, x - 45, y + 78, x - 90, y);
		SDL_RenderDrawLine(renderer, x - 90, y, x - 45, y - 78);
	}
	else {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, x - 70, y - 70, x + 70, y + 70);
		SDL_RenderDrawLine(renderer, x - 70, y + 70, x + 70, y - 70);
	}
}


class Game {
public:
	Game(const char* title);
	bool running() { return isRunning; }
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	void handleEvent();
	void update();
	void render();
	void quit();
	static void reset(vector<Obj*>& obj);
	static const int GAME_WIDTH;
	static const int GAME_HEIGHT;

	static vector<Obj*> obj;

	static vector<vector<int>> grid;
private:
	static bool isRunning;

};
bool Game::isRunning = false;
SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;
const int Game::GAME_WIDTH = 642;
const int Game::GAME_HEIGHT = 642;
vector<Obj*> Game::obj;
vector<vector<int>> Game::grid = {  {40 + (Game::GAME_WIDTH - 80) / 6, 40 + (Game::GAME_HEIGHT - 80) / 6},
									{40 + (Game::GAME_WIDTH - 80) / 2, 40 + (Game::GAME_HEIGHT - 80) / 6},
									{40 + (Game::GAME_WIDTH - 80)*5/6, 40 + (Game::GAME_HEIGHT - 80) / 6},
								    {40 + (Game::GAME_WIDTH - 80) / 6, 40 + (Game::GAME_HEIGHT - 80) / 2},
									{40 + (Game::GAME_WIDTH - 80) / 2, 40 + (Game::GAME_HEIGHT - 80) / 2},
									{40 + (Game::GAME_WIDTH - 80)*5/6, 40 + (Game::GAME_HEIGHT - 80) / 2},
								    {40 + (Game::GAME_WIDTH - 80) / 6, 40 + (Game::GAME_HEIGHT - 80)*5/6},
									{40 + (Game::GAME_WIDTH - 80) / 2, 40 + (Game::GAME_HEIGHT - 80)*5/6},
									{40 + (Game::GAME_WIDTH - 80)*5/6, 40 + (Game::GAME_HEIGHT - 80)*5/6}
								 };

Game::Game(const char* title) {
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WIDTH, GAME_HEIGHT, 0);
	if (window != nullptr) {
		std::cout << "Window Created!" << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer != nullptr) {
		std::cout << "Renderer Created!" << std::endl;
		SDL_SetRenderDrawColor(Game::renderer, 30, 30, 30, 255);
	}
	isRunning = true;
}


void Game::update()
{

}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);

	//draw
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	//around
	SDL_RenderDrawLine(Game::renderer, 40, 40, Game::GAME_WIDTH - 40, 40);
	SDL_RenderDrawLine(Game::renderer, 40, Game::GAME_HEIGHT - 40, Game::GAME_WIDTH - 40, Game::GAME_HEIGHT - 40);
	SDL_RenderDrawLine(Game::renderer, 40, 40, 40, Game::GAME_HEIGHT - 40);
	SDL_RenderDrawLine(Game::renderer, Game::GAME_WIDTH - 40, 40, Game::GAME_WIDTH - 40, Game::GAME_HEIGHT - 40);
	//center
	SDL_RenderDrawLine(Game::renderer, 40, 40 + (Game::GAME_HEIGHT - 80) / 3, Game::GAME_WIDTH - 40, 40 + (Game::GAME_HEIGHT - 80) / 3);
	SDL_RenderDrawLine(Game::renderer, 40, 40 + (Game::GAME_HEIGHT - 80) * 2 / 3, Game::GAME_WIDTH - 40, 40 + (Game::GAME_HEIGHT - 80) * 2 / 3);
	SDL_RenderDrawLine(Game::renderer, 40 + (Game::GAME_WIDTH - 80) / 3, 40, 40 + (Game::GAME_WIDTH - 80) / 3, Game::GAME_HEIGHT - 40);
	SDL_RenderDrawLine(Game::renderer, 40 + (Game::GAME_WIDTH - 80) * 2 / 3, 40, 40 + (Game::GAME_WIDTH - 80) * 2 / 3, Game::GAME_HEIGHT - 40);
	
	//draw stuff
	for (Obj* i : Game::obj) {
		i->Render(Game::renderer);
	}
	SDL_RenderPresent(renderer);
}

void Game::quit()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Renderer and window cleaned!" << std::endl;
}
void Game::reset(vector<Obj*>& obj)
{
	obj.clear();
}
class Mouse {
public:
	Mouse();
	static void HandleEvent(SDL_Event* e);
	static void AddObj(int x, int y);
	static bool isAnObj(int x, int y);
private:

};
Mouse::Mouse() {}
void Mouse::HandleEvent(SDL_Event* e) {
	if (e->type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x > 40 && x < 40 + (Game::GAME_WIDTH - 80) / 3 && y > 40 && y < 40 + (Game::GAME_HEIGHT - 80) / 3) {
			//grid 1
			int x = Game::grid[0][0];
			int y = Game::grid[0][1];
			if(!isAnObj(x,y))
				Mouse::AddObj(Game::grid[0][0], Game::grid[0][1]);
		}
		else if (x > 40 + (Game::GAME_WIDTH - 80) / 3 && x < 40 + (Game::GAME_WIDTH - 80) * 2 / 3 && y > 40 && y < 40 + (Game::GAME_HEIGHT - 80) / 3) {
			//grid 2
			int x = Game::grid[1][0];
			int y = Game::grid[1][1];
			if (!isAnObj(x, y))
				Mouse::AddObj(Game::grid[1][0], Game::grid[1][1]);
		}
		else if (x > 40 + (Game::GAME_WIDTH - 80) * 2 / 3 && x < Game::GAME_WIDTH - 40 && y > 40 && y < 40 + (Game::GAME_HEIGHT - 80) / 3) {
			//grid 3
			int x = Game::grid[2][0];
			int y = Game::grid[2][1];
			if (!isAnObj(x, y))
				Mouse::AddObj(Game::grid[2][0], Game::grid[2][1]);
		}
		else if (x > 40 && x < 40 + (Game::GAME_WIDTH - 80) / 3 && y > 40 + (Game::GAME_HEIGHT - 80) / 3 && y < 40 + (Game::GAME_HEIGHT - 80) * 2 / 3) {
			//grid 4
			int x = Game::grid[3][0];
			int y = Game::grid[3][1];
			if (!isAnObj(x, y))
				Mouse::AddObj(Game::grid[3][0], Game::grid[3][1]);
		}
		else if (x > 40 + (Game::GAME_WIDTH - 80) / 3 && x < 40 + (Game::GAME_WIDTH - 80) * 2 / 3 && y > 40 + (Game::GAME_HEIGHT - 80) / 3 && y < 40 + (Game::GAME_HEIGHT - 80) * 2 / 3) {
			//grid 5
			int x = Game::grid[4][0];
			int y = Game::grid[4][1];
			if (!isAnObj(x, y))
				Mouse::AddObj(Game::grid[4][0], Game::grid[4][1]);
		}
		else if (x > 40 + (Game::GAME_WIDTH - 80) * 2 / 3 && x < Game::GAME_WIDTH - 40 && y > 40 + (Game::GAME_HEIGHT - 80) / 3 && y < 40 + (Game::GAME_HEIGHT - 80) * 2 / 3) {
			//grid 6
			int x = Game::grid[5][0];
			int y = Game::grid[5][1];
			if (!isAnObj(x, y))
				Mouse::AddObj(Game::grid[5][0], Game::grid[5][1]);
		}
		else if (x > 40 && x < 40 + (Game::GAME_WIDTH - 80) / 3 && y > 40 + (Game::GAME_HEIGHT - 80) * 2 / 3 && y < Game::GAME_HEIGHT - 40) {
			//grid 7
			int x = Game::grid[6][0];
			int y = Game::grid[6][1];
			if (!isAnObj(x, y))
				Mouse::AddObj(Game::grid[6][0], Game::grid[6][1]);
		}
		else if (x > 40 + (Game::GAME_WIDTH - 80) / 3 && x < 40 + (Game::GAME_WIDTH - 80) * 2 / 3 && y > 40 + (Game::GAME_HEIGHT - 80) * 2 / 3 && y < Game::GAME_HEIGHT - 40) {
			//grid 8
			int x = Game::grid[7][0];
			int y = Game::grid[7][1];
			if (!isAnObj(x, y))
				Mouse::AddObj(Game::grid[7][0], Game::grid[7][1]);
		}
		else if (x > 40 + (Game::GAME_WIDTH - 80) * 2 / 3 && x < Game::GAME_WIDTH - 40 && y > 40 + (Game::GAME_HEIGHT - 80) * 2 / 3 && y < Game::GAME_HEIGHT - 40) {
			//grid 9
			int x = Game::grid[8][0];
			int y = Game::grid[8][1];
			if (!isAnObj(x, y))
				Mouse::AddObj(Game::grid[8][0], Game::grid[8][1]);
		}
	}
}

void Mouse::AddObj(int x, int y)
{
	Obj* newObj = new Obj(x,y);
	Game::obj.push_back(newObj);
	int AI_Pos = rand() % 9;
	int cnt = 1;
	while (isAnObj(Game::grid[AI_Pos][0], Game::grid[AI_Pos][1]) && cnt < 9) {
		cnt++;
		AI_Pos = rand() % 9;
	}
	if(cnt < 9)
		Game::obj.push_back(new Obj(Game::grid[AI_Pos][0], Game::grid[AI_Pos][1]));	
}

bool Mouse::isAnObj(int x, int y) {
	for (Obj* i : Game::obj) {
		if (i->x == x && i->y == y) {
			return true;
		}
	}
	return false;
}


void Game::handleEvent()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type != SDL_QUIT) {
		Mouse::HandleEvent(&event);
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_r:
				Game::reset(Game::obj);
				break;
			case SDLK_q:
				isRunning = false;
				break;
			default:
				break;
			}

		}
	}
	else {
		isRunning = false;
	}
	
}
int main(int argc, char* args[]) {
	srand((unsigned int)time(nullptr));
	Game* game = new Game("Tic Tac Toe");
	while (game->running()) {
		game->handleEvent();
		game->update();
		game->render();
	}
	game->quit();

	return 0;
}

