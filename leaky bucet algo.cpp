#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

#define NO_OF_PACKETS 10

int arc4rand(int a)
{
    int m = (rand() % 10) % a;
    return (m == 0) ? 1 : m;
}

int main()
{
    int packet_sz[NO_OF_PACKETS];
    int i, clk, b_size, o_rate, p_sz_rm = 0, p_time, op;

    srand(time(0));

    for (i = 0; i < NO_OF_PACKETS; i++)
    {
        packet_sz[i] = arc4rand(6) * 10;
        cout << "Packet[" << i << "] = "
             << packet_sz[i] << " bytes" << endl;
    }

    cout << "\nEnter the Output rate: ";
    cin >> o_rate;

    cout << "Enter the Bucket Size: ";
    cin >> b_size;

    for (i = 0; i < NO_OF_PACKETS; i++)
    {
        // Check if packet size exceeds bucket capacity
        if (packet_sz[i] > b_size)
        {
            cout << "\nIncoming packet size ("
                 << packet_sz[i]
                 << ") is Greater than bucket capacity - "
                 << "PACKET REJECTED!" << endl;
        }
        else
        {
            p_sz_rm += packet_sz[i];

            cout << "\nIncoming packet size: "
                 << packet_sz[i] << endl;

            cout << "Bytes remaining to transmit: "
                 << p_sz_rm << endl;

            // Generate transmission time
            p_time = arc4rand(4) * 10;

            cout << "Time left for transmission: "
                 << p_time << " units" << endl;

            // Transmission
            for (clk = 10; clk <= p_time; clk += 10)
            {
                sleep(1);

                if (p_sz_rm)
                {
                    // Compare remaining packet size
                    // with output rate
                    if (p_sz_rm <= o_rate)
                    {
                        op = p_sz_rm;
                        p_sz_rm = 0;
                    }
                    else
                    {
                        op = o_rate;
                        p_sz_rm -= o_rate;
                    }

                    cout << "Packet of size "
                         << op
                         << " Transmitted" << endl;

                    cout << "Bytes Remaining to Transmit: "
                         << p_sz_rm << endl;
                }
                else
                {
                    cout << "Time left for transmission: "
                         << p_time - clk
                         << " units" << endl;

                    cout << "No packets to transmit!" << endl;
                }
            }
        }
    }

    return 0;
}
