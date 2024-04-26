
#include <list>
#include <iostream>
#include <stdexcept>
#include "tour.h"


class TourList {
private:
	std::list<Tour> tours;

public:
	void addTour(const Tour& newTour) {
		tours.push_back(newTour);
		tours.sort([](const Tour& a, const Tour& b) {
			return a.price < b.price;
			});
	}

	void removeTour(int position) {
		if (position < 0 || position >= tours.size()) {
			throw std::out_of_range("Position is out of range");
		}
		auto iter = tours.begin();
		std::advance(iter, position);
		tours.erase(iter);
	}

	Tour getTour(int position) {
		if (position < 0 || position >= tours.size()) {
			throw std::out_of_range("Position is out of range");
		}
		auto iter = tours.begin();
		std::advance(iter, position);
		return *iter;
	}

	std::string checkDestination(const std::string& destination) {
		std::string positions;
		int pos = 0;
		for (const auto& tour : tours) {
			if (tour.destination == destination) {
				positions += std::to_string(pos) + " ";
			}
			pos++;
		}
		return positions.empty() ? "-1" : positions;
	}

	std::list<Tour> getToursByMaxPrice(double maxPrice) {
		std::list<Tour> result;
		for (const auto& tour : tours) {
			if (tour.price <= maxPrice) {
				result.push_back(tour);
			}
		}
		return result;
	}
};

int main() {
	try {
		TourList tourList;
		Tour tour1 = { "Paris", 7, 1500.0, 10 };
		Tour tour2 = { "London", 5, 1200.0, 8 };
		tourList.addTour(tour1);
		tourList.addTour(tour2);

		tourList.removeTour(1);

		Tour retrievedTour = tourList.getTour(0);
		std::cout << "Retrieved tour: " << retrievedTour.destination << std::endl;

		std::string positions = tourList.checkDestination("Paris");
		std::cout << "Positions of Paris tours: "<< positions << std::endl;

		std::list<Tour> affordableTours = tourList.getToursByMaxPrice(1300.0);
		std::cout << "Affordable tours: ";
		for (const auto& tour : affordableTours) {
			std::cout << tour.destination << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Exception occurred: " << e.what() << std::endl;
		// запись в системный журнал
	}
	return 0;
}
