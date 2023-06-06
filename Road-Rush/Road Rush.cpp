#include <iostream>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include <vector>
#include <queue>
#include <fstream>

class Road {
	private:
		struct RoadConfig {
			int size = 24;
			int line_size = 4;

			std::string line_texture = "||";
			std::string sideLine_texture = "||";
			std::string gap_texture = "  ";
		} road;

	public:
		std::vector<std::string> left;
		std::vector<std::string> right;
		std::vector<std::string> line;

		Road() {
			for (int i = 0; i < road.size; i++) {
				left.push_back("          ");
				right.push_back("          ");
			}

			right[right.size()-4] = "   000    ";
			right[right.size()-3] = "    0     ";
			right[right.size()-2] = "  00000   ";
			right[right.size()-1] = "   000    ";

			std::string str = road.line_texture;
			for (int i = 0; i < road.size; i++) {
				line.push_back(str);

				if (i % road.line_size == 0) {
					str == road.gap_texture ? str = road.line_texture : str = road.gap_texture;
				}
			}
		}
		
		void draw() {

			for (int i = 0; i < road.size; i++) {
				std::cout << road.sideLine_texture << left[i] << line[i] << right[i] << road.sideLine_texture << "\n";
			}

			line.insert(line.begin(), line.back());
			line.pop_back();

			std::chrono::milliseconds duration(200);
			std::this_thread::sleep_for(duration);
		}

};

class Player : public Road {
	private:
		std::ofstream file;
 		std::queue<char> comands;
		bool is_right_lane = true;

	public:
		void detectInput() {
			while (true) {
				char key = _getch();
				comands.push(tolower(key));
			}
		}

		void move() {
			while (true) {
				if (comands.empty()) continue;

				switch (comands.front()) {
				case 'd':
					if (!is_right_lane) {
						
						right[right.size() - 4] = "   000    ";
						right[right.size() - 3] = "    0     ";
						right[right.size() - 2] = "  00000   ";
						right[right.size() - 1] = "   000    ";

						left[left.size() - 4] = "          ";
						left[left.size() - 3] = "          ";
						left[left.size() - 2] = "          ";
						left[left.size() - 1] = "          ";

						is_right_lane = true;

						file.open("log.txt", std::ios_base::app);

						for (auto& e : left) {
							file << e << "\n";
						}

						file << "========================" << "\n";
						file.close();
					}
					
					break;
				case 'a':
					if (is_right_lane) {
						left[left.size() - 4] = "   000    ";
						left[left.size() - 3] = "    0     ";
						left[left.size() - 2] = "  00000   ";
						left[left.size() - 1] = "   000    ";

						right[right.size() - 4] = "          ";
						right[right.size() - 3] = "          ";
						right[right.size() - 2] = "          ";
						right[right.size() - 1] = "          ";

						is_right_lane = false;

						file.open("log.txt", std::ios_base::app);

						for (auto& e : left) {
							file << e << "\n";
						}

						file << "========================" << "\n";
						file.close();
					}
					
					break;
				default:
					break;
				}

				comands.pop();
			}
		}
};

void updateScreen() {
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

int main() {
	Road *road = new Road;
	Player player;

	std::thread Input(&Player::detectInput, &player);
	std::thread Movement(&Player::move, &player);


	while (true) {
		road->draw();
		updateScreen();
	}
}