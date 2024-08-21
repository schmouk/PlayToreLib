/*
    GNU GENERAL PUBLIC LICENSE
    Version 3, 29 June 2007

    This is part of library PlayToreLib, a c++ generic library for coding games applications.

    Copyright (C) 2024 Philippe Schmouker, ph.schmouker (at) gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

//===========================================================================
/*
* French Battle is a very simple cards game, named "Bataille" in French.
* 
* No tactics, no strategy, just randomness with very simple rules.  This
* game  is traditionnally the first one played with cards that is tought 
* to French kids.  It gets the tremendeous advantage that kids  get  the
* same opportunities to win as adults get (well, until these cheat).
* 
* This program is proposed in directory examples/playing_cards  to  show
* the  use  of  PlayTore  library code.  A Visual Studio 2022 project is
* available as well to play with.
* 
* Rules of "Bataille" :
* This game is played with a traditionnal deck of 32  or  52  cards,  as
* players wish.  The  deck  is totally distributed between players,  one 
* card after the other, in a clockwise turn.  The  deck  is  distributed 
* with  cards  faces down.  Players are not allowed to look at the faces 
* of the cards they recieve.
* Once all cards have been distributed (some players may  then  get  one
* more  card than others),  each player puts in front of her the card at
* top of their own deck, discovering the  card  face  to  everyone.  The
* stronger face of the card wins all the played cards. Strength of cards 
* is set as: Aces are the strongest, then Kings, then Queens, ...,  then 
* 3's, then 2's.
* 
* It may happen  that  two,  three  of  even  four  players  played  the 
* strongest  card in the round.  This then is a "Bataille"! Each of them
* has to put face down on the table the card at the  top  of  their  own
* deck,  then to put face up,  visible to everyone, the next card at top
* of their own deck.  The strongest card between them  wins  all  played
* cards at this round. If the situation is that a new "Bataille" arises,
* this  processus  is  repeated  again  until one player wins the round.
* The fact is that during "batailles",  players  may  lose  very  strong
* cards.  This is a (dramatic) way Aces may change of owner,  while they
* may change also during battles of Aces, of course.
* 
* The winner of the round collects all the cards played at  this  round, 
* and  puts  them  at the bottom of her own deck, all faces down.  It is 
* recommended to shuffle the won cards before adding them at the  bottom 
* of the player deck.
* 
* Eventually,  some  players  will  lose  all  their  cards.   They  are 
* eliminated  and  the  game continues with remaining players.  The game 
* ends when a player gets all the cards in her own deck. This may take a
* while  before  it  happens.  It  is  common also to stop the game when 
* players agree to.  The winner is then the one who owns the most cards. 
* Then, it may happen that two or more players are the winners.
* 
* Special cases may happen also, which are not that common and generally
* ignored by young players:
* - During a battle, if an involved player gets only one remaining  card
*   in  her own deck,  she has to play it and then loses the battle.  If 
*   ALL involved players just get one remaining card in their own decks,
*   they  all  play it face up and the strongest card wins.  If a battle
*   situation still remains then the game ends,  all  played  cards  are 
*   returned to their initial owners and the final winner is the one who
*   owns the most cards - deuces may happen then.
* - It may be decided also at beginning, between players,  to play for a
*   limited time duration. At completion of this duration, the winner is
*   the player who owns the greatest number of cards.
* - Finally,  and this is never played in real life but it is so easy to 
*   implement  with a computer,  players may agree on a number of rounds
*   after which the game ends.
* 
* The present example of code implements those rules using the  part  of 
* library  PlayTore  dedicated  to  playing cards,  plus the few ones in
* PlayTore core part that are useful for this.  It is provided  to  show
* how  to  use  PlayTore  library  code  for  the purpose of developping
* cards games.  It is coded at the simplest level, with displays done in
* console.  It  uses  a  32 cards deck and 4 players (North, East, South 
* and West) and defaults to a maximum of 100 rounds.  It waits  for  the
* hitting  of  'Enter' key before running the next round.  It is left to 
* you as an exercice to display cards in a graphical environment if  you
* wish and to add more interactions with user at your wish also.
* 
* Notice: this code uses c++20 standard and some of  its  new  concepts.
* We hope this will be of interest to you, and that it will help you get 
* more informed on these concepts.
*/

//===========================================================================
#include <iostream>

#include "decks.h"
#include "gameplay.h"
#include "player.h"


//===========================================================================
int main()
{
    std::cout << "BATAILLE!" << std::endl << std::endl;

    Gameplay the_game;  // the Bataille game instantiation to run

    // starts a new game
    the_game.start_new_game();

    // runs through successive rounds
    the_game.play();

    // prints results
    the_game.print_ranks();

    // bye bye!
    std::cout << std::endl << "Bye bye!" << std::endl << std::endl;

    // end of application
    return 0;
}
