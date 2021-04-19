# Vehicle factory
### Intro
The program is used to manage vehicles: cars, motorcycles and bicycles. Each vehicle must first be manufactured by a given factory. Then it can be sold to a private owner. Private vehicles can be repainted by a painter, used to drive (only if they have the right amount of fuel or do not need it) or sold to a commission shop, from where they can be re-purchased.

### main
After starting the program, the user enters the name of the commission shop and the margin it imposes (it will later be used to calculate the prices of vehicles sold at the commission shop). The user is then given the option to select an action from the menu. He can create a factory, produce a vehicle in any of the existing factories, etc.

### Vehicles
The program allows you to create three types of vehicles: cars, motorcycles and bicycles. Vehicles have many recurring features, so inheritance has been applied. Motorcycles and cars are derivatives of the "Motor vehicle" class, because both types of vehicles need, among others, fuel tank capacity, fuel consumption and mileage. The "Bicycle" and "Motor Vehicle" classes are derived from the "Vehicle" class (attributes needed for all classes are, for example, color, load capacity, brand, owner).

### Running
The program can be run without arguments and operated directly by the user or with the use of a file containing values loaded by the program (example file: stdinMS.txt).
