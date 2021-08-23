#include "Menu.h"

//the following line is necessary for the
//  GetConsoleWindow() function to work!
//it basically says that you are running this
//  program on Windows 2000 or higher
#define _WIN32_WINNT 0x0500
#include <windows.h>

Menu::Menu(const std::string& title, Application* app) : title(title), app(app)
{
}

void Menu::Paint()
{
	bool readyToGoBack = false;

	while (!readyToGoBack)
	{
		HWND console = GetConsoleWindow();
		RECT r;
		GetWindowRect(console, &r);//stores the console's current dimensions

		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(console, r.left, r.top, 700, 500, TRUE);

		system("color 30");
		Header();
		OutputOptions();
		Line();
		Option('B', "Back");
		Footer();

		char choice = Utils::getCharFromUser();

		if (choice == 'B')
		{
			readyToGoBack = true;
		}
		else
		{
			readyToGoBack = HandleChoice(choice);
		}
	}
}

void Menu::Line()
{
	std::cout << '\n';
}

void Menu::Line(const std::string& text)
{
	std::cout << "  " << text << "\n";
}

void Menu::Option(char id, const std::string& option)
{

	std::cout << "  " << id << ") " << option << '\n';
}

void Menu::Option(int id, const std::string& option)
{
	// shift the integer value up to the correct position in the ascii table
	char ascii = id + '0';
	Option(ascii, option);
}

void Menu::Option(int id, const std::string& option, std::string play)
{
	std::cout << "  " << id << ") " << option << "\t\tPlaytime: " << play << '\n';
}

void Menu::Option(int id, const std::string& option, std::string play, std::string& date)
{
	std::cout << "  " << id << ") " << option << "\t\tPlaytime: " << play << "\tDate Purchased: " << date << "\n";
}

std::string Menu::Question(const std::string& question)
{
	std::cout << "  " << question << ": ";
	return Utils::getLineFromUser();
}

void Menu::BlockingMessage(const std::string& message)
{
	std::cout << "  " << message;
	Utils::getLineFromUser();
}

void Menu::Header()
{

	#if defined _WIN32 || defined _WIN64
		// we are running on windows so use CLS to clear the screen
		system("CLS");
	#else
		// we are running on mac or linux so use CLEAR to clear the screen
		system("CLEAR");
	#endif

		std::cout << '\n';
		std::cout << "  -= " << title << " =-  \n";
		std::cout << '\n';
}

void Menu::Footer()
{
	std::cout << '\n';
	std::cout << '\n';
	std::cout << "  >>> ";
}