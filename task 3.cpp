/*
What was hard?
	The linked lists were a bit of a bothre at first because I forgot to link the first entry to the head and tail, but not the head and tail to the entry, so the program would handle one case correctly but when you added a second one it just
	dissapeared. 
	Getting the colour to show up properly in memory was quite the head-scratcher because everything would show up white. The reason was that I was working with light colours with a black background and a pixel of width. It showed the corect
	colour but all the tiles were indestinguishable by the naked eye. The lab instructions stated that you needed to use the shape class from lab 5 and while I commented out the superclass because I was just using one shape,
	I still tried to use rectangle as much as possible. This eventually ended up with rectangle just drawing the face-down tiles because using vector graphics to fill in a shape is quite counter-productive.
	I eventually settled for the SDL_Rect class and SDL_RenderFillRectangle to show the cursor and face-up tiles. DrawLine could have been used but it would require 70 iterations of drawLine to get to the same place one itteration of
	FillRectangle, so I assume that this is the more efficient way.
	The math that went in to getting the correct movement for the cursor was a bit of a hang-up. It wasn't hard in the end but I simply missed the quite simple solution that I implemented in the end.

What could be improved?
	The cursor not existing at first after flipping two tiles: It is probably a simple fix but I didn't have the time.
	The game not having a victory/game over screen. It would require at least a texture or text to show but learning exactly how these work wasn't the highest on the priority list when the project entered time-crunch mode.
	The game as a whole. I originally wanted to make tetris because beyond being simple, it is also an actually fun game. The problem was that I hit a big snag on task 1 and had to reign in my project to a level where I could finish in time.
	Memory seemed like the easiest sugested game and so I chose that instead;

General feel afterwards:
	It was a fun but stressful project. If it was held before cristmas it might not have been as stressful because you were in the zone from the previous labs, but it was still fun and educational to make a game from (more or less) scratch

How much time?
	I have no idéa if I am to be frank. Could be 40, could be 100, I don't know. I have spent most waking hours trying to pull this together since I came back from cristmas break, and I don't know how much I have been awake.
*/