# Game-in-OpenGL

This is a simple game that uses OpenGL.
By controlling the tank, you cannot let other tanks enter the city. You have 5 chances.
In order to win you have to survive till 12pm. Clock in left corner shows time, real game time is about 5 minutes.

Terrain is loaded from heightmap, calculates vertex products and vertex normals, and linear interpolation of current position.

ParticleSystem creates particles in order to simulate fire or smoke. Particles gets smaller 
with the passage of time, after few seconds disappear and are removed from memory.
