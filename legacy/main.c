#include <stdio.h>

/*Board Representation*/

#define WHITE 0
#define BLACK 1

#define PAWN 0
#define KNIGHT 1
#define BISHOP 2
#define ROOK 3
#define QUEEN 4
#define KING 5
#define EMPTY 6

#define VALUE_PAWN 100
#define VALUE_KNIGHT 300
#define VALUE_BISHOP 300
#define VALUE_ROOK 500
#define VALUE_QUEEN 900
#define VALUE_KING 10000

#define CHECKMATE 10000

#define ONE_RANK 8
#define TWO_RANKS 16 
#define UP -8
#define DOWN 8
#define RIGHT 1
#define LEFT -1
#define UP_RIGHT (UP + RIGHT)
#define UP_LEFT (UP + LEFT)
#define DOWN_RIGHT (DOWN + RIGHT)
#define DOWN_LEFT (DOWN + LEFT)

#define COL(index) ((index)&7)
#define ROW(index) (((unsigned)index)>>3)

int init_piece_position[64] = 
{
    ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK,
    PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 
    PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN,
    ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK
};

int piece_position[64];

int init_color_position[64] = 
{
    BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, 
    BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, 
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 
    WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 
    WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE
};

int color_position[64];

int side_to_move;

/*Move Generation*/

