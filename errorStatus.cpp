#include "errorStatus.h"

ErrorStatus::ErrorStatus(): value(0){}

void ErrorStatus::clear()
{
	value = 0;
}

void ErrorStatus::set(error error_, bool act_)
{
	if (act_) {
		value |= 1 << unsigned long long(error_);
	}
	else {
		value &= ~(1 << unsigned long long(error_));
	}
}

void ErrorStatus::set(ErrorStatus error_)
{
	value |= error_.get();
}

unsigned long long ErrorStatus::get()
{
	return value;
}
