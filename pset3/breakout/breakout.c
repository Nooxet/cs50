
/**
 * breakout.c
 *
 * Jonathan Sonnerup
 * Nooxet@gmail.com
 *
 * An implementation of the game Breakout
 */

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// width of paddle
#define PADDLE_W 50
#define PADDLE_H 7

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
double generateXVel(double y_vel);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GLabel initLivesLabel(GWindow window, int lives);
void updateLivesLabel(GLabel label, int lives);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    double paddle_y = getY(paddle);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel scoreb = initScoreboard(window); 

    // instantiate lives label
    GLabel lives_label = initLivesLabel(window, LIVES);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // velocity of the ball
    double y_vel = 0.5;
    double x_vel = generateXVel(y_vel);

    // click to start the game
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        GEvent event = getNextEvent(MOUSE_EVENT);

        if (event != NULL)
        {
            // move the paddle along with the mouse
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event);
                // check if paddle will be inside window
                if (x < WIDTH - PADDLE_W && x >= 0)
                {
                    setLocation(paddle, x, paddle_y);
                }
            }
        }

        // ball movement
        move(ball, x_vel, y_vel);

        // bounce off left edge
        if (getX(ball) <= 0)
        {
            x_vel = -x_vel;
        }
        // bounce off right edge
        else if (getX(ball) >= (getWidth(window) - getWidth(ball)))
        {
            x_vel = -x_vel;
        }

        // bounce off top edge
        if (getY(ball) <= 0)
        {
            y_vel = -y_vel;
        }
        // player looses a life
        else if (getY(ball) >= (getHeight(window) - getHeight(ball)))
        {
            // update the life label, reducing number of lives
            updateLivesLabel(lives_label, --lives);

            // restore ball's position
            setLocation(ball, WIDTH / 2 - RADIUS, HEIGHT / 2);
            waitForClick();

            // generate a new x-velocity
            x_vel = generateXVel(y_vel);
        }

        GObject obj = detectCollision(window, ball);

        // collision detected
        if (obj != NULL)
        {    
            // collided with paddle
            if (obj == paddle)
            {
                // only bounce on downward movement
                if (y_vel > 0)
                {
                    // bounce off paddle
                    y_vel = -y_vel;
                }
            } 
            // collided with bricks
            else if (strcmp(getType(obj), "GRect") == 0)
            {
                // bounce off brick
                y_vel = -y_vel;

                // remove the brick
                removeGWindow(window, obj);
                bricks--;

                // update player score
                updateScoreboard(window, scoreb, ++points);
            }
        }

        pause(1);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    GRect brick;

    char *colors[] = {"RED", "ORANGE", "YELLOW", "GREEN", "CYAN", 
        "PINK", "MAGENTA", "BLUE"};

    // space between bricks, 10% of the width of brick
    int space = (WIDTH / COLS) / 10;
    int brick_w = WIDTH / COLS - 2 * space;
    int brick_h = 8;
    int offset = 50;

    // keep track of bricks
    int curr;
    for (int i = 0; i < ROWS; i++)
    {
        curr = 0;
        for (int j = 0; j < COLS; j++)
        {
            // space before brick
            curr += space;
            brick = newGRect(curr, 2 * brick_h * i + offset, brick_w, brick_h);
            setColor(brick, colors[i]);
            setFilled(brick, true);
            // width of brick + space
            curr += brick_w + space;
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH / 2 - RADIUS, HEIGHT / 2, 
            2 * RADIUS, 2 * RADIUS);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Generate a random velocity for the x-direction.
 * Depends on velocity in y-direction to prevent too large
 * or too small angles.
 */
double generateXVel(double y_vel)
{
    double x_vel = drand48() * y_vel;

    while (x_vel < y_vel / 2 || x_vel > (4 * y_vel / 5.0))
    {
        x_vel = drand48() * y_vel;
    }

    // randomize the sign
    if (drand48() > 0.5)
    {
        x_vel = -x_vel;
    }

    return x_vel;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(WIDTH / 2 - PADDLE_W / 2, 7 * HEIGHT / 8, 
            PADDLE_W, PADDLE_H);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel scoreb = newGLabel("");
    setFont(scoreb, "SansSerif-36");
    setColor(scoreb, "LIGHT_GRAY");
    add(window, scoreb);

    updateScoreboard(window, scoreb, 0);

    return scoreb;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Instantiates, configures, and returs label for lives.
 */
GLabel initLivesLabel(GWindow window, int lives)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-20");
    setColor(label, "LIGHT_GRAY");
    add(window, label);

    updateLivesLabel(label, lives);

    return label;
}

/**
 * Updates lives' label, keeping it at the top left in the window.
 */
void updateLivesLabel(GLabel label, int lives)
{
    char l[19];
    sprintf(l, "Lives: %i", lives);
    setLabel(label, l);

    setLocation(label, 20.0, 30.0);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
