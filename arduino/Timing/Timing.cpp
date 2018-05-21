#include "Timing.h"

Timing::Timing() {
}

long Timing::getInstant() {
	return millis();
}

long Timing::elapsedSince(long pastInstant) {
	return millis() - pastInstant;
}

bool Timing::hasElapsed(long pastInstant, long duration) {
	return elapsedSince(pastInstant) >= duration;	
}
