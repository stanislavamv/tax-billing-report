/**************************************
Program Name: main.cpp
Input File: customers.txt
Output Files: report.txt
              report_of_errors.txt
Author: stanislavamv
The program creates a detailed billing
report for a company that provides tax
consultations for customers.
Functional Decomposition.
**************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

//Keeps prompting the user for a valid file name until file is open
//PRE: ifstream and ofstream variables point to the valid ifstream and ofstreams
//POST: returns true if files are successfully opened and false otherwise
int OpenFiles (ifstream& inData, ofstream& outData, ofstream& errors);

//Finds and reads the text from the file
//PRE:
//POST: the text file was read and returned
int ProcessData (ifstream& inData, char& fnameInitial, string& lastname, int& customerID, double& yearlyIncome, int& consultTime, int& ID);

//Closes the open files
//PRE:
//POST: Input and output files were closed
void CloseFiles (ifstream& inData, ofstream& outData, ofstream& errors);


//Returns the agents' names and hourly rate
//PRE: agent IDs must contain valid values
//POST: correct agent names and rates are returned
int AgentNames (int& ID, string& agentName, double& agentRate, ofstream& errors, char& fnameInitial, string& lastname, int& customerID);

//Returns the amount due
//PRE:
//POST: low income and yearly income information is being processed and returned depending on the numbers that have been read
int AmountDue (double& yearlyIncome, char& lowIncome , int& consultTime, double& amountdue, int& ID, int& customerID, ofstream& errors, string& lastname, char& fnameInitial);

//Outputs the billing report on the screen and into the file
//PRE:
//POST: writes the billing report to the opened output file and the console
int DisplayOutput(int& consultTime, int& ID, double& yearlyIncome, char& fnameInitial, string& lastname, char& lowIncome, double& amountdue, int& customerID, ofstream& outData);

int main()
{
    ifstream inData;
    ofstream outData, errors;

    char fnameInitial, lowIncome;
    string lastname, agentName;
    int ID, customerID, consultTime;
    double yearlyIncome, amountdue, agentRate;

    cout << fixed << showpoint << setprecision(2);
    outData << fixed << showpoint << setprecision(2);

    cout << "/**************************************\n"
         << "The program creates a detailed billing\n"
         << "report for a company that provides tax\n"
         << "consultations for customers.\n"
         << "**************************************/"
         << endl << endl;

    //Open the files
    OpenFiles (inData, outData, errors);

    AgentNames (ID, agentName, agentRate, errors, fnameInitial, lastname, customerID);

    //billing report on the screen - TITLES
    cout << setw(66) << "Billing Report" << endl << endl;
    cout << "Customer Name" << setw(17) << "Customer ID" << setw(20) << "Yearly Income"
         << setw(18) << "Consulting Time" << setw(14) << "Amount Due" << setw(14)
         << "Low Income" << setw(16) << "Agent Name" << setw(10) << "Rate" << endl << endl;


    //billing report to the output file - TITLES
    outData << setw(66) << "Billing Report" << endl << endl;
    outData << "Customer Name" << setw(17) << "Customer ID" << setw(20) << "Yearly Income"
            << setw(18) << "Consulting Time" << setw(14) << "Amount Due" << setw(14)
            << "Low Income" << setw(16) << "Agent Name" << setw(10) << "Rate" << endl << endl;

    //read the file using a loop that checks for the end of file
    while (true)
        {
            ProcessData (inData, fnameInitial, lastname, customerID, yearlyIncome, consultTime, ID);
            AmountDue (yearlyIncome, lowIncome , consultTime, amountdue, ID, customerID, errors, lastname, fnameInitial);

            //check for the end of the file
            if(inData.eof())
                break;

            DisplayOutput(consultTime, ID, yearlyIncome, fnameInitial, lastname, lowIncome, amountdue, customerID, outData);

        }

    //close all the files
    CloseFiles (inData, outData, errors);

    system("pause");
    return 0;
}


