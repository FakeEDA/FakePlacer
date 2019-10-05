#include<faketimer/faketimer.h>
#include<fakedb/fakedb.h>
#include<iostream>

using namespace std;

int RunPlacer() {
    cout << "-----------------------------------" << endl;
    cout << "Inside Placer" << endl;
    cout << "Running placement on netlist: " << GetNetList() << endl;
    SetNetList(GetNetList() + 2);
    RunSTA();
    cout << "-----------------------------------" << endl;
    return GetNetList();
}