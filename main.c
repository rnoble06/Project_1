/* ECEC-201 - Ryan Noble - rdn39 */

#include <unistd.h>   /* both of these are  */
#include <termios.h>  /* for get_keypress() */

#include <stdio.h>

/* Useful Constants:
 *   -- The house is 69 characters wide
 *   -- The house is 26 characters high
 *   -- Each window interior is 11 characters wide
 *   -- Each window interior is 3 character high
 */
#define HOUSE_WIDTH   69
#define HOUSE_HEIGHT  26
#define WINDOW_WIDTH  11
#define WINDOW_HEIGHT  3


/* Reads a keypress from the keyboard and returns the
 * corresponding character.
 *
 *   This is necessary because scanf() misbehaves inside of looping
 *   constructs.  You do not need to understand how this function works.
 *   Just use this function as a tool.
 *
 * Return Value:
 *   The character corresponding to the key pressed on the keyboard.
 */
static char get_keypress ()
{
    struct termios t;
    char ret;

    static int init = 0;

    if (!init) {
        init = 1;
        tcgetattr(STDIN_FILENO, &t);
        t.c_lflag &= ~ICANON;
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
    }

    ret = (char)getchar();
    printf("\n");

    return ret;
}


/* Updates the graphics for the window @ coordinates (x, y) to match the
 * `state` array.
 *
 *   This function modifies the `house` array by updating the characters
 *   inside the window located at the zero indexed coordinates (x, y) to
 *   match the window's state in the `state` array.  If the window's
 *   state is 1, then the window is filled with the '#' character.
 *   Likewise, if the window's state is 0 in the `state` array, the
 *   window is filled with the ' ' character.
 *
 * Parameters:
 *   house -- pointer to characters representing the house
 *
 *   state -- pointer to the game state array
 *
 *       x -- the horizontal coordinate of the window for which the
 *            state will be updated (zero indexed, with 0 being
 *            the left column and 2 being the right column)
 *
 *       y -- the vertical coordinate of the window for which the
 *            state will be updated (zero indexed, with 0 being
 *            the top row and 2 being the bottom row)
 */
static void window_update_graphics (char *house, const int *state, int x, int y)
{
    /* Step 1: Write this function! */
    
    /* check window
       check state
       apply graphics */
  
  int i;
  int j;

  switch (3*y+x) /* pick variable for window chosen */
  {
    case 0:
    i = 11;
    j = 8;
    break;

    case 1:
    i = 29;
    j = 8;
    break;

    case 2:
    i = 47;
    j = 8;
    break;

    case 3:
    i = 11;
    j = 14;
    break;

    case 4:
    i = 29;
    j = 14;
    break;

    case 5:
    i = 47;
    j = 14;
    break;

    case 6:
    i = 11;
    j = 20;
    break;

    case 7:
    i = 29;
    j = 20;
    break;

    case 8:
    i = 47;
    j = 20;
    break;

  } /* End of Switch-Case */

  if (state[3*y+x] == 0) /* operate on selected window with variables chosen from switch-case */
  {
    int k = j;
    int l = i;
    while (j < k +3)
      {
        i=l;
        while (i < l + 11)
        {
          house[j*HOUSE_WIDTH + i]= ' ';
          i++;
        }
        j++;
      }
  }
  else
  {
    int k = j;
    int l = i;
    while (j < k +3)
      {
        i=l;
        while (i < l + 11)
        {
          house[j*HOUSE_WIDTH + i]= '#';
          i++;
        }
        j++;
      }
  }

}


/* Toggles the state of the window @ coordinates (x, y) in the game
 * state array.
 *
 *   This function modifies the `state` array by toggling the value
 *   corresponding to the window at the provided coordinates (x, y).  If
 *   the current value is 1, then it will be toggled to 0.  Likewise, if
 *   the current value is 0, then it will be toggled to 1.
 *
 * Parameters:
 *   state -- pointer to the game state array
 *
 *       x -- the horizontal coordinate of the window for which the
 *            state will be updated (zero indexed, with 0 being
 *            the left column and 2 being the right column)
 *
 *       y -- the vertical coordinate of the window for which the
 *            state will be updated (zero indexed, with 0 being
 *            the top row and 2 being the bottom row)
 */
