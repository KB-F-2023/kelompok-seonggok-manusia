#include<iostream>
#define N 8
using namespace std;

int Queens = 0;
int sols = 0;
int board[N][N];
int limout=0;

void searchCol(int col) {
    if(Queens >= N) {
        if (limout<1){
            cout<<"one of the solution pattern:\n"<<endl;
         for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
				if ((board[i][j])==1){
					cout<<"Q ";
				}
				else cout<<"* ";
                }
            cout << "\n";
        }
        cout << "\n";
        limout++;}
        sols++;
        return;
    }

    for(int i = 0; i < N; i++) {
        //tidak bertabrakan
        if(board[i][col] > -1) {
            //mark pada lokasi queen dan jalurnya
            board[i][col] = 1;
            for(int j = 0; j < N; j++) {
                if(j != col) board[i][j]--;
                if(j != i) board[j][col]--;
            }
            for(int j = 1; j < N; j++) {
                if(i - j >= 0 && col - j >= 0) board[i - j][col - j]--;
                if(i + j < N && col + j < N) board[i + j][col + j]--;
                if(i - j >= 0 && col + j < N) board[i - j][col + j]--;
                if(i + j < N && col - j >= 0) board[i + j][col - j]--;
            }

            Queens++;
            searchCol(col + 1);
            
        //pembersihan papan
            board[i][col] = 0;
            for(int j = 0; j < N; j++) {
                if(j != col) board[i][j]++;
                if(j != i) board[j][col]++;
            }
            for(int j = 1; j < N; j++) {
                if(i - j >= 0 && col - j >= 0) board[i - j][col - j]++;
                if(i + j < N && col + j < N) board[i + j][col + j]++;
                if(i - j >= 0 && col + j < N) board[i - j][col + j]++;
                if(i + j < N && col - j >= 0) board[i + j][col - j]++;
            }
            Queens--;
        }
    }
}

int main() {
   

    searchCol(0);

    cout << "amount of available solution: "<<sols<<endl;
    return 0;
}