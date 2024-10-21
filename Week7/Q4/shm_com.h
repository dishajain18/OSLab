#define TEXT_SZ 2048
struct shared_use_st {
int whose_turn;
char matrix[3][3];
char who_won;
};

void print_matrix(char matrix[][3])
{
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
      printf("%c ",matrix[i][j]);
    printf("\n");
  }
}

char check_winner(char matrix[][3]) {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (matrix[i][0] != '*' && matrix[i][0] == matrix[i][1] && matrix[i][1] == matrix[i][2]) {
            return matrix[i][0]; // Return the winning character
        }
    }

    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (matrix[0][i] != '*' && matrix[0][i] == matrix[1][i] && matrix[1][i] == matrix[2][i]) {
            return matrix[0][i]; // Return the winning character
        }
    }

    // Check diagonals
    if (matrix[0][0] != '*' && matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2]) {
        return matrix[0][0]; // Return the winning character
    }

    if (matrix[0][2] != '*' && matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0]) {
        return matrix[0][2]; // Return the winning character
    }

    // No winner
    return '*'; // Indicates no winner
}

