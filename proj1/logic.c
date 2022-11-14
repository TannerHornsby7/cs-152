/*
Gameplay Summary

To sum up the gameplay: players take alternating turns. In a turn, a given
player either drops one piece in any non-full column, dropping it as low as
it can go, or turns on their magnet. Magnets only slide pieces of one color,
and only in that color's direction (right for white, left for black). Pieces
defy gravity while the magnet is on, but eventually drop after the magnet
turns off. The Maglock interval defines for how long they stay on, and this
interval is the number of turns, after the one in which the magnet is turned
on, the player loses as a result. It is at the end of that player's last
missed turn that their pieces fall. Opponent pieces held up by those pieces
would also fall at this time. The Maglock interval in the depicted game was
2. The objective of the game is to get a number of pieces of your color in
a square of a configured dimension, here 2.
*/

/*
Magnet Move

To be clear, the properties of turning on a magnet are precisely defined:
all the pieces of the specific color stay within their row and move as
far as they can in the appropriate direction, with no falling. After
this transformation has been completed, then, gravity takes effect,
and any unsupported pieces belonging to the other color fall downwards.

When a player turns on a magnet, it stays on for the Maglock interval;
this represents how many turns the player loses while the magnet remains
on. So, in this game, the Maglock interval happens to be long enough that
white misses a couple of turns and black can play repeatedly. This is in
recognition of the fact that turning on a magnet is a potentially powerful
move and should have somme disadvantage to balance against it.
*/