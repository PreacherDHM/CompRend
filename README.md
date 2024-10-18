# CompRend

CompRend is a comand line game engine that works on linux and window.
This game engine alows for the use of charictor sprites or csprites, and entities.
to fill out your world.

## How to Build
---

This project uses cmake, *link to install cmake*. This alows us to build on multiple
platforms easly.

1. Create a directory called ```build``` then navigate inside.
2. type the command ```cmake ../```, this will configure the project.
3. last but not least use the command ```cmake --build .```, this command will 
the project in the build directory.

## Lua Integration

This project uses lua as the scripting language for all of the entities and scenes.

### Scenes
---

A Scene is a colection of entities and scripts and where the prosses begins.
When an entity is created it is placed in a scene using ```add_to_scene(entity)```. 
when adding an entity to a scene and it has a csprite bound, then it will be 
placed in the render buffer. *Any object that needs to be rendered will be placed 
in the render buffer.* CompRend will handle the rest for you. The main thing to 
remember is just add the entity to the scene

#### Scene Functions
| Function | description |
|:--------:|:-----------:|
| add_to_scene(entity) | This will add a entity to the desired scene. |
| Update() | This will run on every frame. |
| Init() | This will only run once on init. |

### Entities
---
Entities are a crushial part of the CompRend ecosystem. These entities alow the 
user to run code for each entity. Every entity has a **Init** and a **Update** 
function. This alows the entities to have some level of abstraction, so that 
the [[#Scenes]] dosent get ugly. An entity is a complex data type that consists 
of a **position**, an **id** and a **csprite**.

- **position**: The position consists of a X Axis and a Y Axis whitch make up the cordenates to be placed in the world
- **Id**: is a identifier that can help find and return a entity if a entity needs to be referanced
- **csprite**: The [[#csprites]] holds all of the visual data of the entity.

### csprites
---
A csprite holds all the visual data of a entity. This visual data consists of 
charictors that can be displayed in the terminal buffer. alows for charictor data 
as well as **shader** data. The shader data alows the csprite to have color or an effect 
that would be hard to achive with normal charictors. This is done with the usage
of ANSI Escape codes. *link to ANSI Escape codes*. This can give a visual pop 
to your csprites. The csprite is another complex data type that consists of a 
**position**, **char data**, **boundery** also known as **bounds**, and a 
**shader**.
