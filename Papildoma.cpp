#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <iomanip>

struct Zodis {
	std::vector<int> eil;
	int kiekis = 1;
};

int zod = 0, kiek = 0, eilu = 0;

std::vector<std::string> Dalinimas(std::string line)
{
	std::vector<std::string> zodziai;
	int vieta;
	std::string naujas;
	while (!line.empty())
	{
		vieta = line.find(" ");
		naujas = line.substr(0, vieta);
		line.erase(0, vieta + 1);
		if (line == naujas) line.clear();
		zodziai.push_back(naujas);
		naujas.clear();
	}
	return zodziai;
}

std::string Valymas(std::string zodis)
{
	std::replace_if(zodis.begin(), zodis.end(), [](const char& c) { return std::ispunct(c); }, ' ');
	std::transform(zodis.begin(), zodis.end(), zodis.begin(), ::tolower);
	return zodis;
}



void Nuskaitymas(std::vector<std::string>& URL, std::map<std::string, Zodis>& Ats) {
	std::ifstream PD("tekstas.txt");
	std::string line;
	int x, eil = 1;
	std::string zodis;
	std::map<std::string, Zodis>::iterator it;
	while (!PD.eof())
	{
		getline(PD, line);
		std::vector<std::string> zodziai = Dalinimas(line);
		x = zodziai.size();
		for (int i = 0; i < x; i++)
		{
			if (zodziai[i].substr(0, 3) == "www" || zodziai[i].substr(0, 4) == "http") URL.push_back(zodziai[i]);
			else {
				zodis = Valymas(zodziai[i]);
				if (zodis.length() > zod) zod = zodis.length();
				it = Ats.find(zodis);
				if (it != Ats.end()) {
					it->second.kiekis++;
					it->second.eil.push_back(eil);
					if (std::to_string(it->second.kiekis).length() > kiek) kiek = std::to_string(it->second.kiekis).length();
				}
				else {
					Zodis a;
					a.eil.push_back(eil);
					Ats.insert(std::make_pair(zodis, a));
				}
			}
		}
		line.clear();
		zodziai.clear();
		eil++;
	}
	if (std::to_string(eil).length() > eilu) eilu = std::to_string(eil).length();
}


void Isvedimas(std::vector<std::string> URL, std::map<std::string, Zodis> Ats) {
	std::cout << "Jus norite isvesti url i ekrana ar i faila? ";
	std::string nu;
	std::cin >> nu;
	if (nu == "faila") {
		std::ofstream RZ("url.txt");
		for (int i = 0; i < URL.size(); i++) {
			RZ << URL[i] << std::endl;
		}
		RZ.close();
	}
	else {
		std::cout << std::endl << "Tekste buve URL:" << std::endl;
		for (int i = 0; i < URL.size(); i++) {
			std::cout << URL[i] << std::endl;
		}
	}
	if (zod < 7) zod = 5;
	if (kiek < 8) kiek = 6;
	std::cout << std::endl << std::left << std::setw(zod) << "Zodis" << " | " << std::left << std::setw(kiek) << "Kiekis" << " | " << "Eilutes kuriose pamineta" << std::endl;
	for (int i = 0; i < zod + kiek + 30; i++)
	{
		std::cout << "_";
	}
	std::cout << std::endl << std::endl;;
	std::map<std::string, Zodis>::iterator it;
	it = Ats.begin();
	for (int i = 0; i < Ats.size(); i++) {
		if (it->second.kiekis != 1) {
			std::cout << std::left << std::setw(zod) << it->first << " | " << std::left << std::setw(kiek) << it->second.kiekis << " | ";
			for (int l = 0; l < it->second.kiekis; l++) {
				std::cout << std::left << std::setw(eilu) << it->second.eil[l];
				if (l + 1 != it->second.kiekis) std::cout << " - ";
			}
			std::cout << std::endl;
		}
		it++;
	}
}
int main()
{
	int zod = 0, kiek = 0, eil = 0;
	std::vector<std::string> URL;
	std::map<std::string, Zodis> Ats;
	Nuskaitymas(URL, Ats);
	Isvedimas(URL, Ats);
	return 0;
}