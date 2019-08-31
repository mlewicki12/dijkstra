
#include <iostream>
#include <cstdio>

class AdjMatrix {
	private:
		int** distances;
		int size;

		int minvert(int* dist, bool* s) {
			int min = -1;
			for(int i = 0; i < size; ++i) {
				if(!s[i] && (dist[i] < min ||
					    min == -1)) {
					min = i;
				} 
			}

			return min;
		}

	public:
		AdjMatrix(int n) {
			distances = (int**) malloc(sizeof(int*) * n);
			size = n;

			for(int i = 0; i < n; ++i) {
				distances[i] = (int*) malloc(sizeof(int) * n);
			}

			// initialize all values
			for(int i = 0; i < n; ++i) {
				for(int j = 0; j < n; ++j) {
					distances[i][j] = INT_MAX / 2;
				}
			}
		}

		// kill all values
		~AdjMatrix() {
			for(int i = 0; i < size; ++i) {
				for(int j = 0; j < size; ++j) {
					free(&distances[i][j]);
				}

				free(distances[i]);
			}

			free(distances);
		}

		AdjMatrix* Connect(int f, int s, int d) {
			distances[f-1][s-1] = d;
			return this;
		}

		void Print() {
			std::cout << "\t";

			for(int i = 0; i < size; ++i) {
				std::cout << (i + 1) << "\t";
			}

			std::cout << "\n\n";
			for(int i = 0; i < size; ++i) {
				std::cout << (i + 1) << "\t";
				for(int j = 0; j < size; ++j) {
					if(distances[i][j] == INT_MAX / 2) {
						std::cout << "\t";
					} else {
						std::cout << distances[i][j] << "\t";
					}
				}
				std::cout << "\n\n";
			}
		}

		int Dijkstra(int* ret) {
			int vert;
			bool s[size];

			s[0] = true;
			for(int i = 1; i < size; ++i) {
				ret[i] = distances[0][i];
				s[i] = false;
			}

			while((vert = minvert(ret, s)) != -1) {
				s[vert] = true;
				for(int i = 1; i < size; ++i) {
					if(distances[0][vert] + distances[vert][i] < ret[i]) {
						ret[i] = distances[0][vert] + distances[vert][i];
					}
				}
			}

			return 0;
		}
};

int main(int argc, char** argv) {
	auto matr = new AdjMatrix(6);
	int ret[6];

	matr->Connect(1, 2, 4)->Connect(1, 3, 1)->Connect(1, 4, 5)
	    ->Connect(1, 5, 8)->Connect(1, 6, 10)->Connect(3, 2, 2)
	    ->Connect(4, 5, 2)->Connect(5, 6, 1)->Print();

	matr->Dijkstra(ret);
	std::cout << "Results of running Dijkstra's algorithm:\n";
	for(int i = 0; i < 6; ++i) {
		std::cout << (i + 1) << ": " << ret[i] << "\n";
	}
}
