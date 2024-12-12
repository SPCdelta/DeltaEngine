#pragma once

class Debugger
{
public:
	static Debugger& get_instance() { return instance; }
	Debugger(const Debugger&) = delete;
	Debugger(Debugger&&) = delete;
	Debugger& operator=(const Debugger&) = delete;
	Debugger& operator=(Debugger&&) = delete;

	// EnTT
	static int GetEnTTCounter() { return instance.enttCounter; }
	static void AddToEnTTCounter(int amount) { instance.enttCounter += amount; }
	static void RemoveFromEnTTCounter(int amount) { instance.enttCounter -= amount; }

private:
	static Debugger instance;
	Debugger() {}

	// EnTT
	int enttCounter = 0;
};

