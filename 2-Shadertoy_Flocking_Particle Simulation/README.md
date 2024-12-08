# Boids Simulation on Shadertoy

This project implements the Boids algorithm using Shadertoy. The simulation creates a flock of boids (particles) that interact with each other based on the principles of separation, cohesion, alignment, and boundary avoidance.

## Project Overview

The Boids algorithm simulates the flocking behavior of birds. In this implementation, we use two fragment shaders on Shadertoy:

1. **First Fragment Shader**: This shader takes a 4-channel texture (containing 2D position and velocity information of each boid) and updates their positions and velocities based on the update scheme (Semi-implicit Euler method).
2. **Second Fragment Shader**: This shader takes the updated position and velocity texture from the first shader and draws the boids as circles on the screen.

The project includes multiple features as per the assignment and additional bonus features:

### Core Principles:
1. **Separation**: Boids steer away from nearby boids to avoid crowding.
2. **Cohesion**: Boids steer toward the center of nearby boids, helping to form a flock.
3. **Alignment**: Boids match the velocity of nearby boids to maintain group cohesion.
4. **Boundary**: Boids steer away from the domain boundary to stay within the simulation area.

### Bonus Features:
- **3D Boids**: The algorithm is extended to 3D, simulating boids in a 3-dimensional space.
- **User Interaction**: Users can interact with the simulation by clicking on the screen to influence the boids' behavior (e.g., by guiding them toward the clicked position).
- **Predators**: A predator is introduced into the simulation, and the boids flee from it in real-time.

---
## Project Links

Here are the links to the final submission of my Shadertoy implementation, including both the main animation and the bonus features.

### 1. **Main Animation: Boids**
[Boids Simulation on Shadertoy](https://www.shadertoy.com/view/mtVBWz)

This is the core animation where the boids interact based on the four principles mentioned above.

### 2. **Bonus: User Interaction**
- **Boid Size Control**: Users can control the size of the boids by clicking on different screen positions. The boids' size gradually increases as you click from left to right.
  [User Interaction - Boid Size](https://www.shadertoy.com/view/clyfD1)

- **Boids Follow Mouse Clicks**: The boids will move toward the position where the user clicks on the screen.
  [User Interaction - Follow Mouse Click](https://www.shadertoy.com/view/dtGBDh)

### 3. **Bonus: Predators**
In this version, a predator randomly moves within the domain, and the boids flee from it. This adds an extra layer of complexity to the simulation.
[Predators - Boids Flee](https://www.shadertoy.com/view/DtyfRK)

### 4. **Bonus: 3D Boids**
This extension simulates boids in 3D space, with updated position and velocity calculations for each boid.
[3D Boids Simulation](https://www.shadertoy.com/view/dtKBz3)


---

## How to Run
1. Click the "restart" button on Shadertoy to make the simulation start from the beginning.
2. Explore the simulation and interact with the boids as described in the bonus features section.

---

### Final Notes
This project demonstrates my understanding of the Boids algorithm and how to implement it using shaders on Shadertoy. The additional bonus features showcase my ability to extend the core algorithm with user interactions and more advanced behaviors like 3D simulations and predator-prey dynamics.