static void window_toggle_state (int *state, int x, int y)
{
    /* Step 2: Write this function! */
   switch (state[3*y+x]) /* switch value in state based on window selected */
    {
      case 0:
      state[3*y+x] = 1;
      break;
      case 1:
      state[3*y+x] = 0;
      break;
    }

}


/* Toggles the state and, correspondingly, updates the graphics for the
 * window @ coordinates (x, y).
 *
 *   Given the zero indexed coordinates (x, y) of a window, this
 *   function ensures that the corresponding element in the game state
 *   array is toggled appropriately and that the graphics corresponding
 *   to that window are updated appropriately to reflect the new state.
 *
 *   Hint: call other functions you have written to make this easier.
 *
 * Parameters:
 *   state -- pointer to the game state array
 *
 *   house -- pointer to characters representing the house
 *
 *       x -- the horizontal coordinate of the window for which the
 *            state will be updated (zero indexed, with 0 being
 *            the left column and 2 being the right column)
 *
 *       y -- the vertical coordinate of the window for which the
 *            state will be updated (zero indexed, with 0 being
 *            the top row and 2 being the bottom row)
 */
static void window_update (int *state, char *house, int x, int y)
{
    /* Step 2: Write this function! */

    window_toggle_state (state, x, y);

    window_update_graphics (house, state, x, y);


}


/* Toggles the lights based on the user's window selection.
 *
 *   Given the user's choice of window number, this function updates the
 *   corresponding window's (or windows') state and graphics, as
 *   necessary.
 *
 *   Hints:
 *     -- A primary job of this function will be to convert the choice
 *        of the user into the zero indexed (x, y) coordinates of a
 *        window.
 *
 *     -- Converting between `choice` and the (x, y) coordinates will
 *        probably be easier if you internally number the windows
 *        starting at zero (i.e. 0 thru 8 instead of 1 thru 9).
 *
 *     -- This function will need to call one other function
 *        (perhaps multiple times).
 *
 *   While completing Step 2, this function will only toggle the window
 *   corresponding to the user's selection.  For Step 3, this function
 *   will toggle the selected window and its neighbors (as described
 *   above in the instructions).
 *
 * Parameters:
 *    state -- pointer to the game state array
 *
 *    house -- pointer to characters representing the house
 *
 *   choice -- integer corresponding to the user's window selection
 *             (an integer value within the range 1 to 9)
 */
static void window_toggle (int *state, char *house, int choice)
{
    /* Step 2: Write this function! (for single window toggle) */

    int x = (choice - 1) % 3; 
    int y = (choice - x) / 3;
    window_update( state, house, x, y);

    /* Step 3: Rewrite this function! (for multi-window toggle) */
    /* in addition to selected window, adjacent windows also operated on */
    if (choice == 1 )
    {
      choice = 2;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 4;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);
    }
    else if (choice == 2)
    {
      choice = 1;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 3;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 5;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);
    }
    else if (choice == 3)
    {
      choice = 2;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 6;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);
    }
    else if (choice == 4)
    {
      choice = 1;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 5;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 7;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);
    }

    else if (choice == 5)
    {
      choice = 2;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 4;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 6;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 8;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

    }
    else if (choice == 6)
    {
      choice = 3;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 5;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 9;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);
    }
    else if (choice == 7)
    {
      choice = 4;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 8;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);
    }
    else if (choice == 8)
    {
      choice = 5;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 7;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 9;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);
    }
    else if (choice == 9)
    {
      choice = 6;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);

      choice = 8;
      x = (choice - 1) % 3;
      y = (choice - x) / 3;
      window_update( state, house, x, y);
    }

}


