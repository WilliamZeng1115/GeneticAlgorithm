#pragma once
#include <string>

using namespace std;

class Organism {
private:
	float speed;
	float health;
	float size;
	float damage;
	string x[2];
	string y[2];

	void processGene();

public:
	void takeDamage(float damage);
	string* getXGene();
	string* getYGene();
	float getHealth();
	float getSpeed();
	float getDamage();
	float getSize();
	Organism(string* x, string* y);

	~Organism();

};