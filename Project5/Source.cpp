#include <iostream>
#include "Math.h"
#include <iomanip>
using namespace std;

constexpr double m_pi_rad = 3.1415926535;
constexpr double m_pi = 180.0;

double get_pow( double num, double powr ) {
	double num2 = num;

	if ( powr == 0 )
		return 1;

	for ( int i = 1; i < powr; i++ )
		num2 = num2 * num;

	auto lognum = log( num );
	auto exp1 = exp( powr * lognum );

	return powr < 1.0 ? exp1 : num2;
}

double get_sqrt( double x, double sqrts ) {
	return get_pow( x, 1.0 / sqrts );
}

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

__forceinline double normalize(double x) {
    x = fmod( x, 360.0 );

    if ( x > 180.0 ) x -= 360.0;
    if ( x < -180.0 ) x += 360.0;

    return x;
}

__forceinline double get_sin(double x) {
    for ( int i = 1; i <= 5; i++ )
        sum += get_pow( -1, i - 1 ) * ( get_pow( x, 2 * i - 1 ) / factorial( 2 * i - 1 ) );

    const double eps = 1e-6;
    if (fabs(sum) < eps)
        return 0.0;

    return sum;
}

__forceinline double get_cos(double x) {
    double sum = 0.0;
    for ( int i = 0; i <= 5; i++ )
        sum += get_pow( -1, i ) * ( get_pow( x, 2 * i ) / factorial( 2 * i ) );

    const double eps = 1e-6;
    if (fabs(sum) < eps)
        return 0.0;

    return sum;
}

int main( ) {
    setlocale( LC_ALL, "rus" );

    cout << "Введите необходимый угол: ";

    // получаем необходимый угол
    double x = 0.0;
    cin >> x;

    // ограничиваем угол в предел [-180, 180]
    x = normalize( x );

    // переводим угол в радианы для корректного расчёта
    x = deg_to_rad( x );
    
    cout << "sin: " << get_sin( x );
    cout << "\ncos: " << get_cos( x );

    return 0;
}


