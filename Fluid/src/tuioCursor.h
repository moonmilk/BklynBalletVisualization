#ifndef TUIOCURSOR_H_INCLUDED
#define TUIOCURSOR_H_INCLUDED

class tuioCursor {
public:
	int s;			// sequence #
	float x, y;		// position
	float dx, dy;	// movement
	float m;		// acceleration

	// not from message packet
	int age;		// # of frames since last updated

};

#endif // TUIOCURSOR_H_INCLUDED
