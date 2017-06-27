
#include <string.h>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include "GameHelper.h"
#include "Recipment.h"

using namespace std;

int main()
{
    srand( time( NULL ) );
    GameHelper *gh = new GameHelper;
    gh->enterMenu();

    //gh->loadMap();

    return 0;
}
