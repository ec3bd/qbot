#include "Tree.h"
#include <cstring>

int save_tree(StateNode* root, std::string database_name);
int recursive_read(StateNode* node, FILE* load_file);

bool write_node(StateNode* node, char file_buffer[], int buffer_index);
int fill_player(char ch[], int offset, Player p);
int fill_move(char ch[], int offset, Move m);
int fill_gamestate(char ch[], int offset, bool gamestate[][NUMCOLS], bool turn);