#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <math.h> 
#include <string>
#include "Organism.h"

using namespace std;

void naturalSelection(vector<Organism>& population, int populationSize) {
	int halfThePopulation = populationSize / 2;
	int currPopulation = populationSize;
	while (currPopulation > halfThePopulation) {
		int randomIndexA = rand() % currPopulation;
		int randomIndexB = (randomIndexA + 10) / 2;
		Organism &organismA = population.at(randomIndexA);
		Organism &organismB = population.at(randomIndexB);
		float timeA = organismB.getHealth() / ((organismA.getSpeed() / organismA.getSize()) + (organismA.getDamage() * organismA.getSize()));
		float timeB = organismA.getHealth() / ((organismB.getSpeed() / organismB.getSize()) + (organismB.getDamage() * organismB.getSize()));
		if (timeA > timeB)
			population.erase(population.begin() + randomIndexA);
		else population.erase(population.begin() + randomIndexB);
		currPopulation--;
	}
}

void reproduction(vector<Organism>& population, int populationSize, int numberOfPopulationToAdd) {
	int maxNumberPopulation = populationSize * 4;
	int currPopulation = populationSize;
	int tempCounter = 0;
	while (currPopulation < maxNumberPopulation) {
		int randomIndex = tempCounter;
		do {
			randomIndex = rand() % populationSize;
		} while (tempCounter == randomIndex);
		Organism &organismA = population.at(tempCounter);
		Organism &organismB = population.at(randomIndex);
		Organism* newOrganism = new Organism(organismA.getXGene(), organismB.getYGene());
		population.push_back(*newOrganism);
		delete newOrganism;

		currPopulation++;
		tempCounter++;
	}
}

void mutateGene(string* gene) {
	random_shuffle(gene[0].begin(), gene[0].end());
	random_shuffle(gene[1].begin(), gene[1].end());
}

void mutation(vector<Organism>& population) {
	for (Organism &organism : population) {
		float randomIndex = (float)rand() / (float)RAND_MAX;
		randomIndex = randomIndex * 10.0f;
		if (randomIndex <= 7) {
			continue;
		}
		else if (randomIndex <= 8.5f) {
			mutateGene(organism.getXGene());
		}
		else if (randomIndex <= 10) {
			mutateGene(organism.getYGene());
		}
	}
}

void generateRandomGene(string* s, const int length) {
	static const char bits[] = "01";

	for (int i = 0; i < length; ++i) {
		s[0] += bits[rand() % (sizeof(bits) - 1)];
	}

	for (int i = 0; i < length; ++i) {
		s[1] += bits[rand() % (sizeof(bits) - 1)];
	}
}

int main() {
	vector<Organism> population;
	int initialPopulationSize = 50;
	int numberOfPopulationToAdd = initialPopulationSize - (initialPopulationSize / 2);
	int maxNumberOfGeneration = 5;
	int currentGeneration = 0;
	int maxBit = pow(2.0, 7.0);
	srand((unsigned)time(0));

	for (int i = 0; i < initialPopulationSize; i++) {
		string x[2] = { "", "" };
		generateRandomGene(x, 8);
		string y[2] = { "", "" };
		generateRandomGene(y, 8);
		Organism* organism = new Organism(x, y);
		population.push_back(*organism);
		delete organism;
	}

	while (currentGeneration < maxNumberOfGeneration) {
		naturalSelection(population, population.size());
		reproduction(population, population.size(), numberOfPopulationToAdd);
		mutation(population);

		currentGeneration++;
	}
	float averageSpeed = 0;
	float averageSize = 0;
	float averageHealth = 0;
	float averageDamage = 0;
	int populationFinalSize = population.size();
	for (int i = 0; i < population.size(); i++) {
		Organism &organism = population.at(i); 
		averageSpeed += organism.getSpeed();
		averageSize += organism.getSize();
		averageHealth += organism.getHealth();
		averageDamage += organism.getDamage();  
		if (i % 10 != 0) {
			continue;
		}
		cout << " " << endl;
		cout << "Organism " << i << endl;
		cout << "Organism " << i << " speed is " << organism.getSpeed() << endl;
	    cout << "Organism " << i << " size is " << organism.getSize() << endl;
		cout << "Organism " << i << " health is " << organism.getHealth() << endl;
		cout << "Organism " << i << " damage is " << organism.getDamage() << endl;
	}

	cout << "Totaling . . . " << endl;
	averageSpeed /= populationFinalSize;
	averageSize /= populationFinalSize;
	averageHealth /= populationFinalSize;
	averageDamage /= populationFinalSize;
	cout << "Average Speed is " << averageSpeed << endl;
	cout << "Average Size is " << averageSize << endl;
	cout << "Average Health is " << averageHealth << endl;
	cout << "Average Damage is " << averageDamage << endl;

	int stop;
	cout << "Type something to continue . . ." << endl;
	cin >> stop;
	return 0;
}