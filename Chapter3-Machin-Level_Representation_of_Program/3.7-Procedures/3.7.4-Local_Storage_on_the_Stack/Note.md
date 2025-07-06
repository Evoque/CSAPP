

Procedure need registers and local storaget to call sub-procudures, common cases of local data must be stored in memory are:
- Not enough registers to hold all the local data (子函数参数大于6个);
- The address operator '&' is applied to a local variable, and hence must generate an address;
- Some of the local variables are arrays or structures and hence must be accessed by array or structure references.