#include "ConsoleHandler.h"

#include "BookingsDB.h"
#include "CinemasDB.h"
#include "CustomersDB.h"
#include "MoviesDB.h"
#include "ShowsDB.h"

int main()
{
    #pragma region initialization

    ConsoleHandler CH;

    CH.Write("Loading Data!");
    CH.Write("Progress : 0%", true, 12);
    CH.Clear();

    BookingsDB bookingsDB("C:\\_src\\x_temp_files\\bookings.kmd");
    CH.Write("Progress : 20%", true, 12);
    CH.Clear();
    CinemasDB CinemasDB("C:\\_src\\x_temp_files\\cinemas.kmd");
    CH.Write("Progress : 40%", true, 12);
    CH.Clear();
    CustomersDB CustomersDB("C:\\_src\\x_temp_files\\customers.kmd");
    CH.Write("Progress : 60%", true, 12);
    CH.Clear();
    MoviesDB MoviesDB("C:\\_src\\x_temp_files\\movies.kmd");
    CH.Write("Progress : 80%", true, 12);
    CH.Clear();
    ShowsDB ShowsDB("C:\\_src\\x_temp_files\\shows.kmd");
    CH.Write("Progress : 100%", true, 12);

    #pragma endregion

    getchar();
}
