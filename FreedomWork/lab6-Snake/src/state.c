#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

#define BUFFER_SZIE 163840

const char DEFAULT_BOARD[][21] = {
    "####################",
    "#                  #",
    "# d>D    *         #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "####################"};

/* Helper function definitions */
static void set_board_at(game_state_t *state, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t *state, unsigned int snum);
static char next_square(game_state_t *state, unsigned int snum);
static void update_tail(game_state_t *state, unsigned int snum);
static void update_head(game_state_t *state, unsigned int snum);

/* Task 1 */
game_state_t *create_default_state()
{
  // TODO: Implement this function.
  game_state_t *game_state = (game_state_t *)malloc(sizeof(game_state_t));
  game_state->num_rows = 18;
  game_state->board = (char **)malloc(sizeof(char *) * game_state->num_rows);
  for (int i = 0; i < game_state->num_rows; i++)
  {
    game_state->board[i] = (char *)malloc(sizeof(char) * 22);
    strcpy(game_state->board[i], DEFAULT_BOARD[i]);
  }
  game_state->board[2][9] = '*';

  game_state->num_snakes = 1;
  game_state->snakes = (snake_t *)malloc(sizeof(snake_t) * game_state->num_snakes);
  game_state->snakes[0].live = true;
  game_state->snakes[0].head_row = 2;
  game_state->snakes[0].head_col = 4;
  game_state->snakes[0].tail_row = 2;
  game_state->snakes[0].tail_col = 2;

  return game_state;
}

/* Task 2 */
void free_state(game_state_t *state)
{
  free(state->snakes);
  state->snakes = NULL;
  for (int i = 0; i < state->num_rows; i++)
  {
    free(state->board[i]);
    state->board[i] = NULL;
  }

  free(state->board);
  state->board = NULL;
  free(state);
  state = NULL;

  return;
}

/* Task 3 */
void print_board(game_state_t *state, FILE *fp)
{
  for (int i = 0; i < state->num_rows; i++)
  {
    fprintf(fp, "%s\n", state->board[i]);
  }
  return;
}

/*
  Saves the current state into filename. Does not modify the state object.
  (already implemented for you).
*/
void save_board(game_state_t *state, char *filename)
{
  FILE *f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_state_t *state, unsigned int row, unsigned int col)
{
  return state->board[row][col];
}

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_state_t *state, unsigned int row, unsigned int col, char ch)
{
  state->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c)
{
  return c == 'w' || c == 'a' || c == 's' || c == 'd';
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c)
{
  return c == 'W' || c == 'A' || c == 'S' || c == 'D' || c == 'X';
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c)
{
  return is_head(c) || is_tail(c) || c == '^' || c == '<' || c == 'v' || c == '>';
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c)
{
  switch (c)
  {
  case '^':
    return 'w';
  case '<':
    return 'a';
  case 'v':
    return 's';
  case '>':
    return 'd';
  }
  return ' ';
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c)
{
  switch (c)
  {
  case 'W':
    return '^';
  case 'A':
    return '<';
  case 'S':
    return 'v';
  case 'D':
    return '>';
  }
  return ' ';
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c)
{
  if (c == 'v' || c == 's' || c == 'S')
    return cur_row + 1;
  if (c == '^' || c == 'w' || c == 'W')
    return cur_row - 1;
  return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c)
{
  if (c == '>' || c == 'd' || c == 'D')
    return cur_col + 1;
  if (c == '<' || c == 'a' || c == 'A')
    return cur_col - 1;
  return cur_col;
}

/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t *state, unsigned int snum)
{
  snake_t *snake = &state->snakes[snum];
  char head_char = state->board[snake->head_row][snake->head_col];
  unsigned int next_row = get_next_row(snake->head_row, head_char);
  unsigned int next_col = get_next_col(snake->head_col, head_char);
  char next_char = state->board[next_row][next_col];
  return next_char;
}

