#include "ConsoleHandler.h"

#include "BookingsDB.h"
#include "CinemasDB.h"
#include "CustomersDB.h"
#include "MoviesDB.h"
#include "ShowsDB.h"

int main()
{
    #pragma region initialization

    ConsoleHandler con;

    con.Write("Loading Data!");
    con.Write("Progress : 0%", true, 12);
    con.Clear();

    BookingsDB bookingsDB("C:\\_src\\x_temp_files\\bookings.kmd");
    con.Write("Progress : 20%", true, 12);
    con.Clear();
    CinemasDB cinemasDB("C:\\_src\\x_temp_files\\cinemas.kmd");
    con.Write("Progress : 40%", true, 12);
    con.Clear();
    CustomersDB customersDB("C:\\_src\\x_temp_files\\customers.kmd");
    con.Write("Progress : 60%", true, 12);
    con.Clear();
    MoviesDB moviesDB("C:\\_src\\x_temp_files\\movies.kmd");
    con.Write("Progress : 80%", true, 12);
    con.Clear();
    ShowsDB showsDB("C:\\_src\\x_temp_files\\shows.kmd");
    con.Write("Progress : 100%", true, 12);

    #pragma endregion

    getchar();
}
