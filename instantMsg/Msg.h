#ifndef MSG_H
#define MSG_H

//using namespace std;
#ifndef ENTRYSZ
	#define ENTRY_SZ 1024
#endif

const int nameSize = 150;



class Msg
{
private:
	char 	userName[nameSize];
	char 	msg[ENTRY_SZ];
	int 	ID;
public:
	static char filePath [ENTRY_SZ];

    Msg();
    Msg(char* message, char* name, int id);
	Msg(const Msg* newMsg);	//added copy ctor.
    ~Msg();
    void setName(char* newName);  
    void setMsg(char* message);
    char* getName();  
    char* getMsg();
       
    void AppendToFile(); 

};

#endif
