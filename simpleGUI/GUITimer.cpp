#include "GUITimer.h"

Metronome::Metronome():
	is_passed(0),
	mark(clock()),
	period(0)
{}

Metronome::Metronome(clock_t _period) :
	is_passed(0),
	mark(clock()),
	period(_period)
{}

Metronome::~Metronome()
{}

void Metronome::update()
{
	if (clock() - mark > period)
	{
		if (is_passed == 0)
		{
			is_passed = 1;
			mark = clock();
		}
	}
	else
	{
		is_passed = 0;
	}
}

void Metronome::setPeriod(clock_t _period)
{
	period = _period;
	restart();
}

bool Metronome::getIsPassed()
{
	return is_passed;
}

void Metronome::restart()
{
	mark = clock();
}