/* Checks if all lights have been turned off.
 *
 *   Iterates through the game state array and returns 1 if all of the
 *   lights have been successfully turned off; otherwise returns 0.
 *
 * Parameters:
 *   state -- pointer to the game state array
 *
 * Return Values:
 *   1 if all lights have been turned off; 0 otherwise.
 */
static int solved (const int *state)
{
    /* Step 4: Rewrite this function! */
    int i = 0;
    while (state[i] != 1)
    {
      if (i==8)
      return 1;
      i++;
    }
    return 0;

}


/* Prints the characters in the house array to the screen
 *
 * Parameters:
 *   house -- pointer characters representing the house
 */
static void house_display (const char *house)
{
    int x, y;

    for (y=0; y<HOUSE_HEIGHT; y++, printf("\n"))
        for (x=0; x<HOUSE_WIDTH; x++)
            printf ("%c", house[HOUSE_WIDTH * y + x]);
}


/* Initializes the graphics for each of the 9 windows.
 *
 *   Cycles through the 9 windows and fills each window in the `house`
 *   array of chars with either ' ' or '#' characters depending on the
 *   current state of the window in the state array by calling
 *   `window_update_graphics()` for each window individually.
 *
 * Parameters:
 *   house -- pointer to characters representing the house
 *
 *   state -- pointer to the game state array
 */
static void house_init (char *house, const int *state)
{
    int x, y;

    for (y=0; y<3; y++)
        for (x=0; x<3; x++)
            window_update_graphics (house, state, x, y);
}



int main ()
{
    char choice;

    char house[] =
    "                                             ______________          "
    "                                            |______________|         "
    "      _______________________________________|            |_____     "
    "     '                                       |____________|     `    "
    "    |                                                           |    "
    "    '-----------------------------------------------------------'    "
    "    |           1                 2                 3           |    "
    "    |     +-----------+     +-----------+     +-----------+     |    "
    "    |     |           |     |           |     |           |     |    "
    "    |     |           |     |           |     |           |     |    "
    "    |     |           |     |           |     |           |     |    "
    "    |     +-----------+     +-----------+     +-----------+     |    "
    "    |           4                 5                 6           |    "
    "    |     +-----------+     +-----------+     +-----------+     |    "
    "    |     |           |     |           |     |           |     |    "
    "    |     |           |     |           |     |           |     |    "
    "  _ |     |           |     |           |     |           |     |    "
    " |#||     +-----------+     +-----------+     +-----------+     |    "
    " |_||           7                 8                 9           |    "
    "  `-|     +-----------+     +-----------+     +-----------+     |    "
    "    -     |           |     |           |     |           |     |    "
    "    '     |           |     |           |     |           |     |    "
    "    '     |           |     |           |     |           |     |    "
    "   o'     +-----------+     +-----------+     +-----------+     |    "
    "    '                                                           |    "
    "____'___________________________________________________________'____";

    
    /* This will be our initial game state (do not change this!)
     *   [ 1 = Light is ON,  0 = Light is OFF ] */
    int state[] = { 1, 1, 0,
                    1, 1, 0,
                    1, 0, 0 };


    house_init (house, state);

    /* The Game Loop */
    while (1) {
        house_display (house);

        if (solved (state)) {
            printf ("Congratulations!  You won!\n");
            break;
        }

        printf ("Choose a Window (0 to exit): ");
        choice = get_keypress();

        if (choice < '0' || choice > '9') {
            printf ("INVALID SELECTION!\n");
            continue;
        }

        if (choice == '0')
            break;

        /* convert numerical character to corresponding value
           (check the ASCII table if this doesn't make sense) */
        choice -= '0';

        /* update game state & graphics */
        window_toggle (state, house, choice);
    }

    printf ("Goodbye!\n");

    return 0;
}
