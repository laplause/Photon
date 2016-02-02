#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
	Command();
	virtual ~Command();
	virtual void Execute() = 0;

private:
	Command(const Command& rhs);
	const Command& operator=(const Command& rhs);
};
#endif
