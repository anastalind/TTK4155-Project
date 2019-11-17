/** @file PLAY_GAME.h
 *  @brief Header-file for playing the Ping-Pong game.
 *  @authors: Anastasia Lindbäck and Marie Skatvedt
 */

#ifndef PLAY_GAME_H
#define PLAY_GAME_H

#define MAX_MISSES 3

// Global flag interrupt for detecting number of misses
extern int GAME_OVER;


/** Controlling the game based on states. 
 */
void game_controller(void);

/** Initialize necessary functions for playing the game.
 */
void play_game_initialize(void);   

/** Function for playing the ping-pong game. State = Playing.
 */
void play_game(void);

/** Function for ending the ping-pong game. State = Game over. Neutral behaviour.
 */
void end_game(void);



#endif 