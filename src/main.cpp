#include "application.hpp"

int main(void)
{
    int errCode = 0;
    Application app(640, 640, "Hello There!", errCode);

    if (errCode)
        return errCode;

    app.Run();

    return errCode;
}