int OpenFiles (ifstream& inData, ofstream& outData, ofstream& errors)
{
    string fileName, outfileName;
    //request the name of the input file
        cout << endl << "Please enter the name of the INPUT file: ";
        while (true) //loop to open a file and check the state of the file
                {
                    cin >> fileName;
                    //clear remainder of the line input
                    cin.clear();
                    cin.ignore(50, '\n');
                    inData.open(fileName.c_str());

                    if (inData)
                        break;
                    cout << "Invalid file. Please enter the name of the input file: ";
                    inData.close();
                    inData.clear();
                }

        //request an output filename from the user
        cout << endl << "Please enter the name of the OUTPUT file: ";
        getline(cin,outfileName);
        outData.open(outfileName.c_str());

        //check the file state
        if (outData.is_open())
            cout << "Output file successfully open" << endl;
        else
            cout << "Error opening output file" << endl;

        //open the error report file
         errors.open("report_of_errors.txt");
        //check the file state
         if (errors.is_open())
            cout << "report_of_errors successfully open" << endl;
         else
            cout << "Error opening file report_of_errors" << endl;

}

int ProcessData (ifstream& inData, char& fnameInitial, string& lastname, int& customerID, double& yearlyIncome, int& consultTime, int& ID)
{
    inData >> fnameInitial >> lastname >> customerID >> yearlyIncome >> consultTime >> ID;
}

int AgentNames (int& ID, string& agentName, double& agentRate, ofstream& errors, char& fnameInitial, string& lastname, int& customerID)
{
    //switch statement of agent ids
    //any other id == error
    cout << "Enter ID: ";
    while (!(cin >> ID) || ID != 1 ^ ID != 2 ^ ID != 3)
            {
                cin.clear();
                cin.ignore(50,'\n');
                cout << "Wrong input. Enter ID: ";

            }
    switch (ID)
    {
        case 1:
            agentName = "Bortles";
            agentRate = 65.00;
            cout << "Agent ID 1 = " << agentName << "; Hourly Rate = "
                 << agentRate << "$" << endl;
            break;
        case 2:
            agentName = "Cower";
            agentRate = 70.00;
            cout << "Agent ID 2 = " << agentName << "; Hourly Rate = "
                 << agentRate << "$" << endl;
            break;
        case 3:
            agentName = "Watt";
            agentRate = 75.00;
            cout << "Agent ID 3 = " << agentName << "; Hourly Rate = "
                 << agentRate << "$" << endl;
            break;
        default:
            errors << "Customer name: " << fnameInitial << " " << lastname << endl;
            errors << "Customer ID: " << customerID << endl;
            errors << "Invalid agent ID number." << endl << endl;
    }

}

