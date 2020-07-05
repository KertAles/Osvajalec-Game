# Osvajalec-Game
This is a project that I created for my matura. It's a very simple turn-based game in which you exploit the resources on the randomly-generated map to defeat your AI opponents by capturing their base. This project was made in QT Creator.


## A crash course
When I was making this, I didn't have enough time to add a more descriptive UI, so a lot of information about the game is implicit, but here's a crash course:


### UI
On the top bar is displayed your current stockpile of resources and your current income of each resource. You need these to build units and buildings. On the bottom bar are actions that the currently selected unit or building can perform - build, move, attack, etc. along with the health bar, movement points left and the current action of the unit. You select a unit by clicking on it, and that is represented on the board by changing the background of the unit to green. In the far right is a crudely drawn sand hour, with which you end your turn. 


### Tiles

#### Buildings

On each tile you can have at most 1 unit at a time and at most 1 building. Resources are marked with coloured circles in the top right and it goes like this: gold - yellow, iron - grey, brown - wood and green - food. The amount of the resource is represented by the number in the circle. To exploit a resource that is within your area-of-influence(the tiles that are highlighted by your colour) you have to build an economic building on that tile - farm, mine or woodcamp and each building costs 1 wood resource, while the woodcamp is free. To increase your area-of-influence(AOI) you have to build forts which cost 3 iron, 6 wood and 2 gold to build and cost 1 gold to maintain.

To build buildings you need workers. Every player start with 1 worker, represented by a hammer icon. To build buildings, move the worker a controlled tile and select an available building. Workers can only be recruited at the main base and cost 1 food to maintain.

#### Units
Soldier units can be built at either the base or one of the forts and they are represented by: archer - bow, spearman - spear, knight - sword. The archer costs 1 wood and 1 food, the spearman 2 food, the knight 1 iron and 1 food. All cost 1 food to maintain. Each unit type has a bonus against another type, like rock, paper, scissors. Archers are good against spearmen, spearmen are good against knights and knights are good against archers.

You can either move a unit around, or you can attack with it. You switch between different modes by either clicking the blue arrow or the red sword. When attacking, the unit has to have sufficient movement points to attack. The reach of the attack is represented by a red outline of tiles. Different terrain types also drain movement points at different rates, going from least to most are: plains, woods, hills and mountains.

When attacking, the unit can also attack back, if close enough. Beware of bases, they bite back!

### Conclusion
The goal of the game is to destroy the bases of all other players.

## How to run
To run this project, go into release/release/ and run SuperProjekt.exe
