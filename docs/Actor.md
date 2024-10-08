# Actor

**Inherits**: CharacterBody2D

A 2D actor is specialized for movement and level work.

### Description

**Actor** is a class that gives us the basic movement of the character thanks to the parameters of speed and acceleration.

### Properties

| type     | name                                 | default value |
|----------|--------------------------------------|---------------|
| int      | [index](#index)                      | 0             |
| double   | [speed](#speed)                      | 200           |
| double   | [acceleration](#acceleration)        | 200           |

### Methods

| return type | function                                                |
|-------------|---------------------------------------------------------|
| void        | [move](#move)(Vector2 direction, double delta)          |

<hr style="height: 5px; border: none;" />

### Property Descriptions

##### int index = <span style="color: green;">0</span>  {#index}

 - void **set_index** ( const int p_index )
 - int **get_index** ( ) const

Stores the actor index in the layer's actors array so that the layer knows exactly which actor it is interacting with.

<hr style="height: 3px; border: none; opacity: 0.5;" />

##### double speed = <span style="color: green;">200.0</span> {#speed}

 - void **set_speed** ( const double p_speed )
 - double **get_speed** ( ) const

Sets the maximum allowable speed in pixels per second at which the actor can move.

<hr style="height: 3px; border: none; opacity: 0.5;" />

##### double acceleration = <span style="color: green;">200.0</span> {#acceleration}

 - void **set_acceleration** ( const double p_acceleration )
 - double **get_acceleration** ( ) const

Determines the acceleration of the actor. By default, it will gain maximum speed in one second.

<hr style="height: 5px; border: none;" />

### Method Descriptions

##### void move ( Vector2 direction, double delta ) {#move}

Makes the actor move in _direction_. Thanks to the use of variable _acceleration_, the actor will not gain _speed_ instantly, and therefore such a movement is more correct.
