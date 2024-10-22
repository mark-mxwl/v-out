# V-Out ⚡

This is a simple, fun-to-use terminal program (with sound!) for calcuating voltage divider circuits. Perfect for hardware engineers and tinkerers.

### Getting Started

To compile `v_out.cpp` w/ VS Build Tools (via Developer PowerShell):
```
cl /EHsc v_out.cpp
```

To run the .exe in Bash or PowerShell from root dir.:
```
./v_out.exe
```
The user is prompted for voltage input and resistor values, after which the divided voltage is displayed, along with the entered circuit details.

> [!NOTE]
> Options for calcuting inverting/non-inverting op-amp circuits are on the way, as is modularity of user input (for instance, calculating Vin or R1, as opposed to Vout).

> [!IMPORTANT]
> Sound features are currently only available to Windows users.