int AmountDue (double& yearlyIncome, char& lowIncome , int& consultTime, double& amountdue, int& ID, int& customerID, ofstream& errors, string& lastname, char& fnameInitial)
{
            const double HOURLY_AGENT1 = 65.00;
            const double HOURLY_AGENT2 = 70.00;
            const double HOURLY_AGENT3 = 75.00;

            //Y/N low income costumer if <= 25.000$ then Y
            //output that in the report below
            if (yearlyIncome <= 25000)
                lowIncome = 'Y';
            else if (yearlyIncome > 25000)
                lowIncome = 'N';

            //calculate the amount due with reporting an error of invalid agent ID
            if (lowIncome == 'Y')
            {
                if (consultTime <= 30)
                    amountdue = 0.00;
                else if (consultTime > 30)
                {
                    if (ID == 1)
                        amountdue = HOURLY_AGENT1 * 0.40 * (consultTime - 30) / 60;
                    else if (ID == 2)
                        amountdue = HOURLY_AGENT2 * 0.40 * (consultTime - 30) / 60;
                    else if (ID == 3)
                        amountdue = HOURLY_AGENT3 * 0.40 * (consultTime - 30) / 60;
                    else
                        errors << "Error. Invalid Agent ID #" << ID << " " << "Customer: "
                               << fnameInitial << " " << lastname << " id#" << customerID << endl;
                }
            }
            else if (lowIncome == 'N')
            {
                if (consultTime <= 20)
                    amountdue = 0.00;
                else if (consultTime > 20)
                {
                    if (ID == 1)
                        amountdue = HOURLY_AGENT1 * 0.70 * (consultTime - 20) / 60;
                    else if (ID == 2)
                        amountdue = HOURLY_AGENT2 * 0.70 * (consultTime - 20) / 60;
                    else if (ID == 3)
                        amountdue = HOURLY_AGENT3 * 0.70 * (consultTime - 20) / 60;
                    else
                        errors << "Error. Invalid Agent ID #" << ID << " " << "Customer: "
                               << fnameInitial << " " << lastname << " id#" << customerID << endl;
                }
            }

            //if yearly income == 0 then put the error note into the file
            if (yearlyIncome == 0)
            {
                errors << "Error. The yearly income must be greater than zero. Customer: "
                       << fnameInitial << " " << lastname << " id#" << customerID << endl;

            }

            //if consult mins == 0 the put the error note into the file
            if (consultTime == 0){
                errors << "Error. Consulting minutes must be greater than zero. Customer: "
                       << fnameInitial << " " << lastname << " id#" << customerID << endl;

            }
}

int DisplayOutput(int& consultTime, int& ID, double& yearlyIncome, char& fnameInitial, string& lastname, char& lowIncome, double& amountdue, int& customerID, ofstream& outData)
{

        const string AGENT1 = "Bortles";
        const double HOURLY_AGENT1 = 65.00;
        const string AGENT2 = "Cower";
        const double HOURLY_AGENT2 = 70.00;
        const string AGENT3 = "Watt";
        const double HOURLY_AGENT3 = 75.00;
        string agentname;


        //billing report on the SCREEN - DATA
            if ((consultTime >= 20) && ((ID <= 3) && (yearlyIncome >= 1)))
            {
                cout << fnameInitial << " " << lastname << setw(18) << customerID << setw(20) << yearlyIncome
                 << "$" << setw(11) << consultTime << " mins" << setw(16) << amountdue << "$" << setw(13)
                 << lowIncome << setw(17);
                 //figuring out switching the agent's id number into the name plus hourly rate
                if (ID == 1)
                {
                    agentname = AGENT1;
                    cout << agentname << setw(12) << HOURLY_AGENT1 << "$" << endl;
                }
                else if (ID == 2)
                {
                    agentname = AGENT2;
                    cout << agentname << setw(12) << HOURLY_AGENT2 << "$" << endl;
                }
                else if (ID == 3)
                {
                    agentname = AGENT3;
                    cout << agentname << setw(12) << HOURLY_AGENT3 << "$" << endl;
                }
            }

            //billing report in the OUTPUT FILE - DATA
            if ((consultTime >= 20) && ((ID <= 3) && (yearlyIncome >= 1)))
            {
                outData << fnameInitial << " " << lastname << setw(18) << customerID << setw(20) << yearlyIncome
                        << "$" << setw(11) << consultTime << " mins" << setw(16) << amountdue << "$" << setw(13)
                        << lowIncome << setw(17);

                //figuring out switching the agent's id number into the name plus hourly rate
                if (ID == 1)
                {
                    agentname = AGENT1;
                    outData << agentname << setw(12) << HOURLY_AGENT1 << "$" << endl;
                }
                else if (ID == 2)
                {
                    agentname = AGENT2;
                    outData << agentname << setw(12) << HOURLY_AGENT2 << "$" << endl;
                }
                else if (ID == 3)
                {
                    agentname = AGENT3;
                    outData << agentname << setw(12) << HOURLY_AGENT3 << "$" << endl;
                }
            }

}

void CloseFiles (ifstream& inData, ofstream& outData, ofstream& errors)
{
    //close all the files
    inData.close();
    outData.close();
    errors.close();
}

