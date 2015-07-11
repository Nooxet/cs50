/**
 * bounce.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Bounces a circle back and forth in a window.
 */

// standard libraries
#include <stdio.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

int main(void)
{
    // instantiate window
    GWindow window = newGWindow(320, 240);

    // instantiate circle
    GOval circle = newGOval(0, 110, 20, 20);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    add(window, circle);
    
    /*
    GOval circle2 = newGOval(0, 55, 30, 30);
    setColor(circle2, "RED");
    setFilled(circle2, true);
    add(window, circle2);
    */
    
    // initial velocity
    double velocity = 2.0;
    double vel2 = 3.6;
    
    // bounce forever
    while (true)
    {
        // move circle along x-axis
        move(circle, velocity, vel2);
        
        
        if (getY(circle) + getHeight(circle) >= getHeight(window))
        {
            vel2 = -vel2;
            
        } else if (getY(circle) <=0)
        {
            vel2 = -vel2;
        }

        // bounce off right edge of window
        if (getX(circle) + getWidth(circle) >= getWidth(window))
        {
            velocity = -velocity;
        }

        // bounce off left edge of window
        else if (getX(circle) <= 0)
        {
            velocity = -velocity;
        }

        // linger before moving again
        pause(10);
    }
}
