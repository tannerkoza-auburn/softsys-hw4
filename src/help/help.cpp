#include <iostream>

#include <fstream>

#include <valarray>

using namespace std;

//

//

//

//

//

class propogate
{

public:
    double om_X;

    double om_Y;

    double om_Z;

    double dt = 1.0 / 128.0;

    double g[3];

    double a[4];

    double b;

    double c[3];

    double Q[4][1];

    propogate(){

    };

    void update(double (&q)[4], double (&g)[3])
    {

        Q[0][0] = q[0];
        Q[1][0] = q[1];
        Q[2][0] = q[2];
        Q[3][0] = q[3];

        double A[4][4]{

            {1, -0.5 * dt * g[0], -0.5 * dt * g[1], -0.5 * dt * g[2]},

            {0.5 * dt * g[0], 1, 0.5 * dt * g[2], -0.5 * dt * g[1]},

            {0.5 * dt * g[1], -0.5 * dt * g[2], 1, 0.5 * dt * g[0]},

            {0.5 * dt * g[2], 0.5 * dt * g[1], -0.5 * dt * g[0], 1}

        };

        int c1, c2, c3;

        c1 = 1;

        c2 = 4;

        c3 = 4;

        // Matrix multiplication

        double raw[1][4];

        for (int i = 0; i < c1; i++)

        {

            for (int j = 0; j < c2; j++)

            {

                raw[i][j] = 0;

                for (int k = 0; k < c3; k++)

                {

                    raw[i][j] += A[j][k] * Q[k][i];
                }
            }
        }

        double pos1 = raw[0][0];

        double pos2 = raw[0][1];

        double pos3 = raw[0][2];

        double pos4 = raw[0][3];

        double norm[4]{

            pos1, pos2, pos3, pos4

        };

        double sum;

        int ip = 4;

        for (int i = 0; i < ip; ++i)
        {

            sum = sum + norm[i] * norm[i]; // squared values summed
        }

        for (int in = 0; in < ip; ++in)
        {

            norm[in] = norm[in] / sqrt(sum); //normalization
        }

        // redefine for output

        q[0] = norm[0];

        q[1] = norm[1];

        q[2] = norm[2];

        q[3] = norm[3];

        // output
    }
};

int main()
{

    ifstream dataFile;

    ofstream outputFile;

    outputFile.open("help_output.txt");

    double a[3], g[3], m[3];

    dataFile.open("/home/tannerkoza/SFSAS/HW4/data/hw3_data.txt", ios::in);

    int q1;
    int q2;
    int q3;
    int q4;

    double q[4] = {1.0, 0.0, 0.0, 0.0};

    double dt = 0.0078;

    //double *out[4] = {q1, q2, q3, q4};

    if (dataFile.is_open())
    {

        while (dataFile >> a[0] >> a[1] >> a[2] >> g[0] >> g[1] >> g[2] >> m[0] >> m[1] >> m[2])
        {

            propogate position;

            outputFile << q[0] << '\t' << q[1] << '\t' << q[2] << '\t' << q[3] << std::endl;

            position.update(q, g);
        }
    }

    dataFile.close();

    outputFile.close();

    return 0;
}