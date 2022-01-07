#pragma once

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) >(Y)) ? (X) : (Y))

#define TO_KB(X) (X / 1024)

// Represents a single point on screen
struct Point {
	unsigned int X;
	unsigned int Y;
};