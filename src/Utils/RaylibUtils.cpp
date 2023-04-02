#include "RaylibUtils.h"

int RaylibUtils::getWindowWidth()
{
	return GetMonitorWidth(GetCurrentMonitor());
}

int RaylibUtils::getWindowHeight()
{
	return GetMonitorHeight(GetCurrentMonitor());
}
