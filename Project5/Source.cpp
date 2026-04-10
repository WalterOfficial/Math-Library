#include <iostream>
#include <iomanip>
#include <cmath>
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

double normalize( double x ) {
    x = fmod( x, 360.0 );

    if ( x > 180.0 ) x -= 360.0;
    if ( x < -180.0 ) x += 360.0;

    return x;
}

/**
 * METHOD 1: Analytical Transformation
 * Из одного ряда синуса получаем производную и интеграл 
 * путем манипуляции степенями и факториалами.
 */

void analytical_calculus_engine(double x, double& s, double& c, double& int_s) {
    s = 0; c = 0; int_s = 0;
    
    // Рекуррентные множители, чтобы не юзать тяжелые pow и factorial
    double x_pow = x; 
    double fact = 1.0;
    double x2 = x * x;

    for (int n = 0; n < 10; ++n) {
        int p = 2 * n + 1; // Степени синуса: 1, 3, 5, 7...
        if (n > 0) {
            fact *= (p - 1) * p;
            x_pow *= x2;
        }

        double sign = (n % 2 == 0) ? 1.0 : -1.0;
        double s_term = (sign * x_pow) / fact;

        // 1. БАЗА (Синус)
        s += s_term;

        // 2. ДИФФЕРЕНЦИРОВАНИЕ (Косинус)
        // (x^p / p!)' = x^(p-1) / (p-1)!  => s_term * (p / x)
        if (x != 0) c += s_term * (p / x);
        else c = 1.0;

        // 3. ИНТЕГРИРОВАНИЕ (Первообразная -cos x + 1)
        // int(x^p / p!) = x^(p+1) / (p+1)! => s_term * (x / (p + 1))
        int_s += s_term * (x / (p + 1));
    }
}

/**
 * METHOD 2: Limit & State Calculus
 * Производная через двусторонний предел.
 * Интеграл через разность состояний (Ньютон-Лейбниц).
 */

// Представим, что это наш базовый высокоточный ряд
double my_sin(double x) { return std::sin(x); }
double my_cos(double x) { return std::cos(x); }

// Производная как предел: lim h->0 (f(x+h) - f(x-h)) / 2h
double get_derivative_limit(double x) {
    const double h = 1e-8;
    return (my_sin(x + h) - my_sin(x - h)) / (2.0 * h);
}

// Определенный интеграл как разность первообразных
// Для sin(x) первообразная это -cos(x)
double get_integral_state(double a, double b) {
    // ∫ sin(x) dx = F(b) - F(a) = (-cos(b)) - (-cos(a)) = cos(a) - cos(b)
    return my_cos(a) - my_cos(b);
}

int main( ) {
    std::cout << std::fixed;
    double x = 0.0;

    std::cout << "Angle: ";
    std::cin >> x;

    x *= (3.14159 / 180.0);

    std::cout << "--- METHOD: Limits & State Differences ---\n";
    std::cout << "Target X: " << x << "\n\n";

    // Находим производную синуса (должен быть косинус)
    std::cout << "Derivative (cos) via limit: " << get_derivative_limit(x) << "\n";

    // Находим интеграл на отрезке [0, x]
    std::cout << "Definite Integral [0, x]:   " << get_integral_state(0, x) << "\n";
    
    std::cout << "\nCheck std::cos(x): " << std::cos(x) << "\n";
    
    system("pause");

    return 0;
}
