#ifndef PERSON_H
#define PERSON_H

using namespace std;

#ifndef ENTRY_SZ
	#define ENTRY_SZ 1024
#endif


class Person
{
private:
	int	 id;
    char Name[ENTRY_SZ];
    char IP[ENTRY_SZ];
	

public:
	static char filePath [ENTRY_SZ];

	Person();
	Person(char* name, char* ip, int newID);
	~Person();

	void setID(int newID);	
	int getID();
    void setName(char* name);
    void setIP(char* ip);
    char* getName();
    char* getIP();

	void AppendToFile(); 
	void PrintToConsole();
	void ClearListFile();
};

#endif