int generate_moves(int current_side)
{
    int i, j, k, row, col, other_side, move_count;
    move_count = 0;
    if (current_side == WHITE) {
        other_side = BLACK;
    } else {
        other_side = WHITE;
    }

    for (i = 0; i < 64; i++)
    {
        row = ROW(i);
        col = COL(i);
        if (color_position[i] == current_side)
        {
            switch (piece_position[i])
            {
            case PAWN:
                printf(" pawn");
                printf("(%d, %d)", row, col);

                if (current_side == BLACK)
                {
                    /* Checking normal pawn moves */
                    if (color_position[i + DOWN] == EMPTY)
                    {
                        printf("+1");
                        move_count++;
                    }
            
                    /* Checking starting pawn double moves */
                    if (row == 1 && color_position[i + DOWN] == EMPTY && color_position[i + (2 * DOWN)] == EMPTY)
                    {
                        printf("+1");
                        move_count++;
                    }
            
                    /* Checking pawn capturing moves */
                    if (col && color_position[i + DOWN_LEFT] == WHITE)
                    {
                        printf("+1");
                        move_count++;
                    }
                    if (col < 7 && color_position[i + DOWN_RIGHT] == WHITE)
                    {
                        printf("+1");
                        move_count++;
                    }
                } else {
                    if (color_position[i + UP] == EMPTY)
                    {
                        printf("+1");
                        move_count++;
                    }
                    if (row == 6 && color_position[i + UP] == EMPTY && color_position[i + (2 * UP)] == EMPTY)
                    {
                        printf("+1");
                        move_count++;
                    }
                    if (col && color_position[i + UP_LEFT] == BLACK)
                    {
                        printf("+1");
                        move_count++;
                    }
                    if (col < 7 && color_position[i + UP_RIGHT] == BLACK)
                    {
                        printf("+1");
                        move_count++;
                    }
                }
                break;

            case KNIGHT:
                printf(" knight");
                printf("(%d, %d)", row, col);

                /* Checking downward knight moves */
                if (col < 7 && row < 6 && (color_position[i + (2 * DOWN) + RIGHT] != current_side))
                {
                    printf("+1");
                    move_count++;
                }
                if (col && row < 6 && (color_position[i + (2 * DOWN) + LEFT] != current_side))
                {
                    printf("+1");
                    move_count++;
                }
                if (col < 6 && row < 7 && (color_position[i + DOWN + (2 * RIGHT)] != current_side))
                {
                    printf("+1");
                    move_count++;
                }
                if (col > 1 && row < 7 && (color_position[i + DOWN + (2 * LEFT)] != current_side))
                {
                    printf("+1");
                    move_count++;
                }

                /* Checking upward knight moves */
                if (col < 7 && row > 1 && (color_position[i + (2 * UP) + RIGHT] != current_side))
                {
                    printf("+1");
                    move_count++;
                }
                if (col && row > 1 && (color_position[i + (2 * UP) + LEFT] != current_side))
                {
                    printf("+1");
                    move_count++;
                }
                if (col < 6 && row && (color_position[i + UP + (2 * RIGHT)] != current_side))
                {
                    printf("+1");
                    move_count++;
                }
                if (col > 1 && row && (color_position[i + UP + (2 * LEFT)] != current_side))
                {
                    printf("+1");
                    move_count++;
                }
                break;

            case QUEEN:
                printf(" queen");
                printf("(%d, %d)", row, col);

            case BISHOP:
                printf(" bishop");
                printf("(%d, %d)", row, col);

                /* Down and left bishop moves */
                for (j = 1; j < 8; j++)
                {
                    if (col > (j - 1) && row < (8 - j) && (color_position[i + (j * DOWN_LEFT)] == EMPTY))
                    {
                        printf("+1");
                        move_count++;
                    } else if (col > (j - 1) && row < (8 - j) && color_position[i + (j * DOWN_LEFT)] == other_side) {
                        printf("+1");
                        move_count++;
                        break;
                    } else {
                        break;
                    }
                }
                
                /* Down and right bishop moves */
                for (j = 1; j < 8; j++)
                {
                    if (col < (8 - j) && row < (8 - j) && (color_position[i + (j * DOWN_RIGHT)] == EMPTY))
                    {
                        printf("+1");
                        move_count++;
                    } else if (col < (8 - j) && row < (8 - j) && color_position[i + (j * DOWN_RIGHT)] == other_side) {
                        printf("+1");
                        move_count++;
                        break;
                    } else {
                        break;
                    }
                }
            
                /* Up and left bishop moves */
                for (j = 1; j < 8; j++)
                {
                    if (col > (j - 1) && row > (j - 1) && (color_position[i + (j * UP_LEFT)] == EMPTY))
                    {
                        printf("+1");
                        move_count++;
                    } else if (col > (j - 1) && row > (j - 1) && color_position[i + (j * UP_LEFT)] == other_side) {
                        printf("+1");
                        move_count++;
                        break;
                    } else {
                        break;
                    }
                }
            
                /* Up and right bishop moves */
                for (j = 1; j < 8; j++)
                {
                    if (col < (8 - j) && row > (j - 1) && (color_position[i + (j * UP_RIGHT)] == EMPTY))
                    {
                        printf("+1");
                        move_count++;
                    } else if (col < (8 - j) && row > (j - 1) && color_position[i + (j * UP_RIGHT)] == other_side) {
                        printf("+1");
                        move_count++;
                        break;
                    } else {
                        break;
                    }
                }

                if (piece_position[i] == BISHOP)
                {
                    break;
                }

            case ROOK:
                printf(" rook");
                printf("(%d, %d)", row, col);

                /* Down rook moves */
                for (k = 1; k < 8; k++)
                {
                    if (row < (8 - k) && (color_position[i + (k * DOWN)] == EMPTY))
                    {
                        printf("+1");
                        move_count++;
                    } else if (row < (8 - k) && color_position[i + (k * DOWN)] == other_side) {
                        printf("+1");
                        move_count++;
                        break;
                    } else {
                        break;
                    }
                }

                /* Up rook moves */
                for (k = 1; k < 8; k++)
                {
                    if (row > (k - 1) && (color_position[i + (k * UP)] == EMPTY))
                    {
                        printf("+1");
                        move_count++;
                    } else if (row > (k - 1) && color_position[i + (k * UP)] == other_side) {
                        printf("+1");
                        move_count++;
                        break;
                    } else {
                        break;
                    }
                }

                /* Left rook moves*/
                for (k = 1; k < 8; k++)
                {
                    if (col > (k - 1) && (color_position[i + (k * LEFT)] == EMPTY))
                    {
                        printf("+1");
                        move_count++;
                    } else if (col > (k - 1) && color_position[i + (k * LEFT)] == other_side) {
                        printf("+1");
                        move_count++;
                        break;
                    } else {
                        break;
                    }
                }

                /* Right rook moves */
                for (k = 1; k < 8; k++)
                {
                    if (col < (8 - k) && (color_position[i + (k * RIGHT)] == EMPTY))
                    {
                        printf("+1");
                        move_count++;
                    } else if (col < (8 - k) && color_position[i + (k * RIGHT)] == other_side) {
                        printf("+1");
                        move_count++;
                        break;
                    } else {
                        break;
                    }
                }
                
                break;

            case KING:
                printf(" king");
                printf("(%d, %d)", row, col);

                /* Downward king moves */
                if (row < 7 && (color_position[i + DOWN] != current_side))
                {
                    printf("+1");
                    move_count++;
                }

                /* Upward king moves */
                if (row && (color_position[i + UP]) != current_side)
                {
                    printf("+1");
                    move_count++;
                }

                /* Left king moves */
                if (col && (color_position[i + LEFT] != current_side))
                {
                    printf("+1");
                    move_count++;
                }

                /* Right king moves */
                if (col < 7 && (color_position[i + RIGHT]) != current_side)
                {
                    printf("+1");
                    move_count++;
                }

                /* Down left king moves */
                if (row < 7 && col && (color_position[i + DOWN_LEFT] != current_side))
                {
                    printf("+1");
                    move_count++;
                }

                /* Down right king moves */
                if (row < 7 && col < 7 && (color_position[i + DOWN_RIGHT]) != current_side)
                {
                    printf("+1");
                    move_count++;
                }

                /* Up left king moves */
                if (row && col && (color_position[i + UP_LEFT] != current_side))
                {
                    printf("+1");
                    move_count++;
                }

                /* Up right king moves */
                if (row && col < 7 && (color_position[i + UP_RIGHT]) != current_side)
                {
                    printf("+1");
                    move_count++;
                }

                break;
            
            default:
                break;
            }
        }
    }
    return move_count;
}

int main(void)
{
    side_to_move = WHITE;
    
    for (int i = 0; i < 64; i++) {
        piece_position[i] = init_piece_position[i];
        color_position[i] = init_color_position[i];
    }

    int total_moves = generate_moves(side_to_move);

    printf("Total Moves = %d", total_moves);

    return 0;
}