# Decision-Tree
C++ implementation of decision tree algorithm. 

# How to run 
**0.** Put all project files in same folder.
**1.** Use ```make``` command to compile.  
**2.** Use ```./decTree``` command to run. 

# Important Notes
If you change the train or test data, you also need to change the number of data and features in main.cpp.
Change the lines:
```
decTree->train("train_data.txt", 498, 21 );
cout << "Proportion =  " << decTree->test("test_data.txt", 473) << endl;
```

 # License
 ```
     Copyright (C) 2020  Ufuk Palpas

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 
 ```
