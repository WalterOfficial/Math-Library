#include <iostream>
#include "Math.h"
#include <iomanip>
using namespace std;

constexpr double m_pi_rad = 3.1415926535;
constexpr double m_pi = 180.0;

int factorial( int n ) {
    if ( n > 1 )
        return n * factorial( n - 1 );
    else
        return 1;
}

double deg_to_rad( double n ) {
    return n * ( m_pi_rad / m_pi );
}

double rad_to_deg( double n ) {
    return n * ( m_pi / m_pi_rad );
}

int main( ) {
    setlocale( LC_ALL, "rus" );

    cout << "Введите необходимый угол: ";

    double x = 0.0;
    cin >> x;

    double sum = 0.0;
    double sum2 = 0.0;

    x = fmod( x, 360.0 );

    if ( x > 180.0 ) x -= 360.0;
    if ( x < -180.0 ) x += 360.0;

    x = deg_to_rad( x );

    for ( int i = 1; i <= 6; i++ ) {
        sum += pow( -1, i - 1 ) * ( pow( x, 2 * i - 1 ) / factorial( 2 * i - 1 ) );
    }

    for ( int i = 0; i <= 5; i++ ) {
        sum2 += pow( -1, i ) * ( pow( x, 2 * i ) / factorial( 2 * i ) );
    }

    cout << setprecision( 2 ) << fixed;
    cout << "sin: " << sum;
    cout << "\ncos: " << sum2;
    cout << "\ntan: " << ( sum / sum2 );
    cout << "\ncotan: " << ( sum2 / sum );

    return 0;
}
