/**************************************
Program Name: main.cpp
Input File: customers.txt
Output Files: report.txt
              report_of_errors.txt
Author: stanislavamv
The program creates a detailed billing
report for a company that provides tax
consultations for customers.
**************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

int main()
{
    ifstream inData;
    ofstream outData, errors;
    int ID;
    string fileName, outfileName;

    char fnameInitial, lowIncome;
    string lastname, agentname;
    int customerID, consultTime;
    double yearlyIncome, amountdue;

    const string AGENT1 = "Bortles";
    const double HOURLY_AGENT1 = 65.00;
    const string AGENT2 = "Cower";
    const double HOURLY_AGENT2 = 70.00;
    const string AGENT3 = "Watt";
    const double HOURLY_AGENT3 = 75.00;

    cout << fixed << showpoint << setprecision(2);
    outData << fixed << showpoint << setprecision(2);

    cout << "/**************************************\n"
         << "The program creates a detailed billing\n"
         << "report for a company that provides tax\n"
         << "consultations for customers.\n"
         << "**************************************/"
         << endl << endl;

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
            cout << "Agent ID 1 = " << AGENT1 << "; Hourly Rate = "
                 << HOURLY_AGENT1 << "$" << endl;
            break;
        case 2:
            cout << "Agent ID 2 = " << AGENT2 << "; Hourly Rate = "
                 << HOURLY_AGENT2 << "$" << endl;
            break;
        case 3:
            cout << "Agent ID 3 = " << AGENT3 << "; Hourly Rate = "
                 << HOURLY_AGENT3 << "$" << endl;
            break;
    }


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
            inData >> fnameInitial >> lastname >> customerID >> yearlyIncome
                   >> consultTime >> ID;
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

            //check for the end of the file
            if(inData.eof())
                break;

            //billing report on the SCREEN - DATA
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
            else
                cout << "ID " << ID << "(N/A)" << setw(9) << "N/A" << endl;

            //billing report in the OUTPUT FILE - DATA
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
            else
                outData << "ID " << ID << "(N/A)" << setw(9) << "N/A" << endl;

        }

    //close all the files
    inData.close();
    outData.close();
    errors.close();

    system("pause");
    return 0;
}