/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t *state, unsigned int snum)
{
  snake_t *snake = &state->snakes[snum];
  char head_char = state->board[snake->head_row][snake->head_col];
  state->board[snake->head_row][snake->head_col] = head_to_body(head_char);
  snake->head_row = get_next_row(snake->head_row, head_char);
  snake->head_col = get_next_col(snake->head_col, head_char);
  state->board[snake->head_row][snake->head_col] = head_char;
  return;
}

/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_state_t *state, unsigned int snum)
{
  snake_t *snake = &state->snakes[snum];
  char tail_char = state->board[snake->tail_row][snake->tail_col];
  unsigned int next_row = get_next_row(snake->tail_row, tail_char);
  unsigned int next_col = get_next_col(snake->tail_col, tail_char);
  state->board[snake->tail_row][snake->tail_col] = ' ';
  state->board[next_row][next_col] = body_to_tail(state->board[next_row][next_col]);
  snake->tail_row = next_row;
  snake->tail_col = next_col;
  return;
}

/* Task 4.5 */
void update_state(game_state_t *state, int (*add_food)(game_state_t *state))
{
  bool food = false;
  for (unsigned int snum = 0; snum < state->num_snakes; snum++)
  {
    snake_t *snake = &state->snakes[snum];
    if (!snake->live)
      continue;

    char next_char = next_square(state, snum);
    if (next_char == '*')
    {
      food = true;
      update_head(state, snum);
    }
    else if (next_char != ' ' || next_char == '#')
    {
      snake->live = 0;
      state->board[snake->head_row][snake->head_col] = 'x';
    }
    else
    {
      update_head(state, snum);
      update_tail(state, snum);
    }
  }
  if (food)
  {
    add_food(state);
  }

  return;
}

/* Task 5 */
game_state_t *load_board(FILE *fp)
{
  game_state_t *state = (game_state_t *)malloc(sizeof(game_state_t));
  state->num_snakes = 0;
  state->snakes = NULL;
  state->num_rows = 0;
  state->board = (char **)malloc(sizeof(char *));
  char buffer[BUFFER_SZIE];
  while (fgets(buffer, sizeof(buffer), fp) != NULL)
  {
    unsigned int length = strlen(buffer);
    char *data = (char *)malloc(sizeof(char) * length);
    for (int i = 0; i < length - 1; i++)
    {
      data[i] = buffer[i];
    }
    data[length - 1] = '\0';

    state->board = realloc(state->board, sizeof(char *) * (state->num_rows + 1));
    state->board[state->num_rows] = data;
    state->num_rows++;
  }
  return state;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_state_t *state, unsigned int snum)
{
  snake_t *snake = &state->snakes[snum];
  unsigned int head_row = snake->tail_row, head_col = snake->tail_col;
  switch (get_board_at(state, snake->tail_row, snake->tail_col))
  {
  case 'w':
    head_row--;
    break;
  case 'a':
    head_col--;
    break;
  case 's':
    head_row++;
    break;
  case 'd':
    head_col++;
    break;
  default:
    break;
  }
  bool flag = true;
  while (flag)
  {
    switch (get_board_at(state, head_row, head_col))
    {
    case '^':
      head_row--;
      break;
    case '<':
      head_col--;
      break;
    case 'v':
      head_row++;
      break;
    case '>':
      head_col++;
      break;
    default:
      flag = false;
      break;
    }
  }
  snake->head_row = head_row;
  snake->head_col = head_col;

  return;
}

/* Task 6.2 */
game_state_t *initialize_snakes(game_state_t *state)
{
  state->num_snakes = 0;
  state->snakes = (snake_t*) malloc(sizeof(snake_t));
  for (unsigned int row = 0; row < state->num_rows; row++) {
    unsigned int length = strlen(state->board[row]);
    for (unsigned int col = 0; col < length; col++) {
      char c = get_board_at(state, row, col);
      if (c == 'w' || c == 'a' || c == 's' || c == 'd') {
        state->snakes = realloc(state->snakes, sizeof(snake_t) * (state->num_snakes + 1));
        snake_t *snake = &state->snakes[state->num_snakes];
        snake->tail_row = row;
        snake->tail_col = col;
        find_head(state, state->num_snakes);
        snake->live = true;
        state->num_snakes++;
      }
    }
  }
  return state;
}
