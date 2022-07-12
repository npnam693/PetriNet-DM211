#ifndef PETRINET_H
#define PETRINET_H

using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

// Create struct Node
struct Node {
    string label;
    bool isTrans;
    int numToken;
    vector<int> preset;
    vector<int> postset;
    Node() : label(""), numToken(0), isTrans(false) {
        preset.clear();
        postset.clear();
    }
    Node(string _label, int _numToken, vector<int> _preset, vector<int> _postset, bool _isTrans = false) :
        label(_label), numToken(_numToken), preset(_preset), postset(_postset), isTrans(_isTrans) {}
};

// Print a marking
void printMarking(vector<Node> pNet) {
    int size = pNet.size(); 
    string msg("[");
    for(int i = 0; i < size; i++) {
        if(pNet[i].isTrans == false) {
            msg += (pNet[i].label + ", ");
        }
    }
    msg.pop_back();
    msg.pop_back();
    msg += "] = [";
    for(int i = 0; i < size; i++) {
        if(pNet[i].isTrans == false) {
            msg += (to_string(pNet[i].numToken) + ", ");
        }
    }
    msg.pop_back();
    msg.pop_back();
    msg += ']';
    cout << msg << endl;
}

// Check condition to fire
bool checkPreset(vector<Node> pNet, int idx) {
    int sizePreset = pNet[idx].preset.size();
    if(sizePreset == 0) return false;
    for(int i = 0; i < sizePreset; i++) {
        if(pNet[pNet[idx].preset[i]].numToken == 0) {
            return false;
        }
    }
    return true;
}

// Update numbers of token
void updateToken(vector<Node>& pNet, int idx) {
    int sizePreset = pNet[idx].preset.size();
    int sizePostset = pNet[idx].postset.size();
    for(int i = 0; i < sizePreset; i++) {
        pNet[pNet[idx].preset[i]].numToken--;
    }
    for(int i = 0; i < sizePostset; i++) {
        pNet[pNet[idx].postset[i]].numToken++;
    }
}

// Clear screen
void clearScreen() {
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
#endif
