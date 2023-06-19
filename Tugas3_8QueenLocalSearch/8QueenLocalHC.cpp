// queen local search hill climbing
#include <iostream>
#include <math.h>

using namespace std;

#define N 8
// ukuran papan dan jumlah queens
// configuring board and make a random starting point (state)
void RandomConfiguration(int board[][N], int* state) {

	// Seed for the random function
	// srand(time(0));

	for (int i = 0; i < N; i++) {
		// penentuan baris random
		state[i] = rand() % N;
		// penempatan queen pada lokasi yang didapatkan state
		//1 queen per baris dan kolom
		board[state[i]][i] = 1;
	}
}

//printboard
void printBoard(int board[][N])
{

	for (int i = 0; i < N; i++) {
		cout << " ";
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
}

// print array state
void printState(int* state)
{

	for (int i = 0; i < N; i++) {
		cout << " " << state[i] << " ";
	}
	cout << endl;
}

// komparasi array state dengan neighbour
bool compareStates(int* state1, int* state2)
{

	for (int i = 0; i < N; i++) {
		if (state1[i] != state2[i]) {
			return false;
		}
	}
	return true;
}

// fungsi untuk mengisi array tertentu dengan value (0)
void fill(int board[][N], int value)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = value;
		}
	}
}


int calculateObjective(int board[][N], int* state)
{
	// pengecekan pada setiap posisi queen, memastikan
	// tidak saling serang
	int attacking = 0;

	int row, col;

	for (int i = 0; i < N; i++) {

		// baris [state [i]] posisi ratu
		// pengecekan serangan pada setiap kolom
		// array state (queen)ke kiri secara horizontal
		row = state[i], col = i - 1;
		while (col >= 0
			&& board[row][col] != 1) {
			col--;
		}
		if (col >= 0
			&& board[row][col] == 1) {
			attacking++;
		}

		// pengecekan serangan setiap baris
		// array state (queen) ke kanan secara horizontal
		row = state[i], col = i + 1;
		while (col < N
			&& board[row][col] != 1) {
			col++;
		}
		if (col < N
			&& board[row][col] == 1) {
			attacking++;
		}

		// pengecekan serangan setiap baris
		// array state (queen) ke kiri atas secara diagonal
		row = state[i] - 1, col = i - 1;
		while (col >= 0 && row >= 0
			&& board[row][col] != 1) {
			col--;
			row--;
		}
		if (col >= 0 && row >= 0
			&& board[row][col] == 1) {
			attacking++;
		}

		// pengecekan serangan setiap baris
		// array state (queen) ke kanan bawah secara diagonal
		row = state[i] + 1, col = i + 1;
		while (col < N && row < N
			&& board[row][col] != 1) {
			col++;
			row++;
		}
		if (col < N && row < N
			&& board[row][col] == 1) {
			attacking++;
		}

		// pengecekan serangan setiap baris
		// array state (queen) ke kiri bawah secara diagonal
		row = state[i] + 1, col = i - 1;
		while (col >= 0 && row < N
			&& board[row][col] != 1) {
			col--;
			row++;
		}
		if (col >= 0 && row < N
			&& board[row][col] == 1) {
			attacking++;
		}

		// pengecekan serangan setiap baris
		// array state (queen) ke kanan atas secara diagonal
		row = state[i] - 1, col = i + 1;
		while (col < N && row >= 0
			&& board[row][col] != 1) {
			col++;
			row--;
		}
		if (col < N && row >= 0
			&& board[row][col] == 1) {
			attacking++;
		}
	}

	// Return pairs.
	return (int)(attacking / 2);
}

// generate board secara random
void generateBoard(int board[][N], int* state){
	fill(board, 0);
	for (int i = 0; i < N; i++) {
		board[state[i]][i] = 1;
	}
}

void copyState(int* state1, int* state2)
{
	for (int i = 0; i < N; i++) {
		state1[i] = state2[i];
	}
}

// mendapatkan neighbour dengan objective value paling sedikit
// well as the current state.
void getNeighbour(int board[][N], int* state){
	// pembuatan board dan state optimal
	// board saat ini sebagai starting poin

	int opBoard[N][N];
	int opState[N];

	copyState(opState, state);
	generateBoard(opBoard, opState);

	// Initializing the optimal
	// objective value

	int opObjective = calculateObjective(opBoard, opState);

	// pembuatan board dan state sementara

	int NeighbourBoard[N][N];
	int NeighbourState[N];

	copyState(NeighbourState,
			state);
	generateBoard(NeighbourBoard,
				NeighbourState);

	// Iterating through all
	// possible neighbours
	// of the board.

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			// Condition for skipping the
			// current state

			if (j != state[i]) {

				// Initializing temporary
				// neighbour with the
				// current neighbour.

				NeighbourState[i] = j;
				NeighbourBoard[NeighbourState[i]][i] = 1;
				NeighbourBoard[state[i]][i] = 0;

				// Calculating the objective
				// value of the neighbour.

				int temp = calculateObjective(
						NeighbourBoard, NeighbourState);

				// komparasi neighbour optimal dan sementara
				// jika _sementara_ lebih sedikit
				// menjadi nilai optimal.

				if (temp <= opObjective) {
					opObjective = temp;
					copyState(opState, NeighbourState);
					generateBoard(opBoard, opState);
				}

				// Going back to the original
				// configuration for the next
				// iteration.

				NeighbourBoard[NeighbourState[i]][i] = 0;
				NeighbourState[i] = state[i];
				NeighbourBoard[state[i]][i] = 1;
			}
		}
	}

	// optimal board n state yang ditemukan,
	// dipindah ke current

	copyState(state, opState);
	fill(board, 0);
	generateBoard(board, state);
}

void localSearchHC(int board[][N], int* state){

	// current board n state sebagai starting point
	// lalu neoghbour board n state
	int neighbourBoard[N][N] = {};
	int neighbourState[N];
	copyState(neighbourState, state);
	generateBoard(neighbourBoard,
				neighbourState);
	do {
		// neighbour menjadi current,
		// copy state dan board ke current
		copyState(state, neighbourState);
		generateBoard(board, state);
		// Getting the optimal neighbour
		getNeighbour(neighbourBoard, neighbourState);
		if (compareStates(state, neighbourState)) {
			// If neighbour and current are
			// equal then no optimal neighbour
			// exists and therefore output the
			// result and break the loop.
			printBoard(board);
			break;
		}
		else if (calculateObjective(board, state) == 
			calculateObjective(neighbourBoard, neighbourState)) {
			// If neighbour and current are
			// not equal but their objectives
			// are equal then we are either
			// approaching a shoulder or a
			// local optimum, in any case,
			// jump to a random neighbour
			// to escape it.

			// Random neighbour
			neighbourState[rand() % N] = rand() % N;
			generateBoard(neighbourBoard, neighbourState);
		}

	} while (true);
}

int main()
{

	int state[N] = {};
	int board[N][N] = {};

	RandomConfiguration(board, state);

	// local search pada board
	localSearchHC(board, state);

	return 0;
}
