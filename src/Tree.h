#pragma once

#include "Global.h"
#include <cstddef>
#include <vector>
#include <iostream>
#include <list>

typedef struct Player{
	int row;
	int col;
	int numFences;
} Player;

//moves of type 'p' are indexed [9][9], moves of type 'f' are [17][9]
typedef struct Move{
	unsigned char type;
	int row;
	int col;
	bool horizontal; //only matters if type = 'f' ie this move places a fence

	Move(unsigned char type, int row, int col, bool horizontal){
		this->type = type;
		this->row = row;
		this->col = col;
		this->horizontal = horizontal;
	}
	Move(){
		this->type = 'u'; //default created, signifies unset, possibly root
	}
} Move;

class StateNode
{
public:
	std::list<StateNode> children;
	StateNode* parent = nullptr;

	
	Move move; //the move directly prior to this state
	Player p1; //player 1, at the bottom of the screen
	Player p2; //player 2, at the top of the screen
	bool turn; //true for it is currently player 1's turn, false for p2
	bool gamestate[2*NUMROWS - 1][NUMCOLS]; //stores every space in between squares where half a wall could be placed, even numbered rows have 8 0s with a -1 at the end
	double score;
	double vi; //average score of every node below this one
	int visits; //number of times we've visited this node
	int ply; //the total number of moves made up until this point.
	unsigned char serial_type; //bookkeeping for serialization/deserialization


	StateNode(bool turn); //should only be used to start a new game, all positions will be starting positions, p1 starts turn=true p2 starts turn=false
	StateNode(StateNode* parent, Move move, int score); //generate a child node, with a reference to the parent and a the move that takes gamestate from parent->child
	StateNode(unsigned char* node_buffer);
	//StateNode(const StateNode& rhs);

	bool operator==(const StateNode& node);


	void evaluate(); //attempts to score a specific gamestate
	int generate_valid_children(); //returns number of valid children generated
	bool is_valid_move(Move move); //checks whether the resulting gamestate from a certain move is legal or not
	bool good_shrub(); //attempts to pick gamestates to be pruned as a heuristic
	int prune_children(); //uses me-defined heuristics to prune children of this node
	void play_out(); //simulates by random choice to determine a winner from this state
	double UCB(); //simple 
	void update_vi(); //calculates average score for every node under this one.

};

std::ostream& operator<<(std::ostream &strm, const StateNode &sn); //print override for StateNode
bool test_and_add_move(std::vector<std::tuple<Move, int>> vmoves, StateNode* state, Move move); //helps testing validity and also beginning scoring before state fully initialized.
