#include "stdafx.h"
#include "Define.h"

using namespace std;

class Command
{
	string* args;
	void (*fxn)();
	string super;

public:
	inline string Command::getSuper() const { this->super; };
	inline void Command::call() const { this->fxn(); };

	bool Command::checkCommand(string* arg);
};