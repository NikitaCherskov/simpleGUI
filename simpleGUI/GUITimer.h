#pragma once
#include <vector>
#include <ctime>
class Metronome
{
public:
	Metronome();
	Metronome(clock_t _period);
	~Metronome();
	void update();
	void setPeriod(clock_t _period);
	bool getIsPassed();
	void restart();
private:
	clock_t mark;
	clock_t period;
	bool is_passed;
};