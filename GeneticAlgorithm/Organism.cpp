#include "Organism.h";

Organism::Organism(string* x, string* y) {
	this->x[0] = x[0];
	this->x[1] = x[1];
	this->y[0] = y[0];
	this->y[1] = y[1];
	processGene();
}

Organism::~Organism() {
//	delete 
}

void Organism::processGene() {
	int length = x[0].length();
	float numOf01 = 0;
	float numOf10 = 0;
	float numOf00 = 0;
	float numOf11 = 0;
	string xGeneL = x[0];
	string xGeneR = x[1];
	string yGeneL = y[0];
	string yGeneR = y[1];
	for (int i = 0; i < length; i++) {
		if (xGeneL.substr(i, 1) == "0" && xGeneR.substr(i, 1) == "0") {
			numOf00++;
		} else if(xGeneL.substr(i, 1) == "1" && xGeneR.substr(i, 1) == "0") {
			numOf00++;
		} else if (xGeneL.substr(i, 1) == "0" && xGeneR.substr(i, 1) == "1") {
			numOf11++;
		} else if (xGeneL.substr(i, 1) == "1" && xGeneR.substr(i, 1) == "1") {
			numOf11++;
		}
		if (yGeneL.substr(i, 1) == "0" && yGeneR.substr(i, 1) == "0") {
			numOf10++;
		} else if (yGeneL.substr(i, 1) == "1" && yGeneR.substr(i, 1) == "0") {
			numOf10++;
		} else if (yGeneL.substr(i, 1) == "0" && yGeneR.substr(i, 1) == "1") {
			numOf01++;
		} else if (yGeneL.substr(i, 1) == "1" && yGeneR.substr(i, 1) == "1") {
			numOf01++;
		}
	}
	speed = (numOf00 / length) * 20;
	health = (numOf10 / length) * 25;
	damage = (numOf01 / length) * 25;
	size = (numOf11 / length) * 20;
}

void Organism::takeDamage(float damage) {
	health -= damage;
}

string* Organism::getXGene() {
	return x;
}

string* Organism::getYGene() {
	return y;
}

float Organism::getHealth() {
	return health;
}

float Organism::getSpeed() {
	return speed;
}

float Organism::getDamage() {
	return damage;
}

float Organism::getSize() {
	return size;
}

