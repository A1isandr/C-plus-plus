#include <windows.h>
#include <iostream>
#include <conio.h>
#include <utility>
#include <chrono>
#include <thread>
#include <ctime>
#include <queue>
#include <vector>

//Здесь хранятся все данные об игроке
struct Player {
	const char head = 'X';
	const char tail = '8';
	const char body = 'O';
	int head_pos_x = 0;
	int head_pos_y = 0;
	int score = 0;
	bool ate_apple = true;
	bool collision = false;
	std::queue<char> comands;
	std::vector<std::pair<int, int>> coords;
};

//Здесь хранятся все данные о поле и яблоке
struct Board {
	const int height = 15;
	const int width = 30;
	const char borderUpDown = ' ';
	const char borderLeftRight = ' ';
	const std::string borderColor = "\033[46m";
	const std::string bgColor = "\033[42m";
	const std::string fontColor = "\033[1;36m";
	
	const char apple = 'Q';
	int apple_pos_x = 1;
	int apple_pos_y = 1;
};

//Эта функция отвечает за обновление экрана
void updateScreen() {
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

//Эта функция выводит на экран сообщение о проигрыше
void gameOver() {
	std::cout << "\033[41m" << "Game Over!" << "\033[0m" << "\n"
			  << "Press any button to restart!";
}

//Эта функция генерирует новое яблоко после того как предыдущее было съедено
void makeApple(Board& board, const Player& player) {
	srand(time(NULL));
	do {
		board.apple_pos_x = rand() % board.width;
		board.apple_pos_y = rand() % board.height;
	} while (board.apple_pos_x == player.head_pos_x && board.apple_pos_y == player.head_pos_y);
}

//Эта функция отображает поле, яблоко и игрока на экране
void drawBoard(Board& board, const Player& player) {
	std::string border;
	std::string row;
	border.assign(board.width + 2, board.borderUpDown);
	if (player.ate_apple) {
		makeApple(board, player);
	}

	updateScreen();
	std::cout << "Score: " << player.score << "\n";
	std::cout << board.borderColor << border << "\033[0m" << "\n";

	for (int rowNumber = 0; rowNumber < board.height; rowNumber++) {
		row.assign(board.width, ' ');
		for (auto& pair : player.coords) {
			if (rowNumber == pair.second)  row[pair.first] = player.body;
		}
		if (rowNumber == player.head_pos_y) row[player.head_pos_x] = player.head;
		if (rowNumber == player.coords[player.coords.size()-1].second) row[player.coords[player.coords.size() - 1].first] = player.tail;
		if (rowNumber == board.apple_pos_y) row[board.apple_pos_x] = board.apple;
		
		std::cout << board.borderColor << board.borderLeftRight << "\033[0m"
			<< board.bgColor << board.fontColor << row << "\033[0m"
			<< board.borderColor << board.borderLeftRight << "\033[0m" << "\n";
	}

	std::cout << board.borderColor << border << "\033[0m" << "\n";
}

//Эта функция обрабатывает ввод игрока и изменяет направление змейки
void changeDirection(Player& player, char key) {
	switch (key)
	{
	case 'w':
		if (player.comands.front() != 'f') player.comands.push('b');
		break;
	case 's':
		if (player.comands.front() != 'b') player.comands.push('f');
		break;
	case 'd':
		if (player.comands.front() != 'l') player.comands.push('r');
		break;
	case 'a':
		if (player.comands.front() != 'r') player.comands.push('l');
		break;
	default:
		break;
	}
}

//Эта функция перемещает игрока по полю, а также отслеживает, съел ли игрок яблоко и столкновение игрока со стенками и с самим собой
void movePlayer(Board& board, Player& player) {
	while (true) {
		if (player.comands.size() > 1) player.comands.pop();
		
		player.coords.insert(player.coords.begin(), std::make_pair(player.head_pos_x, player.head_pos_y));
		if (!player.ate_apple) player.coords.pop_back();
		
		switch (player.comands.front())
		{
		case 'r':
			player.head_pos_x++;
			break;
		case 'l':
			player.head_pos_x--; 
			break;
		case 'f':
			player.head_pos_y++; 
			break;
		case 'b':
			player.head_pos_y--; 
			break;
		default:
			break;
		}

		if (player.head_pos_x == board.width || player.head_pos_y == board.height || player.head_pos_x < 0 || player.head_pos_y < 0) {
			player.collision = true;
		}
		
		for (auto& pair : player.coords) {
			if (player.head_pos_x == pair.first && player.head_pos_y == pair.second) {
				player.collision = true;
			}
		}

		if (player.collision) break;

		if (player.head_pos_x == board.apple_pos_x && player.head_pos_y == board.apple_pos_y) {
			player.ate_apple = true;
			player.score++;
		}
		else player.ate_apple = false;

		drawBoard(board, player);

		std::chrono::milliseconds duration(200);
		std::this_thread::sleep_for(duration);
	}

	gameOver();
}

//Главная функция
int main() {
	
	while (true) {
		system("cls");
		
		Board board;
		Player player;
		player.comands.push('f');

		std::thread Game(movePlayer, std::ref(board), std::ref(player));

		while (!player.collision) {
			char key = _getch();
			changeDirection(player, std::tolower(key));
		}

		Game.join();
	}

	return 0;
}