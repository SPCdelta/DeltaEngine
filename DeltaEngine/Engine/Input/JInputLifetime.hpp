#pragma once

class JInputEntry;

class JInputLifetime
{
public:
	JInputLifetime(const JInputEntry* entry)
		: _entry{ entry }
	{

	}

	~JInputLifetime();

private:
	const JInputEntry* _entry;
};