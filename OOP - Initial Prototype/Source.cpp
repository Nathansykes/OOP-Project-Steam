#include "Application.h"
#include "LoginAccountMenu.h"
#include <string>

void main()
{
	Application app;
 
	app.Load();
	
	LoginAccountMenu loginAccountMenu("Login Account", &app);
	
	app.Save();
}