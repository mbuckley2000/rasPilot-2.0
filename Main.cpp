#include "Stabiliser.h"

int main() {
	Stabiliser stabiliser = Stabiliser(10, 15, 25, 23);

	stabiliser.initialise();
	stabiliser.setThrottle(2);

	while (true) {
		stabiliser.update();
	}
	return 0;
}