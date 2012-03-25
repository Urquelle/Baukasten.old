BAUKASTEN ENGINE	{#mainpage}
================

DESCRIPTION			{#description}
===========
%Baukasten represents a possible implementation of the object model as described by Britt L. Hannah.

The object model consists of five major classes:

	* [ActionClass]
	* entity
	* form
	* state
	* space

this implementation, however, differs a little from what's described in that it introduces another
major class; entitytype. which basically serves the purpose of being a template for the entities. the
entitytype consists of states with const values. one instance of this class can be assigned to more
than one entity, saving memory.

should, however, the value of this state be changed, a mechanism is triggered and a new state object
is instantiated and filled with the new value, hence preserving the original value of the entitytype.

chains of types can be built, through assigning a parent entitytype to another:

	entitytypes: basic_unit, knight
	entity: unit

	in this example a unit can be built with basic_unit as its initial type. further down
	in the game -- with enough experience points -- unit becomes a knight, hence the type
	has to be changed. before just setting the type of the unit, one can -- there's no obligation
	-- take the old type getType() and assign this as the parent type to the new type. now
	the unit has the states of basic_unit *and* those of the knight.

where entity class is the one to be the main hub in this model. an entity represents the object in a game,
be it a unit, a tree, a car, what have you. however, it has to be modelled to represent all of this objects.
this is done through assignment of states as its properties, other entities, and actions as its behaviour.

states can be set through the addState() methods, actions can be assigned with the addAction() method.

INSTALLATION		{#installation}
============

grab the sources from [bitbucket], [github] or [gitorious].

to build the sources create a build directory in the root directory of Baukasten and start cmake, followed
by make && make install, to install the libs, and include files:

	cd Baukasten
	mkdir build && cd build
	cmake ..
	make && make install

in order for the documentation being built and installed the following sequence of commands is needed

	cd Baukasten
	mkdir build && cd build
	cmake .. -DWITH_DOC=1

Baukasten supports Lua as its scripting language. action classes can be instantiated with a path to the
lua script. whenever the action is executed the given script is executed.

[bitbucket]: https://bitbucket.org/noobsaibot/baukasten "Bitbucket Repository"
[github]: https://github.com/NoobSaibot/Baukasten "Github Repository"
[gitorious]: https://gitorious.org/codingninja/baukasten "Gitorious Repository"
[ActionClass]: @ref Baukasten::Action "Action class"
