#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>	



using namespace std;

// This method will call a function by passing the function name in Python
void CallProcedure(string pName)     
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}


// This method willl call a function by passing the function name in Python; it takes one string parameter
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}


// This method willl call a function by passing the function name in Python; it takes one integer parameter
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main() {
	string menuChoice;
	string userInput;
	string name;
	int quantity = 0;

	// This while loop accepts user input and executes the appropriate function depending on input. 
	while (true) {
		cout << endl;
		cout << "1: Request a list of all items and their frequency" << endl;
		cout << "2: Request frequency for an individual item" << endl;
		cout << "3: Request a histogram" << endl;
		cout << "4: Exit" << endl;
		cout << endl;
		cout << "Enter your slection as a number 1, 2, 3 or 4." << endl;
		cin >> menuChoice;

		// The menu will exit if the user selects option 3
		if (menuChoice == "4") {
			break;
		}
		// Option 1 calls determineInventory function() from Python
		else if (menuChoice == "1") {
			cout << "TOTAL INVENTORY" << endl;
			CallProcedure("determineInventory");
			cout << endl;
		}
		// Option 2 calls determineFrequency() function from Python
		else if (menuChoice == "2") {
			cout << endl;
			cout << "Please enter an item from the list: " << endl;
			cin >> userInput;
			cout << endl;
			cout << userInput << " occur " << callIntFunc("determineFrequency", userInput) << endl;
			cout << endl;
		}
		// Option 3 calls output() function fom Python
		else if (menuChoice == "3") {
			cout << "WRITE OUTPUT TO frequency.dat" << endl;
			cout << endl;
			CallProcedure("output");
			// Opens file frequency.dat and reads name and quantity from the file
			ifstream readFile;
			readFile.open("frequency.dat");

			readFile >> name;
			readFile >> quantity;

			HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE); // Changing the color of histogram https://coderspacket.com/color-coding-in-c
			SetConsoleTextAttribute(color, 11);
			// While the file is successfully open, print the name of each item and iterate through the values, replace w/ "*"
			while (!readFile.fail()) {
				cout << setw(14) << left << name << setw(6);

				for (int i = 0; i < quantity; i++) {
					cout << right << "*";
				}

				cout << endl;
				readFile >> name;
				readFile >> quantity;
			}
			readFile.close();
			SetConsoleTextAttribute(color, 7); // Return the color back to white
		}
		else {
			cout << endl;
			cout << "Invalid Input. Please choose a number from the menu." << endl;
			// If anything other than 1, 2, 3, or 4 is entered, an error message is displayed
		}
	}
}