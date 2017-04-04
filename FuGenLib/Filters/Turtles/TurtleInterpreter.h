#ifndef TURTLE_INTERPRETER_H
#define TURTLE_INTERPRETER_H

#include <string>

class TurtleInterpreter
{
public:
	typedef bool (*TurtleCommandPredicate)(char command);

private:
	TurtleCommandPredicate IsTurtleCommand;
	char Dictionary[256];

public:

	void AddInterpretation(char character,char meaning)
	{
		if(IsTurtleCommand(meaning))
		{
			Dictionary[character] = meaning;
		}
	}

	void Convert(const std::string &str,std::string &dest)
	{
		dest.clear();

		for(int i=0;i < str.size();i++)
		{
			if(Dictionary[str[i]] != '\0')
			{
				dest += Dictionary[str[i]];
			}
		}
	}

	TurtleInterpreter(TurtleCommandPredicate turtle_command_predicate)
		:IsTurtleCommand(turtle_command_predicate)
	{
		for(unsigned int i=0;i < 256;i++)
		{
			Dictionary[i] = '\0';
		}
	}

	~TurtleInterpreter()
	{
		/*
		 * Üres függvénytörzs
		 */
	}
};

#endif // TURTLE_INTERPRETER_H
