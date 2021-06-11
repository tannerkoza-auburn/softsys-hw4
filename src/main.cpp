// Homework 4 Main File

#include <iostream>
#include <fstream>
#include <string>
#include "imu.h"

using namespace std;

int main()
{
    string input_file = "/home/tannerkoza/SFSAS/HW4/data/hw3_data.txt"; // declare file names
    string output_file = "/home/tannerkoza/SFSAS/HW4/data/output.txt";

    double acc[3], gyro[3], mag[3];     // declare arrays to store values
    double q[4] = {1.0, 0.0, 0.0, 0.0}; // declare initial orientation
    double dT = 1.0 / 128.0;            // declare timestep

    IMU imu(q, dT); // declare instance of IMU class

    ifstream infile(input_file); // make class instance of read and write while opening respective files
    ofstream outfile(output_file);

    if (infile.is_open() && outfile.is_open())
    {
        while (infile >> acc[0] >> acc[1] >> acc[2] >> gyro[0] >> gyro[1] >> gyro[2] >> mag[0] >> mag[1] >> mag[2]) // passes input file values to corresponding variables
        {
            outfile << q[0] << "\t"; // write table delimited data to output
            outfile << q[1] << "\t";
            outfile << q[2] << "\t";
            outfile << q[3] << endl;

            imu.update(q, gyro); // call update function from IMU class
        }
        infile.close(); // close files
        outfile.close();
    }
    return 0;
}