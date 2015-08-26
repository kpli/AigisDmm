#pragma once

class CToPy
{
public:
	static CToPy* getInstance();
	CToPy();
	~CToPy();
	void runPython();

	std::string getUrl();
	std::string getMail();
private:
	void reset();
	std::string m_account;
	std::string m_gameurl;
};



