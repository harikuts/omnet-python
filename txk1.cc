/*
 * txk1.cc
 *
 *  Created on: Apr 21, 2021
 *      Author: harikuts
 */

#include <string.h>
#include <omnetpp.h>
#include <Python.h>
#include <fstream>

using namespace omnetpp;
using namespace std;

// Objects in the network
class Txk1 : public cSimpleModule
{
protected:
    // The following redefined virtual function holds the algorithm
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// Module must be registered with omnet++.
Define_Module(Txk1);

void Txk1::initialize()
{
    // Initialize is called at the beginning of the simulation.
    // One of the modules will send the first message as 'tik'.

    if (strcmp("tik", getName()) == 0) {
        // Initialize Python interpreter
        Py_Initialize(); // Init interpreter
        // Create and send the first message on 'out' gate.
        cMessage *msg = new cMessage("Hello world!");
        send(msg, "out");
    }
}

void Txk1::handleMessage(cMessage *msg)
{
    // This function is called whenever a message arrives.

    // Run Python script
    cout << "Running Python script...\n";
    char scriptname[] = "node.py"; // Set target and pointer
    FILE* fp;
    cout << "\tOpening file...\n";
    fp = _Py_fopen(scriptname, "r"); // Open file
    cout << "\tRunning file...\n";
    PyRun_SimpleFile(fp, scriptname); // Run it
//    cout << "\tClosing...\n";
//    Py_Finalize(); // Close interpreter
//    cout << "Done!\n";

    // Print from file
    string txt;
    fstream nodefile;
    nodefile.open("message.txt", ios::in);
    if (nodefile.is_open()) {
        getline(nodefile, txt);
        nodefile.close();
    }
    cMessage *job_msg = new cMessage(txt.c_str());
    send(job_msg, "out");
}

