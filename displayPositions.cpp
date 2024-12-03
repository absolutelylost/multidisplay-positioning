#include <iostream>
#include <Windows.h>
#include <vector>

namespace DisplayPositioning
{
    std::vector<int> positionsX;
    std::vector<int> positionsY;

    BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
    {
        MONITORINFOEX monitorInfo;
        monitorInfo.cbSize = sizeof(MONITORINFOEX);
        GetMonitorInfo(hMonitor, &monitorInfo);

        std::cout << "Monitor Name: " << monitorInfo.szDevice << std::endl;
        std::cout << "Position: (" << monitorInfo.rcMonitor.left << ", " << monitorInfo.rcMonitor.top << ")" << std::endl;
        std::cout << "Size: " << monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left << " x " << monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top << std::endl;
        std::cout << std::endl;

        positionsX.push_back(static_cast<int>(monitorInfo.rcMonitor.left));
        positionsY.push_back(static_cast<int>(monitorInfo.rcMonitor.top));

        return TRUE;
    }

    int displayPositions(std::vector<int> XdesiredPositions, std::vector<int> YdesiredPositions, int choice)
    {
        int iterations = 0;

        // display positions
        EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, 0);
        // if any choice but display is chosen and this process hasn't run 3 times
        if (choice != 2 && iterations < 4)
        {
            // compare config to current positions
            if (positionsX != XdesiredPositions || positionsY != YdesiredPositions)
            {
                positionsX.empty();
                positionsY.empty();
                // configure again to correct state
                EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, 0);
            }
        }

        positionsX.empty();
        positionsY.empty();

        return 0;
    }
}

// int coordinatesX [9] = {0, 2560, 6400, 2560, 6400,
//                         2560, 6400, 2560, 6400};
// int coordinatesY [9] = {0,0, 2160, 2160,
//                         4320, 4320, 6480, 6480};
